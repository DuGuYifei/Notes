# JPA参数化查询@Query

`@Query`里的参数是按照顺序来的，而不是按照名字来的。
比如：
```java
@Query("SELECT * FROM user WHERE name = ?1 AND age = ?2")
User findUserByNameAndAge(String name, Integer age);
```

```java
@Repository
public interface LogRepository extends JpaRepository<Log, UUID> {
  /**
   * Find all logs for a given user.
   *
   * @param pageable - the page
   * @return a list of logs for the user
   */
  /* Requirement 7.4 */
  @Query("SELECT l FROM Log l ORDER BY l.createdAt DESC")
  List<Log> findLogs(Pageable pageable);

  /**
   * Find all logs for a given user that were created after a given timestamp.
   *
   * @param timestamp - the timestamp
   * @return a list of logs for the user
   */
  /* Requirement 7.4 */
  @Query("SELECT l FROM Log l WHERE l.createdAt > ?1 ORDER BY l.createdAt DESC")
  List<Log> findLiveLogs(Timestamp timestamp);
}
```