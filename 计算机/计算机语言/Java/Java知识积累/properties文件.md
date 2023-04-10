# properties文件


文件是:`src/liuyifei/alchemists/configure.properties`

```properties
alchemist.herbPrice = 20
```

```Java
ResourceBundle.getBundle("liuyifei.alchemists.configure").getString("alchemist.herbPrice");
```