#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "collectingpostsdialog.h"
#include "browser/browser.h"
#include "browser/browserwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_pushButtonSearch_clicked();
    void postCollectingEnded(QList<int> posts);
    void newFile();
    
    void on_pushButtonAllowPostToEdit_clicked();
    
    void on_pushButtonSkipPost_clicked();
    
    void on_pushButtonFilterPost_clicked();
    
    void on_listWidgetNotEditedPosts_itemDoubleClicked(QListWidgetItem *postItem);
    
private:
    void clearAll();
    void setEnabledLists(bool enabled);
    void browserOpenPost(int postId);
    void takePostToListWidget(QListWidget *listWid);
    
    Ui::MainWindow *ui;
    collectingpostsdialog *dialog;
    Browser browser;
    BrowserWindow *window;
    
    int currentOpenedPostId = -1;
    int currentPositionInNotEditedPostList = 0;
    
    ///Weblink for posts. At end of link needed add post id
    const QString webSitePostLink = "https://pikabu.ru/story/_";
};
#endif // MAINWINDOW_H
