#include "exqlistwidget.h"
#include "ui_exqlistwidget.h"

ExQListWidget::ExQListWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ExQListWidget)
{
    ui->setupUi(this);
}

ExQListWidget::~ExQListWidget()
{
    delete ui;
}


void ExQListWidget::on_toolBtnInit_clicked()
{
//    for(int i=0; i<10; i++){
//        QString str = QString("Item(%1)").arg(i);
//        new QListWidgetItem(str, ui->listWidget);
//    }
    for(int i=0; i<10; i++){
        QString str = QString("Item(%1)").arg(i);
        QListWidgetItem *item = new QListWidgetItem(str);
        ui->listWidget->addItem(item);
    }
}



void ExQListWidget::on_toolBtnClear_clicked()
{
    ui->listWidget->clear();
}

void ExQListWidget::on_toolBtnInsert_clicked()
{
    QListWidgetItem* item;

    item = new QListWidgetItem();
    item->setText(QString("插入一个项item: " + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:MM:ss:zzz")));
    //item->setCheckState(Qt::Unchecked);
    ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
}

void ExQListWidget::on_toolBtnAdd_clicked()
{
    QListWidgetItem* item;

    item = new QListWidgetItem();
    item->setText(QString("添加一个项item: " + QDateTime::currentDateTime().toString("yyyy-mm-dd hh:MM:ss:zzz")));
    //item->setCheckState(Qt::Unchecked);
    ui->listWidget->addItem(item);
}

void ExQListWidget::on_toolBtnDelete_clicked()
{
    int row = ui->listWidget->currentRow();
    QListWidgetItem *item = ui->listWidget->takeItem(row);
    delete item;
}
