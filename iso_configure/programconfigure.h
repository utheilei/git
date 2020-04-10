#ifndef PROGRAMCONFIGURE_H
#define PROGRAMCONFIGURE_H

#include <QWidget>
#include <DLabel>
#include <DFloatingMessage>
#include <DCommandLinkButton>
#include <DListView>
#include <QSignalMapper>
#include <QEvent>
#include <QMouseEvent>

DWIDGET_USE_NAMESPACE

class ProgramConfigure : public QWidget
{
    Q_OBJECT
public:
    explicit ProgramConfigure(QWidget *parent = nullptr);
    QIcon getIcon(QString filename);

protected:

signals:
    void signalClicked(int row);

public slots:
    void slotSignalMap(QObject *);

private:
    QSignalMapper *m_signalMapper;
    DCommandLinkButton *m_clearbtn;
    DLabel *m_choiceLabel;
    DListView *m_view;
    QMap<DViewItemAction *,DStandardItem *> m_item;
    QWidget *m_groupBox;
};

#endif // PROGRAMCONFIGURE_H
