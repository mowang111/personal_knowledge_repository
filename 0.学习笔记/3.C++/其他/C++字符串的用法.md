# C++字符串的用法

## 遍历字符串

```c++
string s;
for(char i:s) cout<<i;
```

## 字符串输入输出

### 读取一行字符串——getline(cin,line)

> 注意用getchar()读入上一行行末回车

### 将一行字符串按空格分开

```cpp
string line;
getline(cin, line);
stringstream ssin(line);
string keyword;
set<string> keywords;
while (ssin >> keyword) keywords.insert(keyword);
```

### 字符串输出

printf只能输出C语言中的内置数据，string不是c语言内置数据。更深入的来说：s这个string类型的对象并非单单只有字符串，其内还有许多用于操作的函数，于是&s并非字符串“中国”的首地址，而是s这个对象的首地址。

```cpp
string s = “中国”;
printf(“%s” , s.c_str());//string中c_str()成员方法返回当前字符串的首字符地址
```

或`cout<<`

> 注意字符串用scanf输入不能使用s.c_str()，因为字符串类型本身并没有为其开辟存储空间，还是要使用char s[10]来进行定义，再使用scanf读入

