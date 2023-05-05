# flask

```python
from flask import Flask, request, jsonify
from utils.data_handler import handle_data
import joblib
import pandas as pd

app = Flask(__name__)

pred_dict = ["female", "male"]

# 加载训练好的随机森林模型
model = joblib.load("dtc_model.pkl")


# 定义路由和请求方法
@app.route('/predict', methods=['POST'])
def predict():
    df = pd.DataFrame.from_dict(request.form.to_dict(), orient='index').T
    df = handle_data(df)

    # 预测
    prediction = model.predict(df)[0]

    # 返回 JSON
    response = {
        'gender of prediction': pred_dict[prediction]
    }
    return jsonify(response)


if __name__ == '__main__':
    app.run(host='localhost', port=8080, debug=True)
```

## app
app 是flask的核心实例

## @app.router
路由器，用于定义路由和请求方法