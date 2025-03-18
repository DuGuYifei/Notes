# numpy2string

```python
import numpy as np
# 遍历该子组下所有的dataset
for dset in dset_read.keys():
    # 获取dataset数据
    dset1 = f[group + '/' + subgroup + '/' + dset]
    print(dset1.name)
    f2.write(dset1.name + '\n')
    data = np.array(dset1)
    # print("data.shape=", str(data.shape))
    #------------------------------------------下面--------------------
    f2.write("data.shape=" + str(data.shape) + '\n')
    # print("data=\n", data)
    f2.write("data=\n")
    #------------------------------------------下面--------------------
    for i in range(len(data)):
        f2.write(str(data[i]) + '\n')
```