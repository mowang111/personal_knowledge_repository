```
v2ray-core  
├── app // 应用模块  
│ ├── dispatcher // 用于把入站代理所接收到的数据，传送给出站代理  
│ ├── router // 路由  
│ ├── dns // 内置的 DNS 缓存  
│ ├── proxyman // 代理管理器  
├── common // 公用代码  
├── proxy // 各协议具体实现  
│ ├── blackhole  
│ ├── dokodemo-door  
│ ├── freedom  
│ ├── socks  
│ ├── vmess  
├── transport // 传输模块
```


参考文档
[V2Ray 源代码分析](https://medium.com/@jarvisgally/v2ray-%E6%BA%90%E4%BB%A3%E7%A0%81%E5%88%86%E6%9E%90-b4f8db55b0f6)