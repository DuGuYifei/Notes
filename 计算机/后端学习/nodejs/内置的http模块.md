# 内置的http模块

[XHR_AJAX_axios发送请求](../../%E8%AE%A1%E7%AE%97%E6%9C%BA%E8%AF%AD%E8%A8%80/JavaScript%E5%92%8CTypeScript/JavaScript/%E7%9F%A5%E8%AF%86%E7%A7%AF%E7%B4%AF/XHR_AJAX_axios%E5%8F%91%E9%80%81%E8%AF%B7%E6%B1%82.md)

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