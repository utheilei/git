#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <DFrame>
#include <QLabel>
#include <QEvent>
#include <DDialogCloseButton>

DWIDGET_USE_NAMESPACE

class MessageLabel : public QLabel
{
public:
    QSize sizeHint() const override
    {
        return fontMetrics().size(Qt::TextSingleLine, text());
    }
};

class MessageWidget : public DFrame
{
    Q_OBJECT
public:
    explicit MessageWidget(QIcon &icon,QString str,QWidget *parent = nullptr);

private:
    void enterEvent(QEvent *);                      //进入QWidget瞬间事件
    void leaveEvent(QEvent *);

signals:

public slots:

private:
    MessageLabel *label;
    DDialogCloseButton *closeButton;
};

#endif // MESSAGEWIDGET_H
