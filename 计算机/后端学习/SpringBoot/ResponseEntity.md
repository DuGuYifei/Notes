# ResponseEntity

## 常见语法
1. `ResponseEntity.accepted().build()`
2. ResponseEntity.notFound().build()`
3. 

## BadRequest添加错误信息

```java
    @PostMapping
    public ResponseEntity<String> createAnimal(@RequestBody CreateAnimalRequest request, UriComponentsBuilder builder) {
        Optional<Animal> findRes = animalService.find(request.getName());
        if(findRes.isPresent()){
            return ResponseEntity
                    .status(HttpStatus.BAD_REQUEST)
                    .body("This animal has been existed!");
        }
        Animal animal = CreateAnimalRequest.dtoToEntityMapper().apply(request);
        animal = animalService.create(animal);
        return ResponseEntity.created(builder.pathSegment("api", "animals", "{name}").buildAndExpand(animal.getName()).toUri()).build();
    }
```
