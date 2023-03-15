#include "exprogressbar.h"
#include "ui_exprogressbar.h"

ExProgressBar::ExProgressBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExProgressBar)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("QSlider、QScrollBar和QProgressBar控件的梦幻联动"));

    //槽函数的多对一
    connect(ui->horSlider, &QSlider::valueChanged, this, &ExProgressBar::onValChange);
    connect(ui->horScrollBar, &QScrollBar::valueChanged, this, &ExProgressBar::onValChange);
    connect(ui->progressBar, &QProgressBar::valueChanged, this, &ExProgressBar::onValChange);
    connect(ui->verSlider, &QSlider::valueChanged, this, &ExProgressBar::onValChange);
    connect(ui->verScrollBar, &QScrollBar::valueChanged, this, &ExProgressBar::onValChange);
}

ExProgressBar::~ExProgressBar()
{
    delete ui;
}

void ExProgressBar::onValChange(int val){
    ui->horSlider->setValue(val);
    ui->horSlider->setValue(val);
    ui->progressBar->setValue(val);
    ui->verSlider->setValue(val);
    ui->verScrollBar->setValue(val);
}
