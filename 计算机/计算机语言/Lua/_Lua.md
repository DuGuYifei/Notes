# _Lua

1. [基础](#基础)
   1. [全局/局部变量](#全局局部变量)
   2. [nil](#nil)
   3. [赋值](#赋值)
   4. [数据类型](#数据类型)
      1. [number](#number)
      2. [string:](#string)
      3. [function: 返回值默认nil](#function-返回值默认nil)
      4. [table](#table)
      5. [table 字符串下标（对象）](#table-字符串下标对象)
      6. [table \_G global](#table-_g-global)
      7. [boolean 和 if](#boolean-和-if)
         1. [~=](#)
         2. [逻辑](#逻辑)
         3. [特殊点](#特殊点)
   5. [分支判断](#分支判断)
   6. [循环](#循环)
   7. [print](#print)


## 基础

### 全局/局部变量

`local`就是局部，不写就是全局，其他文件也能用

### nil
空，不赋值就是空

### 赋值
```lua
a,b,c = 1,2
-- a = 1 b = 2 c = nil
```
### 数据类型
#### number 
`0x11, 2e10` 2 * 10^10, `10^5` 10的五次方不是异或

#### string: 
1. 两个中括号可以多行`[[]]`
        ```lua
        c = [[
             asdf
             asdf\n
         ]]
        ```
2. `a..b`链接两个字符串变量
3. `tonumber("10")`转换失败是nil
4. `tostring(10)`
5. `print(#a)`返回长度
6. `s = string.char(0x30,0x31,0x00,0x32)` 是`012`，ascii码
7. `n = string.byte(s, 2)` 是`49`，是`1`的ascii码
8. 注意上面0x00也能存，不会使字符串结束

#### function: 返回值默认nil
   ```lua
    function f(a, b, c)
        --body
    end

    f(1,2)
   ```

#### table
* `a = {1,"ab", {}, fcuntion() end}` 
* 索引从1开始
* 可以超过长度取值，返回nil
* 可以超长度赋值
* 也可以用insert赋值
  * `table.insert(a, "d")`
  * `table.insert(a, 2, "d")`
* `table.remove(a, 2)`返回被移除的元素
* `#`返回长度

#### table 字符串下标（对象）
```lua
a = {
    a = 1,
    b = "1234",
    c = function()

    end,
    d = 123123,
    [",;"] = 123
}

print(a["a"])
print(a.a)
print(a[",;"])
```

#### table _G global
所有的全局变量都在`_G`

`print(_G["a"])`

包括之前使用的函数`table.insert`之类的这里的`table`也是一个`_G`的下标，所以可以`print(_G["table"]["insert"])`

#### boolean 和 if

##### ~=
不等于

##### 逻辑
`and or not`

##### 特殊点
* 只有false和nil是假，其他都是真包括0.
* 除了not都会直接返回值
```lua
a = nil --假
b = 0 --真
print(a and b) --nil
print(a or b) -- 0
print(not a) --true
print(6 > 10 and "yes" or "no") -- "no"
```
### 分支判断
```lua
if 1 > 10 then

elseif 1 < 10 then

elseif

end
```

### 循环
```lua
for i=1,10 do
    print(i)
end

for i=10,1,-2 do -- 10 8 6 4 2
    print(i)
    i = 10          -- 赋值均为local变量不影响循环，循环一旦设立无法更改
    local i = 10

    --但可以这样：（但是如果有上面的赋值语句就不行了，因为会按local变量来运算）
    if i == 4 then break end
end

local n = 10
while n > 1 do
    n = n -1 -- 不支持自减n--
end


a = 10
repeat
   print("a的值为:", a)
   a = a + 1
until( a > 15 )
```

### print
```lua
print(a)
print(a,#a)
```