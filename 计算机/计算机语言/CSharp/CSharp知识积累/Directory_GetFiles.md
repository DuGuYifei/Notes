# Directory_GetFiles

```csharp
public static string[] GetFiles(string path);
public static string[] GetFiles(string path, string searchPattern);
public static string[] GetFiles(string path, string searchPattern, SearchOption searchOption);
```

其中，path 参数指定要搜索的目录的路径，searchPattern 参数用于指定搜索模式，可以使用通配符（例如，* 表示匹配任意数量的字符，? 表示匹配一个字符），searchOption 参数用于指定搜索选项，可以是 SearchOption.TopDirectoryOnly（仅搜索当前目录）或 SearchOption.AllDirectories（包括子目录）。

该方法返回一个字符串数组，包含指定目录中符合条件的文件的完整路径。如果指定目录不存在或者无法访问，则会抛出 DirectoryNotFoundException 或 UnauthorizedAccessException 异常。如果指定的搜索模式不正确，则会抛出 ArgumentException 异常。