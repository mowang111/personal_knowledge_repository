## emplace和insert主要区别

emplace 最大的作用是避免产生不必要的临时变量，因为它可以完成 in place 的构造。

```c++
struct Foo {
    Foo(int n, double x);
};

std::vector<Foo> v;
v.emplace(someIterator, 42, 3.1416);        // 没有临时变量产生
v.insert(someIterator, Foo(42, 3.1416));    // 需要产生一个临时变量
v.insert(someIterator, {42, 3.1416});       // 需要产生一个临时变量
```

这是 emplaceemplace 和 insertinsert 最大的区别点。emplaceemplace 的语法看起来不可思议，在上 面的例子中后面两个参数自动用来构造 vector 内部的 Foo 对象。做到这一点主要 使用了 C++11 的两个新特性 变参模板变参模板 和 完美转发完美转发。”变参模板”使得 emplace 可以接受任意参数，这样就可以适用于任意对象的构建。
”完美转发”使得接收下来的参数 能够原样的传递给对象的构造函数，这带来另一个方便性就是即使是构造函数声明为 explicitexplicit 它还是可以正常工作，因为它不存在临时变量和隐式转换。

```c++
struct Bar {
    Bar(int a) {}
    explicit Bar(int a, double b) {}
};

int main(void)
{
    vector<Bar> bv;
    bv.push_back(1);        // 隐式转换生成临时变量
    bv.push_back(Bar(1));   // 显示构造临时变量
    bv.emplace_back(1);     // 没有临时变量

    //bv.push_back({1, 2.0});   //  无法进行隐式转换
    bv.push_back(Bar(1, 2.0));  //  显示构造临时变量
    bv.emplace_back(1, 2.0);    //  没有临时变量

    return 0;
}
```

## map的特殊情况

mapmap 类型的 emplaceemplace 处理比较特殊，因为和其他的容器不同，map 的 emplace 函数把它接收到的所有的参数都转发给 pairpair 的构造函数。对于一个 pairpair 来说，它既需要构造它的 keykey 又需要构造它的 valuevalue。如果我们按照普通的 的语法使用变参模板，我们无法区分哪些参数用来构造 keykey, 哪些用来构造 valuevalue。 比如下面的代码：

```c++
map<string, complex<double>> scp;
scp.emplace("hello", 1, 2);  // 无法区分哪个参数用来构造 key 哪些用来构造 value
                             // string s("hello", 1), complex<double> cpx(2) ???
                             // string s("hello"), complex<double> cpx(1, 2) ???
```

所以我们需要一种方式既可以接受异构变长参数，又可以区分 key 和 value，解决 方式是使用 C++11 中提供的 tuple。

```c++
pair<string, complex<double>> scp(make_tuple("hello"), make_tuple(1, 2));
```

然后这种方式是有问题的，因为这里有歧义，第一个 tuple 会被当成是 key，第二 个tuple会被当成 value。最终的结果是类型不匹配而导致对象创建失败，为了解决 这个问题，C++11 设计了 piecewise_construct_t 这个类型用于解决这种歧义，它 是一个空类，存在的唯一目的就是解决这种歧义，全局变量 std::piecewise_construct 就是该类型的一个变量。所以最终的解决方式如下：

```c++
pair<string, complex<double>> scp(piecewise_construct,
                                  make_tuple("hello"),
                                  make_tuple(1, 2));
```

当然因为 map 的 emplace 把参数原样转发给 pair 的构造，所以你需要使用同样 的语法来完成 emplace 的调用，当然你可以使用 forward_as_tuple 替代 make_tuple，该函数会帮你构造一个 tuple 并转发给 pair 构造。

```c++
map<string, complex<double>> scp;
scp.emplace(piecewise_construct,
            forward_as_tuple("hello"),
            forward_as_tuple(1, 2));
```

所以对于 map 来说你虽然避免了临时变量的构造，但是你却需要构建两个 tuple 。 这种 traedoff 是否值得需要代码编写者自己考虑，从方便性和代码优雅性上来说：

```c++
scp.insert({"world", {1, 2}});
```

这种写法都要胜过前面这个 emplace 版本。所以个人认为对于临时变量构建代价不是 很大的对象（比如基础类型）推荐使用 insert 而不是 emplace。