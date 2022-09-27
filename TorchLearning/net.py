# 拟合问题

import torch
import matplotlib.pyplot as plt


class Net(torch.nn.Module):
    def __init__(self, n_feature, n_hidden, n_output):
        super(Net, self).__init__()
        # 定义每层的形式
        self.hidden = torch.nn.Linear(n_feature, n_hidden)  # 隐藏层线性输出
        self.hidden2 = torch.nn.Linear(n_hidden, n_hidden)
        self.predict = torch.nn.Linear(n_hidden, n_output)  # 输出层线性输出

    def forward(self, x):
        # 正向传播输入值，神经网络分析出输出值
        x = torch.relu(self.hidden(x)) # 线性＋激活函数
        x = torch.relu(self.hidden2(x))
        x = self.predict(x)
        return x


# 数据集
x = torch.unsqueeze(torch.linspace(-1, 1, 100), dim=1)
y = x.pow(2) + 0.2*torch.rand(x.size())
# 画图
# plt.scatter(x.data.numpy(), y.data.numpy())
# plt.show()


# 构建网络
# net = Net(n_feature=1, n_hidden=10, n_output=1)
# 快速搭建
net = torch.nn.Sequential(
    torch.nn.Linear(1, 10),
    torch.nn.ReLU(),
    torch.nn.Linear(10, 1)
)
# 打印网络
print(net)

# 训练网络
# 优化器
optimizer = torch.optim.SGD(net.parameters(), lr=0.2)
# 均方差
loss_func = torch.nn.MSELoss()  # 预测值和真实值的误差计算公式


# 可视化训练过程
plt.ion()
plt.show()


# 训练
for t in range(200):
    prediction = net(x)     # 输入训练数据x，输出预测值

    loss = loss_func(prediction, y)     # 计算误差

    optimizer.zero_grad()   # 清楚累计梯度
    loss.backward()         # 误差反向传播，计算参数更新值
    optimizer.step()        # 将参数更新值施加到 net 的 parameters 上

    # 每 5 次更新
    if t % 5 == 0:
        plt.cla()
        plt.scatter(x.data.numpy(), y.data.numpy())
        plt.plot(x.data.numpy(), prediction.data.numpy(), 'r-', lw=5)
        plt.text(0.5, 0, 'Loss=%.4f' % loss.data.numpy(), fontdict={'size': 20, 'color': 'red'})
        plt.pause(0.1)

# 保存网络
torch.save(net, 'net.pkl')      # 保存整个网络
torch.save(net.state_dict(), 'net_params.pkl')  # 只保存网络中的参数（速度快，占内存少）

# 提取网络
net2 = torch.load('net.pkl')    # 提取整个网络
prediction2 = net2(x)

net3 = torch.nn.Sequential(
    torch.nn.Linear(1, 10),
    torch.nn.ReLU(),
    torch.nn.Linear(10, 1)
)                               # 提取网络参数
net3.load_state_dict(torch.load('net_params.pkl'))
prediction3 = net3(x)

prediction1 = net(x)


if prediction1.equal(prediction2) and prediction1.equal(prediction3):
    print('True')
else:
    print('False')





