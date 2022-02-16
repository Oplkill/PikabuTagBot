#ifndef COLLECTINGPOSTSDIALOG_H
#define COLLECTINGPOSTSDIALOG_H

#include <QObject>
#include <QWidget>
#include <QDialog>

#include "networksearchposts.h"

QT_BEGIN_NAMESPACE
namespace Ui { class collectingpostsdialog; }
QT_END_NAMESPACE

class collectingpostsdialog : public QDialog
{
    Q_OBJECT
public: signals:
    void onAllCollected(QList<int> posts);
    
public:
    collectingpostsdialog(QWidget *parent, const QString &url);
    ~collectingpostsdialog();
    
private slots:
    void userEndedDialog(int result);
    void parsingEnded(QList<int> posts);
    void parsedNumberPosts(int numPosts);
    void updateProgress(int numParsed);
    
private:
    Ui::collectingpostsdialog *ui;
    
    QList<int> posts;
    networkSearchPosts postsSearcher;
    bool readedPosts = false;
};

#endif // COLLECTINGPOSTSDIALOG_H
