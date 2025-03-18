# 按需加载js脚本
```JavaScript
let mobile_flag = false;
function isMobile() {
	let userAgentInfo = navigator.userAgent;
	let mobileAgents = ["Android", "iPhone", "SymbianOS", "Windows Phone", "iPad", "iPod"];
	for (let v = 0; v < mobileAgents.length; v++) {
		if (userAgentInfo.indexOf(mobileAgents[v]) > 0) {
			mobile_flag = true;
			break;
		}
	}
}

function loadScript(url, callback) {
	let script = document.createElement('script');
	if (script.readyState) {
		script.onchangereadystate = function() {
			if (script.readyState == 'complate' || script.readyState == 'loaded') {
				callback();
			}
		}
	} else {
		script.onload = function() {
			callback();
		}
	}
	script.src = url;
	document.body.appendChild(script);
}

isMobile();

if(!mobile_flag)
{
	loadScript("js/head.js", function(){console.log("loding");});
}
```