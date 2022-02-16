#include "collectingpostsdialog.h"
#include "./ui_collectingpostsdialog.h"

#include <QMessageBox>

collectingpostsdialog::collectingpostsdialog(QWidget *parent, const QString &url)
    : QDialog(parent)
    , ui(new Ui::collectingpostsdialog)
{
    ui->setupUi(this);
    
    connect(this, &QDialog::finished, this, &collectingpostsdialog::userEndedDialog);
    
    connect(&postsSearcher, &networkSearchPosts::onParsingEnded, this, &collectingpostsdialog::parsingEnded);
    connect(&postsSearcher, &networkSearchPosts::onParsedNumberPosts, this, &collectingpostsdialog::parsedNumberPosts);
    connect(&postsSearcher, &networkSearchPosts::onParsedUpdateProgress, this, &collectingpostsdialog::updateProgress);
    
    this->show();
    postsSearcher.startParsingSearchPages(url);
}

void collectingpostsdialog::userEndedDialog(int result)
{
    if (!readedPosts)
    {
        posts.append(postsSearcher.getCurrentParsedPosts());
    }
    
    emit onAllCollected(posts);
}

void collectingpostsdialog::parsingEnded(QList<int> posts)
{
    QApplication::beep();
    readedPosts = true;
    this->posts.append(posts);
}

void collectingpostsdialog::updateProgress(int numParsed)
{
    ui->progressBar->setValue(numParsed);
}

void collectingpostsdialog::parsedNumberPosts(int numPosts)
{
    if (numPosts == 0)
    {
        disconnect(&postsSearcher, &networkSearchPosts::onParsingEnded, this, &collectingpostsdialog::parsingEnded);
        QApplication::beep();
        QMessageBox::warning(this, tr("Ошибка!"), tr("Поиск не нашёл ни одного поста!"));
        this->done(-1);
        return;
    }
    
    ui->progressBar->setMaximum(numPosts);
}

collectingpostsdialog::~collectingpostsdialog()
{
    delete ui;
}
