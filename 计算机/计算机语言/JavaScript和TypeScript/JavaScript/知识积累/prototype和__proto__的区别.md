# prototype和__proto__的区别

1. prototype
   也叫原型属性,它是函数独有的,每个函数都有一个prototype属性,它是一个指针,指向一个对象,这个对象包含了所有实例共享的属性和方法.

2. `__proto__`
   实例对象都有的属性(proto左右各两个短杠),它指向了该实例对象对应的原型对象.

prototype与__proto__都指向原型对象,任意一个函数(包括构造函数)都有一个prototype属性,**指向该函数的原型对象**;任意一个构造函数实例化的对象,都有一个__proto__对象,它**指向构造函数的原型对象**（一般来说就是继承对象）.
即：`s.proto === Student.prototype`

`__proto__` 不是对象的属性，而是 `Object.prototype` 的访问器属性