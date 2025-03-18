# get做属性时动态更新

```js
	rotors : {
		r1 : {
			velocity : 0,
			torque : 0,
			torque_direction : 1,
		},
		r2 : {
			velocity : 0,
			torque : 0,
			torque_direction : -1,
		},
		r3 : {
			velocity : 0,
			torque : 0,
			torque_direction : 1,
		},
		r4 : {
			velocity : 0,
			torque : 0,
			torque_direction : -1,
		},
		// calculate the total torque
		get total_torque() {
			return this.r1.torque + this.r2.torque + this.r3.torque + this.r4.torque;
		}
	},
```

这里的get使得可以直接通过`rotors.total_torque`来动态获取总扭矩，但如果
```js
rotors: {
	...
	total_torque : get total_torque() {},
}
```
就是错误的，因为这样的话，`rotors.total_torque`就是一个函数，而不是一个属性，所以不能直接通过`rotors.total_torque`来获取总扭矩，而是要通过`rotors.total_torque()`来获取总扭矩。