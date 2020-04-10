#include "outputwidget.h"
#include <DWaterProgress>
#include <DFontSizeManager>
#include <QBoxLayout>
#include <QTimer>

OutputWidget::OutputWidget(QWidget *parent) : QWidget(parent)
    , m_centerWidget(new QWidget(this))
    , m_successWidget(new QWidget(this))
    , m_failWidget(new QWidget(this))
{
    initsuccessWidget();
    m_successWidget->hide();
    initfailWidget();
    m_failWidget->hide();
    DLabel *label = new DLabel(this);
    QFont font("SimHei");
    font.setBold(true);
    label->setFont(font);
    DFontSizeManager::instance()->bind(label, DFontSizeManager::T3);
    label->setText(tr("准备输出"));

    DWaterProgress *waterProgress = new DWaterProgress(this);
    waterProgress->setFixedSize(100, 100);
    waterProgress->start();
    waterProgress->setValue(0);

    DLabel *centerLabel = new DLabel(this);
    centerLabel->setText(tr("正在制作，请稍后..."));
    centerLabel->hide();

    DPushButton *btn = new DPushButton(tr("下一步"), this);
    btn->setFixedSize(300, 35);

    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(35, 30, 35, 30);

    QVBoxLayout *centerlayout = new QVBoxLayout;
    m_centerWidget->setLayout(centerlayout);
    centerlayout->addStretch();
    centerlayout->addWidget(waterProgress);
    centerlayout->setAlignment(waterProgress, Qt::AlignHCenter);
    centerlayout->addWidget(centerLabel);
    centerlayout->setAlignment(centerLabel, Qt::AlignHCenter);
    centerlayout->addStretch();
    centerlayout->addWidget(btn);
    centerlayout->setAlignment(btn, Qt::AlignHCenter);

    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignHCenter);
    layout->addWidget(m_centerWidget);

    QTimer *timer = new QTimer;
    timer->setInterval(200);
    connect(timer, &QTimer::timeout, [ = ]() {
        count++;
        if (count > 99) {
            timer->stop();
            m_centerWidget->hide();
            m_successWidget->show();
            layout->addWidget(m_successWidget);
            label->setText(tr("输出成功"));
        }
        waterProgress->setValue(count);
    });

    connect(btn, &DPushButton::clicked, [ = ]() {
        timer->start();
        centerLabel->show();
        label->setText(tr("正在输出"));
    });

    connect(m_completeBtn, &DPushButton::clicked, [ = ]() {
        m_successWidget->hide();
        m_centerWidget->show();
        layout->addWidget(m_centerWidget);
        label->setText(tr("准备输出"));
        centerLabel->hide();
        count = 0;
        waterProgress->setValue(0);
    });
}

void OutputWidget::initsuccessWidget()
{
    QVBoxLayout *successlayout = new QVBoxLayout;
    m_successWidget->setLayout(successlayout);

    DLabel *successlabel = new DLabel(m_successWidget);
    successlabel->setPixmap(QPixmap(":/icons/deepin/builtin/light/icons/iso_progress_110px.svg"));

    DLabel *successlabel1 = new DLabel(m_successWidget);
    successlabel1->setText(tr("制作成功"));

    m_completeBtn = new DPushButton(tr("完成"), m_successWidget);
    m_lookfileBtn = new DPushButton(tr("查看文件"), m_successWidget);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_completeBtn);
    hlayout->addWidget(m_lookfileBtn);

    successlayout->addStretch();
    successlayout->addWidget(successlabel);
    successlayout->setAlignment(successlabel, Qt::AlignHCenter);
    successlayout->addWidget(successlabel1);
    successlayout->setAlignment(successlabel1, Qt::AlignHCenter);
    successlayout->addStretch();
    successlayout->addLayout(hlayout);
}

void OutputWidget::initfailWidget()
{
    QVBoxLayout *faillayout = new QVBoxLayout;
    m_failWidget->setLayout(faillayout);

    DLabel *faillabel = new DLabel(m_failWidget);
    faillabel->setPixmap(QPixmap(":/icons/deepin/builtin/light/icons/iso_fail_110px.svg"));

    DLabel *faillabel1 = new DLabel(m_failWidget);
    faillabel1->setText(tr("制作失败"));

    m_closeBtn = new DPushButton(tr("关闭"), m_failWidget);

    faillayout->addStretch();
    faillayout->addWidget(faillabel);
    faillayout->setAlignment(faillabel, Qt::AlignHCenter);
    faillayout->addWidget(faillabel1);
    faillayout->setAlignment(faillabel1, Qt::AlignHCenter);
    faillayout->addStretch();
    faillayout->addWidget(m_closeBtn);
    faillayout->setAlignment(m_closeBtn, Qt::AlignHCenter);
}
