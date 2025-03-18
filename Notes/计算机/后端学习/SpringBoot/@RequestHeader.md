# @RequestHeader

## 1. 作用

用于获取请求头中的信息

## 2. 案例

```java
@GetMapping("/user/{id}")
public String updateUser(@PathVariable("id") Integer id, @RequestHeader("token") String token) {
	System.out.println("token: " + token);
	return "success";
}
```
