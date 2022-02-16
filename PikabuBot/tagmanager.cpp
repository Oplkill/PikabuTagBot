#include "tagmanager.h"

#include <QNetworkCookie>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>

TagManager::TagManager()
{
    netManager = new QNetworkAccessManager();
    connect(netManager, &QNetworkAccessManager::finished, this, &TagManager::PostReplyFinished);
    
    cookieJar = new QNetworkCookieJar();
}

void TagManager::SetCookie(const QString &key, const QString &value)
{
    QByteArray cookieName, cookieValue;
    
    cookieName.append(key.toUtf8());
    cookieValue.append(value.toUtf8());
    
    QNetworkCookie *cookie = new QNetworkCookie(cookieName, cookieValue);
    cookieJar->insertCookie(*cookie);
    
    netManager->setCookieJar(cookieJar);
}

void TagManager::AddTag(int post, const QString &tag)
{
    QByteArray reqdata;
     
    reqdata.append("sid=" + QString::number(post).toUtf8());
    reqdata.append("&tag=" + QUrl::toPercentEncoding(tag.toUtf8()));
 
    QNetworkRequest request;
    QUrl url(linkAddTag);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
 
    connect(netManager, &QNetworkAccessManager::sslErrors, this, &TagManager::findished);
    
    auto reply = netManager->post(request, reqdata);
    //connect(reply, &QNetworkReply::finished, this, &TagManager::findished);
}

void TagManager::findished(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug()<<"---findished";
}

void TagManager::PostReplyFinished(QNetworkReply *reply)
{
    qDebug()<<linkAddTag;
    if(reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"NO ERROR!";
    }
    else
    {
        qDebug()<<"errror!!!!"<<reply->errorString();
    }
 
    reply->deleteLater();
}
