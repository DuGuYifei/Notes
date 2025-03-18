# HttpServletRequest

## 介绍

HttpServletRequest是一个接口，它代表客户端的请求，由服务器创建并传递给Servlet。它提供了访问请求信息的方法，例如请求头，请求参数，请求方法，请求路径等。

## 案例 - 获取Cookie里的token

```java

	@GetMapping(path = "/user", produces = "application/json")
	public ResponseEntity<SuccessResult> getUser(HttpServletRequest request) throws Exception {
		Cookie[] cookies = request.getCookies();
		String token = null;
		for (Cookie cookie : cookies) {
			if (cookie.getName().equals("token")) {
				token = cookie.getValue();
			}
		}
		SuccessResult result = SuccessResult.builder().status(200).data(user).build();
		return ResponseEntity.ok(result);
	}

```