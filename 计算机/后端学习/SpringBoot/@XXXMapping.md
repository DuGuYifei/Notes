# XXXMapping

## 介绍和基本使用
SpringMVC以前版本的*@RequestMapping*，到了新版本被下面新注释替代，相当于增加的选项：

* @GetMapping
* @PostMapping
* @PutMapping
* @DeleteMapping
* @PatchMapping

从命名约定我们可以看到每个注释都是为了处理各自的传入请求方法类型，即 *@GetMapping用于处理请求方法的GET类型，@ PostMapping用于处理请求方法的POST* 类型等。

如果我们想使用传统的 *@RequestMapping* 注释实现URL处理程序，那么它应该是这样的：

@RequestMapping(value = "/get/{id}", method = RequestMethod.GET)

新方法可以简化为：

@GetMapping("/get/{id}")

## 如何工作
所有上述注释都已在内部注释了 *@RequestMapping以及方法* 元素中的相应值。

例如，如果我们查看 *@GetMapping注释的源代码，我们可以看到它已经通过以下方式使用RequestMethod.GET* 进行了注释：
```java
@Target({ java.lang.annotation.ElementType.METHOD })
@Retention(RetentionPolicy.RUNTIME)
@Documented
@RequestMapping(method = { RequestMethod.GET })
public @interface GetMapping {
   // abstract codes
}
```

所有其他注释都以相同的方式创建，即 *@PostMapping使用RequestMethod.POST进行注释，@ PutMapping使用RequestMethod.PUT进行* 注释等。

## 代码示例
```java

```