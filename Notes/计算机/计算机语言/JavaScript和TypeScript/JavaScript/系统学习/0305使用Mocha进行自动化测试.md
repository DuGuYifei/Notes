# 使用Mocha进行自动化测试

## 行为驱动开发（BDD）
测试，文档，示例

示例：

```javascript
describe("pow", function(){
    it("raises to n-th power", function(){
        assert.equal(pow(2,3), 8);
    });
});
```

* `describe("title", function(){...})`
  表示我们正在描述的功能是什么。
* `it("use case description", funciton(){...})`
  it里面的描述部分，我们以一种易于理解的方式描述特定的用例，第二个参数时用于堆其进行测试的函数。
* `assert.equal(value1, value2)`
  it块中的代码，如果实现是正确的，它应该在执行的时候不产生任何错误。\
  `assert.*`函数用于检查pow函数是否按照预期工作。这里用了`assert.equal`，它会堆参数进行比较，如果它们不相等则会抛出一个错误。

规范可以被执行，它将运行在it块中指定的测试。

## 行为规范
Mocha - describe it
Chai - assert
Sinon - 用于见识函数、模拟内建函数和其他函数库

既适用于浏览器端，也适用于服务器端

pow案例完整代码：
```html
<!DOCTYPE html>
<html>
<head>
  <!-- add mocha css, to show results -->
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/mocha/3.2.0/mocha.css">
  <!-- add mocha framework code -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/mocha/3.2.0/mocha.js"></script>
  <script>
    mocha.setup('bdd'); // minimal setup
  </script>
  <!-- add chai -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/chai/3.5.0/chai.js"></script>
  <script>
    // chai has a lot of stuff, let's make assert global
    let assert = chai.assert;
  </script>
</head>

<body>

  <script>
    function pow(x, n) {
      /* function code is to be written, empty now */
    }
  </script>

  <!-- the script with tests (describe, it...) -->
  <script src="test.js"></script>

  <!-- the element with id="mocha" will contain test results -->
  <div id="mocha"></div>

  <!-- run tests! -->
  <script>
    mocha.run();
  </script>
</body>

</html>
```
test.js就是 
```js
describe("pow", function() {

  it("raises to n-th power", function() {
    assert.equal(pow(2, 3), 8);
    assert.equal(pow(3, 4), 81);
  });

});
```
或
```js
describe("pow", function() {

  it("2 raised to power 3 is 8", function() {
    assert.equal(pow(2, 3), 8);
  });

  it("3 raised to power 4 is 81", function() {
    assert.equal(pow(3, 4), 81);
  });

});
```
或
```js
describe("pow", function() {

  function makeTest(x) {
    let expected = x * x * x;
    it(`${x} in the power 3 is ${expected}`, function() {
      assert.equal(pow(x, 3), expected);
    });
  }

  for (let x = 1; x <= 5; x++) {
    makeTest(x);
  }

});
```