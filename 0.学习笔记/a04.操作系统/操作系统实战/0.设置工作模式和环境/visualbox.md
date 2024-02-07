## 存储设备
### 存储控制器
1. **IDE(Integrated Drive Electronics)**:IDE是早期的磁盘驱动器接口技术，现在在虚拟环境中用于向操作系统提供兼容性。
2. **SATA (Serial ATA)**: SATA 控制器是现代硬盘接口技术，提供比 IDE 更高的数据传输速率。在 VirtualBox 中，可以为虚拟机添加 SATA 控制器，并将硬盘映像（如 VDI、VMDK、VHD 等）附加到该控制器。
3. **SCSI (Small Computer System Interface)**: SCSI 控制器是一种专业的硬盘接口，通常用于服务器。在 VirtualBox 中，SCSI 控制器用于提供更高级的存储配置。
4. **SAS (Serial Attached SCSI)**: SAS 是 SCSI 的一个变体，提供高速数据传输。它通常用于要求高性能的服务器环境。
5. **USB (Universal Serial Bus)**: 虽然 USB通常用于外部设备，但在某些情况下，也可以将 USB设备模拟为存储控制器。
6. **NVMe (Non-Volatile Memory Express)**: NVMe 是一种针对固态驱动器（SSD）优化的存储访问和传输协议。它利用 PCIe 接口，提供比 SATA 和 SCSI 更快的数据传输速率。