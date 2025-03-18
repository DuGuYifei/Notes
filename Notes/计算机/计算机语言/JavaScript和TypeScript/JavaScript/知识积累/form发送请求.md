# form发送请求

## form格式的请求
注意格式化那里，不用设置，limit会出错，让chrome自己默认写就行了。

```JS
const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function () {
    if (this.readyState === 4 && this.status === 200) {
        console.log("Pet created successfully");
    }
};
xhttp.open("POST", 'http://localhost:4030/api/files', true);
let file = this.$refs.ipt.files[0];
let formData = new FormData();
formData.append("name", file.name);
formData.append("author", this.author);
formData.append("description", this.description);
formData.append("file", file);
	
//xhttp.setRequestHeader('Content-Type', 'multipart/form-data');
xhttp.send(formData);
```