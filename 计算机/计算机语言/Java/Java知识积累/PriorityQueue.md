# PriorityQueue

## 默认
默认小顶堆

## 常用方法
```java
peek()//返回队首元素
poll()//返回队首元素，队首元素出队列
add()//添加元素
size()//返回队列元素个数
isEmpty()//判断队列是否为空，为空返回true,不空返回false
```

## 比较器
1. Integer
```java
    //自定义比较器，降序排列
	static Comparator<Integer> cmp = new Comparator<Integer>() {
	      public int compare(Integer e1, Integer e2) {
	        return e2 - e1;  //降序
	      }
	    };
	public static void main(String[] args) {
	        //不用比较器，默认升序排列
	        Queue<Integer> q = new PriorityQueue<>();
	        q.add(8);
	        q.add(5);
	        q.add(13);
	        q.add(2);
	        System.out.println("**********不使用比较器********************");
	        while(!q.isEmpty())
	        {
	            System.out.print(q.poll()+" ");
	        }
	        System.out.println();
	        System.out.println("**********使用比较器********************");
	        //使用自定义比较器，降序排列
	        Queue qq = new PriorityQueue(cmp);
	        qq.add(8);
	        qq.add(5);
	        qq.add(13);
	        qq.add(2);
	        while(!qq.isEmpty())
	        {
	            System.out.print(qq.poll()+" ");
	        }
	}
```

2. 自定义1
```java
	    //自定义比较类，先比较长，长升序排列，若长相等再比较宽，宽降序
	    static Comparator<Node> cNode=new Comparator<Node>() {
	        public int compare(Node o1, Node o2) {
	            if(o1.chang!=o2.chang)
	                return o1.chang-o2.chang;
	            else
	                return o2.kuan-o1.kuan;
	        }
	        
	    };
	    public static void main(String[] args) {
	    	Queue<Node> q=new PriorityQueue<>(cNode);
	        Node n1=new Node(1, 2);
	        Node n2=new Node(2, 5);
	        Node n3=new Node(2, 3);
	        Node n4=new Node(1, 2);
	        q.add(n1);
	        q.add(n2);
	        q.add(n3);
	        Node n;
	        while(!q.isEmpty())
	        {
	            n=q.poll();
	            System.out.println("长: "+n.chang+" 宽：" +n.kuan);
	        }
	    }
	
```

3. 自定义2
```java
PriorityQueue<int[]>pq = new PriorityQueue<>((a,b) -> {
    int d1 = (a[1] - a[0])/2, d2 = (b[1] - b[0])/2;
    return d1 != d2? d2 - d1 : a[0] - b[0]; // 按d降序，按x[0]升序
});
```

## 修改类型自带比较器
[Comparable泛型接口_compareTo](Comparable泛型接口_compareTo.md)