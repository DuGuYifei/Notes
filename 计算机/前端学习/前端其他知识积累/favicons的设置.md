# favicons的设置

```html
<!-- 标准 favicon.ico，支持大多数浏览器 -->
<link rel="icon" href="/favicons/favicon.ico" type="image/x-icon">

<!-- PNG 格式 favicon，支持高清屏幕 -->
<link rel="icon" type="image/png" sizes="16x16" href="/favicons/favicon-16x16.png">
<link rel="icon" type="image/png" sizes="32x32" href="/favicons/favicon-32x32.png">

<!-- Apple Touch Icon，用于 iOS/iPadOS 添加到主屏幕 -->
<link rel="apple-touch-icon" sizes="180x180" href="/favicons/apple-touch-icon.png">

<!-- Android Chrome 图标（搭配 manifest） -->
<link rel="manifest" href="/favicons/site.webmanifest">
```

```json
{
  "name": "你的站点名称",
  "short_name": "简名",
  "icons": [
    {
      "src": "/favicons/android-chrome-192x192.png",
      "sizes": "192x192",
      "type": "image/png"
    },
    {
      "src": "/favicons/android-chrome-512x512.png",
      "sizes": "512x512",
      "type": "image/png"
    }
  ],
  "start_url": "/",
  "display": "standalone",
  "theme_color": "#ffffff",
  "background_color": "#ffffff"
}
```