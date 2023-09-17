# C++STL容器 - AcWing

https://www.acwing.com/blog/content/488/

我们一般在用一些基本的数据结构的时候，为了方便与解题技巧我们一般会用到容器!当然具体方法太多，所以建议用什么学什么！

我们来看一下什么叫容器？ 容器是储存其他对象的对象。被储存的对象必须是同一类型。（如果你还没有学习OOP！其实你可以把它看成一个数组，只不过他有特殊的方法与使用技巧！）

分类： 与java的集合不同!他被分为两个部分，一是序列容器（是一种各元素之间有顺序关系的线性表，是一种线性结构的可序群集。顺序性容器中的每个元素均有固定的位置，除非用删除或插入的操作改变这个位置。顺序容器的元素排列次序与元素值无关，而是由元素添加到容器里的次序决定）（forword_list,list,queue,priority_queue,stack,deque,vector,array(虽然他被归为序列容器，但是并不满足序列的所以要求！)）。 另一个是关联容器（关联式容器是非线性的树结构，更准确的说是二叉树结构。各元素之间没有严格的物理上的顺序关系，也就是说元素在容器中并没有保存元素置入容器时的逻辑顺序。但是关联式容器提供了另一种根据元素特点排序的功能，这样迭代器就能根据元素的特点“顺序地”获取元素。元素是有序的集合，默认在插入的时候按升序排列（set,multiset,map,multimap）！

C++11之后还有一种无序关联容器！

## 序列容器

序列的要求：

```cpp
X a(n,t)  //声明一个名为a的有n个t组成的序列
X(n,t)     //匿名序列（这里我们不做过多的解释）
X a(i,j)   //声明一个名为a的序列，并且初始化[i,j）
的内容
X(i,j)      //匿名序列
v.insert()   //由于insert重载方法比较多
   1.v.insert(p,t)//将t插到p的前面
   2.v.insert(p,n,t)//将n个t插入p之前
   3.v.insert(p,i.j)//将区间[i,j)的元素插入到p之前
v.erase(t,k)
   1.v.erase(t,k)//删除他们之间的元素
   2.v.erase(p)//删除p指向的元素
v.chear===v.erase(begin(),end());
```

下面我们来看一下这些容器的特点！

### vector

vector是数组的一种类表示（如果还没有OOP,可以不用理解）！vector表示一段连续的内存，基于数组实现，他有自动的内存管理功能!可以动态的改变vector的长度，并随着元素的增加与减小来自动改变数组大小，它提供了直接添加尾部元素或者删除元素的方法！所以它的时间是固定的！然而他要在头部与中间插入或者删除元素是线性的时间复杂度！ 特点： 他可以反转序列，所以它可以反向遍历可反转序列！（基于他的rbegin,rend）

定义与初始化: 要调用头文件

```cpp
  #include<vector>
```

定义与初始化：

```c++
vector<int> v;//默认初始化
vector<int> v(v1);//用v1初始化v
vector<int>v(v1.begin(),v1.end());//用v1初始化v
vector<int> v(10);//定义一个大小为10的数组！
vector<int> v(10,1)//定义个全为1而且长度为10的数组
```

方法：

```cpp
v.push_back()      //增
v.insert()   //由于insert重载方法比较多
   1.v.insert(p,t)//将t插到p（位置a.begin()+p）的前面
   2.v.insert(p,n,t)//将n个t插入p之前
   3.v.insert(p,i.j)//将区间[i,j)的元素插入到p之前
v.pop_back()       //删
v.erase(t,k)
   1.v.erase(t,k)//删除他们之间的元素[t,k)
   2.v.erase(p)//删除p指向的元素
v.chear===v.erase(begin(),end());
```

遍历

```
//下标法
int length = v.size();
for(int i=0;i<length;i++)
 {
cout<<v[i];
}
cout<<endl;
//迭代器法
vector<int>::const_iterator iterator = v.begin();
 for(;iterator != v.end();iterator++)
{
 cout<<*iterator;
 }
```

### deque

双端队列，他的实现类似与vector,支持随机访问，但是它访问首元素的插入（push_front()）与删除（pop_front()）的时间是固定的！而且他的执行速度要比vector快很多！所以题目中有大量的操作发生在序列的起始位置与结尾处，我们就要考虑用deque!

