#ifndef EDITINGDATA_H
#define EDITINGDATA_H

#include <QObject>
#include <QWidget>

class EditingData : public QObject
{
    Q_OBJECT
public:
    EditingData(const QString &searchLink);

    QString searchLink;
    QList<int> notFilteredPosts;
    QList<int> ignoredPosts;
    QList<int> editedPosts;
    QList<int> willBeEditedPosts;
};

#endif // EDITINGDATA_H
