#include "networksearchposts.h"

networkSearchPosts::networkSearchPosts()
{
    connect(&pageParser, &networkPagePostsParser::onParsedWebPage_PostsList, this, &networkSearchPosts::parsedSinglePage);
    connect(&pageParser, &networkPagePostsParser::onParsedWebPage_NumberPosts, this, &networkSearchPosts::parsedNumberPosts);
}

void networkSearchPosts::startParsingSearchPages(const QString &url)
{
    firstPageUrl = url;
    currentPage = 1;
    
    pageParser.parseNumberFindedPosts(url);
}

void networkSearchPosts::parsedSinglePage(QList<int> posts)
{
    this->posts.append(posts);
    
    if (posts.count() == 0)
    {
        emit onParsingEnded(this->posts);
        return;
    }
    
    currentPage++;
    QString nextPageUrl = firstPageUrl + addressTextPage + QString::number(currentPage);
    pageParser.parseWebPage(nextPageUrl);
    
    emit onParsedUpdateProgress(this->posts.count());
}

QList<int> networkSearchPosts::getCurrentParsedPosts()
{
    return posts;
}

void networkSearchPosts::parsedNumberPosts(int numPosts)
{
    emit onParsedNumberPosts(numPosts);
    
    if (numPosts)
        pageParser.parseWebPage(firstPageUrl);
}
