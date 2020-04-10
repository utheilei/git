#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QWidget>
#include <DLabel>
#include <DPushButton>

DWIDGET_USE_NAMESPACE

class OutputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OutputWidget(QWidget *parent = nullptr);
    void initsuccessWidget();
    void initfailWidget();

signals:

public slots:

private:
    int count = 0;
    QWidget *m_centerWidget;
    QWidget *m_successWidget;
    QWidget *m_failWidget;
    DPushButton *m_completeBtn;
    DPushButton *m_lookfileBtn;
    DPushButton *m_closeBtn;
};

#endif // OUTPUTWIDGET_H
