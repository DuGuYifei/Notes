# value—index数组循环

JavaScript里是（value，index）对，是反过来的。

```html
    let arr = ['123','qwewq','sfds'];
    arr.map(function(value,index){
    console.log(value,index);
    });
    // 输出结果 '123',1  'qwewq',2  'sfds',3
```

```html
<h2 v-for="item in vegetables" v-bind:title="item.name">
    {{ item.name }}
</h2>
```