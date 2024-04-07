update-alternatives 命令用于处理 Linux 系统中软件版本的切换，使其多版本共存。
## 管理gcc版本
```
update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-3.4 0
# 第一个参数: --install 表示向update-alternatives注册服务名。
# 第二个参数: 注册最终地址，成功后将会把命令在这个固定的目的地址做真实命令的软链，以后管理就是管理这个软链；
# 第三个参数: 服务名，以后管理时以它为关联依据。
# 第四个参数: 被管理的命令绝对路径。
# 第五个参数: 优先级，数字越大优先级越高。
update-alternatives --remove gcc /usr/bin/gcc-3.4
update-alternatives --config
```
