# Buffering

[I/O Streams](IOStreams.md)中提到了Buffering，这里是案例。

1. basic stream
```java
InputStream input = ... ;
```
2. buffering stream
```java
BufferedInputStream buffered = new BufferedInputStream(input);
```
3. Stream with buffering and decompression
```java
GZIPInputStream gzipStream = new GZIPInputStream(buffered);
```
4. Stream with deserialization
```java
ObjectInputStream objectStream = new ObjectInputStream(gzipStream);
```