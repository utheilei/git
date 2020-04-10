#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <DListView>

DWIDGET_USE_NAMESPACE

class ListWidget : public DListView
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = nullptr);
    QStandardItemModel *getItemModel();

signals:

public slots:

private:
    QStandardItemModel *itemModel;
};

#endif // LISTWIDGET_H
