# useState_useEffect渲染顺序

useState 创建钩子 会在每次渲染时都会重新计算一次，所以每次渲染都会有一个独立的 state 值。
```
function Example() {
  const [count, setCount] = useState(0);
  console.log('render');
  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
    </div>
  );
}
```

useEffect 会在每次渲染时都会重新计算一次，所以每次渲染都会有一个独立的 effect。
```
function Example() {
  const [count, setCount] = useState(0);
  useEffect(() => {
    console.log('effect');
  });
  return (
    <div>
      <p>You clicked {count} times</p>
      <button onClick={() => setCount(count + 1)}>Click me</button>
    </div>
  );
}
```

顺序：
useState -> 渲染 -> useEffect