#include "choiceframework.h"
#include <DPushButton>
#include <QBoxLayout>

ChoiceFramework::ChoiceFramework(QWidget *parent)
    : QWidget(parent)
    , m_listView(new DListView(this))
{
    DLabel *label = new DLabel(this);
    QFont font("SimHei");
    font.setBold(true);
    label->setFont(font);
    DFontSizeManager::instance()->bind(label, DFontSizeManager::T3);
    label->setText(tr("选择架构"));

    QStandardItemModel *itemModel = new QStandardItemModel;
    QStandardItem *choice_iso = new QStandardItem(tr("ARM"));

    itemModel->appendRow(choice_iso);
    QStandardItem *framework = new QStandardItem(tr("X86"));
    itemModel->appendRow(framework);
    QStandardItem *configure = new QStandardItem(tr("MIPS"));
    itemModel->appendRow(configure);
    m_listView->setModel(itemModel);

    DPushButton *btn = new DPushButton(tr("下一步"), this);
    btn->setFixedSize(300, 35);
    btn->setEnabled(false);

    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(35, 30, 35, 30);

    layout->addWidget(label);
    layout->addWidget(m_listView);
    layout->addStretch();
    layout->addWidget(btn);
    layout->setAlignment(btn, Qt::AlignHCenter);

    connect(m_listView, &DListView::clicked, [ = ](const QModelIndex & index) {
        for (int i = 0; i < itemModel->rowCount(); i++) {
            itemModel->item(i, 0)->setCheckState(Qt::Unchecked);
        }
        itemModel->item(index.row(), 0)->setCheckState(Qt::Checked);
        itemModel->item(index.row(), 0)->setSelectable(false);
        btn->setEnabled(true);
    });

    connect(btn, &DPushButton::clicked, [ = ]() {
        btn->setEnabled(true);
        emit signalClicked(1);
    });

}
