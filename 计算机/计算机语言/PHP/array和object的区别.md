# array和object的区别

## array
```php
<?php
	$arr = array(
		'name' => 'zhangsan',
		'age' => 18
	);
	echo $arr['name'];
?>
```

## object
```php
<?php
	$obj = new stdClass();
	$obj->name = 'zhangsan';
	$obj->age = 18;
	echo $obj->name;
?>