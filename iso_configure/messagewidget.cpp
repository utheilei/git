#include "messagewidget.h"
#include <DIconButton>
#include <DLabel>
#include <DFloatingButton>
#include <QBoxLayout>
#include <QDebug>

MessageWidget::MessageWidget(QIcon &icon, QString str, QWidget *parent) : DFrame(parent)
{
    this->setFixedHeight(45);
    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 10, 0);
    DIconButton *iconbtn = new DIconButton(this);
    iconbtn->setFlat(true);
    iconbtn->setFocusPolicy(Qt::NoFocus);
    iconbtn->setAttribute(Qt::WA_TransparentForMouseEvents);
    iconbtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    iconbtn->setIconSize(QSize(30, 30));
    iconbtn->setIcon(icon);

    label = new MessageLabel;
    label->setWordWrap(true);
    label->setText(str);
    //DIconButton *closebtn = new DIconButton(DStyle::SP_CloseButton);
    closeButton = new DDialogCloseButton(this);
    closeButton->hide();
    //DFloatingButton *closeButton = new DFloatingButton(DStyle::SP_CloseButton);
    layout->addWidget(iconbtn); \
    layout->setSpacing(20);
    layout->addWidget(label);
    layout->addWidget(closeButton);

    connect(closeButton, &DDialogCloseButton::clicked, this, &MessageWidget::close);
}

void MessageWidget::enterEvent(QEvent *)
{
    closeButton->show();
}

void MessageWidget::leaveEvent(QEvent *)
{
    closeButton->hide();
}
