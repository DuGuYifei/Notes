# backward自动的实现原理-autograd-gradfn

在 PyTorch 中建立模型时，forward 函数的定义是必需的，因为它指定了模型的前向传播路径，即如何从输入数据得到输出结果。而 backward 函数通常不需要用户定义，因为它通过自动微分机制（autograd）自动处理。


loss.backward() 和 autograd 系统的联系并不是通过在构造函数中传递模型来实现的，而是通过 PyTorch 的动态计算图和 Tensor 的属性。

* 在 PyTorch 中，每个 Tensor 对象有一个属性 requires_grad，如果设置为 True，那么 PyTorch 会自动追踪在这个 Tensor 上进行的所有操作，并构建一个梯度函数图（计算图）。
* 当你通过模型进行前向传播并计算损失时，由于模型参数通常设定了 requires_grad=True，所有生成的输出和中间 Tensor 都会记录一个 grad_fn。这个 grad_fn 属性指向一个函数，该函数负责计算当前 Tensor 关于其输入 Tensor 的梯度。

* 当调用 loss.backward() 时，PyTorch 查找这个损失 Tensor 的 grad_fn 属性，然后从这里开始，逆向遍历整个计算图。grad_fn 是一个 Function 对象，它有一个 next_functions 属性，它指向了前一个 Tensor 的 grad_fn。
* 对于图中的每一个 Tensor，如果其 requires_grad 属性为 True，PyTorch 将使用链式法则自动计算其梯度，并将梯度累积到对应 Tensor 的 grad 属性中。

```python
import torch

a = torch.tensor(1.0, requires_grad=True)
b = torch.tensor(2.0, requires_grad=True)
c = a * b

print(c.grad_fn)  # 查看c的grad_fn
print(c.grad_fn.next_functions)  # 查看c.grad_fn的输入引用

#### 输出 ####
# <MulBackward0 object at 0x000001D8AC863D60>
# ((<AccumulateGrad object at 0x000001D8AC863D90>, 0), (<AccumulateGrad object at 0x000001D8AC863D30>, 0))
```

