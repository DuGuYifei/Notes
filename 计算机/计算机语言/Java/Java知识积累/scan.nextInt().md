# scan.nextInt()

```Java
Import java.util.*;
public class Main{
    public static void main(String[] args)
    {
        Scanner scan=new Scanner(System.in);
            while(scan.hasNext){
                int n=scan.nextInt();
            }
    }
}
```

Scanner scan=new Scanner(System.in) 这一句是让你从键盘输入什么东西。
如果你输入一个整数10，则
int n=scan.nextInt() 这句的表明n=你输入的这个整数10。