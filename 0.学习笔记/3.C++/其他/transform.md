

# std::transform的使用

包含于\<algorithm\>头文件中

## 声明

```c++
//一元操作
template <class InputIterator, class OutputIterator, class UnaryOperation>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperation op);
//二元操作
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class BinaryOperation>
  OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, OutputIterator result,
                            BinaryOperation binary_op);
```

## 示例

将字符串转换成小写

```c++
string& ToLower(string& st){
    transform(st.begin(),st.end(),st.begin(),tolower);
    return st;
}
```

> 可能的问题：tolower()函数被定义为int tolower(int)
>
> 解决方法：
>
> ```c++
> char toLower(char ch) return tolower(ch);
> ```