```cpp
调用头文件：
 #include<deque>
```

初始化与定义已经在序列要求里面，而且方法与vector类似，只是多了push_front(),pop_front(),我们就不做过多的阐述

### list

双向链表，list在链表中的任意一个位置插入与删除一个元素时间是固定的！但是他不能随机访问，优点是元素的快速插入与删除！从容器中插入与删除元素之后i，迭代器指向元素将不变，不会移动已有元素，只是修改链表信息。

```cpp
#include<list>
```

我们来看一下他的链表独有成员函数！

```cpp
void sort()   //使用<运算符对链表进行排序，时间复杂度O（NlogN）
void merge(list<T,Alloc>&x)  //将x与调用链表合并，要求：两个链表必须要已经排好序！元素将保存在调用链表中，x为空，这个时间复杂度为线性！
void remove(const T &val)//删除val的所有实例
void splice(iterator pos,list<T,Alloc>x)//将链表x的内容加到pos的前面，时间复杂度为固定时间

void unique（） //去重，线性时间
```

### forword_list

参加noip的同学注意了！他是C++11新添加的容器类！它主要实现了单向链表，只需要正向迭代器，他是不可逆转容器，他功能比较少，但是它比较简单！

### queue

他是一个配适器类，ostream_iterator就是一个配适器，让输出流能够使用迭代器接口，同样它实现了队列接口！它不仅不允许随机访问元素，而且还不能遍历队列！元素只能先进先出（FIFO）. 方法：

```cpp
bool empty()//判断是否为空
front()//队首元素的访问
back()//队尾元素的访问
push(x)//队尾插入x
pop()//删除队首元素
```

### priority_queue

另一个配适器，他与queue基本一样，但是他的最大元素被移动到队首（生活不总是公平对，队列也一样），内部区别在于底层结构不一样，他用的是vector,当然我们可以修改确定拿个元素放在队首的比较方式！

```cpp
priority_queue<int> X //大根堆,默认初始化

priority_queue<int, vector<int>, greater<int>> x  //小根堆,运用了预定义函数greater<int>！
```

以下内容摘自C++API：

```cpp
包含priority_queue 的头文件是 <queue>
priority_queue类的主要成员：
priority_queue();    //默认构造函数，生成一个空的排序队列
priority_queue(const queue&);    //拷贝构造函数
priority_queue& operator=(const priority_queue &);    //赋值运算符重载
priority_queue 的私有成员：
value_type;   //priority_queue中存放的对象类型，它和priority_queue中的T类型相同
priority_queue(const Compare& comp);    //构造生成一个空的priority_queue对象，使用comp作为priority_queue的comparison
priority_queue(const value_type* first, const value_type* last);    //带有两个参数的构造 函数，使用默认的Comparison作为第三个参数
size_type;    //正整数类型，和Sequence::size_type类型一样。
bool empty() const;    //判断优先级队列是否为空，为空返回true，否则返回false
size_type size() const;    //返回优先级队列中的元素个数
const value_type& top() const();    //返回优先级队列中第一个元素的参考值。
void push(const value_type& x);    //把元素x插入到优先级队列的尾部，队列的长度加1
void pop();    //删除优先级队列的第一个值，前提是队列非空，删除后队列长度减1
```

### stack

适配器，它可以将任意类型的序列容器转换为一个堆栈，一般使用deque作为支持的序列容器。元素只能后进先出（LIFO）。不能遍历整个stack。他给vector提供了栈接口! 与queue类似，如果要使用栈中元素，先用top检索，然后用pop将他从栈中删除，这个太过于常用不介绍方法！

### array

他不是STL容器，由于他的长度固定，使用没有调节大小的操作，但是他有一些有意义的成员函数，如operator[]和at(),当然有很多STL算法用于array,如copy(),for_each（）。我们后面会详细介绍一些C++知识点！

## 关联容器

它运用了键值对（value-key），与java类似的map,例如hashmap，有点在于他提供了利用key快速访问功能，它的底层结构应该是一种树来实现的，所以他才有如此快的查找速度，最简单的set，他的键值对类型是一致的，而且唯一，元素默认按升序排列。map他的键值对类型不同，键是唯一的,元素默认按键的升序排列。！而muilti_sset/map 键可以不唯一。 迭代器在关联容器中对操作：

