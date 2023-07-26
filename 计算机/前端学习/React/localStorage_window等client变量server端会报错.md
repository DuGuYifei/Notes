# localStorage_window等client变量server端会报错

## 问题描述
有时候会导致react报错 #425 #419 #423

## 解决
有关这些变量的代码一定要写到 useEffect 里。