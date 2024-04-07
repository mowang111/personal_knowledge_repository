```
[common]
server_addr=172.16.1.3
server_port=1883
mqtt_addr=172.16.1.3
protocal=modbustcp

[topic]
factory_name=yuanhong/jiaoxian
topic_send=statusRecord
topic_recv=statusRecordRecv

[connect-arg]
ipaddress=192.168.1.190
port=8888
slave_id=1

[dc-arg]
functioncode=3
interval=30
argnum=5

name1=rotationalSpeed
address1=7
type1=F
multi1=1.0

name2=wireDrawingSpeed
address2=11
type2=F
multi2=1.0

name3=currentLength
address3=5
type3=F
multi3=1.0

name4=twistDistance
address4=19
type4=F
multi4=1.0

name5=tensileStress
address5=9
type5=F
multi5=1.0

```

