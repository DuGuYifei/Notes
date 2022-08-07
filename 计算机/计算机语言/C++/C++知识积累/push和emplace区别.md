# push和emplace区别

[emplace](emplace.md)

```cpp
stack<pair<int, int>> run;

run.push(idx, timestamp); // 会报错
run.emplace(idx, timestamp); // 不会报错
```
