# assertEquals

## assertEquals
assertEquals是JUnit测试框架中的一个断言方法，它用于比较两个值是否相等。在Java中，assertEquals通常用于编写单元测试，以验证代码是否按照预期方式工作。

assertEquals方法有多个重载形式，其中最常用的形式接受两个参数：期望值和实际值。例如，以下代码使用assertEquals比较两个整数值：
```java
int expected = 42;
int actual = calculateAnswerToLifeTheUniverseAndEverything();
assertEquals(expected, actual);
```

如果期望值和实际值不相等，assertEquals会抛出一个AssertionError异常，测试将失败并显示相关的错误信息。

```java
@Test
public void 
givenRequestWithNoAcceptHeader_whenRequestIsExecuted_thenDefaultResponseContentTypeIsJson()
  throws ClientProtocolException, IOException {
 
   // Given
   String jsonMimeType = "application/json";
   HttpUriRequest request = new HttpGet( "https://api.github.com/users/eugenp" );

   // When
   HttpResponse response = HttpClientBuilder.create().build().execute( request );

   // Then
   String mimeType = ContentType.getOrDefault(response.getEntity()).getMimeType();
   assertEquals( jsonMimeType, mimeType );
}
```

## assertThat

语法
```java
public static <T> void assertThat(String reason,
                                  T actual,
                                  @NotNull org.hamcrest.Matcher<? super T> matcher)
```
意思是：期望的实际值actual，应该满足matcher的条件。其中equalTo属于Hamcrest库，它是JUnit的扩展，提供了更丰富的断言方法。

```java
@Test
public void givenRequestWithNoAcceptHeader_whenRequestIsExecuted_thenDefaultResponseContentTypeIsJson()
  throws ClientProtocolException, IOException {
 
   // Given
   String jsonMimeType = "application/json";
   HttpUriRequest request = new HttpGet( "https://api.github.com/users/eugenp" );

   // When
   HttpResponse response = HttpClientBuilder.create().build().execute( request );

   // Then
   String mimeType = ContentType.getOrDefault(response.getEntity()).getMimeType();
   assertThat(mimeType, equalTo(jsonMimeType));
}
```

## 其他assert
* assertTrue
* assertFalse
* assertNull
* assertNotNull