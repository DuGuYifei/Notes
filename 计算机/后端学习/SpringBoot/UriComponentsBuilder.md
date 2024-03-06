# UriComponentsBuilder

## 介绍
[UriComponentsBuilder 拼接URL、解析URL_sayyy的博客-CSDN博客](https://blog.csdn.net/sayyy/article/details/116976772)

```Java
String url = UriComponentsBuilder.fromUriString("http://mydomain/api/getToken")
									.queryParam("appid", "123")
									.queryParam("appsecret", "secret123")
									.build().encode().toString();
System.out.println(url);
————————————————
版权声明：本文为CSDN博主「sayyy」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/sayyy/article/details/116976772
```

这段代码可以得到：`http://mydomain/api/getToken?appid=123&appsecret=secret123`

这段代码实际做了几件事：
1. 实例化 UriComponentsBuilder 。`UriComponentsBuilder.fromUriString("http://mydomain/api/getToken")`
2. 设置 UriComponentsBuilder 实例。`.queryParam("appid", "123").queryParam("appsecret", "secret123")`
3. 创建 UriComponents 实例。`.build()`
4. 设置 UriComponents 实例。`.encode()`
5. UriComponents 实例转成字符串。`.toString()`


## 参数生成uri
```Java
uriComponentsBuilder
                .pathSegment("api", "back-manager", "keys", "{id}")
                .buildAndExpand(key.getId())
                .toUri()
```