
## 第一章

- ### 网络边缘
- ### 网络核心
- ### 接入网



### 1.2 网络边缘
- 端系统（主机）
- C/S（client-server）模式
- 对等（peer-peer）模式

面向连接：TCP
- 可靠
- 流量控制（发送、接收方）
- 拥塞控制（链路）

无连接：UDP
- 不可靠
- 无流量控制
- 无拥塞控制
- 适合实时多媒体应用



### 1.3 网络核心

- 通信网络
  - 电路交换网络
    - FDM
    - TDM
  - 分组交换网络
    - 虚电路网络
    - 数据报网络

- 电路交换（`独享`资源-性能保障、传统电话网络采用）
- 分组交换（package switch，分组、转发、存储、再转发，存储转发避免整条线路被独占，`共享性`、存储延迟、`排队、延迟`，分组丢弃）

带宽分片：
- 频分（FDM、按照`频率`分）
- 时分（TDM、有点像计算机`时间片`的概念）
- 波分（光通信、按照`波段`分）

- 码分

计算机间通信具有突发性，如果使用线路交换，则浪费的片较多

##### 网络核心的关键功能
- `路由`（全局、分组由源到目标的路径、路由算法、路由表）
- `转发`（局部、将分组从路由器的输入链路转移到输出链路）

分组交换：统计多路复用（复杂的TDM）、适合突发性网络应用

##### 分组交换网络 存储-转发
按照由于网络层的连接，分成：
1. `数据报`网络
   - 无需建立连接（`无连接`，不维护主机间通信状态，分组到来就转走）
   - 每个分组独立路由
   - 路由器根据分组的目标地址进行路由
2. `虚电路`网络（`有连接`，有连接体现在中间所有交换节点之上，维护链路通信状态）

有连接：中间路由器维护他们通信状态
面向连接：仅仅体现在端系统和tcp实体上，中间路由器不维护通信状态


### 1.4 接入网和物理媒体

- 住宅接入：modem（调制解调器）、
  - 电话调制解调器
  - DSL
  - 电网
- 企业接入：
  - 交换机级联
- 无线
  - 无线 LANs
  - 广域无线接入（基站）

##### 物理媒体
物理链路
双绞线
同轴电缆
光缆
无线链路：地面微波、LAN（e.g.,wifi）、wide-area（e.g.,蜂窝）、卫星


### 1.5 Internet结构、ISP

网络的网络
ISP
ICP
IXP(Internet Exchange Point)



### 1.6 分组延迟、丢失、吞吐量

产生原因
- 排队延迟：分组到达路由器速率 > 链路输出能力
- 分组丢失：分组等待排到队头（超过路由器缓存容量）

延迟
- 分组延时
  - `处理延迟`：检查bit级差错、检查分组首部和决定将分组导向何处
  - `排队延时`：队列长度/处理速度
  - `传输延时`：分组长度/链路带宽
  - `传播延时`：物理链路长度/在媒体上传播速度

术语
RTT：Round Trip Time 往返延时
TTL：生存时间
ICMP

`吞吐量`（瞬时、平均）：源端和目标端之间的传输速率

`瓶颈链路`：端到端路径上，限制端到端吞吐的链路



### 1.7 协议层次、服务模型

##### 建模方法
- `模块化`(也是一种`对功能封装`)
- `分层`（按照`流程`考虑、`串行封装`、协议）

##### 术语
SAP（Service Access Point）：例如 套接字 Socket 区分不同服务用户 处于层间

PDU（Protocol Data Unit）的不同叫法
- 报文
- 报文段
- 分组（IP数据报）
- 帧
- 位

##### Internet 协议栈
应用层：提供网络应用服务
传输层：将端到端细分为进程到进程，不可靠通信变为可靠通信
网络层：为数据报从源到目的选择路由（转发、路由）
链路层：相邻网络节点间的数据传输
物理层：线路上传bit


### 1.8 历史
线路交换 ---> 分组交换




## 第二章 应用层

### 2.1 应用层协议原理

？？？查一下前面章节讲到的一些术语 SDU，主要是封装PDU的那部分

网络应用体系架构
- C/S
  - 服务端扩展性差
- P2P
- 混合

`分布式进程通信`需要解决的问题：
1. 进程标识和寻址：IP（32位地址） port TCP/UDP
2. 传输层 --- 应用层可利用的服务：源、目的、货物本身（本层SDU）、TCP/UDP
3. 应用层协议




一个端口只运行一个进程？？？

TCP Socket：OS 在应用层、传输层之间建立的 IO句柄（一个整数、会话关系）

UDP Socket：本地 IP、port的二元组


### 2.2 Web、HTTP

http1.0（持久） 1.1（非持久）
流水线方式的持久http

报文格式：
- 请求报文
- 响应报文


### 2.3 FTP


### 2.4 SMTP


### 2.5 DNS

- 命名
- 解析
- 维护





### 2 Transport


#### flow control 防止压倒接收方

