# mounted加载时执行

```javascript
export default {
		data() {
			return {
				animalArr: []
			}
		},
		methods: {
			delAnimal(animal){
				deleteAnimal(animal, this)
			},
			goAdd(){
				this.$router.push("/animals/add");
			},
			goView(animal){
				this.$router.push(
					{
						path: "/animals/view", 
						query: {
							animal: animal
						}
					}
				);
			}
		},
		mounted:function () { 
			fetchAndDisplayAnimals(this);
		},
	};
```