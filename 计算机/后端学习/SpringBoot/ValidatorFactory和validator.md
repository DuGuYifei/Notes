# ValidatorFactory和validator

1. [Validator](#validator)
	1. [1. 介绍](#1-介绍)
	2. [2. 使用](#2-使用)
		1. [2.1. 依赖](#21-依赖)
		2. [2.2. 注解](#22-注解)
		3. [2.3. 使用](#23-使用)
	3. [3. 自定义](#3-自定义)
		1. [3.1. 自定义注解](#31-自定义注解)
		2. [3.2. 自定义注解的实现](#32-自定义注解的实现)
	4. [直接使用Validator类](#直接使用validator类)
2. [ValidatorFactory](#validatorfactory)
	1. [1. 介绍](#1-介绍-1)
	2. [2. 使用代码](#2-使用代码)


## Validator

### 1. 介绍

Validator是一个接口，用于验证对象的状态。它可以用于验证单个属性（例如，验证一个字符串是否是有效的电子邮件地址）或整个对象（例如，验证用户是否已填写了所有必填字段）。

### 2. 使用

#### 2.1. 依赖

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-validation</artifactId>
	<version>2.1.6.RELEASE</version>
</dependency>
```

#### 2.2. 注解

```java
@NotNull
@Size(min = 2, max = 14)
private String name;
```

#### 2.3. 使用

```java
@RestController
public class TestController {

	@PostMapping("/test")
	public String test(@Valid @RequestBody Test test) {
		return "success";
	}
}
```

### 3. 自定义

#### 3.1. 自定义注解

```java
@Target({ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
@Constraint(validatedBy = MyConstraintValidator.class)
public @interface MyConstraint {
	String message() default "自定义注解验证失败";

	Class<?>[] groups() default {};

	Class<? extends Payload>[] payload() default {};
}
```

#### 3.2. 自定义注解的实现

```java
public class MyConstraintValidator implements ConstraintValidator<MyConstraint, Object> {

	@Override
	public boolean isValid(Object value, ConstraintValidatorContext context) {
		return false;
	}
}
```

### 直接使用Validator类

```Java
@RestController
public class TestController {

	@Autowired
	private Validator validator;

	@PostMapping("/test")
	public String test(@RequestBody Test test) {
		Set<ConstraintViolation<Test>> validate = validator.validate(test);
		for (ConstraintViolation<Test> testConstraintViolation : validate) {
			System.out.println(testConstraintViolation.getMessage());
		}
		return "success";
	}
}
```

```Java
public abstract class ValidationRouter {
    /* Requirement 2.6 */
    /** The default validator factory. */
    static final ValidatorFactory factory = Validation.buildDefaultValidatorFactory();

    /** The validator instance to use for validating objects. */
    static final private Validator validator = factory.getValidator();

    /* Requirement 2.6 */
    /**
     * Validates the given DTO.
     *
     * @param <T>    the type of the DTO to validate
     * @param object the object to validate
     * @throws ValidationError if the object fails validation
     */
    static protected <T> void validate(T object) throws ValidationError {
        Set<ConstraintViolation<T>> violations = validator.validate(object);
        if (!violations.isEmpty()) {
            List<String> errors = new ArrayList<>();
            /* Requirement 2.3 */
            violations.forEach(violation -> errors.add(
                    violation.getPropertyPath() + " " + violation.getMessage()));
            String joined = String.join(", ", errors);
            throw new ValidationError(joined);
        }
    }
}
```

## ValidatorFactory

### 1. 介绍

ValidatorFactory是一个接口，用于创建Validator实例。

### 2. 使用代码

```java
public class TestController {

	@Autowired
	private ValidatorFactory validatorFactory;

	@PostMapping("/test")
	public String test(@RequestBody Test test) {
		Validator validator = validatorFactory.getValidator();
		Set<ConstraintViolation<Test>> validate = validator.validate(test);
		for (ConstraintViolation<Test> testConstraintViolation : validate) {
			System.out.println(testConstraintViolation.getMessage());
		}
		return "success";
	}
}
```

```java
public abstract class ValidationRouter {
    /* Requirement 2.6 */
    /** The default validator factory. */
    static final ValidatorFactory factory = Validation.buildDefaultValidatorFactory();

    /** The validator instance to use for validating objects. */
    static final private Validator validator = factory.getValidator();

    /* Requirement 2.6 */
    /**
     * Validates the given DTO.
     *
     * @param <T>    the type of the DTO to validate
     * @param object the object to validate
     * @throws ValidationError if the object fails validation
     */
    static protected <T> void validate(T object) throws ValidationError {
        Set<ConstraintViolation<T>> violations = validator.validate(object);
        if (!violations.isEmpty()) {
            List<String> errors = new ArrayList<>();
            /* Requirement 2.3 */
            violations.forEach(violation -> errors.add(
                    violation.getPropertyPath() + " " + violation.getMessage()));
            String joined = String.join(", ", errors);
            throw new ValidationError(joined);
        }
    }
}
```