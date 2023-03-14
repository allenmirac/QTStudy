#include "exqslider.h"
#include "ui_exqslider.h"

ExQSlider::ExQSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExQSlider)
{
    ui->setupUi(this);
    setWindowTitle(QString("QSlider的用法"));

    //设置最大值为255,初始范围是0-100;
    ui->sliderRed->setMaximum(255);
    ui->sliderGreen->setMaximum(255);
    ui->sliderBlue->setMaximum(255);
    ui->sliderAlpha->setMaximum(255);

    //设置初值
    ui->sliderRed->setValue(145);
    ui->sliderGreen->setValue(190);
    ui->sliderBlue->setValue(251);
    ui->sliderAlpha->setValue(255);

    //设置初试颜色
    QColor color;
    color.setRgb(145, 190, 251, 255);
    QPalette palette = ui->textColor->palette();
    palette.setColor(QPalette::Base, color);
    ui->textColor->setPalette(palette);

    connect(ui->sliderRed, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
    connect(ui->sliderGreen, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
    connect(ui->sliderBlue, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
    connect(ui->sliderAlpha, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
}

ExQSlider::~ExQSlider()
{
    delete ui;
}

void ExQSlider::onSetColor(int val){
    Q_UNUSED(val);

    int nRed = ui->sliderRed->value();
    int nGreen = ui->sliderGreen->value();
    int nBlue = ui->sliderBlue->value();
    int nAlpha = ui->sliderAlpha->value();

    QColor color;
    color.setRgb(nRed, nGreen, nBlue, nAlpha);
    QPalette palette = ui->textColor->palette();
    palette.setColor(QPalette::Base, color);
    ui->textColor->setPalette(palette);

    ui->labRGBVal->setText(QString("RGB(%1, %2, %3, %4)").arg(nRed).arg(nGreen).arg(nBlue).arg(nAlpha));

}

