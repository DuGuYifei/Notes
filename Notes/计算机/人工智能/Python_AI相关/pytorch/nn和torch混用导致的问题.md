# nn和torch混用导致的问题

在学习VAE(Variational Autoencoder)的时候，我发现在使用`nn`模块的时候，如果和`torch`模块混用，会导致梯度计算出现问题。损失很早就停止下降了。

当时的问题是用了`torch.nn.linear`但是用了`torch.relu`。后来用了`nn.ReLU`就解决了。