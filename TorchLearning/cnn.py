import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torch.utils.data as Data
import torchvision


# Hyper Parameters
EPOCH = 1
BATCH_SIZE = 50
LR = 0.001
DOWNLOAD_MNIST = False

train_data = torchvision.datasets.MNIST(
    root='./mnist',
    train=True,
    transform=torchvision.transforms.ToTensor(),
    download=DOWNLOAD_MNIST
)

# plot one example
# print(train_data.train_data.size())
# print(train_data.train_labels.size())
# plt.imshow(train_data.train_data[0].numpy(), cmap='gray')
# plt.title('%i' % train_data.train_labels[0])
# plt.show()

train_loader = Data.DataLoader(dataset=train_data, batch_size=BATCH_SIZE, shuffle=True, num_workers=2)

test_data = torchvision.datasets.MNIST(root='./mnist', train=False)
test_x = torch.unsqueeze(test_data.test_data, dim=1).type(torch.FloatTensor)[:2000]/255.
test_y = test_data.test_labels[:2000]


# CNN 网络
class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.conv1 = nn.Sequential(
            nn.Conv2d(
                in_channels=1,  # ---> (1, 28, 28)
                out_channels=16,
                kernel_size=5,
                stride=1,
                padding=2,  # if stride = 1, padding = (kernel_size-1)/2
            ),        # 卷基层 过滤器 ---> (16, 28, 28)
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2)  # ---> (16, 14, 14)
        )
        self.conv2 = nn.Sequential(  # ---> (16, 14, 14)
            nn.Conv2d(16, 32, 5, 1, 2),     # ---> (32, 14, 14)
            nn.ReLU(),
            nn.MaxPool2d(2)                  # ---> (32, 7, 7)
        )
        self.out = nn.Linear(32*7*7, 10)

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)           # (batch, 32, 7, 7)
        x = x.view(x.size(0), -1)   # (batch, 32 * 7 * 7)
        output = self.out(x)
        return output

if __name__ == '__main__':

    cnn = CNN()
    print(cnn)

    # optimizer and loss
    optimizer = torch.optim.Adam(cnn.parameters(), lr=LR)
    loss_func = torch.nn.CrossEntropyLoss()

    # training and testing
    for epoch in range(EPOCH):
        for step, (x, y) in enumerate(train_loader):
            output = cnn(x)
            loss = loss_func(output, y)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            # 训练效果
            if step % 50 == 0:
                test_output = cnn(test_x)
                pred_y = torch.max(test_output, 1)[1].data.numpy().squeeze()
                accuracy = sum(pred_y == test_y.data.numpy()) / test_y.size(0)
                # print(type(accuracy))
                print('Epoch: ', epoch, '| train loss: %.4f' % loss, '| test accuracy: %.2f' % accuracy)