# UObject::CreateDefaultSubobject

Create a component or subobject, allows creating a child class and returning the parent class.

| 参数                       | 描述                                                                                         |
| -------------------------- | -------------------------------------------------------------------------------------------- |
| TReturnType                | Class of return type, all overrides must be of this type                                     |
| TClassToConstructByDefault | Class of object to actually construct, must be a subclass of TReturnType                     |
| SubobjectName              | Name of the new component                                                                    |
| bTransient                 | 如果将组件分配给瞬态(Transient)属性，则为 True。这不会使组件本身瞬态，但会阻止它继承父默认值 |