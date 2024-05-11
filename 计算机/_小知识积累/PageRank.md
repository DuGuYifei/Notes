# PageRank

## algorithm
The PageRank value for any page u can be expressed as:

$$PR(u) = \sum_{v \in B} \frac{PR(v)}{L(v)}$$

即页面 u 的 PageRank 值取决于包含在集合 B（包含链接到页面 u 的所有页面的集合）的每个页面 v 中的 PageRank 值除以来自页面 v 的链接数 L(v)。

**然后iteration，直到收敛。**

$$v'=M^nv_0$$ 

M是转移矩阵，v是PageRank向量，v'是迭代完n次的的PageRank向量。n是迭代多少代。

$$MMMMM...Mv_0$$

## example

## propagation
![](_attachments/old/2023-04-12-00-16-06.png)

![](_attachments/old/2023-04-12-00-16-48.png)

![](_attachments/old/2023-04-12-00-17-08.png)


## aggregation
![](_attachments/old/2023-04-12-00-17-38.png)

![](_attachments/old/2023-04-12-00-18-13.png)

## 2nd iteration
![](_attachments/old/2023-04-12-00-18-23.png)

## convergence 收敛
![](_attachments/old/2023-04-12-00-18-36.png)

## Spider Traps and Taxation

$$v' = βMv + (1 − β)e/n$$
