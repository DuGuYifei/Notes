# 使用pipeline来Transform数据

## fit()方法
fit()是Pipeline类中的一个方法，用于训练整个Pipeline中的模型。具体来说，当你调用fit()方法时，每个Estimator会被按照指定的顺序拟合到数据上，产生一系列Transformer，这些Transformer被串联起来以形成一个完整的Pipeline，最终产生一个模型。这个模型可以用来对新数据进行预测。

## fit().transform()
piped_data = flights_pipe.fit(model_data).transform(data)
