# BiFunction

```
BiFuction <参数类型1，参数类型2，返回类型>
```

```java
    public static BiFunction<Animal, UpdateAnimalRequest, Animal> dtoToEntityUpdater(){
        return (animal, request) -> {
            animal.setFoodType(request.getFoodType());
            return animal;
        };
    }
```