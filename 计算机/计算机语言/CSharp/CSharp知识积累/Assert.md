# Assert

`Debug.Assert(templateFiles.Any())` 是一个断言语句，**用于在调试期间检查某个条件是否为 true。如果条件为 false，则会抛出 AssertionException 异常，指示断言失败。**

通常，断言语句用于在开发过程中帮助开发人员快速发现程序中的错误。在发布版本中，这些断言语句通常会被编译器忽略或禁用，以避免对程序性能的影响。