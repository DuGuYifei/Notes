# 读取和写入json


## 读取
[Javascript——读取json文件方法总结_js读取json文件_helloyangkl的博客-CSDN博客](https://blog.csdn.net/helloyangkl/article/details/126644237)

1. fetch
    ```javascript
    fetch('./data.json')
        .then((response) => response.json())
        .then((json) => console.log(json));

    fetch('https://server.com/data.json')
        .then((response) => response.json())
        .then((json) => console.log(json));
    ```

    注意：npm项目路径应该是：`./src/...`
2. import (有些特殊问题，详见上面链接)


## 写入
1. xhr/fetch 得有服务器端
   ```javascript
    fetch('/save', {
      method: 'POST',
      body: jsonData,
      headers: {
        'Content-Type': 'application/json'
      }
    }).then(response => {
      console.log('数据已保存到文件');
    });
   ```
2. localstorage 不好用，只是存到f12应用程序
   ```javascript
    let jsonData = JSON.stringify(originData);
    localStorage.setItem('data.json', jsonData);
   ```
3. fs服务器端
   ```javascript
    const fs = require('fs');

    const data = [1, 2, 3, 4, 5];
    const jsonData = JSON.stringify(data);

    fs.writeFile('data.json', jsonData, (err) => {
      if (err) throw err;
      console.log('数据已写入到文件');
    }); 

   ```

4. 下载文件的方式
   ```javascript
   downloadFile(data, type, filename) {
    	let blob = new Blob([data], {
    		type
    	});
    	let url = URL.createObjectURL(blob);
    	let link = document.createElement('a');
    	link.download = filename;
    	link.href = url;
    	document.body.appendChild(link);
    	link.click();
    	document.body.removeChild(link);
    	URL.revokeObjectURL(url);
    },


    handleDelete(name: string) {
    	originData = originData.filter((data) => data.user != name);
    
    	let jsonData = JSON.stringify(originData);
    
    	let type = 'application/json';
    	let filename = './scr/assets/users.json';
    	this.downloadFile(jsonData, type, filename);
    },
    ```