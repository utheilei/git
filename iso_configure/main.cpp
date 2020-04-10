#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DLog>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setOrganizationName("deepin");
    a.setApplicationName("ISO定制工具");
    a.setApplicationVersion("1.0.4");
    a.setProductIcon(QIcon::fromTheme("iso_image"));
    a.setProductName("ISO Customizer");
    a.setApplicationDescription("ISO Customizer is a configuration tool to create custom ISO images.");

    Dtk::Core::DLogManager::registerConsoleAppender();
    a.loadTranslator();

    DApplicationSettings savetheme;

    MainWindow w;
    w.setMinimumSize(900, 600);
    w.show();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
