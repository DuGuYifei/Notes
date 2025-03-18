# 重写equals和hashCode

## JAVA重写equal方法后为什么必须要重写Hashcode方法
java规范中规定，相等的两个对象他们的散列码必定相等。

## 重写hashCode
```java
public int hashCode(){

    System.out.println(this.name +"...hashCode");

    return 60;

}
```