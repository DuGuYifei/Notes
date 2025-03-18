# "switch"语句

* switch必须严格相等（例子中输入3是未知值）
* case可以分组，上一个case里为空会和下一个合并（例子输入0/1）
  
  ```javascript
  let arg = prompt("Enter a value?")
  switch (arg) {
  	case '0': 
  	case '1':
		  alert( 'One or zero' );
		  break;
	  case '2':
		  alert( 'Two' );
		  break;
	  case 3:
		  alert( 'Never executes!' );
		  break;
	  default:
		  alert( 'An unknown value' )
  }
  ```




