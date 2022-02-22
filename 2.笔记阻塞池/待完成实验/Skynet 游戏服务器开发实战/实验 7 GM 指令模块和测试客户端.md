# 实验介绍

本节实验介绍了 GM 指令模块的作用和如何设计一个方便扩展的指令模块，然后实现了指令模块。再介绍了测试客户端的作用和实现了测试客户端的架构，最后采用测试客户端演示了运行效果。

#### 知识点

- GM 指令模块设计和实现
- 测试客户端设计和实现

本节实验的代码可以从这里下载：

```txt
https://labfile.oss.aliyuncs.com/courses/2770/code7.zip
```

# GM 指令模块设计和实现

#### GM 指令模块设计

GM(Game Manager) 指令在维基百科上是这样解释的：

> 在游戏正式发布之前，游戏公司通常会组织专人对游戏内容进行全面测试，而为了方便测试，游戏程序员在开发时就将大量专供测试和操作游戏内容用的专用命令写入。这些开放给 GM 使用的命令就是 GM 指令。
>
> 指令一般会涵盖游戏的全部功能，这些指令包括对服务器操作类（服务器重启，刷新，关闭等）、操作角色类（修改角色属性，角色位置，角色状态等）、广播类（发送全服消息，发布游戏活动消息），亦有方便 GM 活动的 GM 隐身，无敌等指令。例如：魔兽世界新的资料片巫妖王之怒开放的 GM 指令就包括直接到达 80 级等
>
> 由于 GM 指令功能多样，一些私服为了吸引玩家，也有将 GM 指令开放给普通玩家的。

用途跟上面解释的差不多，在我们游戏开发中有两个用途：

- 游戏开发期间用指令制造测试环境
- 游戏上线期间用指令修复玩家数据

测试游戏功能的时候，不可能每次都从头开始创建一个号。比如新做了一个玩法，需要 20 级后才能开放，这时候就需要有个指令设置玩家的等级。

指令模块又分为服务器指令和客户端指令，因此我们设计指令输入框时需要区分客户端指令和服务器指令。

可以这样设定，输入框输入的指令格式为： **指令名称 指令参数 1 指令参数 2** 。

这里区分客户端指令的方法就是服务器指令前面加个美元符号 `$` ，客户端识别指令的时候，发现没有 `$` 就客户端自己的指令，如果有 `$` 前缀，就删掉前缀，然后把指令发给服务器。

这样客户端指令就是这样的： **客户端指令名 指令参数 1 指令参数 2** ，服务器指令就是这样的： **$服务器指令名 指令参数 1 指令参数 2** 。

先定义一个协议用来接收客户端传输的指令，如下：

```json
{
    "pid": "c2s_gm_run_cmd",
    "cmd": "cmd line"
}
{
    "pid": "s2c_gm_run_cmd",
    "ok": true,
    "msg": "result msg"
}
```

假设有个修改玩具名字的的指令 `user setname` ，前端输入指令的时候，输入 `$user setname hello` 表示设置玩家名字为 `hello` 。传输给服务器的协议内容为：

```json
{
  "pid": "c2s_gm_run_cmd",
  "cmd": "user setname hello"
}
```

#### GM 指令模块设计实现

实现 GM 指令模块需要做到指令添加方便，可扩展。指令模块的目录结果如下：

```txt
module/ws_agent/gm/
├── main.lua
└── user.lua
```

`main.lua` 是指令模块的入口，也是指令模块框架的实现。 `user.lua` 是子指令 `user` 的实现，新增子指令则新增一个文件来实现逻辑。

先来看 `main.lua` 初始化相关的代码：

```lua
local M = {}
local RPC = {}
local gm_cmds = {} -- 指令名: 指令实现模块

function M.init()
    -- 引入 user 指令模块
    gm_cmds.user = require "ws_agent.gm.user"
end

M.RPC = RPC

return M
```

`gm_cmds` 用来存放指令对应的模块实现， `RPC` 用来实现客户端发起的请求的逻辑。再来看 `c2s_gm_run_cmd` 函数的实现：

```lua
-- 删除首尾空格
local function trim(str)
    return str:match("^%s*(.-)%s*$")
end

-- 处理 GM 指令
function RPC.c2s_gm_run_cmd(req, fd, uid)
    -- 对命令内容做切割处理
    local iter = string.gmatch(trim(req.cmd), "[^ ,]+")
    -- 切割出来的第一个值为指令名
    local cmd = iter()
    local args = {}
    for v in iter do
        table.insert(args, v)
    end

    local ok
    local msg
    -- 根据命令名找到对应的模块
    local m = gm_cmds[cmd]
    if m then
        ok, msg = M.do_cmd(m.CMD, uid, table.unpack(args))
    else
        msg = "invalid cmd!"
    end
    local res = {
        pid = "s2c_gm_run_cmd",
        ok = ok,
        msg = msg,
    }
    return res
end
```

