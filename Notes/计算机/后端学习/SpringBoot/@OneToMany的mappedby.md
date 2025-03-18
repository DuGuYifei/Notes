# @OneToMany的mappedby

引用映射
```java
    @OneToMany(cascade = CascadeType.REMOVE, mappedBy = "user")
    @ToString.Exclude
    private List<Character> characters;
```
细节见[@OneToMany@ManyToOne](%40OneToMany%40ManyToOne.md)