#include "preparewidget.h"
#include <DFontSizeManager>
#include <DPushButton>
#include <DFileDialog>
#include <QBoxLayout>
#include <QFileInfo>
#include <QFileIconProvider>

PrepareWidget::PrepareWidget(QWidget *parent) : QWidget(parent)
    , m_signalMapper(new QSignalMapper(this))
{
    DLabel *label = new DLabel(this);
    QFont font("SimHei");
    font.setBold(true);
    label->setFont(font);
    DFontSizeManager::instance()->bind(label, DFontSizeManager::T3);
    label->setText(tr("前期准备"));

    m_clearbtn = new DCommandLinkButton(tr("全部清除"), this);
    m_clearbtn->hide();

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label);
    hlayout->addWidget(m_clearbtn);
    hlayout->setAlignment(m_clearbtn, Qt::AlignRight);

    m_groupBox = new QWidget(this);
    QVBoxLayout *pVBoxLayoutCheck = new QVBoxLayout;
    m_groupBox->setLayout(pVBoxLayoutCheck);

    m_view = new DListView(this);
    m_view->hide();
    QStandardItemModel *model = new QStandardItemModel(m_view);
    m_view->setModel(model);
    pVBoxLayoutCheck->addWidget(m_view);

    m_choiceLabel = new DLabel(this);
    QFont font1("SimHei");
    m_choiceLabel->setFont(font1);
    DFontSizeManager::instance()->bind(m_choiceLabel, DFontSizeManager::T2);
    m_choiceLabel->setText(tr("请选择前期准备"));
    m_choiceLabel->setEnabled(false);

    DCommandLinkButton *registerbtn = new DCommandLinkButton(tr("选择脚本"), this);

    DPushButton *btn = new DPushButton(tr("下一步"), this);
    btn->setFixedSize(300, 35);

    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(35, 30, 35, 30);

    layout->addLayout(hlayout);
    layout->addWidget(m_groupBox);
    layout->addStretch();
    layout->addWidget(m_choiceLabel);
    layout->setAlignment(m_choiceLabel, Qt::AlignHCenter);
    layout->addStretch();
    layout->addWidget(registerbtn);
    layout->setAlignment(registerbtn, Qt::AlignHCenter);
    layout->addWidget(btn);
    layout->setAlignment(btn, Qt::AlignHCenter);

    connect(registerbtn, &DCommandLinkButton::clicked, [ = ]() {
        DFileDialog *pDFileDialog = new DFileDialog();
        pDFileDialog->setAcceptMode(QFileDialog::AcceptOpen); //文件对话框为打开文件类型
        pDFileDialog->setFileMode(QFileDialog::ExistingFiles);
        pDFileDialog->setNameFilter(tr("*.job"));
        //QString filename = QFileDialog::getOpenFileName(nullptr,"Please Select File","./","*.deb");
        if (pDFileDialog->exec() == QDialog::Accepted) {
            m_choiceLabel->hide();
            m_clearbtn->show();
            m_view->show();
            QStringList strlistSelectedName = pDFileDialog->selectedFiles();
            for (int i = 0; i < strlistSelectedName.size(); i++) {
                DStandardItem *item = new DStandardItem();
                item->setIcon(getIcon(strlistSelectedName[i]));
                item->setText(strlistSelectedName[i]);
                DViewItemAction *closeAct = new DViewItemAction(Qt::AlignCenter, QSize(30, 30), QSize(70, 70), true);
                closeAct->setIcon(QIcon::fromTheme("iso_close"));
                DViewItemActionList *list = new DViewItemActionList();
                list->append(closeAct);
                item->setActionList(Qt::RightEdge, *list);
                model->appendRow(item);
                m_item.insert(closeAct, item);
                connect(closeAct, SIGNAL(triggered()), m_signalMapper, SLOT(map()));
                m_signalMapper->setMapping(closeAct, closeAct);
            }
        }
    });

    connect(m_clearbtn, &DCommandLinkButton::clicked, [ = ]() {
        m_choiceLabel->show();
        m_clearbtn->hide();
        m_view->hide();
    });

    connect(btn, &DPushButton::clicked, [ = ]() {
        emit signalClicked(3);
    });

    connect(m_signalMapper, SIGNAL(mapped(QObject *)), this, SLOT(slotSignalMap(QObject *)));
}

QIcon PrepareWidget::getIcon(QString filename)
{
    QFileInfo file_info(filename);
    QFileIconProvider file_icon;
    QIcon icon = file_icon.icon(file_info);
    return icon;
}

void PrepareWidget::slotSignalMap(QObject *w)
{
    DViewItemAction *message = qobject_cast<DViewItemAction *>(w);
    DStandardItem *item = m_item.value(message);
    m_view->removeItem(item->row());
    m_item.remove(message);
    if (m_item.isEmpty()) {
        m_choiceLabel->show();
        m_view->hide();
        m_clearbtn->hide();
    }
}
