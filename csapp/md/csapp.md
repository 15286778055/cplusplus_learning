### 编译器优化影响
#### 移位操作(<< >>)、加法 代替 乘法(需要较多时钟周期)


#### for(statement1; statement2; statement3)

statement2、statement3循环多次，避免函数调用


#### 内存别名
以下代码对a[i]进行多次内存读写
为了避免存在**内存别名**(a、b指向同块内存)，优化后改变原义，编译器不优化
```
int i;
for (i=0; i < len; ++i) {
    a[1] += b[i]
}
```
改为：
```
int i = 0;
int var = 0;
for (i=0; i < len; ++i) {
    var += b[i]
}
a[1] = var
```


###