软件包管理中的依赖问题

+ 基于SAT的依赖解决

单独关注包管理的依赖问题

​	CUDF（用于通用可升级性描述格式[20]）;将其用作包管理器和求解器之间的通用语言

+ 面向依赖关系求解用户请求的包管理器将首先将其转换为用 CUDF 表示的升级问题，
+ 然后在其上调用 CUDF enabled 依赖关系求解器，这将向原始包管理器返回 CUDF encoded 解决方案。
+ 只有来回的 CUDF 翻译是特定于平台的; 依赖关系求解器本身与包管理器无关，因此可重用。
+ 实例：MISC

最先进的软件包管理器的依赖关系求解能力普查

+ 来自 libraries.io[13]的主要特定语言包管理器

+ 来自著名的自由/开源软件（FOSS）发行版和平台（如Debian，RedHat和Eclipse）的包管理器

![image-20211217230736997](https://raw.githubusercontent.com/mowang111/image-hosting/master/typora_images/image-20211217230736997.png)

版本控制方案（versioning scheme）

+ 语义版本控制（semver）及其衍生物
+ Debian的版本规范
+ 使用没有排序语义的自由格式字符串（git标签、字符串）

分发（Distribution）

+ 集中式存档（centralized archives） 
  + 使用github平台


Granularity

+ 版本的最小单元：package, branches

版本锁（Version Locking）

Qualifiers：包管理器是否支持基于外部生成配置选择特定的依赖性？

依赖项范围运算符（Dependency range operators）:

范围修饰符（Range modifiers）

+ 依赖项范围可能会出现更复杂的情况：如果开发人员想要表达一个约束，例如"更新到所有新的次要版本，但不更新到下一个主要版本"，该怎么办？范围修饰符使开发人员能够预测新的修补程序（弹性修补程序）或新的次要（弹性次要）版本，而无需显式修改其项目的清单文件

解决过程（Resolution process）

+ Correctness：解决方案是否尊重依赖关系
+ Completeness：找到解决方案后还会寻找方案吗
+ User preferences：用户能否提供自定义优化标准来区分有效的解决方案
  + OCaml 编程语言的 opam 包管理器为用户提供了一组丰富的首选项
  + opam install merlin --criteria="-changed,-removed"
  + 由于这是一个开发工具，因此用户不希望其安装影响系统中安装的其他库，这些库也可能用作项目的生成依赖项。为此，-changed，-remove 首选项表明，在所有可能的解决方案中，我们更喜欢最小化对系统更改并最小化删除其他软件包的解决方案。

Approximate solutions：替代方案？

+ 当找不到解决方案时，某些包管理器会放宽约束
  + 缺少依赖项：当无法满足依赖项版本约束时，大多数包管理器将报告错误，而某些包管理器（例如，Cargo 和 Maven）将忽略该错误并安装最新的可用版本
  + 冲突：当依赖关系解析的传递关闭包含同一工件的多个版本时，大多数包管理器将出现错误，因为不存在有效的解决方案。另一方面，一些包管理器将强制安装完成：Cargo重写冲突的符号名称，以使库的多个版本共存;其他人选择更接近正在解析其依赖关系的包的依赖关系树根的版本

Eclipse使用基于Sat4J [15]构建的P2，SUSE和RedHat使用libsolv（本身基于libzypp2 SAT求解器），而Debian和Opam可以使用任何外部CUDF求解器。这是个好消息：使用完全依赖关系求解器的重要性现在似乎得到了很好的承认，而且似乎众所周知，这需要利用SAT、MaxSAT、PBO、ASP或MILP等求解器技术，而不是临时依赖关系图遍历。我们认为，[2]的第一个主张的很大一部分实际上已经通过。

另一方面，似乎只有Opam接受了[1]中提倡的"关注点分离"方法，并且apt-get有点中途，因为它仅作为一种选择提供外部求解器。有几个因素可以解释这种有限的成功：一些是技术性的，另一些是社会性的。

从技术角度来看，我们注意到两个问题。首先，CUDF格式有一些缺点。虽然它非常适合使用类似于Debian的版本控制和依赖方案的包管理器，但它不支持涉及限定符（由Eclipse P2使用）或非重叠版本间隔（npm）的本机依赖关系约束 - 它们可以被支持，但代价是CUDF适配器中的额外复杂性。其次，虽然从长远来看，依赖一个或多个外部求解器可能是一个明智的选择，3 但它在需要适当满足的关键组件（包管理器）中引入了外部依赖关系。 这两个方面可能会减少依赖第三方 CUDF 求解器的支持









