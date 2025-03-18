# @ComponentScan

```java
@SpringBootApplication
@ComponentScan({"com.pokemoney.userservice", "com.pokemoney.commons.mail", "com.pokemoney.commons.advice", "com.pokemoney.commons.config", "com.pokemoney.commons.errors", "com.pokemoney.commons.dto"})
@EnableFeignClients
public class UserServiceApplication {
    /**
     * Application main entry point.
     *
     * @param args Command line arguments.
     */
    public static void main(String[] args) {
        SpringApplication.run(UserServiceApplication.class, args);
    }
}
```