# ElementPlus上传文件

## 获取文件内容
[上传文件获取文件内容](../../../计算机语言/JavaScript和TypeScript/JavaScript/知识积累/上传文件获取文件内容.md)

```html

<template>
	<el-upload class="upload-demo" drag :auto-upload="false" :on-change="handleChange">
		<el-icon class="el-icon--upload">
			<upload-filled />
		</el-icon>
		<div class="el-upload__text">
			Drop file here or <em>click to upload</em>
		</div>
		<template #tip>
			<div class="el-upload__tip">
				Use the exported file or write json/text by yourself.
			</div>
		</template>
	</el-upload>
</template>

<script>
	import {
		UploadFilled
	} from '@element-plus/icons-vue';

	import {
		defineProps
	} from 'vue';

	export default {
		components: {
			UploadFilled,
		},
		props: {
			fileVal: {
				type: JSON,
				required: false
			},
		},
		methods: {
			handleChange(file, fileList) {
				console.log(file.raw); // 上传的文件对象
				console.log(fileList); // 上传的文件列表
				const reader = new FileReader();
				reader.onload = (event) => {
					// 将读取到的文件内容存储到 Vue 实例的 data 中
					let jsonData = JSON.parse(event.target.result);
					console.log(jsonData);
				};
				reader.readAsText(file.raw); // 以文本方式读取文件内容
			}
		}
	}
</script>

<style>
</style>

```