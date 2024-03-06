# lambda表达式

```csharp
(parameters) => expression

Func<int, int, int> add = (x, y) => x + y;
int sum = add(2, 3); // sum = 5

() => { return 2; }

get => _name;
```