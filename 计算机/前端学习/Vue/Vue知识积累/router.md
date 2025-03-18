# router

## index.js
### 参数
path: 路径
name: 不重要


### 去掉井号
将`history: createWebHashHistory()`改为`history: createWebHistory()`


### 完整案例
```js
import {
	createRouter,
	createWebHashHistory,
	createWebHistory
} from "vue-router"

const routes = [
	{
		path: '',
		name: 'rootP',
		component: () => import('../views/animals/animal_list.vue')
	},
	{
		path: '/animals',
		name: 'Animals',
		component: () => import('../views/animals/animal_list.vue')
	},
	{
		path: '/animals/view',
		name: 'AnimalView',
		component: () => import ('../views/animals/animal_view.vue')
	},
	{
		path: '/animals/add',
		name: 'AnimalAdd',
		component: () => import ('../views/animals/animal_add.vue')
	},
	{
		path:'/pet',
		name:'PetView',
		component: () => import('../views/pets/pet_view.vue')
	},
	{
		path:'/pet/add',
		name:'PetAdd',
		component: () => import('../views/pets/pet_add.vue')
	},
]

const router = createRouter({
	history: createWebHistory(),
	routes
})

export default router
```

### 旧学习案例
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

## 跳转

### 带query参数案例
```js
// 跳转来源代码
goView(pet, animal){
	this.$router.push(
		{
			path: "/pet", 
			query: {
				pet: pet,
				animal: animal
			}
		}
	);
},
// 跳转目标代码
data() {
	return {
		id: this.$route.query.pet,
		petName: "petName",
		isSick: "false",
		animalName: this.$route.query.animal
	}
},
```