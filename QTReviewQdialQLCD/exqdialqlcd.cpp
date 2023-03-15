#include "exqdialqlcd.h"
#include "ui_exqdialqlcd.h"

ExQdialQLCD::ExQdialQLCD(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExQdialQLCD)
{
    ui->setupUi(this);
    QIcon *icon = new QIcon(":/icon/qt.ico");
    this->setWindowIcon(*icon);
    setWindowTitle(QString("QDia表盘输入，在LCD以多种进制显示"));
    connect(ui->dial, &QDial::valueChanged, this, &ExQdialQLCD::onDisplayLCD);
}

ExQdialQLCD::~ExQdialQLCD()
{
    delete ui;
}

void ExQdialQLCD::onDisplayLCD(int val)
{
    ui->lcdNumber->display(val);
}

void ExQdialQLCD::on_radioBtn2_clicked()   //设置LCD显示二进制数
{
    ui->lcdNumber->setBinMode();
}

void ExQdialQLCD::on_radioBtn8_clicked()   //设置LCD显示八进制数
{
    ui->lcdNumber->setOctMode();
}

void ExQdialQLCD::on_radioBtn10_clicked()  //设置LCD显示十进制数
{
    ui->lcdNumber->setDecMode();
}

void ExQdialQLCD::on_radioBtn16_clicked()  //设置LCD显示十六进制数
{
    ui->lcdNumber->setHexMode();
}

