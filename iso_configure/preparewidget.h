#ifndef PREPAREWIDGET_H
#define PREPAREWIDGET_H

#include <QWidget>
#include <DLabel>
#include <DFloatingMessage>
#include <DCommandLinkButton>
#include <DListView>
#include <QSignalMapper>

DWIDGET_USE_NAMESPACE

class PrepareWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrepareWidget(QWidget *parent = nullptr);
    QIcon getIcon(QString filename);

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

#endif // PREPAREWIDGET_H
