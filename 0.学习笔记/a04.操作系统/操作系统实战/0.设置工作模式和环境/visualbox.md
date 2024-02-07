## 系统
![[Pasted image 20240207112201.png]]
### Matherboard(主板选项卡)
- **Base Memory**: 虚拟机被分配的基础内存大小。在这个例子中，滑块显示基础内存设置在 8192 MB (8 GB)。
- **Boot Order**: 启动顺序，定义了虚拟机启动时检查引导设备的顺序。勾选的设备将会被包括在启动过程中。顺序为：
    - Floppy（软驱，当前未勾选）
    - Optical（光驱，当前勾选）
    - Hard Disk（硬盘，当前勾选）
    - Network（网络启动，当前勾选）
- **Chipset**: 虚拟机使用的芯片组类型。PIIX3 是较老的芯片组类型，但足以满足大多数需求。其他选项可能包括 ICH9，这是一个较新的芯片组模拟。
- **Pointing Device**: 指定模拟的指针设备类型，例如PS/2鼠标。
- **Extended Features**: 包括额外的硬件功能，如：
    - **Enable I/O APIC**: 支持高级配置和电源接口，对于多核处理器或多线程操作系统来说可能是必需的。
    - **Enable EFI (special OSes only)**: 启用EFI启动，这是一种替代传统BIOS的固件接口，对于一些特别的操作系统或设置来说可能是必需的。
    - **Hardware Clock in UTC Time**: 设置硬件时钟使用协调世界时（UTC）。
## 存储设备
### 存储控制器
在 VirtualBox 中，可以根据需要为虚拟机添加多个存储控制器，并在这些控制器上配置虚拟硬盘。选择哪种控制器类型取决于要安装的操作系统的兼容性、虚拟硬盘的性能需求，以及可能的硬件模拟需求。通常，现代操作系统和虚拟机配置更倾向于使用 SATA 或 SAS 控制器，因为它们提供了更好的性能和兼容性。
1. **IDE(Integrated Drive Electronics)**:IDE是早期的磁盘驱动器接口技术，现在在虚拟环境中用于向操作系统提供兼容性。
2. **SATA (Serial ATA)**: SATA 控制器是现代硬盘接口技术，提供比 IDE 更高的数据传输速率。在 VirtualBox 中，可以为虚拟机添加 SATA 控制器，并将硬盘映像（如 VDI、VMDK、VHD 等）附加到该控制器。
3. **SCSI (Small Computer System Interface)**: SCSI 控制器是一种专业的硬盘接口，通常用于服务器。在 VirtualBox 中，SCSI 控制器用于提供更高级的存储配置。
4. **SAS (Serial Attached SCSI)**: SAS 是 SCSI 的一个变体，提供高速数据传输。它通常用于要求高性能的服务器环境。
5. **USB (Universal Serial Bus)**: 虽然 USB通常用于外部设备，但在某些情况下，也可以将 USB设备模拟为存储控制器。
6. **NVMe (Non-Volatile Memory Express)**: NVMe 是一种针对固态驱动器（SSD）优化的存储访问和传输协议。它利用 PCIe 接口，提供比 SATA 和 SCSI 更快的数据传输速率。
每种控制器都模拟了特定的硬件接口
1. **PIIX4 / PIIX3**: 这些是较旧的IDE控制器接口，主要用于早期的操作系统兼容性。
2. **ICH6**: 这是Intel I/O Controller Hub的一个型号，也是一个IDE控制器，支持更现代的操作系统。
3. **AHCI (Advanced Host Controller Interface)**: 这是现代SATA控制器的接口标准，支持热插拔和本地命令队列（NCQ）等特性，适用于现代操作系统。
4. **LsiLogic**: 这是由LSI公司开发的SCSI控制器，模拟传统的SCSI环境，通常用于较旧的操作系统和企业级应用。
5. **BusLogic**: 另一种SCSI控制器，与LsiLogic类似，也是为了支持特定的旧操作系统和应用。
6. **I82078**: 这通常是一个软驱控制器，现在已经很少使用。
7. **LsiLogic SAS**: LSI的一种串行连接SCSI控制器，用于高端和企业级的存储解决方案。
8. **USB (Universal Serial Bus)**: 这允许虚拟机模拟USB存储设备。
9. **NVMe (Non-Volatile Memory Express)**: 这是一种为固态存储提供支持的控制器，使用PCI Express接口，能够提供高速存储性能。
10. **virtio-scsi**: 这是一种为虚拟环境优化的SCSI子系统，它是virtio家族的一部分，旨在提供高效的存储虚拟化。
这些控制器模拟硬件以便虚拟机可以与之通信，就像它们是物理机上的实际硬件一样。在创建和配置虚拟机时，应根据安装的操作系统和性能需求选择合适的控制器类型。