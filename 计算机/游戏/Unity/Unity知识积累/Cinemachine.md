# Cinemachine

## follow 和 lookat
2d里 只需要 follow 因为视角固定不变

## Lens参数
1. Orthographic size: 画面大小

## Body参数
1. 类型： 
   1. transposer: 只有参数Damping
   2. framing transposer: 有不同色区了，高级点
2. Daming: 减震，影响摄像机跟随的速度，越小跟随越快（我觉得应该叫Dampling 阻尼）
   1. Yaw Damping：旋转
3. Screen X/Y: 偏移量 [0,1] 0.5 是居中
4. Soft Zone: 蓝区，缓慢跟随；红区，立刻跟随；
5. Bias X/Y: 红区偏移量
6. Dead Zone: 白区/死区，不跟随
7. Look ahead Time: 向前看一点，方向视区会变大
   1. Look ahead ignore y: 上下不用预判
