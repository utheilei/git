#include "mainwindow.h"
#include "listwidget.h"
#include "choiceiso.h"
#include "choiceframework.h"
#include "programconfigure.h"
#include "preparewidget.h"
#include "installwidget.h"
#include "clearwidget.h"
#include "kernelwidget.h"
#include "outputwidget.h"
#include <DMenu>
#include <DSearchEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
    , m_stackedWidget(new QStackedWidget(this))
    , listwidget(new ListWidget(this))
    , leftWidget(new DFrame(this))
    , rightWidget(new DFrame(this))
{
    m_titlebar = this->titlebar();
    m_titlebar->setDisableFlags(Qt::WindowMinimizeButtonHint
                                | Qt::WindowMaximizeButtonHint
                                | Qt::WindowSystemMenuHint);
    m_titlebar->setAutoHideOnFullscreen(true);
    m_titlebar->setIcon(QIcon::fromTheme("iso_image3"));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QWidget *centerWidget = new QWidget(this);
    centerWidget->setLayout(mainLayout);
    setCentralWidget(centerWidget);

    ChoiceISO *isoWidget = new ChoiceISO(this);
    m_stackedWidget->addWidget(isoWidget);
    m_listWidget.insert(tr("选择ISO"), isoWidget);

    ChoiceFramework *frameworkWidget = new ChoiceFramework(this);
    m_stackedWidget->addWidget(frameworkWidget);
    m_listWidget.insert(tr("选择架构"), frameworkWidget);

    ProgramConfigure *configureWidget = new ProgramConfigure(this);
    m_stackedWidget->addWidget(configureWidget);
    m_listWidget.insert(tr("程序配置"), configureWidget);

    PrepareWidget *prepareWidget = new PrepareWidget(this);
    m_stackedWidget->addWidget(prepareWidget);
    m_listWidget.insert(tr("前期准备"), prepareWidget);

    InstallWidget *installWidget = new InstallWidget(this);
    m_stackedWidget->addWidget(installWidget);
    m_listWidget.insert(tr("中期安装"), installWidget);

    ClearWidget *clearWidget = new ClearWidget(this);
    m_stackedWidget->addWidget(clearWidget);
    m_listWidget.insert(tr("后期清理"), clearWidget);

    KernelWidget *kernelWidget = new KernelWidget(this);
    m_stackedWidget->addWidget(kernelWidget);
    m_listWidget.insert(tr("选择Kernel"), kernelWidget);

    OutputWidget *outputWidget = new OutputWidget(this);
    m_stackedWidget->addWidget(outputWidget);
    m_listWidget.insert(tr("输出"), outputWidget);

    m_stackedWidget->setCurrentWidget(isoWidget);
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftWidget->setLayout(leftLayout);
    leftLayout->addWidget(listwidget);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightWidget->setLayout(rightLayout);
    rightLayout->addWidget(m_stackedWidget);

    mainLayout->addWidget(leftWidget, 1);
    mainLayout->addWidget(rightWidget, 3);

    QItemSelectionModel *selectModel = listwidget->selectionModel();
    connect(selectModel, &QItemSelectionModel::currentChanged
    , [ = ](const QModelIndex & current, const QModelIndex & previous) {
        qDebug() << current << previous;
        QWidget *widget = m_listWidget.value(current.data().toString());
        m_stackedWidget->setCurrentWidget(widget);
    });

    connect(isoWidget, &ChoiceISO::signalClicked, [ = ](int row) {
        setWidget(row);
    });

    connect(frameworkWidget, &ChoiceFramework::signalClicked, [ = ](int row) {
        setWidget(row);
    });

    connect(configureWidget, &ProgramConfigure::signalClicked, [ = ](int row) {
        setWidget(row);
    });

    connect(prepareWidget, &PrepareWidget::signalClicked, [ = ](int row) {
        setWidget(row);
    });

    connect(installWidget, &InstallWidget::signalClicked, [ = ](int row) {
        setWidget(row);
    });

    connect(clearWidget, &ClearWidget::signalClicked, [ = ](int row) {
        setWidget(row);
    });

    connect(kernelWidget, &KernelWidget::signalClicked, [ = ](int row) {
        setWidget(row);
    });
}

void MainWindow::setWidget(int row)
{
    QStandardItemModel *itemModel = listwidget->getItemModel();
    itemModel->item(row)->setCheckState(Qt::Checked);
    itemModel->item(row + 1, 0)->setEnabled(true);
    listwidget->setCurrentIndex(itemModel->indexFromItem(itemModel->item(row + 1, 0)));
}
