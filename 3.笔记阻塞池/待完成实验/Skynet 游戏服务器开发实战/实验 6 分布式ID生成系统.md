# 实验介绍

本节实验先介绍了分布式 ID 生成系统的几种常见方案，然后再根据已有的方案设计出适合游戏开发使用的一套方案，最终目的是使用 `skynet` 实现一套分布式 ID 生成系统，这套系统依赖于 `skynet` 和 `MongoDB` 数据库。最后也采用了测试用例来演示效果。

#### 知识点

- 分布式 ID 生成系统的种类
- 设计分布式 ID 生成系统
- 分布式 ID 生成系统的实现
- 实例演练

本节实验的代码可以从这里下载：

```txt
https://labfile.oss.aliyuncs.com/courses/2770/code6.zip
```

# 分布式 ID 生成系统

分布式 ID 生成系统在游戏开发中用的比较多的地方有：

- 玩家 ID
- 队伍 ID
- 帮派或公会 ID

#### 分布式 ID 生成系统的种类

关于分布式 ID 生成系统，这篇文章讲的比较好，可以参考下： 《 [Leaf——美团点评分布式 ID 生成系统](https://tech.meituan.com/2017/04/21/mt-leaf.html) 》

市面上主流的 ID 生成系统应该就是下面几种方案了：

- [通用唯一识别码 UUID](https://baike.baidu.com/item/UUID)
- 数据库自增 ID
- 数据库集群模式
- 数据库号段模式
- [雪花算法 SnowFlake](https://github.com/cloudyan/snowflake)
- [滴滴的 TinyID](https://github.com/didi/tinyid/wiki)
- [百度的 Uidgenerator](https://github.com/baidu/uid-generator/blob/master/README.zh_cn.md)
- [美团的 Leaf](https://github.com/Meituan-Dianping/Leaf/blob/master/README_CN.md)

在游戏开发中，一般都会根据服务器架构自己实现一套 ID 生成系统。这里就只解释下上面列出的三种数据库方案了：

数据库自增 ID 的方案就是采用数据库自增字段来生成 ID，比如 MySQL 的 `auto_increment` 。每次插入一条记录都会生成自增的 ID 。这个方案在小服模式的游戏中常见，每个服都是独立的数据库，数据也不互通，只要保证 ID 在本服内不冲突即可。

比如这样创建数据库和表：

```sql
CREATE DATABASE `GUID`;
CREATE TABLE GUID.SEQUENCE_ID (
    id bigint(20) unsigned NOT NULL auto_increment,
    value char(10) NOT NULL default '',
    PRIMARY KEY (id),
) ENGINE=MyISAM;
```

然后插入一条数据：

```sql
insert into SEQUENCE_ID(value)  VALUES ('values');
```

使用返回的 id 就可以了。

数据库集群模式的方案是在数据库自增 ID 的方案的基础上，设置每个数据库的起始值和自增步长。比如 MySQL 的 `auto_increment_increment` 和 `auto_increment_offset` 。这种方案在游戏开发中也见过，比如分配玩家的 ID ，多个服务器之间不能冲突，在部署游戏数据库的时候，设定好每个数据库的 `auto_increment_increment` 和 `auto_increment_offset` 。优点就是不用修改已有的架构和代码，缺点就是部署前就要确定好未来最大开多少个服务器，每个服务器容纳的最大玩家数量。

假如计划开 100 个服务器，则步长设为 100 ，数据库 ID 从 1 开始分配，则 ID 分配规则如下：

![数据库集群模式生成 ID 结果](https://doc.shiyanlou.com/courses/2770/1456966/3f30108af745d47cf47b5e2b38abf936-0)

数据库号段模式应该是最适合游戏开发的，因为游戏服务器一般都是使用了数据库的，所以完全可以依赖数据库，其次游戏中需要的 ID 只要全局唯一即可，无需考虑是否趋势递增或者单调递增，又或者信息安全。参考 Leaf-segment 数据库方案，数据库表结构设计如下：

| biz_tag | max_id | step |
| ------- | ------ | ---- |
| uid     | 300    | 100  |
| roomid  | 100    | 10   |

`biz_tag` 是使用 ID 的 tag 名， `max_id` 是取走分段时最大的 ID， `step` 是步长。

用法一般就是游戏服务器用定时器检查待分配的 ID 池子是否足够，如果小于 20 % 就去数据库申请一段 ID 放进池子里。

#### 设计分布式 ID 生成系统

我们设计的分布式 ID 生成系统是采用的数据库号段模式 (segment) ，数据库是单节点的，游戏数据库一般会有个全局库用来存放账号的，所以用于生成 ID 的数据库也可以放到全局库里。数据库单节点可以采用 MongoDB 的分片集群来提升安全性，这个只要运维去配置数据库就行。

下图是设计好的分布式 ID 架构图：

![分布式 ID 架构](https://doc.shiyanlou.com/courses/2770/1456966/dc5f0840b90d02cebeeb0646d150e6bd-0)

上面一个方框代表一个 `skynet` 进程，一个 `skynet` 进程里开启一个 `guid` 服务，当前进程内的服务需要分配 ID 的时候就去 `guid` 服务里申请。每个 `guid` 服务都连接同一个数据库，`guid` 服务内部就是定时检查 ID 池子数量，即将不足的时，就去数据库申请一段 ID 来补充池子。

这一套方案实现下来，此系统就可以作为 `skynet` 的一个第三方库来使用，使用者无需关心内部实现，就像前面的实验中见到的分配玩家 ID 的逻辑里用到的一样。

# 分布式 ID 生成系统的实现

先设计数据库存储结构，如下：

| idtype | nextid |
| ------ | ------ |
| uid    | 1000   |
| teamid | 2000   |

给 `idtype` 设置唯一索引， `idtype` 用来区分业务的，比如这里的 `uid` 用来表示角色 ID 申请的号段， `teamid` 用来表示队伍 ID 申请的号段。 `nextid` 用来表示下一次申请的 ID 的最小值。这里跟上面提到的号段数据库结构有点不一样，没有 `step` 字段来记录步长，因为 `step` 配置到每个申请服务的配置里面更合适，按需配置 `step` ，按需申请多少个就行。

分布式 ID 生成系统命名为 `guidd` 服务，代码路径为 `service/guidd.lua` ，接口文件实现在 `lualib/guid.lua` ，先看接口文件，代码如下：

```lua
local skynet = require "skynet"

local M = {}
local guidd

-- cfg: {
--   host = "127.0.0.1", -- 数据库 IP
--   port = 27107,       -- 数据库端口
--   username = nil,     -- 数据库账号
--   password = nil,     -- 数据库密码
--   authdb = nil,       -- 认证数据库
--   dbname = "guid",    -- 存储数据的数据库名
--   tblname = "guid",   -- 存储数据的表名
--   idtypes = {"uid" = step, "teamid" = step}, -- 配置每个 ID 类型和对应的步长
-- }
-- 初始化配置
function M.init(cfg)
    skynet.call(guidd, "lua", "init", cfg)
end

-- 取一个 ID
function M.get_guid(idtype)
    return skynet.call(guidd, "lua", "get_guid", idtype)
end

-- 创建 guidd 服务
skynet.init(function()
    guidd = skynet.uniqueservice("guidd")
end)

return M
```

接口很简单，就两个接口，初始化 `M.init(cfg)` 和 获取唯一 ID `M.get_guid(idtype)` 。因为我们设计的 `guidd` 服务在进程内是唯一的，所以可以用 `skynet.uniqueservice` 函数创建服务。

继续去 `service/guidd.lua` 里看 `init` 函数的实现：

```lua
local skynet = require "skynet"
local mongo = require "skynet.db.mongo"

local CMD = {}

-- block_datas = {
--    [idtype] = {
--      blocks = {
--         [start_idx] = len,  -- 有效数据, 表示从某段开始, 长度为 len , 使用时段内自减
--      },
--      cur_idx = 0,  -- 记录当前在使用的段 ID , 当某段不足 step/10 时, 自动申请, 优先使用低段位
--      step = step,  -- 每次从 db 取的 id 数量
--      ids_cnt = 0,  -- 当前空闲 ID 总数
--    }
-- }
local block_datas     -- ID 池子
local creator         -- 生产协程
local is_busy = false -- 是否繁忙
local tbl_guid        -- 数据库操作对象

function CMD.init(cfg)
    local db = mongo.client(cfg)
    local db_guid = db[cfg.dbname]
    tbl_guid = db_guid[cfg.tblname]
    -- 创建索引
    tbl_guid:createIndex({{idtype = 1}, unique = true})

    -- 初始化 ID 池子
    block_datas = {}
    for idtype,step in pairs(cfg.idtypes) do
        block_datas[idtype] = {
            blocks = {},
            step = step,
        }
        -- 首次申请 ID
        try_init_generator(idtype)
        -- 更新生成器
        update_generator(idtype)
    end

    -- 生产协程
    creator = skynet.fork(create_new_ids)
end
```

初始化函数首先是创建数据库连接，然后拿到数据库的表操作对象，再创建索引。接着初始化 ID 池子，最后创建一个协程来创建新的空闲 ID 放到池子里。

`block_datas` 就是存放空闲 ID 的池子列表，每个 `idtype` 对应一个池子。`step` 是步长，`ids_cnt` 是空闲 ID 总数， `blocks` 就是记录已申请到的空闲 ID 段， 这里做多个分段管理是因为可能同时申请到多个分段，申请过来了就缓存在 `blocks` 里， `cur_idx` 用来标记当前使用的是哪一段。

先通过下面这个图来理解 ID 池子和变化情况：

![ID 池子](https://doc.shiyanlou.com/courses/2770/1456966/63df6fee2de5b70179de47efe0890302-0)

假设池子初始化时申请了三段 ID ，分别是 `11~20, 21~30, 31~40` ， ID 总数为 `30` 。 此时池子的数据结构如下：

```lua
{
    blocks = {
        [10] = 10,
        [20] = 10,
        [30] = 10,
    },
    cur_index = 10,
    step = 10,
    ids_cnt = 30,
}
```

`cur_index` 指向最小的 `block` ， 接下来申请一个 ID ，申请到的 ID 为 `20` ，计数公式为：

```lua
-- 10 + 10 = 20
local new_id = blocks[cur_idx] + cur_idx
```

然后池子的结构变成下面这样：

```lua
{
    blocks = {
        [10] = 9,
        [20] = 10,
        [30] = 10,
    },
    cur_index = 10,
    step = 10,
    ids_cnt = 29,
}
```

这里要注意 `blocks[cur_idx]` 最小取值为 1 ，当 `blocks[cur_idx]` 的值为 1 时说明是分配最后一个 ID 了，需要删除 block 和 cur_index 。

ID 池子的生成者消费者模型图示如下：

![生成者消费者模型](https://doc.shiyanlou.com/courses/2770/1456966/e7330e538a168f1c6c797644ab3ee1ec-0)

有了上面的示例介绍，现在来看从池子里取一个 ID 的逻辑应该就好理解了，代码如下：

```lua
-- 从池子里取一个 ID
local function get_new_id(idtype)
    local info = block_datas[idtype]

    if not info.cur_idx then
        -- 处理换 block 的情况
        if info.ids_cnt > 0 then
            -- 更新生成器
            update_generator(idtype)
            if not info.cur_idx then
                skynet.error("new guid too busy. idtype:", idtype)
                return
            end
        else
            skynet.error("id pool null. idtype:", idtype)
            return
        end
    end

    local cur_idx = info.cur_idx
    local diff = info.blocks[cur_idx]
    if diff <= 0 then
        --本段已经消耗完，正在切段
        skynet.error("id block all used. idtype:", idtype)
        return
    end

    -- 计算产出的 ID
    local new_id = diff + cur_idx
    if diff == 1 then
        skynet.error("id block used. cur:", cur_idx)
        info.blocks[cur_idx] = nil
        info.cur_idx = nil
    else
        info.blocks[cur_idx] = diff - 1
    end
    info.ids_cnt = info.ids_cnt - 1

    -- 当存量低于阀值
    if not is_busy and info.ids_cnt < info.step/10 then
        is_busy = true
        skynet.wakeup(creator)
    end

    skynet.error("consume ok. guid:", new_id)
    return new_id
end

-- 提供接口
function CMD.get_guid(idtype)
    assert(block_datas[idtype], "Unknow idtype. idtype:" .. idtype)
    return get_new_id(idtype)
end
```

首先是当 `ids_cnt > 0` 且 `cur_idx` 不存在的时候，调用 `update_generator(idtype)` 函数来更新 `cur_idx` 和 `ids_cnt` 。

然后再计算产出的 ID ，最后判断池子的存量是否低于阈值，低于阈值则唤醒生产者协程开始干活。接下来看看 `update_generator()` 函数的实现：

```lua
-- 更新生成器: 重新计算 cur_idx 和 ids_cnt
local function update_generator(idtype)
    local info = block_datas[idtype]
    local old_block = info.cur_idx or 0
    local cnt = 0
    -- 选最小的 cur_idx 和 计算 ids_cnt
    for idx, size in pairs(info.blocks) do
        if not info.cur_idx then
            info.cur_idx = idx
        elseif info.cur_idx > idx then
            info.cur_idx = idx
        end
        cnt = cnt + size
    end

    info.ids_cnt = cnt
    if old_block ~= info.cur_idx then
        skynet.error("switch id block. idtype:", idtype, ",cur:", info.cur_idx, ",old:", old_block, ",ids_cnt:", cnt)
    end
end
```

更新生成器的目的就是更新 `cur_idx` 和 `ids_cnt` 。

再来看看 ID 生产者协程的逻辑：

```lua
local function create_new_ids()
    while true do
        for idtype,info in pairs(block_datas) do
            skynet.error("creator going to check id space. idtype:", idtype)
            if info.ids_cnt < info.step/10 then
                skynet.error("creator start update id space. idtype:", idtype)
                -- 申请新的 ID 段
                try_init_generator(idtype)
                -- 更新生成器
                update_generator(idtype)
                skynet.error("creator update id space ok. idtype:", idtype)
            else
                skynet.error("not need create new ids. idtype:", idtype)
            end
        end
        is_busy = false
        skynet.wait()
    end
end
```

就是一个死循环在检测空闲 ID 是否足够，小于阈值的时候就去数据库申请新的 ID 段。

下面三个函数的主要目的就是从数据库里申请一个 ID 段：

```lua
-- 从数据库申请新的 ID 段
local function new_db_id(idtype, step)
    local ret = tbl_guid:findAndModify({query = {idtype = idtype}, update = {["$inc"] = {nextid = step}}, upsert = true})

    local result = math.floor(ret.ok)
    if result ~= 1 then
        skynet.error("new_db_id not ret. idtype:", idtype, ",step:", step, ",msg:", ret.errmsg)
        return
    end

    if not ret.value.nextid then
        skynet.error("new_db_id failed. ignore first step. idtype:", idtype, ",step:", step)
        return
    end

    return ret.value.nextid
end

-- 从数据库申请新的 ID 段
local function init_generator(idtype, step)
    local id = new_db_id(idtype, step)
    if not id then
        return
    end

    skynet.error("get new id block. start:", id, ", step:", step)
    block_datas[idtype].blocks[id] = step
end

-- 申请新的 ID 段
local function try_init_generator(idtype)
    local info = block_datas[idtype]
    local cnt = 0
    for idx, size in pairs(info.blocks) do
        cnt = cnt + size
    end

    -- 申请新的 ID 段
    local step = info.step
    if cnt < step/10 then
        if not init_generator(idtype, step) then
            skynet.error("cannot get new id. idtype:", idtype)
        end
    end
end
```

其中 `try_init_generator()` 先是统计出空闲的数量，如果空闲数量小于阈值才取数据库里申请。这里的申请 ID 段的函数是 `new_db_id()` ，使用了 MongDB 的 `findAndModify` 和 `$inc` 操作数据库。

#### 实例演练

先准备好测试环境，新建 `test/test.lua` ，代码内容如下：

```lua
require "test.guid"
local skynet = require "skynet"

skynet.start(function()
    skynet.error("start test service")
end)
```

`test/test.lua` 文件类似于 `service/main.lua` ，作为测试用例的启动入口。测试 `guid` 模块的代码放在 `test/guid.lua`，代码内容如下：

```lua
local skynet = require "skynet"
local guid = require "guid"
local timer = require "timer"

local cfg = {
  host = "127.0.0.1",
  port = 27017,
  username = nil,
  password = nil,
  authdb = nil,
  dbname = "guidtest",
  tblname = "guid",
  idtypes = {uid = 10},
}

-- 申请 ID
local function test_new_uid()
    local uid = guid.get_guid("uid")
    skynet.error("--------------------uid:", uid)
end

skynet.init(function()
    guid.init(cfg)

    -- 开个循环定时器取申请 ID
    local id = timer.timeout_repeat(2, test_new_uid)

    -- 超时后关闭定时器
    skynet.timeout(18000, function ()
        skynet.error("cancel", id)
        timer.show()
        timer.cancel(id)
        timer.show()
    end)
end)
```

测试用例就是用了个循环定时器去不停的申请新的 ID ，然后打印出来。

然后新建配置文件 `etc/config.test` ，代码如下：

```lua
include "config.path"

-- 线程个数
thread = 8

-- 启动配置
bootstrap = "snlua bootstrap"   -- The service for bootstrap
start = "test/test"  -- main script

harbor = 0
```

配置里没有过多其他配置，只是把启动入口改为了 `test/test.lua` 文件。

最后修改 `Makefile` 文件，加入 `make test` 指令， diff 内容如下：

```diff
diff --git a/server/Makefile b/server/Makefile
index ba896ca..111aceb 100644
--- a/server/Makefile
+++ b/server/Makefile
@@ -5,6 +5,7 @@ help:
        @echo "make build       # 编译 skynet"
        @echo "make start       # 开服"
        @echo "make client      # 测试客户端"
+       @echo "make test        # 启动测试用例"

 build:
        @cd skynet && make linux
@@ -18,3 +19,8 @@ client:
 console:
        @rlwrap telnet 127.0.0.1 8000

+t:
+       @./skynet/skynet etc/config.test
+
+test: t
+
```

然后我们在终端里运行 `make build` :

![make build](https://doc.shiyanlou.com/courses/2770/1456966/1ab0c4d753daec17d2bd1db65ccd6ad9-0)

再开启 MongoDB 服务器：

```bash
sudo mongod -f /etc/mongod.conf --smallfiles
```

接下来我们在新开一个终端运行 `make test` ，效果如下：

![测试效果](https://doc.shiyanlou.com/courses/2770/1456966/ec80b6d50cf1c23b75a717c3330b339b-0)

# 实验总结

在本节实验中，了解到了分布式 ID 生成的几种常见方案，还了解到了游戏开发中哪些地方经常需要使用 ID 生成系统。最后用 `skynet` 框架实现了一套分布式 ID 生成系统，并通过测试用例看到运行效果。