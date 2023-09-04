# Feign基本使用

## 重要！
Feign 可以不要把原本的接口的@Validated加到FeignClient上，但是原接口必须要加上@ResponseBody，否则会报错。

## 基本配置
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

```java
package com.pokemoney.userservice.service.feignclient;

import com.pokemoney.commons.dto.RedisKeyValueDto;
import com.pokemoney.commons.dto.ResponseSuccessDto;
import com.pokemoney.commons.dto.validation.RedisGetValueGroup;
import com.pokemoney.commons.dto.validation.RedisSetValueGroup;
import com.pokemoney.commons.errors.GenericNotFoundError;
import com.pokemoney.userservice.Constants;
import org.springframework.cloud.openfeign.FeignClient;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

import java.io.Serializable;

/**
 * Leaf client for feign client of leaf-service.
 * Setup strategy for feign client in application properties.
 */
@FeignClient(name = Constants.REDIS_IN_EUREKA_KEY)
public interface RedisClient {
    /**
     * Store key, value and timeout in redis.
     *
     * @param redisKeyValueDto The {@link RedisKeyValueDto} to be stored.
     * @return The {@link ResponseSuccessDto} of the result.
     */
    @PostMapping("/api/v1/set")
    ResponseEntity<ResponseSuccessDto> setKeyValue(RedisKeyValueDto redisKeyValueDto);

    /**
     * Get value from redis.
     *
     * @param redisKeyValueDto The {@link RedisKeyValueDto} to get.
     * @return The {@link ResponseSuccessDto} with data of {@link RedisKeyValueDto}.
     * @throws GenericNotFoundError If key or value not found.
     */
    @PostMapping("/api/v1/get")
    ResponseEntity<ResponseSuccessDto> getKeyValue(RedisKeyValueDto redisKeyValueDto) throws GenericNotFoundError;
}
```

## 添加cloud自带load balancer
feign会自动使用

```java
public class LoadBalancerConfiguration {

    /**
     * Configure load balance as Round Robin in current version.
     *
     * @param environment Environment.
     * @param loadBalancerClientFactory Load balancer client factory.
     * @return ReactorLoadBalancer instance.
     */
    @Bean
    public ReactorLoadBalancer<ServiceInstance> reactorServiceInstanceLoadBalancer(
            Environment environment,
            LoadBalancerClientFactory loadBalancerClientFactory) {
        String name = environment.getProperty(LoadBalancerClientFactory.PROPERTY_NAME);
        return new RoundRobinLoadBalancer(loadBalancerClientFactory.getLazyProvider(name,
                ServiceInstanceListSupplier.class), name);
    }
}
```

```java
/**
 * This class is used to configure load balance.
 */
@Configuration(proxyBeanMethods = false)
@LoadBalancerClients(defaultConfiguration = LoadBalancerConfiguration.class)
public class DefaultLoadBalancerConfiguration {
}
```


