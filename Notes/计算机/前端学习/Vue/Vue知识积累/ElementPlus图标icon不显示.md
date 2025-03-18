# ElementPlus图标icon不显示

可能是因为export导致的，加上这段代码
```javascript
	import {
		Suitcase,
		User,
		CreditCard
	} from '@element-plus/icons-vue';


	export default {
		components: {
			Suitcase,
			User,
			CreditCard
		}
	}
```