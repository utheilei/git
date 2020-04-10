#ifndef CHOICEISO_H
#define CHOICEISO_H

#include <dfilechooseredit.h>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

DWIDGET_USE_NAMESPACE

class ChoiceISO : public QWidget
{
    Q_OBJECT
public:
    explicit ChoiceISO(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void signalClicked(int row);

public slots:

private:
    DFileChooserEdit *fileEdit;
};

#endif // CHOICEISO_H
