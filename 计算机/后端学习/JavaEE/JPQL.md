# JPQL

Queries without parameters:

```java
String queryString = "SELECT p FROM Product p";
Query query = em.createQuery(queryString);
List<Product> products = query.getResultList();
```

```java
String queryString = "SELECT p FROM Product p WHERE p.name LIKE :name";
Query query = em.createQuery(queryString);
query.setParameter("name", "Laptop");
List<Product> products = query.getResultList();
```

em是[EntityManager](EntityManager_EntityManagerFactory.md)