# Dictionary

```Java
Dictionary<Person, Integer> dic = new Hashtable<>();
dict.put(p1,p2);
dict.put(p3,p4);//pi都是Person类
Enumeration e = dic.keys();
while(e.hasMoreElements()) {
    Person key = (Person) e.nextElement();
    System.out.print(key.name);
}
```