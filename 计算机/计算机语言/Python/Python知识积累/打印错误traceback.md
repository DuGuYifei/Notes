# 打印错误traceback

```python
    try:
        convert(file_directory, filename)
    except Exception as e:
        print("Convert error: ")
        traceback.print_exc()
    finally:
        print("Convert error: ")
```