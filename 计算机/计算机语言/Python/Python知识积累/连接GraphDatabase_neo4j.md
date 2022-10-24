# 连接GraphDatabase_neo4j

```py
from py2neo import *
import numpy as np
import matplotlib.pyplot as plt

name = "Gala"
# name = "Gumayusi"
role = "ADC"

graph = Graph('bolt://localhost:11003', auth=("neo4j", "******"))

query = "MATCH (p:Player) - [:IS_MEMBER_OF] -> (t:Team) - [:FIGHT_IN] -> (m:Match) <- [a:ATTEND] - (p) " \
        "with t, sum(a.kill) as team_ka, sum(a.damage) as team_dmg, sum(a.gold) as team_gold " \
        "MATCH (p:Player) - [:IS_MEMBER_OF] -> (t) - [:FIGHT_IN] -> (m) <- [a:ATTEND] - (p) " \
        "WHERE p.role = \"" + role +"\" " \
        "WITH " \
        "(sum(a.kill) + sum(a.assistance))/sum(a.death) as KDA, " \
        "sum(a.damage) / toFloatOrNull(sum(m.duration)) * 60 as DPM, " \
        "sum(a.gold) / toFloatOrNull(sum(m.duration)) * 60 as GPM, " \
        "sum(a.kill + a.assistance)/toFloatOrNull(team_ka) as KP_Percent," \
        "sum(a.damage)/toFloatOrNull(team_dmg) as DMG_Percent," \
        "(sum(a.damage)/toFloatOrNull(team_dmg))/(sum(a.gold)/ toFloatOrNull(team_gold)) as DGCR " \
        "RETURN " \
        "max(KDA) as KDA, max(DPM) as DPM, max(GPM) as GPM, max(KP_Percent) as KP_Percent, max(DMG_Percent) as DMG_Percent, max(DGCR) as DGCR;"

max_results = graph.run(query).data()

# print(max_results[0]["KDA"])

coefficient = [100 / max_results[0]["KDA"], 100 / max_results[0]["DPM"], 100 / max_results[0]["GPM"],
               100 / max_results[0]["KP_Percent"], 100 / max_results[0]["DMG_Percent"], 100 / max_results[0]["DGCR"]]

# print(coefficient)

query = "MATCH (p:Player) - [:IS_MEMBER_OF] -> (t:Team) - [:FIGHT_IN] -> (m:Match) <- [a:ATTEND] - (p) " \
        "WITH t, sum(a.kill) as team_ka, sum(a.damage) as team_dmg, sum(a.gold) as team_gold " \
        "MATCH (p:Player) - [:IS_MEMBER_OF] -> (t) - [:FIGHT_IN] -> (m) <- [a:ATTEND] - (p) " \
        "WHERE p.name = \"" + name + "\"" \
                                     "RETURN " \
                                     "(sum(a.kill) + sum(a.assistance))/sum(a.death) as KDA," \
                                     "sum(a.damage) / toFloatOrNull(sum(m.duration)) * 60 as DPM," \
                                     "sum(a.gold) / toFloatOrNull(sum(m.duration)) * 60 as GPM," \
                                     "sum(a.kill + a.assistance)/toFloatOrNull(team_ka) as KP_Percent," \
                                     "sum(a.damage)/toFloatOrNull(team_dmg) as DMG_Percent," \
                                     "(sum(a.damage)/toFloatOrNull(team_dmg))/(sum(a.gold)/ toFloatOrNull(team_gold)) as DGCR;"

# print(graph.run(query).data())
results = graph.run(query).data()

# 解决中文显示问题
plt.rcParams['font.sans-serif'] = ['KaiTi']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题
plt.style.use('ggplot')  # 设置ggplot样式

data_length = len(results[0])

angles = np.linspace(0, 2 * np.pi, data_length, endpoint=False)  # 将极坐标根据数据长度进行等分

# 分离属性字段和数据
labels = [key for key in results[0].keys()]
score = [[v for v in result.values()] for result in results]

for i in range(6):
    score[0][i] = score[0][i] * coefficient[i]

# 使雷达图数据封闭
angles = np.concatenate((angles, [angles[0]]))
labels = np.concatenate((labels, [labels[0]]))
score_player = np.concatenate((score[0], [score[0][0]]))

# 设置图形的大小
fig = plt.figure(figsize=(6, 8))

# 新建一个子图
ax = plt.subplot(111, polar=True)

# 绘制角度轴和框线
for j in np.arange(0, 100 + 20, 20):
    ax.plot(angles, 7 * [j], '-.', lw=0.5, color='black')  # 沿半径方向的等值线
for j in range(5):
    ax.plot([angles[j], angles[j]], [0, 100], '-.', lw=0.5, color='black')  # 绘制角度轴

# 绘制雷达图并填充颜色
ax.plot(angles, score_player, color='orange')
ax.fill(angles, score_player, color='orange', alpha=0.4)

# 设置雷达图中每一项的标签显示
ax.set_thetagrids(angles * 180 / np.pi, labels, fontsize=15)

ax.set_theta_zero_location('E')  # 设置0度坐标轴起始位置，东西南北

ax.set_rlim(0, 100)  # 设置雷达图的坐标刻度范围

ax.set_title("Adc professional player ability chart - " + name)

plt.show()
```