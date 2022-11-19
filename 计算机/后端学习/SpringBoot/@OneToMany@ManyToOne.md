# @OneToMany@ManyToOne

## 一对多和多对一关系

下例展示了：单向（character和profession）双向
```Java
@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
@Entity
@Table(name = "users")
public class User implements Serializable {

    /**
     * User's login.
     */
    @Id
    private String login;

    /**
     * List of user's characters. By default list of characters is not loaded from the database.
     */
    @OneToMany(cascade = CascadeType.REMOVE, mappedBy = "user")
    @ToString.Exclude
    private List<Character> characters;

}
--------------------------------------
@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
@Entity
@Table(name = "professions")
public class Profession implements Serializable {

    /**
     * Name of the profession.
     */
    @Id
    private String name;

    /**
     * Set of skills available on different levels. While leveling up, character gains access to new skills. One skill
     * every limit level. There is no rule which levels are limit ones. Skills are now ignored as they are waiting for
     * more complex implementation.
     */
    @Transient
    private Map<Integer, Skill> skills;

}
---------------------------------------
@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString(callSuper = true)
@EqualsAndHashCode(callSuper = true)
@Entity
@Table(name = "characters")
public class Character extends Creature {

    /**
     * Character's background story.
     */
    private String background;

    /**
     * Character's profession (class). By default profession is loaded from database.
     */
    @ManyToOne
    @JoinColumn(name = "profession")
    private Profession profession;

    /**
     * Owner of this character. By default user is loaded from the database.
     */
    @ManyToOne
    @JoinColumn(name ="user")
    private User user;
}

```

## @JoinColumn批注和mappedby属性
```java
    @ManyToOne
    @JoinColumn(name ="user")
    private User user;
```
@JoinColumn 注释定义了拥有方的实际物理映射。 
[@JoinColumn](@JoinColumn.md)

```java
    @OneToMany(cascade = CascadeType.REMOVE, mappedBy = "user")
    @ToString.Exclude
    private List<Character> characters;
```
引用端是使用 @OneToMany 注释的 mappedBy 属性定义的。

## mappedby
[@OneToMany的mappedby](@OneToMany的mappedby.md)

## Cascade
[@的属性的的cascade](cascade.md)

## fetch
[@的属性的的fetch](fetch.md)