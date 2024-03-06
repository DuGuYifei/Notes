# 对于http请求返回的控制

1. [HttpBaseError类](#httpbaseerror类)
   1. [创建：](#创建)
   2. [使用：](#使用)
2. [@RestControllerAdvice](#restcontrolleradvice)
   1. [原理](#原理)
3. [@ControllerAdvice](#controlleradvice)
   1. [区别](#区别)
4. [@ResponseBody](#responsebody)
5. [@ExceptionHandler](#exceptionhandler)
6. [@ResponseStatus](#responsestatus)
7. [案例1](#案例1)
8. [案例2](#案例2)


## HttpBaseError类

throw这个error会被@RestControllerAdvice捕获，然后返回一个ResponseEntity对象，这个对象的body就是这个error对象。

### 创建：
```java
/**
 * This class represents a generic conflict error, which occurs when a resource
 * request conflicts with another resource.
 * It extends the HttpBaseError class.
 */
public class GenericConflictError extends HttpBaseError {

  /**
   * Constructs a new GenericConflictError object with the specified message.
   *
   * @param message the error message to display
   */
  public GenericConflictError(String message) {
    super(409, message);
  }

  /**
   * Constructs a new GenericConflictError object with the specified exception.
   *
   * @param e the exception that caused the error
   */
  public GenericConflictError(Exception e) {
    super(409, e);
  }
}
```

### 使用：
```java
throw new GenericConflictError("The user already exists");
```

## @RestControllerAdvice

### 原理

`@RestControllerAdvice`是`@ControllerAdvice`和`@ResponseBody`的组合注解，它是一个增强的Controller，里面使用了@ExceptionHandler、@InitBinder、@ModelAttribute注解的方法都会作用在所有的@RequestMapping注解的方法上。

## @ControllerAdvice

@ControllerAdvice是一个@Component，它会被@ComponentScan扫描到，所以我们无需在使用的时候再次添加@Component注解。作用是将对于控制器的全局配置放置在同一个位置，注解了@Controller的类的方法可以使用@ExceptionHandler、@InitBinder、@ModelAttribute注解到方法上。

### 区别
1. 和RestControllerAdvice不同的是，ControllerAdvice不会将返回值转换为json格式。
2. @ControllerAdvice用于处理传统的Spring MVC控制器（**Controller**）。这些控制器返回的是视图（View）或模型与视图（ModelAndView），主要用于传统的Web应用程序。@ControllerAdvice注解的类可以包含异常处理方法，用于捕获控制器方法中抛出的异常，并进行适当的处理。
3. @RestControllerAdvice用于处理基于RESTful风格的控制器（**RestController**）。这些控制器返回的是数据（通常是JSON或XML），主要用于构建Web服务的后端。@RestControllerAdvice注解的类可以包含异常处理方法，用于捕获RESTful控制器方法中抛出的异常，并以适当的方式返回错误响应。
4. @RestControllerAdvice是@ControllerAdvice和@ResponseBody的组合注解。

## @ResponseBody

@ResponseBody注解表示该方法的返回结果直接写入HTTP response body中，一般在异步获取数据时使用，通常是在使用@RequestMapping后，返回值通常解析为跳转路径，加上@ResponseBody后返回结果不会被解析为跳转路径，而是直接写入HTTP response body中。比如异步获取json数据，加上@ResponseBody后，会直接返回json数据。

## @ExceptionHandler

@ExceptionHandler用于全局处理控制器里的异常。@ExceptionHandler标记的方法为异常处理方法，其作用范围为标记的方法所在的类内。@ExceptionHandler方法可以直接在方法签名中传入Exception类型的参数，也可以加入BindingResult、WebRequest/WebRequest、Locale等任意参数。@ExceptionHandler方法的返回值可以是ModelAndView、String、View、Map、Model或者@ResponseBody注解的对象等。如果返回的是视图名（String）或视图（View）时，需要使用@ResponseStatus注解标记该异常的Http响应状态码。

## @ResponseStatus

```java
@ResponseStatus(value = HttpStatus.NOT_FOUND)
```

@ResponseStatus注解用于将特定的异常映射到HTTP状态码上。@ResponseStatus注解可以用于标注异常类和异常处理器类（@ExceptionHandler注解标注的方法所在的类）。@ResponseStatus注解标注的异常类会被ResponseStatusExceptionResolver解析，而标注在异常处理器类上的@ResponseStatus注解会被ExceptionHandlerExceptionResolver解析。

## 案例1
```java
@RestControllerAdvice
public class ControllerExceptionHandler {
  
  @ExceptionHandler(value = {ResourceNotFoundException.class, CertainException.class})
  @ResponseStatus(value = HttpStatus.NOT_FOUND)
  public ErrorMessage resourceNotFoundException(ResourceNotFoundException ex, WebRequest request) {
    ErrorMessage message = new ErrorMessage(
        status,
        date,
        ex.getMessage(),
        description);
    
    return message;
  }
}
```

## 案例2
一个全局异常处理类，用于处理所有的HTTP错误和未知异常。

```java
package lsea.middleware;

import lsea.errors.HttpBaseError;
import lsea.utils.ErrorResult;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

/**
 * This class acts as a global exception handler for HTTP errors and unknown
 * exceptions.
 * It catches exceptions thrown by the controllers and returns an appropriate
 * response to the client.
 */
@RestControllerAdvice
public class GlobalExceptionHandler {

  /**
   * This method handles HttpBaseError exceptions and returns an HTTP response
   * with the appropriate status code and message.
   *
   * @param error The HttpBaseError object representing the exception
   * @return A ResponseEntity object with the status code and error message
   */
  @ExceptionHandler(HttpBaseError.class)
  public ResponseEntity<ErrorResult> handleException(HttpBaseError error) {
    ErrorResult result = ErrorResult
        .builder()
        .message(error.e.getMessage())
        .status(error.statusCode)
        .build();

    return ResponseEntity.status(error.statusCode).body(result);
  }

  /**
   * This method handles unknown exceptions and returns an HTTP response with a
   * 422 status code and a generic error message.
   *
   * @param e The exception
   * @return A ResponseEntity object with the 422 status code and a generic error
   *         message
   */
  @ExceptionHandler(Exception.class)
  public ResponseEntity<ErrorResult> handleUnknownException(Exception e) {
    System.out.println("And error occured to a user:");
    System.out.println(e.getMessage());
    System.out.println("Here is the stack trace:");
    e.printStackTrace();
    ErrorResult result = ErrorResult
        .builder()
        .message("Something went wrong")
        .status(422)
        .build();

    return ResponseEntity.status(422).body(result);
  }
}
```

案例中的ErrorResult类：

```java
package lsea.utils;

import javax.annotation.Nullable;
import lombok.*;

/**
 * Represents a standard error result.
 */
@Builder
@Setter
@Getter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class ErrorResult {

  /**
   * The error message.
   */
  @Nullable
  private String message;

  /**
   * The HTTP status code of the response.
   */
  private final boolean success = false;

  /**
   * The HTTP status code of the response.
   */
  private int status;
}
```