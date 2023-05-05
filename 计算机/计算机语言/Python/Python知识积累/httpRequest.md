# httpRequest

```python
import requests

url = 'http://localhost:8080/predict'

data = {
    'Age': 32,
    'Height(cm)': 175,
    'Weight(kg)': 70,
    'Occupation': 'SoftwareEngineer',
    'EducationLevel': "Master'sDegree",
    'MaritalStatus': 'Married',
    'Income(USD)': 75000,
    'FavoriteColor': 'Blue'
}

response = requests.post(url, data=data)

print(response.text)

```