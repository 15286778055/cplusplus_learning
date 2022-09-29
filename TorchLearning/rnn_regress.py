import torch
from torch import nn
import numpy as np
import torch.utils.data as Data
import torchvision
import matplotlib.pyplot as plt


torch.manual_seed(1)  # reproducible

# Hyper Parameters
TIME_STEP = 10  # rnn 时间步数 / 图片高度
INPUT_SIZE = 1  # rnn 每步输入值 / 图片每行像素
LR = 0.02  # learning rate
DOWNLOAD_MNIST = False  # 如果你已经下载好了mnist数据就写上 Fasle

# # Mnist
# train_data = torchvision.datasets.MNIST(
#     root='./mnist',
#     train=True,
#     transform=torchvision.transforms.ToTensor(),
#     download=DOWNLOAD_MNIST
# )
#
#
# test_data = torchvision.datasets.MNIST(root='./mnist', train=False)

# # 批训练
# train_loader = Data.DataLoader(
#     dataset=train_data,
#     batch_size=BATCH_SIZE,
#     shuffle=True
# )
#
# # 只测试前 2000 个
# test_x = torch.unsqueeze(test_data.test_data, dim=1).type(torch.FloatTensor)[:2000] / 255.
# test_y = test_data.test_labels[:2000]
#
# test_x = test_x.view(-1, TIME_STEP, INPUT_SIZE)


# RNN
class RNN(nn.Module):
    def __init__(self):
        super(RNN, self).__init__()

        self.rnn = nn.RNN(
            input_size=1,
            hidden_size=32,
            num_layers=1,
            batch_first=True
        )

        self.out = nn.Linear(32, 1)

    def forward(self, x, h_state):              # hidden state 连续，要一直传递这个state
        # x shape (batch, time_step, input_size)
        # r_out shape (batch, time_step, output_size)
        # h_state shape (n_layers, batch, hidden_size)
        r_out, h_state = self.rnn(x, h_state)

        outs = []        # 保存所有时间点的预测值
        for time_step in range(r_out.size(1)):
            outs.append(self.out(r_out[:, time_step, :]))
        return torch.stack(outs, dim=1), h_state


rnn = RNN()
print(rnn)

# 训练
# 优化器 loss
optimizer = torch.optim.Adam(rnn.parameters(), lr=LR)
loss_func = nn.MSELoss()

h_state = None

# plt.figure(1, figsize=(12, 5))
plt.ion()
plt.show()

for step in range(100):
    start, end = step * np.pi, (step+1)*np.pi       # time steps
    # sin 预测 cos
    steps = np.linspace(start, end, 10, dtype=np.float32)
    x_np = np.sin(steps)
    y_np = np.cos(steps)
    # print('x_np shape', x_np.shape)
    # print('y_np shape', y_np.shape)

    x = torch.from_numpy(x_np[np.newaxis, :, np.newaxis])       # shape (batch, time_step, input_size)
    y = torch.from_numpy(y_np[np.newaxis, :, np.newaxis])

    # print('x size, ', x.size())
    # print('y size, ', y.size())

    prediction, h_state = rnn(x, h_state)
    # print(prediction.size())
    # print(h_state.size())
    print(prediction.size())
    h_state = h_state.data

    loss = loss_func(prediction, y)
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    print('Step: ', step, '| train loss: %.4f' % loss)


    # plt.cla()
    plt.plot(steps, y_np.flatten(), 'r-')
    plt.plot(steps, prediction.data.numpy().flatten(), 'b-')
    plt.draw()
    plt.pause(0.05)
