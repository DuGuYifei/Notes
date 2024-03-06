# Path_File

## 背景

旧版的`File`有很多问题，比如：
1. Many method do not throw exceptions
2. Limited access to metadata (e.g. the owenr of a file)
3. Scalable problems (e.g. listing numerous elements)
4. etc.

`Parh` and `Files` classes are the newer version of the basic `File` class.
* shaed under Java SE 7
* `java.nio.file` package

Solved many problems of the old `File` class.

## Path

1. Representing the localization of a file or directory on the disk, including the operation system specificity
2. Implements `Watchable` interface, which allows to monitor changes (e.g. adding file in the folder, deleting file, file modification) in the file system

```java
Path absolute = Paths.get("/home", "sthg"); // 1.表示根目录下的 "home" 目录 2.表示在 "home" 目录下的一个子目录或文件名。
Path relative = Paths.get("home", "sthg", "user.properties"); //1. 表示当前目录相对路径中的第一级目录或文件名。2. 表示相对路径中的第一级目录或文件名。3. 表示相对路径中的第三级文件名
```

等价于

```java
String baseDir = props.getProperty("base.dir");
Path basePath = Paths.get(baseDir);
```

补充：
```java
Path path = Paths.get("home", "sthg", "user.properties");
Path absolute = path.toAbsolutePath();
```

### InvalidPathException

如果路径不存在

### resolve()

helps to determine path to some file

e.g. to get path of our applications

人话: 
1. 在Java中，Path类提供了resolve()方法用于解析路径并生成新的Path对象。resolve()方法可以将相对路径或者子路径追加到现有路径上，生成一个新的路径。

	```java
	Path basePath = Paths.get("/home/user");
	Path resolvedPath = basePath.resolve("file.txt");
	```
	在这个例子中，resolve("file.txt") 将会将 "file.txt" 追加到 "/home/user" 路径上，生成新的Path对象 "/home/user/file.txt"。
2. 解析另一个Path对象：
   	```java
   	Path basePath = Paths.get("/home/user");
	Path subPath = Paths.get("dir", "file.txt");
	Path resolvedPath = basePath.resolve(subPath);
	```
	在这个例子中，resolve(subPath) 将会将 subPath 对象追加到 basePath 路径上，生成新的Path对象 "/home/user/dir/file.txt"。

resolve()方法会自动处理路径分隔符和规范化路径，确保生成的路径是正确的。需要注意的是，resolve()方法不会修改原始的Path对象，而是返回一个新的Path对象。原始的Path对象保持不变。

## File

```java
// read file
byte[] bytes = Files.readAllBytes(path);
// save to file
File.write(path, content.getBytes(chatset));
// other
Files.copy(fromPath, toPath)
FIles.move(fromPath, toPath)
Files.delete(path)
// 创建文件夹
Files.createDirectory(path)
// 创建路径里所有不存在的父目录
Files.createDirectories(path)
// 创建空文件
Files.createFile(path)
```

### lock 保护

```java
FileChannel channel = FileChannel.open(path, StandardOpenOption.WRITE);
FileLock lock = channel.lock();
// or
FileLock lock = channel.tryLock();
```

* 部分锁
  ```java
  FileLock lock(long start, long size, boolean shared)
  FileLock tryLock(long start, long size, boolean shared)
  ```

* 释放锁
  [try-with-resources](try-with-resources.md)
  ```java
  try(FileLock lock = channel.lock()) {
	  // do something
  }
  ```

### 注意点
1. close() 会释放锁
2. locking files  基于操作系统和以下几点
   1. supporting - 意思是支持锁定文件的操作系统或有权限就锁，没有权限，也会继续执行使用文件，只是没有锁不锁而已
   2. JVM level - 锁是基于JVM的，单个VM上运行的两个application不能锁同一个文件会抛出`OverlappingFileLockException`异常, 即该文件已经被锁定
   3. **有时候** closing channel 会释放VM上的所有锁。