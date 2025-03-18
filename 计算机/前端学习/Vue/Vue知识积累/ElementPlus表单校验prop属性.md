# ElementPlus表单校验prop属性

```html
<el-form :model="ruleForm" :rules="rules">
  <el-form-item label="活动名称" prop="name">
    <el-input v-model="ruleForm.name"></el-input>
  </el-form-item>
</el-form>
<script>
  export default {
    data() {
      return {
        ruleForm: {
          name: '',
        },
        rules: {
          name: [
            { required: true, message: '请输入名称', trigger: 'blur' },
            { min: 3, max: 5, message: '长度在 3 到 5 个字符', trigger: 'blur' }
          ]
        }
      };
    }
  }
</script>
```

以上的一个简单的例子可以告诉我们：prop 属性绑定了字段名 name，在表单验证时，就会找到其内部的表单组件绑定的变量 ruleForm.name 的值是否符合 rules 中与 name 对应的验证规则. (ruleForm 这个名字是随便起的，关键在于html中有 v-model 绑定了它)