import torch
from torch import nn
import torch.utils.data as Data
import torchvision
import matplotlib.pyplot as plt


torch.manual_seed(1)    # reproducible

# Hyper Parameters
EPOCH = 1           # 训练整批数据多少次, 为了节约时间, 我们只训练一次
BATCH_SIZE = 64
TIME_STEP = 28      # rnn 时间步数 / 图片高度
INPUT_SIZE = 28     # rnn 每步输入值 / 图片每行像素
LR = 0.01           # learning rate
DOWNLOAD_MNIST = False  # 如果你已经下载好了mnist数据就写上 Fasle


# Mnist
train_data = torchvision.datasets.MNIST(
    root='./mnist',
    train=True,
    transform=torchvision.transforms.ToTensor(),
    download=DOWNLOAD_MNIST
)

# plot one example
# print(train_data.train_data.size())
# print(train_data.train_labels.size())
# plt.imshow(train_data.train_data[1].numpy(), cmap='gray')
# plt.title('%i' % train_data.train_labels[0])
# plt.show()

test_data = torchvision.datasets.MNIST(root='./mnist', train=False)

# 批训练
train_loader = Data.DataLoader(
    dataset=train_data,
    batch_size=BATCH_SIZE,
    shuffle=True
)

# 只测试前 2000 个
test_x = torch.unsqueeze(test_data.test_data, dim=1).type(torch.FloatTensor)[:2000]/255.
test_y = test_data.test_labels[:2000]

test_x = test_x.view(-1, TIME_STEP, INPUT_SIZE)

# RNN
class RNN(nn.Module):
    def __init__(self):
        super(RNN, self).__init__()

        self.rnn = nn.LSTM(
            input_size=28,      # 图片每行的数据像素点
            hidden_size=64,     # RNN hidden unit
            num_layers=1,       # 有几层 RNN layers
            batch_first=True    # input & output 以 batch_size 为第一维度的特征集 （batch, time_step, input_size）
        )

        self.out = nn.Linear(64, 10)

    def forward(self, x):
        # x shape (batch, time_step, input_size) (64, 28, 28)
        # r_out shape (batch, time_step, output_size)
        # h_n shape (n_layers, batch, hidden_size)
        # h_c shape (n_layers, batch, hidden_size)
        r_out, (h_n, h_c) = self.rnn(x, None)


        # 选取最后一个时间点上的 r_out 输出
        # 这里 r_out[:, -1, :] 的值也是 h_n 的值
        # print('x, ', x.size())
        # print(r_out.size())
        
        # 对比 CNN 的做法，CNN 是 resize 展平
        # 而 RNN，是取最后一个时间点上的 r_out
        
        
        out = self.out(r_out[:, -1, :])
        return out


rnn = RNN()
print(rnn)


# 训练
# 优化器 loss
optimizer = torch.optim.Adam(rnn.parameters(), lr=LR)
loss_func = nn.CrossEntropyLoss()

for epoch in range(EPOCH):
    for step, (x, b_y) in enumerate(train_loader):
        b_x = x.view(-1, 28, 28)            # reshape x to (batch, time_step, input_size)
        # print(b_x.size())

        output = rnn(b_x)
        loss = loss_func(output, b_y)
        # print(b_y.size())
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        # 测试
        if step % 50 == 0:
            # print(test_x.size())
            # print(test_y.size())
            test_output = rnn(test_x)
            pred_y = torch.max(test_output, 1)[1].data.numpy().squeeze()
            accuracy = sum(pred_y == test_y.data.numpy()) / test_y.size(0)
            # print(type(accuracy))
            print('Step: ', step, '| train loss: %.4f' % loss, '| test accuracy: %.2f' % accuracy)



        


