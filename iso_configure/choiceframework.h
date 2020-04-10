#ifndef CHOICEFRAMEWORK_H
#define CHOICEFRAMEWORK_H

#include <DLabel>
#include <DListView>
#include <QWidget>

DWIDGET_USE_NAMESPACE

class ChoiceFramework : public QWidget
{
    Q_OBJECT
public:
    explicit ChoiceFramework(QWidget *parent = nullptr);

signals:
    void signalClicked(int row);

public slots:

private:
    DListView *m_listView;
};

#endif // CHOICEFRAMEWORK_H
