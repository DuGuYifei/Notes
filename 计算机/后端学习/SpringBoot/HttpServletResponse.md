# HttpServletResponse

## 介绍

在使用Spring MVC框架时，我们可以通过在方法参数中使用HttpServletResponse对象来操作响应。

HttpServletResponse是Java Servlet API中的一个接口，它代表一个HTTP响应。在Java Web开发中，我们可以使用HttpServletResponse接口来设置和控制HTTP响应的一些属性和行为。

通过HttpServletResponse接口，我们可以实现以下操作：

1. 设置响应头信息（setHeader、addHeader、setContentType等）
2. 设置响应状态码（setStatus）
3. 获取输出流（getOutputStream）或字符输出流（getWriter）
4. 设置Cookie（addCookie）
5. 设置重定向（sendRedirect）
6. 设置缓存控制（setCacheControl、setDateHeader、setExpires等）

## 案例 - cookie token

```java

    @PostMapping(path = "/authorize", produces = "application/json")
    public ResponseEntity<SuccessResult> authorize(@RequestBody AuthorizeUserDto dto, HttpServletResponse response)
            throws Exception {
        ValidationRouter.validate(dto);
        String token = userService.authorize(dto);
        SuccessResult result = SuccessResult.builder().status(200).data(token).build();

        // Set the token as a cookie in the response
        Cookie cookie = new Cookie("token", token);
        cookie.setHttpOnly(true);
        cookie.setMaxAge(60 * 60 * 24 * 7); // set the cookie to expire in 1 week
        response.addCookie(cookie);
        return ResponseEntity.ok(result);
    }

```