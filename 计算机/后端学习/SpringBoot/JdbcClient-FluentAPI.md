# JdbcClient-FluentAPI
## 讲解

[微信文章:https://mp.weixin.qq.com/s/-eZc931Y3G1hXic9uWVzWA](https://mp.weixin.qq.com/s/-eZc931Y3G1hXic9uWVzWA)

## 案例

```text-x-java
@Repository
public class StudentRepository {

    private final JdbcClient jdbcClient;

    @Autowired
    public StudentRepository(JdbcClient jdbcClient) {
        this.jdbcClient = jdbcClient;
    }

    public List<Student> findAll() {
        return jdbcClient.sql("SELECT * FROM student")
                .query(Student.class)
                .list();
    }

    public Optional<Student> findById(Long id) {
        return jdbcClient.sql("SELECT * FROM student WHERE id = :id")
                .param("id", id)
                .query(Student.class)
                .optional();
    }

    public void create(Student student) {
        jdbcClient.sql("INSERT INTO student (name, age) VALUES (?, ?)")
                .params(student.getName(), student.getAge())
                .update();
    }

    public void update(Student student) {
        jdbcClient.sql("UPDATE student SET name = ?, age = ? WHERE id = ?")
                .params(student.getName(), student.getAge(), student.getId())
                .update();
    }

    public void delete(Long id) {
        jdbcClient.sql("DELETE FROM student WHERE id = ?")
                .param("id", id)
                .update();
    }
}
```