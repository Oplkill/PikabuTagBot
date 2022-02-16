#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QObject>
#include <QWidget>
#include <QNetworkAccessManager>

class TagManager : public QObject
{
    Q_OBJECT
public:
    TagManager();
    
    void SetCookie(const QString &key, const QString &value);
    void AddTag(int post, const QString &tag);
    
private slots:
    void PostReplyFinished(QNetworkReply *reply);
    void findished(QNetworkReply *reply, const QList<QSslError> &errors);
    
private:
    QNetworkAccessManager *netManager;
    QNetworkCookieJar *cookieJar;
    
    ///Link for sending post request to add tag
    const QString linkAddTag = "https://pikabu.ru/ajax/cedit_actions.php?action=add-tag";
};

#endif // TAGMANAGER_H
