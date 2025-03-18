# 配置跨域_代理_url

## changeOrigin对跨域没什么卵用
[我误会了 changeOrigin 这么多年 - 掘金](https://juejin.cn/post/7151966465606811678)

更改host请求头，就是把后端收到的请求头信息中的host改为前端的名字，对跨域没什么卵用。

甚至在运行 HTTP/1.1 协议的网站中，请求头中要求携带 host 头。现在很多网站都已经支持了 HTTP/2 版本协议，它就不要求携带 host 请求了。

## rewrite
rewrite的作用就是将请求地址的/api去掉，如果不需要去掉api的话，不写rewrite就行。

## vue.config.js
[前端localhost调用本地localhost后端接口时的跨域问题_localhost 跨域_NJR10byh_migu的博客-CSDN博客](https://blog.csdn.net/NJR10byh/article/details/122694315)

### Step1：在vue.config.js中配置proxy
```js
module.exports = {
  publicPath: '/',
  outputDir: 'dist',
  assetsDir: 'static',
  lintOnSave: false,
  productionSourceMap: false,
  devServer: {
    proxy: {
      '/api': {
        target: 'http://localhost:端口号', // 配置好的后端接口地址
        changeOrigin: true,  // 无用，可删，默认false
        ws: true,
        pathRewrite: {
          '^/api': '' // 以'/api'开头的url会进行接口转发
        }
      }
    }
  },
}
```

### Step2：在main.js中配置axios
```js
// 引入axios
import axios from 'axios'
Vue.prototype.$axios = axios
axios.defaults.baseURL = '/api' // 一定要设置 axios.defaults.baseURL 为proxy中的转发头
```

## vite.config.js
```js
// vite.config.js

import { defineConfig } from "vite";

export default defineConfig({
  server: {
    proxy: {
      "/api": {
        target: "http://localhost:3001",
        changeOrigin: true, // 无用，可删，默认false
        rewrite: (path) => path.replace(/^\/api/, ""),
      },
    },
  },
});
```
`fetch("/api/posts");`


官方：[Vite](https://vitejs.dev/config/server-options.html#server-proxy)
```js
export default defineConfig({
  server: {
    proxy: {
      // string shorthand: http://localhost:5173/foo -> http://localhost:4567/foo
      '/foo': 'http://localhost:4567',
      // with options: http://localhost:5173/api/bar-> http://jsonplaceholder.typicode.com/bar
      '/api': {
        target: 'http://jsonplaceholder.typicode.com',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, ''),
      },
      // with RegEx: http://localhost:5173/fallback/ -> http://jsonplaceholder.typicode.com/
      '^/fallback/.*': {
        target: 'http://jsonplaceholder.typicode.com',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/fallback/, ''),
      },
      // Using the proxy instance
      '/api': {
        target: 'http://jsonplaceholder.typicode.com',
        changeOrigin: true,
        configure: (proxy, options) => {
          // proxy will be an instance of 'http-proxy'
        },
      },
      // Proxying websockets or socket.io: ws://localhost:5173/socket.io -> ws://localhost:5174/socket.io
      '/socket.io': {
        target: 'ws://localhost:5174',
        ws: true,
      },
    },
  },
})
```