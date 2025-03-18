# createApp.use.mount


```js
import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

createApp(App).use(store).use(router).mount('#app')
```


## createApp
createApp() 从某个 .vue 文件创建一个app

## app.use
app.use() 使用一个插件 
```js
interface App {
  use(plugin: Plugin, ...options: any[]): this
}
```

第一个参数应是插件本身，可选的第二个参数是要传递给插件的选项。

插件可以是一个带 install() 方法的对象，亦或直接是一个将被用作 install() 方法的函数。插件选项 (app.use() 的第二个参数) 将会传递给插件的 install() 方法。

若 app.use() 对同一个插件多次调用，该插件只会被安装一次。

## app.mount
将应用实例挂载在一个容器元素中。