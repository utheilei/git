#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <DTitlebar>
#include <QStackedWidget>
#include <DFrame>

DWIDGET_USE_NAMESPACE

class ListWidget;
class MainWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setWidget(int row);

signals:

public slots:
    //void slotsetWidget(const QModelIndex &index);
    //void slotChangeWidget(const QModelIndex &previous);

private:
    DTitlebar *m_titlebar;
    QMap<QString,QWidget *> m_listWidget;
    QStackedWidget *m_stackedWidget;
    ListWidget *listwidget;
    DFrame *leftWidget;
    DFrame *rightWidget;
};

#endif // MAINWINDOW_H
