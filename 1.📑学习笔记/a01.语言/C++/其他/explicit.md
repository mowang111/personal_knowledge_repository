# explicit

构造函数分为三种：1.拷贝构造函数 2.转换构造函数 3 构造函数

在C++中，explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换，只能以显示的方式进行类型转换。

explicit使用注意事项:

* explicit 关键字只能用于类内部的构造函数声明上。

* explicit 关键字作用于单个参数的构造函数。

* 在C++中，explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换

例子：

未加explicit时的隐式类型转换

```c++
 \1. class Circle 
  \2. { 
  \3. public: 
  \4.   Circle(double r) : R(r) {} 
  \5.   Circle(int x, int y = 0) : X(x), Y(y) {} 
  \6.   Circle(const Circle& c) : R(c.R), X(c.X), Y(c.Y) {} 
  \7. private: 
  \8.   double R; 
  \9.   int  X; 
 \10.   int  Y; 
 \11. }; 
 \12. 
 \13. int _tmain(int argc, _TCHAR* argv[]) 
 \14. { 
 \15. //发生隐式类型转换 
 \16. //编译器会将它变成如下代码 
 \17. //tmp = Circle(1.23) 
 \18. //Circle A(tmp); 
 \19. //tmp.~Circle(); 
 \20.   Circle A = 1.23; 
 \21. //注意是int型的，调用的是Circle(int x, int y = 0) 
 \22. //它虽然有2个参数，但后一个有默认值，任然能发生隐式转换 
 \23.   Circle B = 123; 
 \24. //这个算隐式调用了拷贝构造函数 
 \25.   Circle C = A; 
 \26.   
 \27.   return 0; 
 \28. } 
```

加了explicit关键字后，可防止以上隐式类型转换发生

```c++
  \1. class Circle 
  \2. { 
  \3. public: 
  \4.   explicit Circle(double r) : R(r) {} 
  \5.   explicit Circle(int x, int y = 0) : X(x), Y(y) {} 
  \6.   explicit Circle(const Circle& c) : R(c.R), X(c.X), Y(c.Y) {} 
  \7. private: 
  \8.   double R; 
  \9.   int  X; 
 \10.   int  Y; 
 \11. }; 
 \12. 
 \13. int _tmain(int argc, _TCHAR* argv[]) 
 \14. { 
 \15. //一下3句，都会报错 
 \16.   //Circle A = 1.23; 
 \17.   //Circle B = 123; 
 \18.   //Circle C = A; 
 \19.   
 \20. //只能用显示的方式调用了 
 \21. //未给拷贝构造函数加explicit之前可以这样 
 \22.     Circle A = Circle(1.23); 
 \23.     Circle B = Circle(123); 
 \24.     Circle C = A; 
 \25. 
 \26. //给拷贝构造函数加了explicit后只能这样了 
 \27.     Circle A(1.23); 
 \28.     Circle B(123); 
 \29.     Circle C(A); 
 \30.   return 0; 
 \31. } 
```

