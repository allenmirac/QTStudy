#include "exqdatetime.h"
#include "ui_exqdatetime.h"
#include <QDebug>

ExQDateTime::ExQDateTime(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExQDateTime)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("时间日期(QTime/QDate/QDateTime)和定时器(QTimer)"));
    setWindowIcon(QIcon(":/qt.ico"));

    m_timer = new QTimer(this);
    m_timer->stop();
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &ExQDateTime::onTimerOut);
    ui->progressBar->setValue(0);
}

ExQDateTime::~ExQDateTime()
{
    delete ui;
}

void ExQDateTime::on_btnGetDateTime_clicked(){
    QDateTime currentTime = QDateTime::currentDateTime();

    ui->timeEdit->setTime(currentTime.time());
    ui->dateEdit->setDate(currentTime.date());
    ui->dateTimeEdit->setDateTime(currentTime);

    ui->lEditTime->setText(currentTime.toString("hh:mm:ss:zzz"));
    ui->lEditDate->setText(currentTime.toString("yyyy-MM-dd"));
    ui->lEditDateTime->setText(currentTime.toString("yyyy-MM-dd hh:mm:ss:zzz"));
    ui->labCurrTime->setText(currentTime.toString("yyyy-MM-dd hh:mm:ss:zzz"));
}


void ExQDateTime::on_btnStart_clicked(){
    m_time.start();
    m_timer->start();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetPeriod->setEnabled(false);
    ui->labGo->setText(QString("时间流逝计算中......"));
}

void ExQDateTime::on_btnStop_clicked(){
    m_timer->stop();
    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(true);

    int timeMSec = m_time.elapsed();
    int msec = timeMSec % 1000;
    int sec = timeMSec / 1000;
    ui->btnSetPeriod->setEnabled(true);
    ui->labGo->setText(QString("时间已流逝：%1 秒 %2 毫秒").arg(sec).arg(msec));
}

void ExQDateTime::on_btnSetPeriod_clicked(){
    m_timer->setInterval(ui->spinBox->value());//单位: ms
}

void ExQDateTime::on_calendarWidget_selectionChanged(){
    QDate date = ui->calendarWidget->selectedDate();
//    qDebug()<<date.toString("yyyy年MM月dd日");
    ui->lEditCalendar->setText(date.toString("yyyy年MM月dd日"));
}

//计时器触发
void ExQDateTime::onTimerOut(){
    QTime currTime = QTime::currentTime();
    ui->lcdNumber->display(currTime.hour());
    ui->lcdNumber_2->display(currTime.toString("mm"));
    ui->lcdNumber_3->display(currTime.toString("ss"));

    int val = ui->progressBar->value();
    val++;
    if(val>100) val=0;
    ui->progressBar->setValue(val);
}


