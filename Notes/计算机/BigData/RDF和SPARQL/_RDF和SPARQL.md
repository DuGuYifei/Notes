# _RDF和SPARQL
## RDF

1. Resource Description Framework
2. 三元组模型：主谓宾

## SPARQL

编辑器网址：[https://dbpedia.org/snorql/](https://dbpedia.org/snorql/) 和 https://dbpedia.org/sparql

### 语法

1. SELECT:用于指定要从RDF数据中检索的结果。你可以选择特定的变量或使用`*****`表示所有变量。
2. **WHERE 子句**：用于定义查询模式，即描述你要检索的数据的模式。这包括主体、谓词和宾语的模式匹配。
3. **过滤条件**：你可以在WHERE子句中使用过滤条件来进一步限制结果。SPARQL提供了多种内置函数和运算符，如**FILTER**、**<**、**>**、**=**等。
4. **ORDER BY 子句**：用于指定结果的排序方式，可以按一个或多个变量进行排序
5. **LIMIT 和 OFFSET 子句**：用于分页查询结果，**LIMIT**指定返回的结果数量，**OFFSET**用于跳过前面的结果。
6. **SELECT DISTINCT**：用于返回唯一的结果，去除重复的行。
7. **CONSTRUCT 子句**：用于构建新的RDF图，而不是返回结果集。你可以在CONSTRUCT子句中定义新的三元组模式。
8. **ASK 子句**：用于检查是否存在与查询模式匹配的数据，返回布尔值（true或false）。

```text-x-sql
SELECT ?subject ?predicate ?object
WHERE {
    ?subject ?predicate ?object
}
WHERE {
    ?subject rdf:type foaf:Person ;
            foaf:age ?age .
    FILTER (?age > 30)
}
ORDER BY ?name
LIMIT 10
OFFSET 20
SELECT DISTINCT ?name
WHERE {
    ?person foaf:name ?name .
}
CONSTRUCT {
    ?subject rdf:type foaf:Person .
}
WHERE {
    ?subject foaf:name ?name .
}
ASK
WHERE {
    ?subject rdf:type foaf:Person ;
            foaf:name "John" .
}
```

### 常见前缀

1. `**foaf:**` **<http://xmlns.com/foaf/0.1/>**
2. `**rdf:**` 

### 案例

### Acquiring RDF data – report

### 1. Assumptions

What the data are about? Have any assumptions been made about them?

1. The data are about the universities in the world. http://lookup.dbpedia.org/api/search/KeywordSearch?QueryClass=university
2. Assumptions (Only based on the data in the DBPedia)
    1. Find the data about Gdansk University of Technology
    2. Find all the places of universities in Poland.
    3. Find the amount of students in the Polish universities.

### 2. SPARQL Queries

A SPARQL query or queries which is used to acquire the data

### 案例：

#### Assumptions 1 - Preliminary query to explore the data

**Find the data about Gdansk University of Technology**

```text-plain
PREFIX dbo: <http://dbpedia.org/ontology/>
PREFIX dbr: <http://dbpedia.org/resource/>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

SELECT ?predicate ?object WHERE {
    ?un rdf:type dbo:University .
    ?un dbo:country dbr:Poland .
    ?un rdfs:label ?label .
    FILTER (STR(?label) = "Gdańsk University of Technology")
    ?un ?predicate ?object
}
```

#### Assumption 2 - Preliminary query to explore the data for specific country

**Find all the places of universities in Poland.** Due to the data some university only has `country`, some university only has `location`, so we need union the query for which location is belong to Poland and directly query for Poland. Then we need show both columns and bind location to place column if location is not null. Then, we bind country to place column if country is not null.

```text-plain
PREFIX dbo: <http://dbpedia.org/ontology/>
PREFIX : <http://dbpedia.org/resource/>
PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
PREFIX dbp: <http://dbpedia.org/property/>

SELECT DISTINCT ?un ?location ?country ?place WHERE {
    { 
        ?un rdf:type dbo:University .
        ?un dbo:country ?country .
        FILTER (?country = :Poland)
    }
    UNION
    {
        ?un rdf:type dbo:University .
        ?un dbp:location ?location .
        FILTER (?location = :Poland)
    }
    OPTIONAL {
        ?un dbp:location ?location .
    }
    OPTIONAL {
        ?un dbo:country ?country .
    }
    BIND (IF(bound(?location), ?location, ?country) AS ?place)
} ORDER BY DESC(?location)
```

#### Assumption 3

**Find the top 20 of amount of students of univerities among the Polish and Chinese universities if the dataset contains this columns.**

```text-plain
PREFIX dbo: <http://dbpedia.org/ontology/>
PREFIX : <http://dbpedia.org/resource/>
PREFIX xsd: <http://www.w3.org/2001/XMLSchema#>
select ?un, xsd:string(?place) AS ?loc, ?PostgraduateStudents, ?UndergraduateStudents, MAX(?res) AS ?numberOfStudents where{
    {
        ?un rdf:type dbo:University .
        ?un dbo:country :Poland .
        ?un dbp:country ?country .
        OPTIONAL {
            ?un dbo:numberOfPostgraduateStudents ?numberOfPostgraduateStudents .
        }
        OPTIONAL {
            ?un dbo:numberOfUndergraduateStudents ?numberOfUndergraduateStudents .
        }
    }
    UNION 
    {
        ?un rdf:type dbo:University .
        ?un dbo:country :China .
        ?un dbp:country ?country .
        OPTIONAL {
            ?un dbo:numberOfPostgraduateStudents ?numberOfPostgraduateStudents .
        }
        OPTIONAL {
            ?un dbo:numberOfUndergraduateStudents ?numberOfUndergraduateStudents .
        }
    }
    UNION 
    {
        ?un rdf:type dbo:University .
        ?un dbp:location ?location .
        FILTER (?location = :Poland || ?location = :China)
        OPTIONAL {
            ?un dbo:numberOfPostgraduateStudents ?numberOfPostgraduateStudents .
        }
        OPTIONAL {
            ?un dbo:numberOfUndergraduateStudents ?numberOfUndergraduateStudents .
        }
    }
    BIND (IF(bound(?location), ?location, ?country) AS ?place)
    BIND (IF(bound(?numberOfPostgraduateStudents), xsd:integer(?numberOfPostgraduateStudents), 0) AS ?PostgraduateStudents)
    BIND (IF(bound(?numberOfUndergraduateStudents),  xsd:integer(?numberOfUndergraduateStudents), 0) AS ?UndergraduateStudents)
    BIND (?PostgraduateStudents + ?UndergraduateStudents AS ?res)
} ORDER BY DESC(?numberOfStudents) LIMIT 20
```

### 3. Characteristics of the Obtained Set

What do variables mean? How many rows are included? Are there any missing or special values?

To get the rows, use script in F12 as below

```text-plain
let elements = document.getElementsByTagName('tr');
console.log(elements.length);
```

For Assumption 1:

1. varaiables:
    1. ?predicate is the predicate of the university.
    2. ?object is the object of the property.
    3. ?un is the university.
2. rows: 360

For Assumption 2:

1. varaiables:
    1. ?location is the field of the university, which is the location of the university.
    2. ?country is the field of the university, which is the country of the university.
    3. ?place is the result of the query, which is the place of the university.
    4. ?un is the university.
2. rows: 121
3. missing and special values:
    1. Not all university have both location and country (acutally, it just has one of these two properties, which means the `distinct` can be deleted), so we need to use `OPTIONAL` to get the data. And also some university have more than one location and in different countries, so we need use Filter to get only 1 item for each of them.

For Assumption 3:

1. varaiables:
    1. ?un is the university.
    2. ?PostgraduateStudents is the number of postgraduate students in the university.
    3. ?UndergraduateStudents is the number of undergraduate students in the university.
    4. ?numberOfStudents is the result of the query, which is the number of students in the university.
2. rows: 20
3. missing and special values:
    1. Not all university have both postgraduate students and undergraduate students, so we need to use `OPTIONAL` to get the data.
    2. We need give the default value 0 to the students number if it is missing value

### 4. Additional Remarks

Remarks about phrases used in your queries. Remarks about specifics of DBPedia data used to obtain your set. Any other remarks :-)

1. During using the editor in the website, I find when I try to use `+` in `https://dbpedia.org/snorql/` it will be auto ignored and result in error. So I change to use `https://dbpedia.org/sparql` for the assumption 3.
2. In last query, I use two different way to query data for `location` and `country` but they are acutally same thing.
3. WHY in query 2, I use`?un dbo:country ?country . FILTER (?country = :Poland)` not `?un dbo:country :Poland .`? Because during my exploring, if use the second one, and the query `OPTIONAL { ?un dbp:location ?location .}` will make duplicate rows. Because one `univerisy` may have several same property of `location` and `country`.
4. Use several prefix to make the query more readable.
5. Use xsd to change the format of the number of students and make the result more readable.
6. Use `OPTIONAL` to get the data which is missing and give default value to the missing data. Especially for query 3, the number of student should be sum up of postgraduate students and undergraduate students, but some university only have one of them or directly have no this data, so we need to give default value 0 to the missing data.