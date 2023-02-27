# location.reload()

刷新界面`location.reload();`

这个方法还可以接受一个可选的布尔型参数，用来指定是否强制刷新页面而不使用缓存。如果这个参数设置为 true，则会强制刷新页面，而不是使用缓存。例如：
`location.reload(true);`


这个方法也可以使用 window 对象来调用：`window.location.reload();`

注意，在一些情况下，比如在使用 Vue.js 或 React.js 等现代前端框架的应用中，直接重新加载整个页面可能会破坏应用的状态和行为。这时候可以考虑使用框架提供的路由导航方法来切换页面。