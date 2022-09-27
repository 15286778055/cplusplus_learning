# 拟合问题

import torch
import matplotlib.pyplot as plt
import torch.utils.data as Data

LR = 0.01
BATCH_SIZE = 32
EPOCH = 12


class Net(torch.nn.Module):
    def __init__(self, n_feature, n_hidden, n_output):
        super(Net, self).__init__()
        # 定义每层的形式
        self.hidden = torch.nn.Linear(n_feature, n_hidden)  # 隐藏层线性输出
        # self.hidden2 = torch.nn.Linear(n_hidden, n_hidden)
        self.predict = torch.nn.Linear(n_hidden, n_output)  # 输出层线性输出

    def forward(self, x):
        # 正向传播输入值，神经网络分析出输出值
        x = torch.relu(self.hidden(x)) # 线性＋激活函数
        # x = torch.relu(self.hidden2(x))
        x = self.predict(x)
        return x


# 数据集
x = torch.unsqueeze(torch.linspace(-1, 1, 1000), dim=1)
y = x.pow(2) + 0.1*torch.normal(torch.zeros(*x.size()))
# 画图
# plt.scatter(x.data.numpy(), y.data.numpy())
# plt.show()


# 构建网络
net_SGD = Net(n_feature=1, n_hidden=20, n_output=1)
net_Momentum = Net(n_feature=1, n_hidden=20, n_output=1)
net_RMSprop = Net(n_feature=1, n_hidden=20, n_output=1)
net_Adam = Net(n_feature=1, n_hidden=20, n_output=1)
nets = [net_SGD, net_Momentum, net_RMSprop, net_Adam]



# 快速搭建
# net = torch.nn.Sequential(
#     torch.nn.Linear(1, 10),
#     torch.nn.ReLU(),
#     torch.nn.Linear(10, 1)
# )
# # 打印网络
# print(net)


# data loader
torch_dataset = Data.TensorDataset(x, y)
loader = Data.DataLoader(
    dataset=torch_dataset,
    batch_size=BATCH_SIZE,
    shuffle=True,
    num_workers=2
)





# 训练网络
# 优化器
opt_SGD = torch.optim.SGD(net_SGD.parameters(), lr=LR)
opt_Momentum = torch.optim.SGD(net_Momentum.parameters(), lr=LR, momentum=0.8)
opt_RMSprop = torch.optim.RMSprop(net_RMSprop.parameters(), lr=LR, alpha=0.8)
opt_Adam = torch.optim.Adam(net_Adam.parameters(), lr=LR, betas=(0.9, 0.99))
optimizers = [opt_SGD, opt_Momentum, opt_RMSprop, opt_Adam]



# 均方差
loss_func = torch.nn.MSELoss()  # 预测值和真实值的误差计算公式
losses_his = [[], [], [], []]

# 可视化训练过程
plt.ion()
plt.show()

if __name__ == '__main__':

    # 训练
    for epoch in range(EPOCH):
        for step, (b_x, b_y) in enumerate(loader):
            # 对每个优化器，优化属于他的神经网络
            for net, opt, l_his in zip(nets, optimizers, losses_his):
                output = net(b_x)
                loss = loss_func(output, b_y)
                opt.zero_grad()
                loss.backward()
                opt.step()
                l_his.append(loss.data.numpy())

    labels = ['SGD', 'Monmentum', 'RMSprop', 'Adam']
    for i, l_his in enumerate(losses_his):
        plt.plot(l_his, label=labels[i])
    plt.legend(loc='best')
    plt.xlabel('Steps')
    plt.ylabel('Loss')
    plt.ylim((0, 0.2))
    plt.show()