#### two basic approaches
- stop and wait
  - 发送方仅发送一个包，发送之后同步等待
- sliding window 滑动窗口协议
  - sequence number space size 不太明白

#### Retransmission Strategies
- `go back n`
- `selective repeat`

#### TCP Header
![TCP Header](pics/2-10%20TCP%20Header.png)

#### TCP Setup and Teardown
- 三次握手
- 四次挥手

#### `end to end principle`

#### What i learned
- Transport Layer： TCP、UDP、ICMP
- How TCP works：Connections and Retransmissions
- How UDP works
- How ICMP works
- The End to End Principle



### 3 packet switching

why?
- efficient use of expensive links
- resilience to failure of links and routers


#### end to end delay 延迟
- propagation delay 传播延迟 取决于路程（fixed）
- packetization delay 打包延迟（传输延迟）（fixed）
- Queueing delay 数据包等待延迟（排队延迟）（variable）

路由器`存储`、`转发`，等到所有数据包到了，再转发，而且还要等待已经进入缓冲区的其他数据包，有了排队延迟。

一些实时应用使用`playback buffers`来避免可变的`排队延迟`
比如：b站、youtube视频播放缓冲

![end to end delay](pics/3.3%20end%20to%20end%20delay.png)


统计复用

排队延迟、占用率的举例不太看懂？？？？

#### queue properties
- burstiness increases delay
- Little's result: 占用 = 到达率 * 延迟


#### how a packet switch works

ethernet switch
![](pics/3.7%20ethernet%20switch.png)
internet router
![](pics/3.7%20internet%20router.png)


- lookup address
  - 最长前缀匹配（TCAM）
- switching
  - output queueing (minimizes packet delay)（FIFO，最小化延迟）
  - input queueing (with output queues to maximize throughput)（最大化吞吐量）




存储 转发，最小粒度？能够组成IP数据报？


#### 分组转发：`延迟`、`交换`
what i learned
- queueing delay and end to end delay
- why streaming applications use a playback buffer
- a simple deterministic queue model
- rate guarantees ???
- delay guarantees ???
- how packets are switched and forwarded




### 4 congestion control 防止压倒网络

`Max-min fairness`

- 实现
  - end host（Where TCP realizes）
  - int the internet

- silding window
  - R * RTT = Window size 发送速度和RTT的关系？？？
![](pics/4%20TCP%20silding%20window.png)

![](pics/4%20TCP%20congestion%20window%20size.png)

`TCP Strategy`：**`AIMD`**
![](pics/4%20AIMD.png)

![](pics/4%20little%20summary.png)



##### 路由器缓冲区大小
= RTT * C
![](pics/4%20buffer%20size1.png)

![](pics/4%20buffer%20size2.png)


#### when should you send new data? `TCP Tahoe`

![](pics/4%20TCP%20Tahole%20FSM.png)

![](pics/4%20TCP%20Tahole%20Behavior.png)


#### when should you send data retransmissions? `RTT Estimate`

![](pics/4%20TCP%20Tahole%20timeout.png)



#### when should you send acknowledgments? `self-clocking`

![](pics/4%20TCP%20self-coking.png)



#### More Modern TCP: `TCP Reno`

对 `timeout` 和 `triple same ack` 做不同处理

- 快恢复
- 快重传

- Tahoe
![](pics/4%20TCP%20Tahoe.png)
- Reno
![](pics/4%20TCP%20Reno.png)


#### TCP NewReno

在快速重传中发送新的数据包

- New Reno
![](pics/4%20TCP%20NewReno.png)

![Tahoe Reno NewReno Summary](pics/4%20TCP%20Reno%20Summary.png)


#### 性能提升：`fast retransmit`、`fast recovery`

![TCP Reno FSM](pics/4%20TCP%20Reno%20FSM.png)

 
AIMD flow, max-min fairness ???








### application and NAT



#### NAT

Strong end to end principle

NAT ip port 到 local machine ip port 的映射

Types of NATs
- Full Cone NAT (NAT IP、NAT Port)
- Restricted Cone NAT (NAT IP、NAT Port、External Sender IP)
- Port Restricted NAT (NAT IP、NAT Port、External Sender IP、External Sender Port)
- Symmetric NAT (Symmetric Mapping 内网同一个endpoint向外网不同的endpoint12建立链接，需要建立不同的映射关系)
- Hairpining


##### 分类
- Mapping Behavior (出):
  - Endpoint Independent Mapping
  - Address Dependent Mapping
  - Address and Port Dependent Mapping

- Filtering Behavior (进):
  - Endpoint Independent Filtering
  - Address Dependent Filtering
  - Address and Port Dependent Filtering

`NAT 打洞`，peer to peer 通信
Full Cone NAT、Restricted Cone NAT、Port Restricted NAT（三者都是Endpoint Independent Mapping，Filtering 策略不同） 都可以实现 NAT 打洞
[点击查看具体分析](https://www.modb.pro/db/251631)

