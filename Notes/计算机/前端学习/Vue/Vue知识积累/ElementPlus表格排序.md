# ElementPlus表格排序
```html
<template>
  <el-table :data="tableData" :default-sort="{ prop: 'name', order: 'ascending' }">
    <el-table-column prop="name" label="姓名" :sort-orders="nameSortOrders"></el-table-column>
    <el-table-column prop="age" label="年龄"></el-table-column>
    <el-table-column prop="address" label="地址"></el-table-column>
  </el-table>
</template>

<script>
import { ref } from 'vue';

export default {
  setup() {
    const nameSortOrders = [
      { label: '升序', value: 'ascending' },
      { label: '降序', value: 'descending' },
      { label: '不排序', value: null },
    ];
    const tableData = ref([
      { name: '张三', age: 20, address: '北京' },
      { name: '李四', age: 30, address: '上海' },
      { name: '王五', age: 25, address: '广州' },
    ]);

    return { nameSortOrders, tableData };
  },
};
</script>
```