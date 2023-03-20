#ifndef EXQDATETIME_H
#define EXQDATETIME_H

#include <QWidget>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQDateTime; }
QT_END_NAMESPACE

class ExQDateTime : public QWidget
{
    Q_OBJECT

public:
    ExQDateTime(QWidget *parent = nullptr);
    ~ExQDateTime();

private slots:
    void on_btnGetDateTime_clicked();
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void onTimerOut();  //超时的时候就会触发

    void on_calendarWidget_selectionChanged();
    void on_btnSetPeriod_clicked();

private:
    Ui::ExQDateTime *ui;

    QTimer* m_timer;    //定时器
    QTime m_time;       //计时器
};
#endif // EXQDATETIME_H
