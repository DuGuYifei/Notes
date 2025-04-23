# 读取文hdfs里的文件

```java
public static String readHDFSFile(String path, Configuration conf) throws IOException {
    Path pt = new Path(path);
    FileSystem fs = FileSystem.get(pt.toUri(), conf);
    FSDataInputStream file = fs.open(pt);
    BufferedReader buffIn = new BufferedReader(new InputStreamReader(file));

    StringBuilder everything = new StringBuilder();
    String line;
    while ((line = buffIn.readLine()) != null) {
        everything.append(line);
        everything.append("\n");
    }
    return everything.toString();
}

this.stopWords = Arrays.asList(readHDFSFile(stopWordsPath, conf).split("\n"));
this.stopWords = readHDFSFile(stopWordsPath, conf).split("\n");
this.delimiters = readHDFSFile(delimitersPath, conf);
```
