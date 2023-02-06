# sort

* Arrays.sort(obj[])
* Collections.sort(list)
* 默认升序，多维要自写排序
* 由于是泛型，不支持原始类型（注意二维数组不是原始类型，一维则不能用原始类型）
```Java
// int[][] cuboids
Arrays.sort(cuboids, (a,b)->{int s = (a[2] - b[2]); return s == 0? (a[1] - b[1] == 0? a[0] - b [0] : a[1] - b[1]): s;});
```

a-b 升序
b-a 降序


```Java
//降序排序
Student studentWang = new Student("王小二", 10);
Student studentZhang = new Student("张三", 1);
Student studentGou = new Student("狗子", 99);
Student studentZhao = new Student("赵六", 40);
Student studentLi = new Student("李四", null);
List<Student> students = new ArrayList<Student>(Arrays.asList(studentWang, studentZhang, studentGou, studentZhao, studentLi));
Collections.sort(students, new Comparator<Student>() {
    public int compare(Student o1, Student o2) {
        if(null == o1.getAge()) {
            return 1;
        }
        if(null == o2.getAge()) {
            return -1;
        }
        return o2.getAge().compareTo(o1.getAge());
    }
});
System.out.println("自定义对象，降序排序：");
for(Student student : students) {
    System.out.println(student.toString());
}
```

## 根据另一个数组排序
`Collections`即`List`可以，用上述`new Comparator`,

`Arrays`不可以