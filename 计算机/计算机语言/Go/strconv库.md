# strconv库

```go
pathSegments := strings.Split(r.URL.Path, "/")
id, err := strconv.Atoi(pathSegments[2])
```