# trypedef和struct

```C
typedef type-name new-type-name
```


```C
struct person {
    char name[20];
    int age;
};
struct person p1;
/////////////////////////
typedef struct person {
    char name[20];
    int age;
} Person;
Person p1;
/////////////////////////
typedef struct person Person;
struct person {
    char name[20];
    int age;
};
```

**C++则不同：它既支持C语法，又支持直接使用struct的名字person。**