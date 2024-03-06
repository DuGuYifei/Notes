# Enum

## int或string或同时，以及enum和mysql关系
[案例](https://yulaiz.com/java-mysql-enum/)

其中int和string同时，且mysql是数字：
```java
public enum OrderStatus {
    CREATE(0, "创建"),
    PAYING(1, "支付中"),
    IN_PROGRESS(2, "支付成功"),
    FAILED(3, "支付失败"),
    REVERSED(4, "取消订单");

    private int value;
    private String desc;

    OrderStatus(int value, String desc) {
        this.value = value;
        this.desc = desc;
    }

    public int getValue() {
        return value;
    }

    public String getDesc() {
        return desc;
    }
}

public class OrderInfo {
    private int id;
    private OrderStatus status;
}

orderInfo.setStatus(OrderStatus.CREATE);
```

## 案例
```java
enum Season{
    spring,summer,autumn,winter;
//   常量有 spring, summer, autumn，winter,分别表示春天，夏天，秋天，冬天，系统会自动添加 public static final 修饰
}
 
 
public class SeasonEnum {
 
    public static void main(String[] args) {
 
 
        System.out.println("请输入季节"+"\n"+"1、春天"+"\n"+"2、夏天"+"\n"+"3、秋天"+"\n"+"4、冬天");
        Scanner scan =new Scanner(System.in);
        int seasons= scan.nextInt();
        change(seasons);
    }
 
    private static void change(int seasons) {
        Season season=Season.spring;
        switch (seasons){
            case 1:
                season=Season.spring;
 
                break;
            case 2:
                season=Season.summer;
                break;
            case 3:
                season=Season.autumn;
                break;
            case 4:
                season=Season.winter;
                break;
        }
        System.out.println(season);
    }
}
```

### Season.values()
所有的值

### season.ordinal()
```java
enum Season{
    spring,summer,autumn,winter;
//   常量有 spring, summer, autumn，winter,分别表示春天，夏天，秋天，冬天，系统会自动添加 public static final 修饰
}

 
 
public class SeasonEnum {
   public static void main(String[] args) {
//        迭代季节
        for (Season season : Season.values()) {
//            ordinal可以找到每个枚举常量的索引，就像数组索引一样。
            System.out.println(season+"  索引为  "+season.ordinal());
        }
   }
}
```


## 自定义索引

```java
enum Season{
    spring(1),summer(2),autumn(3),winter(4);

    private int index;

    Season(int index) {
        this.index = index;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }
    
}
```

