#include "choiceiso.h"
#include "messagewidget.h"
#include <DLabel>
#include <DFontSizeManager>
#include <DPushButton>
#include <QBoxLayout>
#include <QMimeData>
#include <QDebug>

ChoiceISO::ChoiceISO(QWidget *parent) : QWidget(parent)
{
    DLabel *label = new DLabel(this);
    QFont font("SimHei");
    font.setBold(true);
    label->setFont(font);
    DFontSizeManager::instance()->bind(label, DFontSizeManager::T3);
    label->setText(tr("选择ISO"));

    fileEdit = new DFileChooserEdit();
    fileEdit->setNameFilters(QStringList("ISO(*.iso)"));
    fileEdit->setAcceptDrops(true);

    DPushButton *btn = new DPushButton(tr("下一步"), this);
    btn->setFixedSize(300, 35);
    btn->setEnabled(false);

    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(35, 30, 35, 30);

    layout->addWidget(label);
    layout->addWidget(fileEdit);
    layout->addStretch();
    layout->addWidget(btn);
    layout->setAlignment(btn, Qt::AlignHCenter);

    connect(fileEdit, &DFileChooserEdit::fileChoosed, [ = ](const QString & fileName) {
        if (!fileName.isEmpty()) {
            btn->setEnabled(true);
        }
    });

    connect(btn, &DPushButton::clicked, [ = ]() {
        emit signalClicked(0);
    });
}

void ChoiceISO::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void ChoiceISO::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();

    if (urls.isEmpty()) {
        return;
    }

    QString fileName = urls.first().toString();

    if (fileName.isEmpty()) {
        return;
    }

    QStringList type = fileName.split(".");

    if (type[1] == "iso") {
        fileEdit->setText(type[1]);
    }
}
