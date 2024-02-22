

## DevTools (Debugging Tools) 发展史



## DevTools 架构

![image-20230815170139821](C:\Users\11547\AppData\Roaming\Typora\typora-user-images\image-20230815170139821.png)

DevTools 是 `client-server` 架构：

- client 端提供可视化 Web UI 界面供用户操作，它负责接收用户操作指令，然后将操作指令发往浏览器内核或 Node.js 中进行处理，并将处理结果数据展示在 Web UI 上。
- server 端启动了两类服务：
  - HTTP 服务： 提供内核信息查询能力，比如获取内核版本、获取调试页的列表、启动或关闭调试。
  - WebSocket 服务：提供与内核进行真实数据通信的能力，负责 Web UI 传递过来的所有操作指令的分发和处理，并将结果送回 Web UI 进行展示。

### Chrome DevTools

