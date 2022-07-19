# hdf52txt

hdf5先分group， group里面还分不同的dataset

```python
import h5py
import numpy as np
import os

paths = os.listdir("./")

for path in paths:
    if path.endswith(".h5"):
        print(path.split('.')[0])
        f2 = open(path.split('.')[0] + '.txt', 'w', encoding='utf-8')
        # 打开文件
        f = h5py.File(path, 'r')
        # 遍历文件中的一级组
        for group in f.keys():
            print(group)
            # 根据一级组名获得其下面的组
            group_read = f[group]
            # 遍历该一级组下面的子组
            for subgroup in group_read.keys():
                print(subgroup)
                f2.write(subgroup)
                # 根据一级组和二级组名获取其下面的dataset
                dset_read = f[group + '/' + subgroup]
                # 遍历该子组下所有的dataset
                for dset in dset_read.keys():
                    # 获取dataset数据
                    dset1 = f[group + '/' + subgroup + '/' + dset]
                    print(dset1.name)
                    f2.write(dset1.name + '\n')
                    data = np.array(dset1)
                    # print("data.shape=", str(data.shape))
                    f2.write("data.shape=" + str(data.shape) + '\n')
                    # print("data=\n", data)
                    f2.write("data=\n")
                    for i in range(len(data)):
                        f2.write(str(data[i]) + '\n')
        f.close()
        f2.close()
```