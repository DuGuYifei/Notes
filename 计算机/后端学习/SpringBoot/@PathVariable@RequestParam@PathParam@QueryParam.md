# @PathVariable@RequestParam@PathParam@QueryParam

1. Spring: 
   RequestParam + PathVariable
2. JAX-RS(**JAVA EE6自带**)(**注解中只有一个配置参数**): 
   QueryParam + PathParam

## @PathVariable
`localhost:8080/demo2/Bob/12`
```java
    @RequestMapping(value="/demo2/{name}/{id}")   
    public void demo2(@PathVariable String name, @PathVaribale int id)
    {
        System.out.println("get name is : " + name + ", id: " + id);
        return;
    }
输出：
   get name is : Bob, id: 12
```

## PathParam
`@PathParam("userId") String userId`


## @RequestParam
（1）不加@RequestParam前端的参数名需要和后端控制器的变量名保持一致才能生效

（2）**不加@RequestParam参数为非必传，加@RequestParam写法参数为必传**。但@RequestParam可以通过@RequestParam(required = false)设置为非必传。**required 属性默认为 true**，所以如果默认下缺失该变量就报400错

（3）@RequestParam可以通过@RequestParam(“userId”)或者@RequestParam(value = “userId”)指定传入的参数名。

（4）@RequestParam可以通过@RequestParam(defaultValue = “0”)指定参数默认值

（5）如果接口除了前端调用还有后端RPC调用，则不能省略@RequestParam，否则RPC会找不到参数报错


`localhost:8080/demo1?name=Aaron&age=18`
```java
    @RequestMapping(value="/demo1")
    public void demo1(@RequestParam String name, @RequestParam int age ){
        System.out.println("get name is : " + name + ", age: " + age);
        return;
    }
输出：
    get name is : Aaron, age: 18
```

1. Note: 后端如果是分别接收前端传过来的多个基本类型参数，可以使用上文所示的@RequsetParam来分别按名进行绑定即可。但是如果参数数量过多，上述写法下的方法中的形参列表将会过长导致可读性降低。可以直接使用一个[POJO对象](../../计算机语言/Java/Java知识积累/POJO.md来进行绑定接收，而不需要使用@RequestParam注解，其自动将参数按名绑定到对象的属性中。如下所示，形参使用Student对象进行数据绑定，其含有name，age属性
```java
    @RequestMapping(value="/demo1")
    public void demo1(Student student){
        System.out.println("get name is : " + name + ", age: " + age);
        return;
    }
```

2. 当请求头中的 Content-Type 类型为：multipart/form-data 或 application/x-www-form-urlencoded 时，该@RequestParam注解同样可以把请求体中相应的参数绑定到Controller方法的相应形参中

   1. 例1
    ```java
    @Controller
    @RequestMapping("receive")
    public class receiveTest {
        @RequestMapping("/receiveFile")
        @ResponseBody
        public String receiveFile(@RequestParam(required = false, value = "file2") MultipartFile File2, @RequestParam String FirstName, @RequestParam String LastName) {
            System.out.println("FirstName : " + FirstName);
            System.out.println("LastName : " + LastName);
            return "Success";
        }
    }
    ```
   2. 例2 
    ```java
    @PutMapping(value = "{id}/portrait", consumes = MediaType.MULTIPART_FORM_DATA_VALUE)
        public ResponseEntity<Void> putCharacterPortrait(@PathVariable("id") long id,
                                                         @RequestParam("portrait") MultipartFile portrait) throws IOException {
            Optional<Character> character = characterService.find(id);
            if (character.isPresent()) {
                characterService.updatePortrait(character.get().getId(), portrait.getInputStream());
                return ResponseEntity
                        .accepted()
                        .build();
            } else {
                return ResponseEntity
                        .notFound()
                        .build();
            }
        }
    ```
    [http讲解](../../服务器网络/域名和网址以及超文本传输协议/超文本传输协议.md)
    http请求：
    ```http
    ###

    PUT http://localhost:8082/api/characters/1/portrait
    Content-Type: multipart/form-data; boundary=boundary

    --boundary
    Content-Disposition: form-data; name="portrait"; filename="uhlbrecht.png'

    < ../../src/main/resources/pl/edu/pg/eti/kask/rpg/configuration/avatar/uhlbrecht.png
    --boundary--
    ```

## @QueryParam
`@QueryParam("date") String date`