# getElementById

```html
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>菜鸟教程(runoob.com)</title>
<script>
function changeLink(){
    document.getElementById('myAnchor').innerHTML="RUNOOB";
    document.getElementById('myAnchor').href="//www.runoob.com";
    document.getElementById('myAnchor').target="_blank";
}
</script>
</head>
<body>
 
<a id="myAnchor" href="//www.microsoft.com">Microsoft</a>
<input type="button" onclick="changeLink()" value="修改链接">
 
</body>
</html>
```