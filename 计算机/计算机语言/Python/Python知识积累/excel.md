# excel

```python
def save_to_xlsx(employee):
    headers = list(employee.keys())
    try:
        # 尝试加载现有的XLSX文件
        workbook = load_workbook(file_name)
        sheet = workbook.active
    except FileNotFoundError:
        # 如果文件不存在，则创建一个新的XLSX文件
        workbook = Workbook()
        sheet = workbook.active
        # 写入表头
        sheet.append(headers)

    # 将字典的值按顺序组成列表
    values = [employee[key] if not isinstance(employee[key], list) else str(employee[key]) for key in headers]
    # 追加数据
    sheet.append(values)
    # 保存文件
    workbook.save(file_name)
```