#ifndef NETWORKSEARCHPOSTS_H
#define NETWORKSEARCHPOSTS_H

#include <QObject>
#include <QWidget>

#include "networkpagepostsparser.h"

class networkSearchPosts : public QObject
{
    Q_OBJECT
public: signals:
    void onParsingEnded(QList<int> posts);
    void onParsedNumberPosts(int numPosts);
    void onParsedUpdateProgress(int currentParsedNumPosts);
    
public:
    networkSearchPosts();
    
    ///
    /// \param url must be first page!(without any "&page=XX" at end)
    ///
    void startParsingSearchPages(const QString &url);
    
    QList<int> getCurrentParsedPosts();
    
private slots:
    void parsedSinglePage(QList<int> posts);
    void parsedNumberPosts(int numPosts);
    
private:
    ///using for selecting pages in search
    const QString addressTextPage = "&page=";
    
    QList<int> posts;
    networkPagePostsParser pageParser;
    QString firstPageUrl;
    int currentPage;
    
    
    //https://pikabu.ru/tag/%D0%92%D0%B8%D0%B4%D0%B5%D0%BE,%D0%9C%D0%BE%D0%BF%D1%81?et=%D0%A1%D0%BE%D0%B1%D0%B0%D0%BA%D0%B0&page=1
};

#endif // NETWORKSEARCHPOSTS_H
