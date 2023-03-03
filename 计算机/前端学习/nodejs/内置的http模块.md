# 内置的http模块

[XHR_AJAX_axios发送请求](../../计算机语言/JavaScript和TypeScript/JavaScript/知识积累/XHR_AJAX_axios发送请求.md)

```javascript
const http = require('http');
const apiKey = 'YOUR_API_KEY_HERE';

const data = JSON.stringify({
  prompt: 'Hello, World!',
  max_tokens: 100,
  temperature: 0.7
});

const options = {
  hostname: 'api.openai.com',
  path: '/v1/engines/davinci-codex/completions',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    'Authorization': `Bearer ${apiKey}`
  }
};

const req = http.request(options, res => {
  let responseData = '';

  res.on('data', chunk => {
    responseData += chunk;
  });

  res.on('end', () => {
    const response = JSON.parse(responseData);
    console.log(response.choices[0].text);
  });
});

req.on('error', error => {
  console.error(error);
});

req.write(data);
req.end();

```