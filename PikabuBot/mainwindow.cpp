#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QLayout>
#include "browser/tabwidget.h"
#include "tagmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setEnabledLists(false);
    
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::newFile);
    
    window = browser.createWindow();
    window->tabWidget()->setUrl(QUrl("https://pikabu.ru"));
    ui->layoutBrowser->addWidget(window);
    
    
    //todo for test purpose only
    TagManager *tagMan = new TagManager();
    tagMan->AddTag(3898012, "Кот");
    //--------------
    
    
    //-----------------------------
    //todo for test purpose only
    ui->textEditSearchLink->setText("https://pikabu.ru/tag/%D0%92%D0%B8%D0%B4%D0%B5%D0%BE,%D0%9C%D0%BE%D0%BF%D1%81?et=%D0%A1%D0%BE%D0%B1%D0%B0%D0%BA%D0%B0");
    //--------------
}

void MainWindow::on_pushButtonSearch_clicked()
{
    newFile();
    
    dialog = new collectingpostsdialog(this, ui->textEditSearchLink->toPlainText());
    connect(dialog, &collectingpostsdialog::onAllCollected, this, &MainWindow::postCollectingEnded);
}

void MainWindow::postCollectingEnded(QList<int> posts)
{
    currentPositionInNotEditedPostList = 0;
    
    dialog->deleteLater();
    dialog = nullptr;
    
    QStringList strList;
    for (int post : posts)
    {
        strList.append(QString::number(post));
    }
    ui->listWidgetNotEditedPosts->addItems(strList);
    
    if (posts.count())
    {
        setEnabledLists(true);
        
        browserOpenPost(posts.first());
    }
}

void MainWindow::browserOpenPost(int postId)
{
    currentOpenedPostId = postId;
    
    QUrl url(webSitePostLink + QString::number(postId));
    window->tabWidget()->setUrl(url);
}

void MainWindow::newFile()
{
    //... todo
    
    clearAll();
    setEnabledLists(false);
}

void MainWindow::setEnabledLists(bool enabled)
{
    ui->listWidgetNotEditedPosts->setEnabled(enabled);
    ui->listWidgetEditedPosts->setEnabled(enabled);
    ui->listWidgetFiltred->setEnabled(enabled);
    ui->listWidgetPlannedToEditPosts->setEnabled(enabled);
}

void MainWindow::clearAll()
{
    ui->listWidgetNotEditedPosts->clear();
    ui->listWidgetEditedPosts->clear();
    ui->listWidgetFiltred->clear();
    ui->listWidgetPlannedToEditPosts->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::takePostToListWidget(QListWidget *listWid)
{
    if (ui->listWidgetNotEditedPosts->count() == 0)
        return;
    
    auto item = ui->listWidgetNotEditedPosts->takeItem(currentPositionInNotEditedPostList);
    auto post = item->text();
    auto postId = post.toInt();
    
    listWid->addItem(post);
    
    if (currentPositionInNotEditedPostList >= ui->listWidgetNotEditedPosts->count())
        currentPositionInNotEditedPostList = 0;
    
    auto nextPostItem = ui->listWidgetNotEditedPosts->item(currentPositionInNotEditedPostList);
    int nextPostId = 0;
    if (nextPostItem)
    {
        ui->listWidgetNotEditedPosts->setCurrentItem(nextPostItem);
        auto nextPost = nextPostItem->text();
        nextPostId = nextPost.toInt();
    }
    
    browserOpenPost(nextPostId);
    
    delete item;
}

void MainWindow::on_pushButtonAllowPostToEdit_clicked()
{
    takePostToListWidget(ui->listWidgetPlannedToEditPosts);
}


void MainWindow::on_pushButtonSkipPost_clicked()
{
    if (ui->listWidgetNotEditedPosts->count() == 0)
        return;
    
    currentPositionInNotEditedPostList++;
    if (currentPositionInNotEditedPostList >= ui->listWidgetNotEditedPosts->count())
        currentPositionInNotEditedPostList = 0;
    
    auto nextPostItem = ui->listWidgetNotEditedPosts->item(currentPositionInNotEditedPostList);
    auto nextPost = nextPostItem->text();
    auto nextPostId = nextPost.toInt();
    
    ui->listWidgetNotEditedPosts->setCurrentItem(nextPostItem);
    browserOpenPost(nextPostId);
}


void MainWindow::on_pushButtonFilterPost_clicked()
{
    takePostToListWidget(ui->listWidgetFiltred);
}


void MainWindow::on_listWidgetNotEditedPosts_itemDoubleClicked(QListWidgetItem *postItem)
{
    currentPositionInNotEditedPostList = ui->listWidgetNotEditedPosts->currentRow();
    auto post = postItem->text();
    auto postId = post.toInt();
    
    browserOpenPost(postId);
    ui->tabWidget->setCurrentWidget(ui->tab_2);
}

