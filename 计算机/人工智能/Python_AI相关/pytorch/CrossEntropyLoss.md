# CrossEntropyLoss

```python
torch.nn.CrossEntropyLoss(weight=None, size_average=None, ignore_index=-100, reduce=None, reduction='mean')
```

ignored_index: 忽略的index，比如-100，那么在计算loss的时候，这个index的loss会被忽略。不是说导数100个index，而是就直接index是-100的loss值不会被计算。