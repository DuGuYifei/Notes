# bs4整理html内容

content_page 可以用 [selenium](selenium.md) 的 `driver.page_source` 获取
```python
from bs4 import BeautifulSoup

content_page = self.driver.page_source

soup = BeautifulSoup(content_page, 'html.parser')

# 获取所有的标签
soup.find_all('div')
rows = soup.find_all('tr', class_='no-hover-tr')
for row in rows:
	work_exp_rows = row.find_all('div', class_='c-edu-wrap')[0].find_all('p')
	company_position = exp_row.find('span', class_='c-sp').text.strip()
```
