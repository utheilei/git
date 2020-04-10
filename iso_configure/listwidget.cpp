#include "listwidget.h"
#include <QStandardItemModel>
#include <QStandardItem>

ListWidget::ListWidget(QWidget *parent) : DListView(parent)
{
    itemModel = new QStandardItemModel;
    QStandardItem *choiceIso = new QStandardItem(QIcon::fromTheme("iso_inactive1"), tr("选择ISO"));
    choiceIso->setEnabled(true);
    choiceIso->setEditable(false);
    itemModel->appendRow(choiceIso);

    QStandardItem *frameWork = new QStandardItem(QIcon::fromTheme("iso_inactive2"), tr("选择架构"));
    frameWork->setEnabled(false);
    frameWork->setEditable(false);
    itemModel->appendRow(frameWork);

    QStandardItem *configure = new QStandardItem(QIcon::fromTheme("iso_inactive3"), tr("程序配置"));
    configure->setEnabled(false);
    configure->setEditable(false);
    itemModel->appendRow(configure);

    QStandardItem *prepare = new QStandardItem(QIcon::fromTheme("iso_inactive4"), tr("前期准备"));
    prepare->setEnabled(false);
    prepare->setEditable(false);
    itemModel->appendRow(prepare);

    QStandardItem *install = new QStandardItem(QIcon::fromTheme("iso_inactive5"), tr("中期安装"));
    install->setEnabled(false);
    install->setEditable(false);
    itemModel->appendRow(install);

    QStandardItem *clear = new QStandardItem(QIcon::fromTheme("iso_inactive6"), tr("后期清理"));
    clear->setEnabled(false);
    clear->setEditable(false);
    itemModel->appendRow(clear);

    QStandardItem *kernel = new QStandardItem(QIcon::fromTheme("iso_inactive7"), tr("选择Kernel"));
    kernel->setEnabled(false);
    kernel->setEditable(false);
    itemModel->appendRow(kernel);

    QStandardItem *output = new QStandardItem(QIcon::fromTheme("iso_inactive8"), tr("输出"));
    output->setEnabled(false);
    output->setEditable(false);
    itemModel->appendRow(output);

    this->setModel(itemModel);
}

QStandardItemModel *ListWidget::getItemModel()
{
    return itemModel;
}
