#ifndef EXWIDGET_H
#define EXWIDGET_H

#include <QWidget>
#include "expersion.h"

namespace Ui {
class ExWidget;
}

class ExWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExWidget(QWidget *parent = nullptr);
    ~ExWidget();
public slots:
    void onAgeChange(int val);      //自定义的槽函数
    void onSpinValChange(int val);

    void onBtnClear();              //ui界面的槽函数
    void onBtnBoyInc();
    void onBtnGirlInc();
    void onClassInfo();
private:
    Ui::ExWidget *ui;

private:
    ExPersion* m_boy;
    ExPersion* m_girl;
};

#endif // EXWIDGET_H
