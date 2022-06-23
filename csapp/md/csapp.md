## Lecture 10 Program optimization

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



## Lecture 11 Memory Hierachy

- the speed gap between CPU, memory and mass storage continus to widen
- Well-written programs exhibit a property called **locality**（程序的局限性：时间局限性、空间局限性）
- Memory hierarchied based on caching close the gap by exploiting locality（内存层级基于缓存，上级是下级的缓存）、


## Lecture 12 Cache Memories

code improve locality (include spatial locality and temporal locality)
focus on inner loop



## Lecture 13 Linking

#### Why Linkers?
- modularity
- efficiency: 分离式编译 改动源文件不需要全部重新编译


#### What do linkers do
- step1: Symbol resolution（符号解析）
- step2: Relocation

