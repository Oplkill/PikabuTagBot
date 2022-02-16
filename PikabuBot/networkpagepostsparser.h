#ifndef NETWORKPAGEPOSTSPARSER_H
#define NETWORKPAGEPOSTSPARSER_H

#include <QObject>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class networkPagePostsParser : public QObject
{
    Q_OBJECT
public: signals:
    void onParsedWebPage_PostsList(QList<int> posts);
    void onParsedWebPage_NumberPosts(int numberPosts);

public:
    networkPagePostsParser();

    void parseWebPage(const QString &url);
    void parseNumberFindedPosts(const QString &htmlCode);

private slots:
    void loadWebPageEnded();
    void loadWebPageEnded_numPosts();

private:
    bool IsHTMLCodeHavePostsLeft(const QString &htmlCode);
    int ParseSinglePost(QString &htmlCode);
    int StringGetNumberInFirstSymbols(const QString &str);

    ///using to detect posts in html code. but some advert posts or other rubbish things have that comment mark, need to skip them
    const QString htmlPostComment = "<!--story_";
    
    ///using to detect number posts in html code.
    const QString htmlNumPostsTag_FirstPart = "<div class=\"stories-search__feed-panel\">";
    ///using to detect number posts in html code. after first part, need find first entry in html code of that string
    const QString htmlNumPostsTag_SecondPart = "<span>";
    
    QNetworkAccessManager manager;
};

#endif // NETWORKPAGEPOSTSPARSER_H
