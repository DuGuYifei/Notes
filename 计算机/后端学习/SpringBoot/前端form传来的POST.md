# 前端form传来的POST

`@RequestBody`就不能使用`multipart/form-data`了，所以这里是RequestParam

后端
```java
    @PostMapping
    public ResponseEntity<Void> createFile(@RequestParam("name") String name,
                                           @RequestParam("author") String author,
                                           @RequestParam("description") String description,
                                           @RequestParam("file") MultipartFile file,
                                           UriComponentsBuilder builder) {

        System.out.println(file.getOriginalFilename() + "name: " + name);

        FileInfo fileInfo = CreateFileRequest
                .dtoToEntityMapper()
                .apply(new CreateFileRequest(name, author, description));

        fileInfo = fileService.create(fileInfo);

        File directoryFile = new File(filePath + fileInfo.getId().toString() + "/");

        if (!directoryFile.exists()) {
            directoryFile.mkdirs();
        }

        saveFile(file, fileInfo.getId());

        return ResponseEntity.created(builder.pathSegment("api", "files", "{id}").buildAndExpand(fileInfo.getId()).toUri()).build();
    }
```


前端:
[form发送请求](../../计算机语言/JavaScript和TypeScript/JavaScript/知识积累/form发送请求.md)