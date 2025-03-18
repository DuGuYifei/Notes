# Proxy和Reflect

## 用法
[ES6 中的Reflect和Proxy简单介绍_ANGWH的博客-CSDN博客](https://blog.csdn.net/ANGWH/article/details/107125398)

## 理论
[系统学习-1401Proxy和Reflect](../系统学习/1401Proxy和Reflect.md)

## 去掉Proxy
好像都不行，再遇到就再次尝试：

1. Proxy.revocable()
```javascript
const target = { foo: 'bar' };
const proxy = new Proxy(target, {});
const { proxy: unwrappedTarget } = Proxy.revocable(proxy, {});
console.log(unwrappedTarget === target);  // 输出: true
```

2. Object.getPrototypeOf()
```javascript
const target = { foo: 'bar' };
const proxy = new Proxy(target, {});
const unwrappedTarget = Object.getPrototypeOf(proxy);
console.log(unwrappedTarget === target);  // 输出: true
```