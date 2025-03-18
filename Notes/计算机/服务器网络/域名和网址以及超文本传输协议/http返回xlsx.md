# http返回xlsx

需要设置header:
1. `Content-Type: application/vnd.ms-excel` 意思是返回的是excel文件
2. `Content-Disposition: attachment; filename=report.xlsx` 意思是附件，文件名是report.xlsx
3. `Cache-Control: must-revalidate, post-check=0, pre-check=0` 意思是不缓存，每次都从服务器获取

```java
	Workbook workbook = managementService.generateReport(
        dto,
        resultLongest,
        resultShortest,
        iterations);

    ByteArrayOutputStream bos = new ByteArrayOutputStream();

    workbook.write(bos);
    workbook.close();

    HttpHeaders headers = new HttpHeaders();
    headers.setContentType(MediaType.parseMediaType("application/vnd.ms-excel"));
    headers.setContentDispositionFormData("attachment", "report.xlsx");
    headers.setCacheControl("must-revalidate, post-check=0, pre-check=0");
    ResponseEntity<byte[]> response = new ResponseEntity<>(
        bos.toByteArray(),
        headers,
        HttpStatus.OK);
    return response;
```