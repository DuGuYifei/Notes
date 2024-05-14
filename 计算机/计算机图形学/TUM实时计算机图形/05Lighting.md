# Lighting

## 1. 光照

照亮模型需要：
1. 光源属性（比如光强度，颜色，位置等）
2. 外观属性（比如反射，吸收等）

首先，我们看到的反射光会受表面接收到多少光影响。接收到的光取决于表面对光源的朝向。

## 2. 表面朝向

### 2.1 Lambert反射模型

Lambert反射模型：表面朝向和光线朝向之间的夹角越小，反射光越强。

有效照亮面积: dA = dA´ / cosθ

每单位面积的光照强度：$dE = cos\theta \cdot L_i(\omega)d\omega$

($\omega$是入射角)

个人理解：就是在法向量上的光强度。下面都可以这么理解。

![alt text](_attachments/05Lighting/image-2.png)

### surface normal

tangent plane + normal vector(normalize to 1)

#### Per-vertex normal

##### 标准化法线

![alt text](_attachments/05Lighting/image.png)

$$\vec{N_v}=\sum_{i=1}^{k}\vec{N_i}/||\sum_{i=1}^{k}\vec{N_i}||$$

##### 中心差分法

[中心差分法](../计算机图形学知识积累/中心差分法计算法线.md)

##### 保存格式

1. 存储为$n_i$ ([obj文件格式](../计算机图形学知识积累/obj文件格式.md))
2. render时候，插值计算

![alt text](_attachments/05Lighting/image-1.png)

##### Light reflection(光反射)

###### 粗糙材料的漫反射（Lambertian reflection）

1. 无论入射方向，都均匀散射
2. $k_d$是漫反射系数,范围$[0,1]$
3. $I_i$是光源强度, $I_r$是反射光强度
4. $n$是法向量

$$I_r(x,\omega_r)=k_d(n\cdot l_i)I_i(x,\omega_i)$$

![alt text](_attachments/05Lighting/image-3.png)

###### 镜面反射
1. 光主要反射到镜像方向周围
2. $k_s$是镜面反射系数，范围$[0,1]$
3. $n$是镜面指数/高光指数，控制高光的范围
4. r是反射方向，v是视线方向（相机方向）
5. $I_i$是光源强度, $I_r$是反射光强度

$$I_r(x,\omega_r)=k_s(r\cdot v)^nI_i(x,\omega_i)$$

![alt text](_attachments/05Lighting/image-4.png)


## 3. 光照模型（暂定）

* Gouraud Shading，着色应用在顶点上，用顶点的法线算出顶点的颜色，然后面内部像素的颜色用顶点的颜色进行插值的方法得出。
* Phong shading着色应用在每个像素上，同样是求面的顶点法线，然后面内部的每个像素的法线用插值的方法得出，再计算每个像素的颜色