`RPC.c2s_gm_run_cmd()` 函数首先对 `req.cmd` 内容用空格和逗号进行切割，取第一个字符串作为 `cmd` ，然后根据 `cmd` 去找到对应的模块执行 `M.do_cmd()` ，最后返回 `s2c_gm_run_cmd` 协议给客户端。现在继续看 `M.do_cmd()` 的实现：

```lua
-- 执行命令
function M.do_cmd(CMD, uid, cmd, ...)
    if not cmd then return false, "empty sub cmd." end
    local cb = CMD[cmd]
    if not cb then return false, "unkonw sub cmd:" .. cmd end

    local fun = cb.fun
    local args_format = cb.args

    -- 解析参数
    local ok,n,args = parse_cmd_args(uid, args_format, ...)
    if not ok then
        return ok, "invalid sub args."
    end

    -- 执行指令逻辑
    return fun(table.unpack(args, 1, n))
end
```

`do_cmd()` 函数主要是从 `CMD` 中取出 `cmd` 对应的 `fun` 和 `args` ，并调用 `parse_cmd_args()` 函数对 `...` 参数进行解析，最后把解析出来的参数丢给 `fun` 函数执行。我们先来看看 `CMD[cmd]` 的构成，这样就比较好理解 `parse_cmd_args` 的实现了。代码路径 `module/ws_agent/gm/user.lua` ：

```lua
-- 修改玩家名字的指令实现
local function set_name(uid, name)
    local ret = db_cache.call_cached("set_username", "user", "user", uid, name)
    if ret then
        return true, "set name succ"
    end
    return false, "set name failed"
end

-- 指令参数配置
M.CMD = {
    setname = { -- 指令名
        fun = set_name, -- 指令实现逻辑
        args = { "uid", "string" }, -- 指令参数格式
    },
}
```

上面定义了指令 `setname` ，有两个参数，其中 `uid` 是特殊参数，不用在指令中输入。指令示例就是这样的 `user setname shiyanlou` 。

再来看看 `parse_cmd_args` 的实现，根据配置的 `args` 对 `...` 进行格式转换。

```lua
-- 根据配置的参数类型来解析参数值
local function parse_cmd_args(uid, args_format, ...)
    local args = table.pack(...)
    local real_args = {}
    local n = 0

    local parse_cnt = 0
    for i = 1,#args_format do
        local arg_type = args_format[i]
        if arg_type == "uid" then
            n = n + 1
            real_args[n] = uid
            goto continue
        elseif arg_type == "string" then
            n = n + 1
            parse_cnt = parse_cnt + 1
            local arg = args[parse_cnt]
            if not arg then arg = "nil" end
            if arg == "nil" then
                real_args[n] = nil
            else
                real_args[n] = arg
            end
            goto continue
        elseif arg_type == "number" then
            n = n + 1
            parse_cnt = parse_cnt + 1
            local arg = args[parse_cnt]
            if not arg then arg = "nil" end
            if arg == "nil" then
                real_args[n] = nil
            else
                real_args[n] = tonumber(arg)
            end
            goto continue
        elseif arg_type == "boolean" then
            n = n + 1
            parse_cnt = parse_cnt + 1
            local arg = args[parse_cnt]
            if arg and arg == "true" then
                real_args[n] = true
            else
                real_args[n] = false
            end
            goto continue
        end
        ::continue::
    end
    return true, n, real_args
end
```

最后就是把 GM 模块加入到 `ws_agent/mng.lua` 的代码中，代码 diff 如下：

```diff
diff --git a/server/module/ws_agent/mng.lua b/server/module/ws_agent/mng.lua
index 32f4a40..b807805 100644
--- a/server/module/ws_agent/mng.lua
+++ b/server/module/ws_agent/mng.lua
@@ -3,6 +3,7 @@ local log = require "log"
 local json = require "json"
 local db_op = require "ws_agent.db_op"
 local db_cache = require "db_cache"
+local gm = require "ws_agent.gm.main"

 local M = {} -- 模块接口
 local RPC = {} -- 协议绑定处理函数
@@ -16,6 +17,12 @@ function M.init(gate, watchdog)
     GATE = gate
     WATCHDOG = watchdog
     db_op.init_db()
+
+    -- 初始化 gm 模块
+    gm.init()
+
+    -- 注册 gm 的协议
+    M.regist_rpc(gm.RPC)
 end

 -- 返回协议给客户端
@@ -95,6 +102,13 @@ function RPC.c2s_set_username(req, fd, uid)
     }
 end

+-- 注册 RPC 处理函数
+function M.regist_rpc(rpc)
+    for k,v in pairs(rpc) do
+        RPC[k] = v
+    end
+end
+
 -- 协议处理逻辑
 function M.handle_proto(req, fd, uid)
     -- 根据协议 ID 找到对应的处理函数
```