```cpp
m.lower_bound(k)//返回一个迭代器，指向键不小于 k 的第一个元素
m.upper_bound(k)//返回一个迭代器，指向键大于 k 的第一个元素
m.equal_range(k)//返回一个迭代器的 pair 对象。它的 first 成员等价于 m.lower_bound(k)。而 second 成员则等价于 m.upper_bound(k)
```

### map

map 是键－值对的集合。map 类型通常可理解为关联数组：可使用键作为下标来获取一个值，正如内置数组类型一样。而关联的本质在于元素的值与某个特定的键相关联，而并非通过元素在数组中的位置来获取。 定义与初始化

```cpp
map<int,string> map1;    //默认为空
m.insert()
    1.m.insert(e)//e是一个用在m上的value_kry 类型的值。如果键（e.first不在m中，则插入一个值为e.second 的新元素；如果该键在m中已存在，则保持m不变。该函数返回一个pair类型对象，包含指向键为e.first的元素的map迭代器，以及一个 bool 类型的对象，表示是否插入了该元素
    2.m.insert(begin,end)//begin和end是标记元素范围的迭代器，其中的元素必须为m.value_key 类型的键－值对。对于该范围内的所有元素，如果它的键在 m 中不存在，则将该键及其关联的值插入到 m。返回 void 类型
    3.m.insert(iter,e)//e是一个用在m上的 value_key 类型的值。如果键（e.first）不在m中，则创建新元素，并以迭代器iter为起点搜索新元素存储的位置。返回一个迭代器，指向m中具有给定键的元素
m.count(k) //返回m中k的出现次数
m.find()   //如果m容器中存在按k索引的元素，则返回指向该元素的迭代器。如果不存在，则返回超出末端迭代器.
m.erase()  //具体与序列该方法一致！
```

### set

支持插入，删除，查找等操作，就像一个集合一样。所有的操作的都是严格在logn时间之内完成，效率非常高。set和multiset的区别是：set插入的元素不能相同，但是multiset可以相同。Set默认自动排序。使用方法类似list。 set容器的定义和使用

set 容器的每个键都只能对应一个元素。以一段范围的元素初始化set对象，或在set对象中插入一组元素时，对于每个键，事实上都只添加了一个元素。

```cpp
vector<int> ivec;
for(vector<int>::size_type i = 0; i != 10; ++i) {
ivec.push_back(i);
ivec.push_back(i);
}
set<int> iset(ivec.begin(), ivec.end());
cout << ivec.size() << endl;//20个
cout << iset.size() << endl;// 10个
```

添加

```cpp
set<string> set1;
set1.insert("the"); //第一种方法：直接添加
set<int> iset2;
iset2.insert(ivec.begin(), ivec.end());//第二中方法：通过指针迭代器
```

获取：

```cpp
set<int> iset;
for(int i = 0; i<10; i++)
iset.insert(i);
iset.find(1)// 返回指向元素内容为1的指针
iset.find(11)// 返回指针iset.end()
iset.count(1)// 存在，返回1
iset.count(11)// 不存在，返回0
```

由于其他两个不常用我们不做过多介绍！有兴趣的童鞋可以去CPPAPI或者 CPP底层源码参考学习！

底层结构基于哈希表，主要主要与提高添加与删除元素得速度与提高查找算法得效率！无序关联容器（unordered_set、unordered_multiset、unordered_map和 unordered_multimap）使用键和哈希表，以便能够快速存取数据。下面简要地介绍这些概念。哈希函数（hash function）将键转换为索引值。例如，如果键为string对象，哈希函数可能将其中每个字符的数字编码相加，再计算结果除以13的余数，从而得到 一个0～12的索引。而无序容器将使用13个桶（bucket）来存储string，所有索引为4的string都将存储在第4个桶中。如果您要在容器中搜索键，将对键执行哈希函数，进而只在索引对应的桶中搜索。理想情况下，应有足够多的桶，每个桶只包含为数不多的string。 C++11库提供了模板hash[HTML_REMOVED]，无序关联容器默认使用该模板。为各种整型、浮点型、指针以及一些模板类（如string）定义了该模板的具体化。

