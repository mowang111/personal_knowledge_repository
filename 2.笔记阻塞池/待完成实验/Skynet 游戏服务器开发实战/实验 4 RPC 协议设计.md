# 实验介绍

本节实验先介绍了 RPC 协议是什么，有哪些分类。再分别介绍了 `Protobuf` 和 `JSON-RPC` 。通过测试例子熟悉了下 `Protobuf` 的使用，最后再设计了一种 RPC 协议。

#### 知识点

- RPC 是什么
- 序列化数据结构的协议 Protobuf
- 无状态且轻量级的 RPC 传送协议 JSON-RPC
- 自己设计一套 RPC 协议

本实验的代码可以从这里下载：[code4.zip](https://labfile.oss.aliyuncs.com/courses/2770/code4.zip)

# RPC 协议

RPC 在维基百科上是这样解释的：

> 在分布式计算，远程过程调用（英语：Remote Procedure Call，缩写为 RPC）是一个计算机通信协议。该协议允许运行于一台计算机的程序调用另一个地址空间（通常为一个开放网络的一台计算机）的子程序，而程序员就像调用本地程序一样，无需额外地为这个交互作用编程（无需关注细节）。RPC 是一种服务器-客户端（Client/Server）模式，经典实现是一个通过发送请求-接受回应进行信息交互的系统。

本节实验讲的 RPC 协议是用来客户端和服务器通讯的，RPC 协议按数据格式来区分有模式 (schema) 和无模式 (schema-less)。有模式的协议将介绍 Protobuf，无模式的协议将介绍 JSON-RPC。

有模式的特点：

- 通讯双方需要提前定义协议模板
- 数据传输过程中只传输值，无需传输数据结构，节省流量

无模式的特点：

- 无需协议模板
- 数据传输过程中需要带上数据结构

`Protobuf` 是数据序列化的协议，对应的序列化协议是 `JSON` 。跟 `JSON-RPC` 对应的 RPC 协议是 [gRPC](https://doc.oschina.net/grpc) ， `gRPC` 是使用的 `Protobuf` ， `JSON-RPC` 是使用的 `JSON` 。

游戏开发一般不会直接使用 `gRPC` 和 `JSON-RPC` ，而是在 `Protobuf` 或者 `JSON` 等数据序列化格式上自定义一套 RPC 协议。

#### Protobuf

`Protobuf` 包含序列化格式的定义和一个 `proto` 文件编译器，要先定义 `proto` 文件，然后使用编译器编译成 `pb` 文件。然后代码中使用 `pb` 文件来打包和解包数据。

我们采用 [cloudwu/pbc](https://github.com/cloudwu/pbc) 这个库来演示 `Protobuf` 的使用。

先来看看 `proto` 文件格式：

```c
package addressbook;

message Person {
  required string name = 1;
  required int32 id = 2;        // Unique ID number for this person.
  optional string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    required string number = 1;
    optional PhoneType type = 2;
  }

  repeated PhoneNumber phone = 4;
}
```

文件行首定义包名 `package` 关键字来定义包名，这里的包名是 `addressbook` 。 `message` 用来定义一个消息，消息使用大括号括起来， `enum` 是用来定义枚举类型的。

定义字段格式的有 3 个关键字：

- `required` 必选字段
- `optional` 可选字段
- `repeated` 重复字段（数组）

常用的字段数据类型有：

- string 字符串
- bool 布尔类型
- int32 32 位整数
- int64 64 位整数
- 其他自定义类型：枚举类型或者子消息

这个协议结构对应的 Lua 表结构大概是这样的：

```lua
addressbook = {
  name = "Alice",
  id = 12345,
  phone = {
    { number = "1301234567" },
    { number = "87654321", type = "WORK" },
  }
}
```

可以看出， `email` 可选字段可以为空， `phone` 是一个数组，数组的元素是 `PhoneNumber` 结构的，`PhoneNumber` 里的 `PhoneType` 也是可选的。

接下来我们实操下，先下载 `pbc` 库：

```bash
cd Code
mkdir code4
cd code4
git clone https://github.com/cloudwu/pbc.git
```

![下载 pbc](https://doc.shiyanlou.com/courses/2770/1456966/34a4f549630a8a9cfcf3094bb8bb7ee4-0)

然后执行下面的命令安装 `protoc` 命令，用于编译 `proto` 文件为 `pb` 文件：

```bash
sudo apt update
sudo apt install -y protobuf-compiler
```

然后编译 `pbc` 库：

```bash
cd pbc
make
```

![编译 pbc](https://doc.shiyanlou.com/courses/2770/1456966/47fbd4a7edfbae3a0be4eb650b62127b-0)

从输出的截图中可以看到把 `proto` 文件生成 `pb` 文件的命令就是 `protoc` ，比如我们把 `addressbook.proto` 编译成 `addressbook.pb` 就可以这样执行命令：

```bash
protoc -o addressbook.pb addressbook.proto
```

测试例子中的 `addressbook.proto` 里的包名是 `tutorial` 。实际开发过程中，建议协议包名和文件名一致，一个玩法模块对应一个包，一个包对应一个协议定义文件。

接下来我们写 Lua 代码测试下，进入到 `Code/code4/pbc/binding/lua53` 目录，修改下 `Makefile` 文件，需要修改 `LUADIR` 为 `/usr/include/lua5.3` ，然后执行 `make` ：

```bash
cd Code/code4/pbc/binding/lua53
vim Makefile
make
```

修改 diff 如下：

```diff
diff --git a/binding/lua53/Makefile b/binding/lua53/Makefile
index d7eb401..1104524 100644
--- a/binding/lua53/Makefile
+++ b/binding/lua53/Makefile
@@ -1,6 +1,6 @@
 CC = gcc
 CFLAGS = -O2 -fPIC -Wall
-LUADIR = /usr/local/include
+LUADIR = /usr/include/lua5.3
 TARGET = protobuf.so
 SHARED = -shared
```

执行 `make` 编译后会生成 `protobuf.so` 文件，接下来写段 Lua 代码来使用它，新建一个文件 `t.lua` ，内容如下：

```lua
-- require protobuf.so
local protobuf = require "protobuf"

addr = io.open("addressbook.pb","rb")
buffer = addr:read "*a"
addr:close()

protobuf.register(buffer)

person = {
  name = "Alice",
  id = 12345,
  phone = {
    { number = "1301234567" },
    { number = "87654321", type = "WORK" },
  }
}

code = protobuf.encode("addressbook.Person", person)

decode = protobuf.decode("addressbook.Person" , code)

print(decode.name)
print(decode.id)
for _,v in ipairs(decode.phone) do
  print("\t"..v.number, v.type)
end
```

`protobuf.register` 是加载协议模板， `protobuf.encode` 是打包协议，`protobuf.decode` 是解包协议。

接下来我们制作 `addressbook.pb` 文件，先新建 `addressbook.proto` 文件，内容如下：

```cpp
package addressbook;

message Person {
  required string name = 1;
  required int32 id = 2;        // Unique ID number for this person.
  optional string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    required string number = 1;
    optional PhoneType type = 2 [default = HOME];
  }

  repeated PhoneNumber phone = 4;
}
```

然后使用 `protoc` 命令编译成 `addressbook.pb` 文件：

```bash
protoc -o addressbook.pb addressbook.proto
```

接下来执行 `lua5.3 t.lua` 看到如下效果：

![运行测试结果](https://doc.shiyanlou.com/courses/2770/1456966/d56f60f104324099e1166b338c52c9e6-0)

#### JSON-RPC

`JSON-RPC` 在维基百科上是这样介绍的：

> JSON-RPC，是一个无状态且轻量级的远程过程调用（RPC）传送协议，其传递内容透过 JSON 为主。相较于一般的 REST 透过网址（如 GET /user）调用远程服务器，JSON-RPC 直接在内容中定义了欲调用的函数名称（如 {"method": "getUser"}），这也令开发者不会陷于该使用 PUT 或者 PATCH 的问题之中。 本规范主要定义了一些数据结构及其相关的处理规则。它允许运行在基于 Socket、HTTP 等诸多不同消息传输环境的同一进程中。其使用 JSON（RFC 4627）作为数据格式。

`JSON-RPC` 主要包含两个部分，请求对象和响应对象。发送一个请求对象至服务端代表一个 `RPC` 调用，一个请求对象包含下列成员：

- `jsonrpc` 指定 JSON-RPC 协议版本的字符串，必须准确写为 `"2.0"`
- `method` 所要调用方法名称的字符串
- `params` 所要调用方法的参数数组
- `id` 可以理解为 session id ，响应对象以相同的 id 返回

当发起一个 `RPC` 调用后，服务端需要回复响应。响应表示为一个 JSON 对象，一个响应对象包含下列成员：

- `jsonrpc` 指定 JSON-RPC 协议版本的字符串，必须准确写为 `"2.0"`
- `result` 远程方法的返回的结果
- `error` 远程方法出错时返回此字段
- `id` 跟请求对象里的 id 一致

下面是两个简单的示例：

client 第一次远程调用 server 的 `subtract(42, 23)` 方法，返回 `19` ：

```txt
client -> server {"jsonrpc": "2.0", "method": "subtract", "params": [42, 23], "id": 1}
server -> client {"jsonrpc": "2.0", "result": 19, "id": 1}
```

client 第二次远程调用 server 的 `subtract(23, 42)` 方法，返回 `-19` ：

```txt
client -> server {"jsonrpc": "2.0", "method": "subtract", "params": [23, 42], "id": 2}
server -> client {"jsonrpc": "2.0", "result": -19, "id": 2}
```

详细的规范可以参考 [JSON-RPC 2.0 规范(中文版)](https://wiki.geekdream.com/Specification/json-rpc_2.0.html)

# 设计自己的 RPC 协议

这次设计的 RPC 协议在注册登录实现的实验中见过，协议结构采用 `JSON` 格式。协议结构很简单，就是包含必选字段 `pid` 为协议 ID ，其他字段就是协议的实际内容了，通讯双方根据 `pid` 进入对应的处理函数执行逻辑即可。

我们通过实操来一步一步实现自己的 RPC 协议框架，首先准备好工程目录 `Code/code4/rpc` 。

```bash
cd ~/Code/code4
mkdir rpc
cd rpc
```

然后下载 `json.lua` 库，用于解析 `JSON` 数据。

```bash
curl -LOR https://raw.githubusercontent.com/rxi/json.lua/master/json.lua
```

然后新建 `net.lua` 文件，用于模拟网络收发数据，文件内容如下：

```lua
local M = {}

local server
local client

function M.send_to_server(fd, data)
    if not server then
        server = require "server"
    end

    server.handle_proto(fd, data)
end

function M.send_to_client(fd, data)
    if not client then
        client = require "client"
    end

    client.handle_proto(fd, data)
end

local fd = 0
function M.connect_server()
    fd = fd + 1
    return fd
end

return M
```

总共三个接口，分别模拟了客户端发数据给服务器，服务器发数据给客户端，以及连接服务器。接下来我们新建 `server.lua` 文件，用来实现处理客户端的请求逻辑。代码如下：

```lua
local json = require "json"
local net = require "net"

local M = {}

local RPC = {}

function RPC.c2s_add(fd, proto)
    print("c2s_add:", proto.a, proto.b)
    local ret = proto.a + proto.b
    return {
        pid = "s2c_add",
        ret = ret,
    }
end

function RPC.c2s_sub(fd, proto)
    print("c2s_sub:", proto.a, proto.b)
    local ret = proto.a - proto.b
    return {
        pid = "s2c_sub",
        ret = ret,
    }
end

function M.handle_proto(fd, json_proto)
    local proto = json.decode(json_proto)
    local pid = proto.pid
    local func = RPC[pid]
    if not func then
        print("Unkonw pid:", pid)
        return
    end

    local r = func(fd, proto)
    net.send_to_client(fd, json.encode(r))
end

return M
```

其中 `RPC` 表是 `pid` 映射协议处理函数的表，实现了两个远程调用函数 `c2s_add` 和 `c2s_sub` ，分别做加法和减法逻辑。处理函数的参数就两个，`fd` 是网络链接 ID ， `proto` 是协议内容，处理完协议后返回对应的协议给客户端。这两组协议的定义如下：

```json
{
  "pid": "c2s_add",
  "a": 1,
  "b": 1
}
{
  "pid": "s2c_add",
  "ret": 1
}
{
  "pid": "c2s_sub",
  "a": 1,
  "b": 1
}
{
  "pid": "s2c_sub",
  "ret": 1
}
```

由于我们采用的是无模式的 `JSON` 序列化结构，所以无需提前定义协议内容文件，但是方便客户端和服务器开发，先定好协议格式，双方开发时可以以此作为开发的接口文档。

接下来实现 `client.lua` ，代码如下：

```lua
local json = require "json"
local net = require "net"

local M = {}

local RPC = {}

function RPC.s2c_add(fd, proto)
    print("s2c_add:", proto.ret)
end

function RPC.s2c_sub(fd, proto)
    print("s2c_sub:", proto.ret)
end

function M.handle_proto(fd, json_proto)
    local proto = json.decode(json_proto)
    local pid = proto.pid
    local func = RPC[pid]
    if not func then
        print("Unkonw pid:", pid)
        return
    end

    func(fd, proto)
end

return M
```

客户端的处理跟服务器的差不多，两个处理函数 `s2c_add` 和 `s2c_sub` 只是打印出计算结果。

接下来我们写个 `test.lua` 测试下 RPC 逻辑：

```lua
local json = require "json"
local net = require "net"

function test()
    local fd = net.connect_server()
    local proto = {
        pid = "c2s_add",
        a = 1,
        b = 2,
    }
    local json_proto = json.encode(proto)
    net.send_to_server(fd, json_proto)

    local proto = {
        pid = "c2s_sub",
        a = 10,
        b = 4,
    }
    local json_proto = json.encode(proto)
    net.send_to_server(fd, json_proto)
end

test()
```

测试代码中就是发送两个协议给服务器。最后执行 `lua5.3 test.lua` 查看运行结果：

![运行结果](https://doc.shiyanlou.com/courses/2770/1456966/6ca163b8654ae0eef68d838584706b66-0)

# 实验总结

在本节实验中，分别介绍了有模式和无模式的两种协议结构。然后练习了 `Protobuf` 的使用，再讲解了 `JSON-RPC` ，最后设计了自己的协议格式。后续的玩法实验都将会采用自己设计的协议格式来实现。