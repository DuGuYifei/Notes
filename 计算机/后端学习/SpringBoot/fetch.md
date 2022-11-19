# @OneToMany的fetch

fetch：设置关联对象的加载方式

FetchType.EAGER：立即加载，比如在加载学生对象信息时，立刻加载学生的成绩信息

FetchType.LAZy：延迟加载，需要用到的时候再加载