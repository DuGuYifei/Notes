# Function

## 语法
```
Function<参数类型，返回值类型>
```

## apply
```Java
import java.util.function.Function;
public class Student {
    public String name;
    public int age;
    public Student(String name,int age){
        this.name = name;
        this.age = age;
    }
    public  String customShow(Function<Student,String> fun){
        return fun.apply(this);
    }
}
————————————————
版权声明：本文为CSDN博主「猫巳」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_31635851/article/details/116985000
```

```java
@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
public class CreatePetRequest {
    /**
     * Name of the pet.
     */
    private String name;

    /**
     * Whether the pet is sick.
     */
    private Boolean isSick;

    /**
     * Name of the pets's animal.
     */
    private String animal;

    /**
     * @param animalFunction function for converting animal name to animal entity object
     * @return mapper for convenient converting dto object to entity object
     */
    public static Function<CreatePetRequest, Pet> dtoToEntityMapper(Function<String, Animal> animalFunction){
        return request -> Pet.builder()
                .name(request.getName())
                .isSick(request.getIsSick())
                .animal(animalFunction.apply(request.getAnimal()))
                .build();
    }
}
```


