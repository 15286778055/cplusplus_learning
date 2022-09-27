import torch
import torch.utils.data as Data
torch.manual_seed(1)   # reproducible 可重现

BATCH_SIZE = 5

x = torch.linspace(1, 10, 10)
y = torch.linspace(10, 1, 10)

# 转换成 torch 能识别的 Dataset
torch_dataset = Data.TensorDataset(x, y)

# 把 dataset 放入 DataLoader
loader = Data.DataLoader(
    dataset=torch_dataset,
    batch_size=BATCH_SIZE,
    shuffle=True,
    num_workers=2
)


if __name__ == '__main__':

    for epoch in range(3):
        for step, (batch_x, batch_y) in enumerate(loader):
            # 训练
            # ...
            # ...

            # 打印 batch 的数据
            print('Epoch: ', epoch, '| Step: ', step, '| batch x: ',
                  batch_x, '| batch y: ', batch_y)

