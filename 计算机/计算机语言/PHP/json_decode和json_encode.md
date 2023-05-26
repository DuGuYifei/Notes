# json_decode和json_encode

## json_decode

### 1. json_decode的作用

将json字符串转换为PHP对象或数组

### 2. json_decode的语法

```php
mixed json_decode ( string $json [, bool $assoc = false [, int $depth = 512 [, int $options = 0 ]]] )
```

```php
<?php
	$json = '{"name":"zhangsan","age":18}';
	$obj = json_decode($json);
	echo $obj->name;
?>
```

### 3. json_decode的参数

#### 3.1 json

要解码的json字符串，必须是utf-8编码的数据

#### 3.2 assoc

当该参数为true时，将返回数组，false时返回对象

#### 3.3 depth

设置最大深度，超过该深度的将被抛弃

#### 3.4 options

该参数是PHP5.4.0版本新增的，用于指定json_decode的行为，可以是以下常量的组合：

- JSON_BIGINT_AS_STRING：将大数字转换为字符串
- JSON_OBJECT_AS_ARRAY：将对象转换为数组
- JSON_BIGINT_AS_STRING：将大数字转换为字符串
- JSON_OBJECT_AS_ARRAY：将对象转换为数组

## json_encode

### 1. json_encode的作用

将PHP对象或数组转换为json字符串

### 2. json_encode的语法

```php
string json_encode ( mixed $value [, int $options = 0 [, int $depth = 512 ]] )
```

```php
<?php
	$arr = array(
		'name' => 'zhangsan',
		'age' => 18
	);
	echo json_encode($arr);
?>

<?php
	$obj = new stdClass();
	$obj->name = 'zhangsan';
	$obj->age = 18;
	echo json_encode($obj);
?>
```

### 3. json_encode的参数

#### 3.1 value

要编码的值，该参数必须是utf-8编码的数据

#### 3.2 options

该参数是PHP5.3.0版本新增的，用于指定json_encode的行为，可以是以下常量的组合：

- JSON_HEX_TAG：所有的<和>都将被转换为\u003C和\u003E
- JSON_HEX_AMP：所有的&都将被转换为\u0026
- JSON_HEX_APOS：所有的'都将被转换为\u0027
- JSON_HEX_QUOT：所有的"都将被转换为\u0022
- JSON_FORCE_OBJECT：将数组强制转换为对象
- JSON_NUMERIC_CHECK：将所有数字字符串编码为数字
- JSON_PRETTY_PRINT：用空白字符格式化返回的数据
- JSON_UNESCAPED_SLASHES：不对/进行转义
- JSON_UNESCAPED_UNICODE：不对Unicode编码的多字节字符进行转义
- JSON_PARTIAL_OUTPUT_ON_ERROR：当编码失败时，只输出部分数据
- JSON_PRESERVE_ZERO_FRACTION：对浮点数进行编码时，不使用小数点后面的0
- JSON_UNESCAPED_LINE_TERMINATORS：不对换行符进行转义