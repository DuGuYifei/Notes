# ElementPlus组件的class问题

组件的class就是组件名，如：

```html
<el-form-item>
	<el-icon :size="size" class="svg-container">
		<Edit />
	</el-icon>
	<el-input v-model="form.name" />
</el-form-item>
```

scss中

```css
:deep(.el-form-item) {}
```

**带点**，而如果想直接操控标签，应使用:

比如：el-input, 组件class为`.el-input`，但是html标签为

```css
input {}
```