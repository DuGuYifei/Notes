# 数组filter

```JavaScript
handleDelete(name: string) {	
				originData = originData.filter((data) => data.user == name);
				console.log(originData);
			},
```

读json文件并filter
```JavaScript
function fetchAndDisplayUsers(obj: any) {
		let tableData = [];
		fetch('./src/assets/users.json')
			.then(response => response.json())
			.then(json => {
				originData = json;
				let i = 1;
				json.forEach(data => {
					tableData.push(new User(data, i++));
				});
				obj.filterTableData = computed(() =>
					tableData.filter(
						(data) =>
							!obj.search ||
							data.name.toLowerCase().includes(obj.search.toLowerCase())
					));
			});
	}
```