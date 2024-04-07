cmd窗口

```
for /L %i IN (1,1,254) DO ping -w 1 -n 1 192.168.0.%i
arp -a
```

