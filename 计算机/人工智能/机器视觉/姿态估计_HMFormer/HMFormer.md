# HMFormer

[GitHub - Vegetebird/MHFormer: [CVPR 2022] MHFormer: Multi-Hypothesis Transformer for 3D Human Pose Estimation](https://github.com/Vegetebird/MHFormer)

## 识别视频
```py
python demo/vis.py --video sample_video.mp4
```

### 参数输出的地方

在函数`get_pose3D(video_path, output_dir):` 中：
```py
## 3D
        fig = plt.figure(figsize=(9.6, 5.4))
        gs = gridspec.GridSpec(1, 1)
        gs.update(wspace=-0.00, hspace=0.05)
        ax = plt.subplot(gs[0], projection='3d')
        ax.set_xlabel('X Label')
        ax.set_ylabel('Y Label')
        ax.set_zlabel('Z Label')
        with open('points.txt', 'ab') as f:
            np.savetxt(f, post_out, delimiter="\n") # 在这里
            # print(post_out)
        show3Dpose(post_out, ax)

        output_dir_3D = output_dir + 'pose3D/'
        os.makedirs(output_dir_3D, exist_ok=True)
        plt.savefig(output_dir_3D + str(('%04d' % i)) + '_3D.png', dpi=200, format='png', bbox_inches='tight')
```

### 结果数据顺序

```
右                 左
         10
         9
16 15 14 8 11 12 13
         7
      1  0  4
      2     5
      3     6
```