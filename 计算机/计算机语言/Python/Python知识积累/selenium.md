# selenium

## 介绍

selenium是一个自动化工具，可以用来模拟浏览器操作，比如打开网页，点击按钮，输入文字等等。它可以用来做爬虫，也可以用来做自动化测试。

## 常用方法

### 打开网页

```python
from selenium import webdriver
driver = webdriver.Chrome()
driver.get('https://www.baidu.com')
```

### 查找元素

```python
# 通过id查找
driver.find_element(By.ID, 'id')
# 通过class查找
driver.find_element(By.CLASS_NAME, 'class')
...
```

### 点击元素

```python
driver.find_element(By.ID, 'id').click()
```

### 输入文字

```python
driver.find_element(By.ID, 'id').send_keys('text')
```

### 获取元素的文字

```python
driver.find_element(By.ID, 'id').text
```

### 获取元素的属性

```python
wait = WebDriverWait(self.driver, 10)
element = wait.until(EC.visibility_of_element_located((By.ID, 'resume-search-nprogress-loading')))
while element.get_attribute('class') != 'wrap':
    # print(element.get_attribute('class'))
    continue
```

### 等待直到某个元素出现或超时

```python
from selenium.webdriver.support.ui import WebDriverWait
WebDriverWait(self.driver, 180, 0.5).until(EC.title_contains(self.main_page_title))
```

#### EC

```python
from selenium.webdriver.support import expected_conditions as EC

# 等待某个元素可见
EC.visibility_of_element_located((By.ID, 'id'))
# 等待某个元素可点击
EC.element_to_be_clickable((By.ID, 'id'))
# 等待某个元素的属性值变为某个值
EC.attribute_to_be((By.ID, 'id'), 'attribute', 'value')
# 等待某个元素的属性值包含某个值
EC.attribute_contains((By.ID, 'id'), 'attribute', 'value')
```

## 案例登录和cookie登录

```python
    def login(self):
        self.driver.get(self.login_url)

        # cookie may expire,do remember delete cookies.pkl file, then you can re-login
        if os.path.exists('cookies.pkl'):
            cookies = load_cookies()
            # print(cookies)
            self.driver.delete_all_cookies()
            for cookie in cookies:
                self.driver.add_cookie(cookie)
        else:
            username_input = self.driver.find_element(By.CLASS_NAME, "phone-item-input")
            username_input.send_keys(self.phone_number)
            WebDriverWait(self.driver, 180, 0.5).until(EC.title_contains(self.main_page_title))
            self.cookies = self.driver.get_cookies()
            save_cookies(self.cookies)
            # print(self.cookies)

        print("登录成功 - login success")
```