总结下 GM 模块的实现就是用一条特殊协议来接收客户端输入的指令，根据指令内容执行相应的 GM 代码。

可以改进的地方有：

- 权限管理
- 开关控制
- 支持 web 接口

权限管理是指控制某些账号允许执行 GM 指令。开关控制是允许设定开发服开启指令功能，正式服关闭指令功能。支持 web 接口是方便从管理后台输入 GM 指令。

# 测试客户端设计和实现

#### 测试客户端设计

测试客户端是一个命令行交互式的客户端，操作方式类似于 `telnet` 命令。工具的作用类似于 [Postman](https://www.postman.com/) 。测试客户端的架构如下：

![测试客户端架构](https://doc.shiyanlou.com/courses/2770/1456966/fb5f92d4cd55e9c3d45b7e8f1d0167a5-0)

其中 `console loop` 和 `websocket loop` 分别为终端线程和网络线程。终端线程负责处理交互式的命令行输入和输出，然后根据输入的指令执行相应的指令逻辑。网络线程则是负责接收网络协议。

#### 测试客户端实现

实现这个测试客户端依然采用 skynet 框架来实现，因为已经官方已经支持了 websocket 客户端和 `socket.readline()` 接口来接收命令行输入。

先从配置文件开始，配置文件为 `etc/config.client` ：

```lua
include "config.cfg"

-- 线程个数
thread = 2

-- 服务器IP
server_host = "127.0.0.1"

-- 启动配置
bootstrap = "snlua bootstrap"   -- The service for bootstrap
start = "test/client"  -- main script
daemon = nil
```

直接引入了服务器的配置文件 `config.cfg` ，方便直接读取服务器的端口。从配置中可以看出入口文件为 `test/client.lua` 。先来看启动入口的实现：

```lua
local ws_id -- websocket 连接 ID
local cmds = {} -- 命令模块集合, 命令名: 模块

-- 搜索并加载已实现的命令
local function fetch_cmds()
    local t = util_file.scandir("test/cmds")
    for _,v in pairs(t) do
        local cmd = util_string.split(v, ".")[1]
        local cmd_mod = "test.cmds."..cmd
        cmds[cmd] = require(cmd_mod)
    end
end

skynet.start(function()
    dns.server() -- 初始化 dns
    fetch_cmds() -- 搜索并加载已实现的命令
    skynet.fork(websocket_main_loop)
    skynet.fork(console_main_loop)
end)
```

`fetch_cmds()` 函数是去 `test/cmds/` 目录下找所有命令的实现，文件名对应命令名。然后启动 `websocket_main_loop` 和 `console_main_loop` 两个循环逻辑。先看 `websocket_main_loop()` 的实现：

```lua
-- 处理网络返回
local function handle_resp(ws_id, res)
    for _, cmd_mod in pairs(cmds) do
        if cmd_mod.handle_res then
            cmd_mod.handle_res(ws_id, res)
        end
    end
end

-- 网络循环
local function websocket_main_loop()
    -- 初始化网络并连接服务器
    local ws_protocol = config.get("ws_protocol")
    local ws_port = config.get("ws_port")
    local server_host = config.get("server_host")
    local url = string.format("%s://%s:%s/client", ws_protocol, server_host, ws_port)
    ws_id = websocket.connect(url)

    print("websocket connected. ws_id:", ws_id)
    -- 网络收包循环
    while true do
        local res, close_reason = websocket.read(ws_id)
        if not res then
            print("disconnect.")
            break
        end
        print("res:", ws_id, res)
        local ok, err = xpcall(handle_resp, debug.traceback, ws_id, json.decode(res))
        if not ok then
            print(err)
        end
        websocket.ping(ws_id)
    end
end
```

先读取服务器的 IP 和端口，然后连接服务器，再用死循环去读取网络数据。读取到网络数据后，把数据交给 `handle_resp()` 函数处理，目的是执行所有模块的 `handle_res()` 函数。

再看看 `console_main_loop()` 的实现：

```lua
-- 执行注册的命令
local function run_command(cmd, ...)
    print("run_command:", cmd, ...)
    print("ws_id:", ws_id)
    local cmd_mod = cmds[cmd]
    if cmd_mod then
        cmd_mod.run_command(ws_id, ...)
    end
end

-- 切割命令
local function split_cmdline(cmdline)
    local split = {}
    for i in string.gmatch(cmdline, "%S+") do
        table.insert(split,i)
    end
    return split
end

-- 交互式命令主循环
local function console_main_loop()
    local stdin = socket.stdin()
    while true do
        local cmdline = socket.readline(stdin, "\n")
        if cmdline ~= "" then
            local split = split_cmdline(cmdline)
            local cmd = split[1]
            local ok, err = xpcall(run_command, debug.traceback, cmd, select(2, table.unpack(split)))
            if not ok then
                print(err)
            end
        end
    end
end
```

采用 `socket.readline` 函数读取一行输入的字符串，然后用 `split_cmdline` 切割字符串，切割出来的第一个作为 `cmd` ，然后执行 `run_command()` 函数。

目前已经有了两个测试指令的实现：

```txt
test/cmds/
├── gm.lua
└── ws.lua
```

`ws.lua` 里实现了登录的测试指令，实现如下：

```lua
local websocket = require "http.websocket"
local json = require "json"
local mng = require "test.mng" -- 用于绑定 ws_id 和 uid
local md5 = require "md5"

local M = {} -- 模块接口
local CMD = {} -- 命令接口实现
local RPC = {} -- RPC 消息处理实现

-- 处理网络消息
function M.handle_res(ws_id, res)
    local f = RPC[res.pid]
    if f then
        f(ws_id, res)
    else
        print("recv:", json.encode(res))
    end
end

-- 执行指令
function M.run_command(ws_id, cmd, ...)
    local f = CMD[cmd]
    if not f then
        print("not exist cmd")
        return
    end
    f(ws_id, ...)
end
```

这里实现了 `handle_res` 和 `run_command` 函数，就是 `test/client.lua` 里调用的两个接口。再来看看登录指令的实现：

```lua
-- 实现登录指令
function CMD.login(ws_id, acc)
    local token = "token"
    local checkstr = token .. acc
    local sign = md5.sumhexa(checkstr)
    local req = {
        pid = "c2s_login",
        acc = acc,
        token = token,
        sign = sign,
    }
    -- 把消息发给服务器
    websocket.write(ws_id, json.encode(req))
end

-- 处理登录成功的协议
function RPC.s2c_login(ws_id, res)
    mng.set_uid(res.uid)
end
```

`CMD.login()` 函数接收的第一个参数是 `ws_id` ，是网络连接 ID ，第二个参数开始就是从命令行输入的参数了， `acc` 就是要输入的登录账号。最后调用 `websocket.write` 把协议发送给服务器。接收到服务的协议 `s2c_login` 后会进入到 `RPC.s2c_login()` 函数。

`ws.lua` 中还实现了 `echo` ， `getname` ， `setname` 三个指令，代码如下：

```lua
function CMD.echo(ws_id, msg)
    local req = {
        pid = "c2s_echo",
        msg = msg,
    }
    websocket.write(ws_id, json.encode(req))
end

function CMD.getname(ws_id)
    local req = {
        pid = "c2s_get_username",
    }
    websocket.write(ws_id, json.encode(req))
end

function CMD.setname(ws_id, name)
    local req = {
        pid = "c2s_set_username",
        username = name,
    }
    websocket.write(ws_id, json.encode(req))
end
```

最后来看看 `gm.lua` 的实现：

```lua
local websocket = require "http.websocket"
local json = require "json"

local M = {}

function M.run_command(ws_id, ...)
    local cmd = table.concat({...}, " ")
    local req = {
        pid = "c2s_gm_run_cmd",
        cmd = cmd,
    }
    websocket.write(ws_id, json.encode(req))
end

return M
```

`gm` 指令的实现就是把参数打包为 `cmd` ，然后用协议 `c2s_gm_run_cmd` 发送给服务器。

#### 测试客户端和 GM 指令的演示

执行 `sudo mongod -f /etc/mongod.conf --smallfiles` 指令启动数据库进程，然后执行 `make start` 启动服务器，最后执行 `make client` 启动测试客户端。在测试客户端的终端里输入指令 `ws login shiyanlou` 登录服务器：

![启动服务器和测试客户端](https://doc.shiyanlou.com/courses/2770/1456966/1acce2492979d081cc6c0bc056e828e9-0)

`ws login shiyanlou` 表示执行 `test/ws.lua` 里的 `CMD.login` 函数， `acc` 参数为 `shiyanlou` 。

再输入 `gm user setname shiyanlou` 指令，表示给服务器发送指令 `user setname shiyanlou` 。运行效果如下：

![测试 GM 指令](https://doc.shiyanlou.com/courses/2770/1456966/59df938e4de7fa72842edff932e3a836-0)

可以从截图中看到，运行了 `ws getname` 指令查看 GM 修改玩家名字是否成功。

# 实验总结

在本节实验中，学到了 GM 指令模块的设计和实现，也熟悉了测试客户端的设计架构和实现，这两个工具可以加快游戏开发的效率和测试效率。可以更加熟练的为后续实验中实现玩法逻辑时提供测试指令。