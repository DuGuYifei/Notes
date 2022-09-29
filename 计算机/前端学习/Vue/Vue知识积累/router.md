# router

```js
import {
	createRouter,
	createWebHashHistory
} from "vue-router";

createWebHashHistory()

const routes = [{
	path: '/login',
	name: 'Login',
	component: () => import('../views/login')
}]

const router = createRouter({
	history: createWebHashHistory(),
	routes
})
```

也可以：
```js
import {
	createRouter,
	createWebHashHistory
} from "vue-router";

import Login from '../views/login'

createWebHashHistory()

const routes = [{
	path: '/login',
	name: 'Login',
	component: Login
}]

const router = createRouter({
	history: createWebHashHistory(),
	routes
})
```