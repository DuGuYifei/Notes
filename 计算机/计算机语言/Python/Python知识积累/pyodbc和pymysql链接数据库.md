## pyodbc

使用连接字符串连接

```python
conn_str = 'DRIVER={MySQL ODBC 8.0 Unicode Driver};Port=3306;Server=xxxxx;Database=translation;User=root;Password=xxxx;Option=3;'

def connect_db():
    """
    Connect db_connection to database
    :return:
    """
    db_connection = pyodbc.connect(conn_str)
```

## pymysql

```python
 def connect_db():
    """
    Connect db_connection to database
    :return:
    """
    db_connection = pymysql.connect(host='xxxxx', port=3306, user='root', passwd='xxxxx', db='translation', charset='utf8mb4')
    return db_connection
    
    if try_count > 3:
        return
    try:
        with connect_db() as db_connection:
            db_cursor = db_connection.cursor()
            db_cursor.execute("INSERT INTO file_t (path, filename) VALUES (%s, %s)", (path, filename))
            db_connection.commit()
    except pyodbc.OperationalError:
        add_file(path, filename, try_count + 1)
```