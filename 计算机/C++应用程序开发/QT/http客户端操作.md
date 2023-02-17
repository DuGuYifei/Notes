# http客户端操作

[Qt实现HTTP客户端操作_龚建波的博客-CSDN博客_qt http](https://blog.csdn.net/gongjianbo1992/article/details/97568863)


## 添加模块
* CMake添加：[Qt Network 6.4.2](https://doc.qt.io/qt-6/qtnetwork-index.html)
* qMake：QT += Network

## 基本操作
```cpp
//构建一个manager对象
QNetworkAccessManager *manager = new QNetworkAccessManager(this); 
//manager具有异步API，当http请求完成后，会通过finished信号进行通知
connect(manager,&QNetworkAccessManager::finished,this,&MyClass::replyFinished); 
//发送异步get请求
manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
 
//这里也可以用一个QEventLoop来等待请求完成，但是我更爱用槽函数
//QNetworkReply *reply=manager->get(request);
//QEventLoop eventLoop;
//connect(reply, &QNetworkReply ::finished, &eventLoop, &QEventLoop::quit);
//eventLoop.exec();
//QByteArray reply_data=reply->readAll();
```

## 状态码
```cpp
QVariant code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
if (!code.isNull() && code.toInt() == 200)
{
	result = reply->readAll();
	qDebug() << "Code: " << code.toInt() << "response: " << result;
	response = result;
	return code.toInt();
}
else if (!code.isNull())
{
	qDebug() << "Code: " << code.toInt();
	return code.toInt();
}
```

## error
* Forbidden - QNetworkReply::ContentAccessDenied
* not found - QNetworkReply::ContentNotFoundError
* bad request - QNetworkReply::ProtocolInvalidOperationError
```cpp
QNetworkReply* reply = manager->put(request, requestBody);
if(reply->error() == QNetworkReply::ContentNotFoundError)
{
    messageBox.setText("Invalid key");
    messageBox.setDefaultButton(QMessageBox::Ok);
    messageBox.exec();
}
```

## 完整案例 (按下按钮发送带request body的请求)
```cpp
#include "confirmsendpushbutton.h"
#include <QEventLoop>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkInterface>
#include <QJsonDocument>
#include <QNetworkReply>

#define CHECK_IN_URL "http://localhost:8089/api/keys/key-check"

QString getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    int cnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < cnt; i++)
    {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;
}

void handleReply(QNetworkReply* reply)
{
    QMessageBox messageBox;
    qDebug() << reply->error();
    if(reply->error() == QNetworkReply::ContentNotFoundError)
    {
        messageBox.setText("Invalid key");
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
    else if(reply->error() == QNetworkReply::ContentAccessDenied)
    {
        const QByteArray reply_data = reply->readAll();
        messageBox.setText(reply_data);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
    else if(reply->error() == QNetworkReply::NoError)
    {
        const QByteArray reply_data = reply->readAll();
        messageBox.setText(reply_data);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
    else
    {
        messageBox.setText(&"Error type: " [reply->error()]);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
}

ConfirmSendPushButton::ConfirmSendPushButton(const QString &text, QWidget *parent, QLineEdit* keyEdit) :QPushButton(text, parent)
{
    this->keyEdit = keyEdit;
    manager = new QNetworkAccessManager(this);
    connect(this, &ConfirmSendPushButton::clicked, this, &ConfirmSendPushButton::clickEvents);
}

void ConfirmSendPushButton::clickEvents()
{
    // url
    QUrl url(CHECK_IN_URL);
    QNetworkRequest request(url);

    // requestbody
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=utf-8");
    QJsonObject requestJson;
    requestJson.insert("key_str", keyEdit->text());
    requestJson.insert("mac_hash", getHostMacAddress());
    QJsonDocument requestDoc;
    requestDoc.setObject(requestJson);
    QByteArray requestBody = requestDoc.toJson(QJsonDocument::Compact);

    // send request
    QNetworkReply* reply = manager->put(request, requestBody);
    QMessageBox messageBox(QMessageBox::Information, "", "Checking...", QMessageBox::Cancel);
    connect(reply, &QNetworkReply::finished, &messageBox, &QMessageBox::close);
    messageBox.exec();

    handleReply(reply);
}
```