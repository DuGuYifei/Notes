# EntityManager_EntityManagerFactory

- JPA allows to query entities and their relationships in an object-oriented way;
- EntityManager shares operations that can be made on entities
  - they change the state of the entity object (new/managed/detached/removed);
  - manage entities, read/write from/to DB;
  - is an interface whose implementation is done by the persistence provider(e.g. Spring);
  - from the technical point of view it hides the JDBC (low-levelled) calls to DB


```java
EntityManagerFactory factory = Persistence.createEntityManagerFactory("name_pu");
EntityManager em = factory.createEntityManager();

// create
em.getTransaction().begin();
em.persist(entity);
em.getTransaction().commit();

// read
em.find(entityClass, primaryKey);

// update
em.getTransaction().begin();
em.merge(entity);
em.getTransaction().commit();

// delete
em.getTransaction().begin();
em.remove(entity);
em.getTransaction().commit();
```

其中entity是一个POJO，entityClass是entity的类，primaryKey是entity的主键。

```java
@Entity
public class Employee {
	@Id
	private int id;
	private String name;
	private int salary;
	private String deg;
	// getters and setters
}
```

## 系统性方法介绍
```java
void persist (Object o) // save to DB
<T> T merge (T entity) // 见上面例子
void remove (Object o) // delete entitiy
void refresh(Object o) // update object state based on DB
<T> T find(Class<T> entityClass, Object key) // search based on primary key
EntityTransaction getTransaction() // returns transaction object
```

[EntityTransaction](EntityTransaction.md)

### 案例
```java
public class Main {
	public static void main(String[] args) {
		// Creates an instance of the Club
		Club barca = new Club( ... );
		// Obtains an entity manager and a transaction
		EntityManagerFactory emf = Persistence.createEntityManagerFactory("name_PU");
		EntityManager em = emf.createEntityManager();
		// Persists the club to the database
		EntityTransaction tx = em.getTransaction();
		tx.begin();
		em.persist(barca);
		tx.commit();
		// Executes the named query
		barca = em.createNamedQuery("findPlayer", Club.class).getSingleResult();
		// Closes the entity manager and the factory
		em.close();
		emf.close();
	}
}
```

## JPQL
[JPQL](JPQL.md)