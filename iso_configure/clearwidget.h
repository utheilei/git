#ifndef CLEARWIDGET_H
#define CLEARWIDGET_H

#include <QWidget>
#include <DLabel>
#include <DFloatingMessage>
#include <DCommandLinkButton>
#include <DListView>
#include <QSignalMapper>

DWIDGET_USE_NAMESPACE

class ClearWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClearWidget(QWidget *parent = nullptr);
    QIcon getIcon(QString filename);

signals:
    void signalClicked(int row);

public slots:
    void slotSignalMap(QObject *w);

private:
    QSignalMapper *m_signalMapper;
    DCommandLinkButton *m_clearbtn;
    DLabel *m_choiceLabel;
    DListView *m_view;
    QMap<DViewItemAction *,DStandardItem *> m_item;
    QWidget *m_groupBox;
};

#endif // CLEARWIDGET_H
