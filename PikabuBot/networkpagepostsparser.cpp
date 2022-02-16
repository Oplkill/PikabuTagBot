#include "networkpagepostsparser.h"

#include <QUrl>

networkPagePostsParser::networkPagePostsParser()
{
    
}

void networkPagePostsParser::loadWebPageEnded()
{
    QNetworkReply *response = (QNetworkReply*)sender();
    QString htmlCode = QString(response->readAll());
    
    response->deleteLater();
    response = nullptr;
    
    QList<int> list;
    
    while (true)
    {
        int post = ParseSinglePost(htmlCode);

        if (post == -1)
        {
            int offset = htmlCode.indexOf(htmlPostComment);

            if (offset == -1)
                break;

            continue;
        }
        
        if (list.contains(post))
            continue;

        list.append(post);
    }
    
    emit onParsedWebPage_PostsList(list);
}

void networkPagePostsParser::parseWebPage(const QString &url)
{
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    connect(response, &QNetworkReply::finished, this, &networkPagePostsParser::loadWebPageEnded);
}

void networkPagePostsParser::loadWebPageEnded_numPosts()
{
    QNetworkReply *response = (QNetworkReply*)sender();
    QString htmlCode = response->readAll();
    
    response->deleteLater();
    response = nullptr;
    
    int offset = htmlCode.indexOf(htmlNumPostsTag_FirstPart);
    
    if (offset == -1)
    {
        emit onParsedWebPage_NumberPosts(0);
        return;
    }
    
    auto slicedCode = htmlCode.sliced(offset + htmlNumPostsTag_FirstPart.length());
    
    offset = slicedCode.indexOf(htmlNumPostsTag_SecondPart);
    if (offset == -1)
    {
        emit onParsedWebPage_NumberPosts(0);
        return;
    }
    
    auto slicedCode2 = slicedCode.sliced(offset + htmlNumPostsTag_SecondPart.length());
    int numPosts = StringGetNumberInFirstSymbols(slicedCode2);
    if (numPosts == -1)
        numPosts = 0;
    
    emit onParsedWebPage_NumberPosts(numPosts);
}

void networkPagePostsParser::parseNumberFindedPosts(const QString &url)
{
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    connect(response, &QNetworkReply::finished, this, &networkPagePostsParser::loadWebPageEnded_numPosts);
}

///
/// \brief parsing code to any postid, slicing "*htmlCode"
///
int networkPagePostsParser::ParseSinglePost(QString &htmlCode)
{
    int offset = htmlCode.indexOf(htmlPostComment);
    if (offset == -1)
        return -1;

    
    auto slicedCode = htmlCode.sliced(offset + htmlPostComment.length());
    htmlCode = QString(slicedCode);

    return StringGetNumberInFirstSymbols(htmlCode);
}

///
/// \brief returns number in string from first symbol until reached end of first number(any non number symbol)
/// \return '-1' if no number finded in first symbols
///
int networkPagePostsParser::StringGetNumberInFirstSymbols(const QString &str)
{
    QString strNumber = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i].isDigit())
            strNumber += str[i];
        else
            break;
    }

    bool isInt;
    int postId = strNumber.toInt(&isInt);
    if (!isInt)
        return -1;

    return postId;
}

///
/// \return Returns true if left any "htmlPostComment", including rubbish things
///
bool networkPagePostsParser::IsHTMLCodeHavePostsLeft(const QString &htmlCode)
{
    int offset = htmlCode.indexOf(htmlPostComment);

    return offset != -1;
}
