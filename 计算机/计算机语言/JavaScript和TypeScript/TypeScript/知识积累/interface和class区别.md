# interface和class区别

ts中class除了建立一个类以外，同时也会建立一个同名的interface，该interface只包含其中实例属性和实例方法，因此class既能够看成类，也能够看成interface使用。

所以：**当一个class iimplements interface时，所有的属性得重抄一遍**


```Typescript
//类Person
class Person {
 name: string;
 age: number;
 constructor(name: string, age: number) {
  this.name = name;
	this.age = age;
 }
};

//类充当接口使用,接口中只包含其中的实例属性和实例方法（constructor和static不在其中）
const person: Person = {
 name: '张三',
 age: 18
};

//接口继承类
interface Person1 extends Person{
 sex: string,
 printName() : void
};

const person1: Person1 = {
 name: '张三',
 age: 18,
 sex: '男',
 printName() {
    console.log(this.name) 
 }
};

//类实现接口
class Person2 implements Person1 {
  name: string;
  age: number;
  sex: string;
  email: string;
  printName() {
    console.log(this.name)
  };
}
```