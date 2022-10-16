# GraphDatabase_neo4j

1. [no broken links](#no-broken-links)
2. [cypher command](#cypher-command)
   1. [变量](#变量)
3. [语法补充](#语法补充)
   1. [曾经的作业](#曾经的作业)
4. [Graph analysis](#graph-analysis)

## no broken links
Ensure that an existing relationship will never point to a non-existing endpoint. Since a relationship always has a start and end node, you cannot delete a node without also deleting its associated relationships.

确保现有关系永远不会指向不存在的端点。 由于关系始终具有开始节点和结束节点，因此您无法删除节点而不删除其关联关系。

## cypher command
### 变量
`param name=>"Johan"`

调用：`$name`

## 语法补充
```cypher
MATCH (n {name: 'Teresa'}) 
REMOVE n:PERSON RETURN labels(n);


match (n)-->(m) return n,m;
match (n)-[rel]->(m) return type(rel);
match (n:Person)-[rel]->(m:Person) return distinct type(rel)

match ()-[]->()<-[]-() return.... LIMIT 2
```

### 曾经的作业
```sql
CREATE (N:PERSON {name:'John', age:12});
CREATE (N:PERSON {name:'Sally', age:15});
MATCH (N {name:'John'}), (M {name:'Sally'})
CREATE (N)-[:IS_FRIEND_OF {date:date('2021-10-10')}]->(M);
CREATE (N:BOOK {name:'Graph Databases', author:'XYZ'});
MATCH (N {name:'John'}), (M {name:'Sally'}), (B {name:'Graph Databases'})
CREATE (N)-[:READ {score:3, start_date:date('2022-10-10')}]->(B), (M)-[:READ {score:5, start_date:date('2021-10-10')}]->(B);

MATCH (M {name:'John'}) - [r:IS_FRIEND_OF] - (N {name:'Sally'})
RETURN r.date;

MATCH () - [r:READ] - (B:BOOK {name:'Graph Databases'})
RETURN avg(r.score);

MATCH (B:BOOK {name:'Graph Databases'})
RETURN B.author;

MATCH (M {name:'Sally'})
RETURN M.age;

MATCH (M {name:'John'})
RETURN M.age;

//MATCH (M:PERSON)
//WITH M ORDER BY M.age desc limit 1
//RETURN COLLECT(M.name);

MATCH (M:PERSON)
WITH max(M.age) as a
Match(M:PERSON)
where M.age = a
RETURN M.name;

MATCH (M:PERSON) - [r:READ] -> (B:BOOK {name:'Graph Databases'})
WITH M,r ORDER BY r.start_date desc limit 1
RETURN M.name;
```

## Graph analysis
- community detection algorithm
- centrality algorithm
- similarity algorithm
- path