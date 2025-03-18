# @RequestBody

注解@RequestBody接收的参数是来自requestBody中，即请求体。一般用于处理 **非** `Content-Type: application/x-www-form-urlencoded和multipart/form-data`编码格式的数据，比如：
`application/json`、`application/xml`等类型的数据。

```java
    /**
     * Updates existing character.
     *
     * @param request character's data parsed from JSON
     * @param id      character's id
     * @return accepted or not found if character does not exist
     */
    @PutMapping("{id}")
    public ResponseEntity<Void> putCharacter(@RequestBody PutCharacterRequest request, @PathVariable("id") long id) {
        Optional<Character> character = characterService.find(id);
        if (character.isPresent()) {
            PutCharacterRequest.dtoToEntityUpdater().apply(character.get(), request);
            characterService.update(character.get());
            return ResponseEntity
                    .accepted()
                    .build();
        } else {
            return ResponseEntity
                    .notFound()
                    .build();
        }
    }
-------------------------------------
    public static BiFunction<Character, PutCharacterRequest, Character> dtoToEntityUpdater() {
        return (character, request) -> {
            character.setName(request.getName());
            character.setAge(request.getAge());
            character.setBackground(request.getBackground());
            return character;
        };
    }
```
http请求：
```http
###

PUT http://localhost:8082/api/characters/5
Content-Type: application/json

{
  "name": "Sir Sigrid",
  "background": "Someone well known.",
  "age": 30
}
```


