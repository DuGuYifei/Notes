# ElementPlus按需导入

vue ui 可以直接下载

安装unplugin-vue-components 和 unplugin-auto-import这两款插件

```cmd
npm install -D unplugin-vue-components unplugin-auto-import
```

```js
import {
	defineConfig
} from 'vite'
import vue from '@vitejs/plugin-vue'
import AutoImport from 'unplugin-auto-import/vite'
import Components from 'unplugin-vue-components/vite'
import { ElementPlusResolver } from 'unplugin-vue-components/resolvers'

// https://vitejs.dev/config/
export default defineConfig({
	plugins: [vue(),
		AutoImport({
			resolvers: [ElementPlusResolver()],
		}),
		Components({
			resolvers: [ElementPlusResolver()],
		}),
	]
})
```