```cpp
X(n, hf, eq)//创建一个至少包含n个桶的空容器，并将hf用作哈希函数，将eq用作键值相等谓词。如果省略了eq，则将ke

y_equal( )用作键值相等谓词；如果也省略了hf，则将hasher( )用作哈希函数

X a(n, hf, eq)//创建一个名为a的空容器，它至少包含n个桶，并将hf用作哈希函数，将eq用作键值相等谓词。如果省略eq，则将key_equal( )用作键值相等谓词；如果也省略了hf，则将hasher( )用作哈希函数

X(i, j, n, hf, eq)//创建一个至少包含n个桶的空容器，将hf用作哈希函数，将eq用作键值相等谓词，并插入区间[i, j]中的元素。如果省略了eq，将key_equal( )用作键值相等谓词；如果省略了hf，将hasher( )用作哈希函数；如果省略了n，则包含桶数不确定

X a(i, j, n, hf, eq)//创建一个名为a的的空容器，它至少包含n个桶，将hf用作哈希函数，将eq用作键值相等谓词，并插入区间[i, j]中的元素。如果省略了eq，将key_equal( )用作键值相等谓词；如果省略了hf，
将hasher( )用作哈希函数；如果省略了n，则包含桶数不确定

b.hash_function( )//返回b使用的哈希函数

b.key_eq( )//返回创建b时使用的键值相等谓词

b.bucket_count( )//返回b包含的桶数

b.max_bucket_count ( )//返回一个上限数，它指定了b最多可包含多少个桶

b.bucket(k)//返回键值为k的元素所属桶的索引

b.bucket_size(n)//返回索引为n的桶可包含的元素数

b.begin(n)//返回一个迭代器，它指向索引为n的桶中的第一个元素

b.end(n)//返回一个迭代器，它指向索引为n的桶中的最后一个元素

b.cbegin(n)//返回一个常量迭代器，它指向索引为n的桶中的第一个元素

b.cend(n)//返回一个常量迭代器，它指向索引为n的桶中的最后一个元素

b.load_factor()//返回每个桶包含的平均元素数

b.max_load_factor()//返回负载系数的最大可能取值；超过这个值后，容器将增加桶

b.max_load_factor(z)//可能修改最大负载系统，建议将它设置为z

a.rehash(n)//将桶数调整为不小于n，并确保a.bucket_count( )> a.size( ) / a.max_load_factor( )

a.reserve(n)//等价于a.rehash(ceil(n/a.max_load_factor( )))，
其中ceil(x)返回不小于x的最小整数
```

用法基本都是一致，所以我在这里给大家一个可以寻找到一些数据结构的方法的路径!故没有给大家分析与解读他们的一些存储与方法作用图用于理解！

### 小结

1.有序容器（除了list）：存储底层vector,只是添加了不同的接口！ 2.deque（队列）：它不像vector 把所有的对象保存在一块连续的内存块，而是采用多个连续的存储块，并且在一个映射结构中保存对这些块及其顺序的跟踪。向deque 两端添加或删除元素的开销很小，它不需要重新分配空间。 3、list（列表）：是一个线性链表结构，它的数据由若干个节点构成，每一个节点都包括一个信息块（即实际存储的数据）、一个前驱指针和一个后驱指针。它无需分配指定的内存大小且可以任意伸缩，这是因为它存储在非连续的内存空间中，并且由指针将有序的元素链接起来。 4.后面的关联与无序关联都是用的一种树状结构！

用法与选择： 1.当数组大小未知时，和需要高效的查询功能，用vector!高效地随机存储。 2.不使用连续的内存空间,而且可以随意地进行动态操作，有大量的插入、删除操作，用list！ 3.需要在两端进行push 、pop用daque！它兼顾了数组和链表的优点，它是分块的链表和多个数组的联合。所以它有被list 好的查询性能，有被vector 好的插入、删除性能。 如果你需要随即存取又关心两端数据的插入和删除，那么deque 是最佳之选。 4.需要查找或者打表可以选择map与set,当然一定条件下我们可以优秀考虑用无序关联容器！

由于这个太过于固定化，而且偏向理论，故我们没有用一些生动的例子来说明，当然还有一些重要的东西可能没有提到，所以我建议大家可以研读一下C++prime plus,这一次分享基本来源于本书以及自己的理解！好了，这个就是STL容器的一些基本知识点，谢谢你的阅读！希望你有所收获！