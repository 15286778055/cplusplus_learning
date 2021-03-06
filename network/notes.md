
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
