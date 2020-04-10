#ifndef KERNELWIDGET_H
#define KERNELWIDGET_H

#include <QWidget>
#include <DLabel>
#include "dfilechooseredit.h"

DWIDGET_USE_NAMESPACE

class KernelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KernelWidget(QWidget *parent = nullptr);

signals:
    void signalClicked(int row);

public slots:
};

#endif // KERNELWIDGET_H
