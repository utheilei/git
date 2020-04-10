#include "kernelwidget.h"
#include <DFontSizeManager>
#include <DPushButton>
#include <QBoxLayout>

KernelWidget::KernelWidget(QWidget *parent) : QWidget(parent)
{
    DLabel *label = new DLabel(this);
    QFont font("SimHei");
    font.setBold(true);
    label->setFont(font);
    DFontSizeManager::instance()->bind(label, DFontSizeManager::T3);
    label->setText(tr("选择Kernel"));

    DFileChooserEdit *fileEdit = new DFileChooserEdit();

    DFileChooserEdit *fileEdit1 = new DFileChooserEdit();
    fileEdit1->setNameFilters(QStringList("initrd(*.lz)"));

    DPushButton *btn = new DPushButton(tr("下一步"), this);
    btn->setFixedSize(300, 35);
    btn->setEnabled(false);

    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(35, 30, 35, 30);

    layout->addWidget(label);
    layout->addWidget(fileEdit);
    layout->addWidget(fileEdit1);
    layout->addStretch();
    layout->addWidget(btn);
    layout->setAlignment(btn, Qt::AlignHCenter);

    connect(fileEdit, &DFileChooserEdit::fileChoosed, [ = ](const QString & fileName) {
        if (!fileName.isEmpty() && !fileEdit1->text().isEmpty()) {
            btn->setEnabled(true);
        }
    });

    connect(fileEdit1, &DFileChooserEdit::fileChoosed, [ = ](const QString & fileName) {
        if (!fileName.isEmpty() && !fileEdit->text().isEmpty()) {
            btn->setEnabled(true);
        }
    });

    connect(btn, &DPushButton::clicked, [ = ]() {
        emit signalClicked(6);
    });
}
