#ifndef EXPROGRESSBAR_H
#define EXPROGRESSBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ExProgressBar; }
QT_END_NAMESPACE

class ExProgressBar : public QWidget
{
    Q_OBJECT

public:
    ExProgressBar(QWidget *parent = nullptr);
    ~ExProgressBar();

public slots:
    void onValChange(int);
private:
    Ui::ExProgressBar *ui;
};
#endif // EXPROGRESSBAR_H
