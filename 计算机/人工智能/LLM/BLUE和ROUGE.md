# BLUE和ROUGE

也可以用到agent和rag评估。

- [对比](#对比)
- [BLUE](#blue)
  - [公式](#公式)
  - [案例](#案例)
- [ROUGE](#rouge)
  - [公式](#公式-1)
  - [案例](#案例-1)


## 对比

* BLEU分母是去重的，rouge分母是不去重的
* BLEU分母是生成的 n-gram 数，rouge分母是参考答案的 n-gram 数。
* 二者分子是相同的
* BLEU（precision）：在你生成的内容里，有多少是参考答案认可的（你说的有多“准”）。
* ROUGE（recall）：在参考答案的内容里，有多少被你生成出来了（你覆盖了多少“该说的”）。

## BLUE

BLEU（Bilingual Evaluation Understudy）是一种用于评估机器翻译质量的指标。它通过比较机器翻译输出与一个或多个参考翻译之间的n-gram重叠来计算得分。BLEU得分范围从0到1，得分越高表示机器翻译输出与参考翻译越接近。

### 公式

$$
p_n =
\frac{
\text{生成的能在答案中找到匹配的 n-gram 数}
}{
\text{生成的 n-gram 数}
}
$$

PS：一般带clip，即：某个单词生成次数是2，但参考答案里只有1个，那么这个单词的匹配数就是1。比如 `the cat is on the table` 里 `the` 出现了两次，但如果生成的句子里 `the` 出现了三次，那么`the`的匹配数就是2，下面案例原句里 `the` 出现了两次，但生成的句子里 `the` 只出现了一次，所以 `the` 的匹配数是1。

最终：

$$
BLEU = \text{长度惩罚} \times \text{多个 } p_n \text{ 的组合}
$$


### 案例

用一个例子，**把 BLEU 完整算一遍**。

我用这组句子：

* **Reference**: `the cat is on the table`
* **Generated**: `the cat is on table`

我们算 **BLEU-4**，也就是看 1-gram 到 4-gram，再乘上长度惩罚。

1. 先准备长度

Reference 长度

$$
r = 6
$$

因为有 6 个词：

`the | cat | is | on | the | table`

Generated 长度

$$
c = 5
$$

因为有 5 个词：

`the | cat | is | on | table`

---

2. 计算 1-gram precision

Generated 的 1-gram

`the`, `cat`, `is`, `on`, `table`

总数：
$$
\text{分母} = 5
$$

能匹配的 1-gram

Reference 里有：

* `the`，匹配 1 次
* `cat`，匹配 1 次
* `is`，匹配 1 次
* `on`，匹配 1 次
* `table`，匹配 1 次

匹配总数：
$$
\text{分子} = 5
$$

所以：

$$
p_1 = \frac{5}{5} = 1
$$

---

3. 计算 2-gram precision

Generated 的 2-gram

从左到右相邻两个词组成：

1. `the cat`
2. `cat is`
3. `is on`
4. `on table`

总数：
$$
\text{分母} = 4
$$

Reference 的 2-gram

1. `the cat`
2. `cat is`
3. `is on`
4. `on the`
5. `the table`

匹配情况

* `the cat` ✅
* `cat is` ✅
* `is on` ✅
* `on table` ❌

匹配总数：
$$
\text{分子} = 3
$$

所以：

$$
p_2 = \frac{3}{4} = 0.75
$$

---

4. 计算 3-gram precision

Generated 的 3-gram

1. `the cat is`
2. `cat is on`
3. `is on table`

总数：
$$
\text{分母} = 3
$$

Reference 的 3-gram

1. `the cat is`
2. `cat is on`
3. `is on the`
4. `on the table`

匹配情况

* `the cat is` ✅
* `cat is on` ✅
* `is on table` ❌

匹配总数：
$$
\text{分子} = 2
$$

所以：

$$
p_3 = \frac{2}{3}
$$

---

5. 计算 4-gram precision

Generated 的 4-gram

1. `the cat is on`
2. `cat is on table`

总数：
$$
\text{分母} = 2
$$

Reference 的 4-gram

1. `the cat is on`
2. `cat is on the`
3. `is on the table`

匹配情况

* `the cat is on` ✅
* `cat is on table` ❌

匹配总数：
$$
\text{分子} = 1
$$

所以：

$$
p_4 = \frac{1}{2} = 0.5
$$

---

6. 长度惩罚 BP

BLEU 的长度惩罚是：

$$
BP =
\begin{cases}
1, & c > r \\
e^{1-r/c}, & c \le r
\end{cases}
$$

这里：

* (c = 5)
* (r = 6)

因为 (5 \le 6)，所以用第二个公式：

$$
BP = e^{1-6/5}
$$

$$
= e^{-0.2}
$$

$$
\approx 0.8187
$$

---

7. 组合 1 到 4 gram

BLEU-4 默认对 4 个 precision 等权重平均：

$$
BLEU = BP \cdot \exp\left(
\frac{1}{4}(\ln p_1 + \ln p_2 + \ln p_3 + \ln p_4)
\right)
$$

代入：

$$
BLEU = 0.8187 \cdot \exp\left(
\frac{1}{4}\left(\ln 1 + \ln 0.75 + \ln \frac{2}{3} + \ln 0.5\right)
\right)
$$

先算对数部分：

$$
\ln 1 = 0
$$

$$
\ln 0.75 \approx -0.2877
$$

$$
\ln \frac{2}{3} \approx -0.4055
$$

$$
\ln 0.5 \approx -0.6931
$$

相加：

$$
0 - 0.2877 - 0.4055 - 0.6931 = -1.3863
$$

再除以 4：

$$
\frac{-1.3863}{4} = -0.3466
$$

取指数：

$$
\exp(-0.3466) \approx 0.7071
$$

最后乘长度惩罚：

$$
BLEU = 0.8187 \times 0.7071 \approx 0.5789
$$

---

8. 最终结果

$$
\boxed{BLEU \approx 0.579}
$$

---

9. 所有分子分母汇总

| n-gram | 分子（匹配数） | 分母（生成总数） |    precision |
| ------ | -------------: | ---------------: | -----------: |
| 1-gram |              5 |                5 |    (p_1 = 1) |
| 2-gram |              3 |                4 | (p_2 = 0.75) |
| 3-gram |              2 |                3 |  (p_3 = 2/3) |
| 4-gram |              1 |                2 |  (p_4 = 0.5) |

长度惩罚：

$$
BP = e^{1-6/5} \approx 0.8187
$$

最终：

$$
BLEU = 0.8187 \times (1 \cdot 0.75 \cdot \frac{2}{3} \cdot 0.5)^{1/4}
\approx 0.579
$$

## ROUGE

ROUGE（Recall-Oriented Understudy for Gisting Evaluation）是一种用于评估自动文本摘要质量的指标。它通过比较自动生成的摘要与一个或多个参考摘要之间的重叠来计算得分。ROUGE得分范围从0到1，得分越高表示自动生成的摘要与参考摘要越接近。

### 公式
ROUGE-N 的公式：
$$
ROUGE\text{-}N = \frac{\text{匹配的 n-gram 数}}{\text{Reference 的 n-gram 总数}}
$$

最长公共子序列 Longest Common Subsequence - LCS

ROUGE-L 的公式：

1. 先计算最长公共子序列长度 LCS
2. 计算 recall 和 precision：
$$
R_{LCS} = \frac{LCS}{\text{Reference 长度}}
$$
$$
P_{LCS} = \frac{LCS}{\text{Generated 长度}}
$$
3. 最后计算 F 值：
$$
F = \frac{2PR}{P+R}
$$



### 案例

* **Reference**: `the cat is on the table`
* **Generated**: `the cat is on table`

---

1. ROUGE-1

ROUGE-1 看 **1-gram recall**：

$$
ROUGE\text{-}1 = \frac{\text{匹配的 1-gram 数}}{\text{Reference 的 1-gram 总数}}
$$

Reference 的 1-gram

`the`, `cat`, `is`, `on`, `the`, `table`

总数：
$$
\text{分母} = 6
$$

Generated 里能匹配上的 1-gram

`the`, `cat`, `is`, `on`, `table`

匹配总数：
$$
\text{分子} = 5
$$

所以：

$$
ROUGE\text{-}1 = \frac{5}{6} \approx 0.8333
$$

---

2. ROUGE-2

ROUGE-2 看 **2-gram recall**：

$$
ROUGE\text{-}2 = \frac{\text{匹配的 2-gram 数}}{\text{Reference 的 2-gram 总数}}
$$

Reference 的 2-gram

1. `the cat`
2. `cat is`
3. `is on`
4. `on the`
5. `the table`

总数：
$$
\text{分母} = 5
$$

Generated 的 2-gram

1. `the cat`
2. `cat is`
3. `is on`
4. `on table`

其中能匹配上的：

* `the cat`
* `cat is`
* `is on`

匹配总数：
$$
\text{分子} = 3
$$

所以：

$$
ROUGE\text{-}2 = \frac{3}{5} = 0.6
$$

---

3. ROUGE-L

ROUGE-L 看 **最长公共子序列**。

先找 Reference 和 Generated 的最长公共子序列。

* Reference: `the cat is on the table`
* Generated: `the cat is on table`

最长公共子序列是：

`the cat is on table`

长度：
$$
LCS = 5
$$

---

3.1 Recall

$$
R_{LCS} = \frac{LCS}{\text{Reference 长度}} = \frac{5}{6} \approx 0.8333
$$

---

3.2 Precision

$$
P_{LCS} = \frac{LCS}{\text{Generated 长度}} = \frac{5}{5} = 1
$$

---

3.3 F 值

ROUGE-L 常写成 F-measure。最简单先按 F1 理解：

$$
F = \frac{2PR}{P+R}
$$

代入：

$$
F = \frac{2 \cdot 1 \cdot \frac{5}{6}}{1 + \frac{5}{6}}
$$

$$
= \frac{\frac{10}{6}}{\frac{11}{6}} = \frac{10}{11} \approx 0.9091
$$

所以：

$$
ROUGE\text{-}L \approx 0.9091
$$

---
4. 汇总

| 指标              | 分子 | 分母 |   结果 |
| ----------------- | ---: | ---: | -----: |
| ROUGE-1           |    5 |    6 | 0.8333 |
| ROUGE-2           |    3 |    5 |    0.6 |
| ROUGE-L recall    |    5 |    6 | 0.8333 |
| ROUGE-L precision |    5 |    5 |    1.0 |
| ROUGE-L F1        |    - |    - | 0.9091 |

---

5. 和 BLEU 对比

同一个例子里：

* **BLEU** 分母用的是 **Generated**
* **ROUGE-N** 分母用的是 **Reference**

所以：

BLEU-1

$$
\frac{5}{5} = 1
$$

它在问：

> 你生成出来的内容里，有多少是对的？

---

ROUGE-1

$$
\frac{5}{6} = 0.8333
$$

它在问：

> 标准答案里的内容，你覆盖了多少？

---
