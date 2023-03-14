#include "exwidget.h"
#include "ui_exwidget.h"
#include <QMetaProperty>

ExWidget::ExWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExWidget)
{
    ui->setupUi(this);

    m_boy = new ExPersion("王二");
    m_boy->setProperty("score", 90);
    m_boy->setProperty("age", 23);
    m_boy->setProperty("sex", "Boy");
    connect(m_boy, &ExPersion::ageChanged, this, &ExWidget::onAgeChange);

    m_girl = new ExPersion("小红");
    m_girl->setProperty("score", 59);
    m_girl->setProperty("age", 18);
    m_girl->setProperty("sex", "Girl");
    connect(m_girl, &ExPersion::ageChanged, this, &ExWidget::onAgeChange);

    ui->spinBoy->setProperty("isBoy", true);
    ui->spinGirl->setProperty("isGirl", false);

    connect(ui->spinBoy, SIGNAL(valueChange()), this, SLOT(onSpinValChange(int)));
    connect(ui->spinGirl, SIGNAL(valueChange()), this, SLOT(onSpinValChange(int)));

    connect(ui->btnBoyAdd, SIGNAL(clicked()), this, SLOT(onBtnBoyInc()));
    connect(ui->btnGirlAdd, SIGNAL(clicked()), this, SLOT(onBtnGirlInc()));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(onBtnClear()));
}

void ExWidget::onAgeChange(int val){
    Q_UNUSED(val);

    ExPersion* person = qobject_cast<ExPersion *>(sender());
    QString name = person->property("name").toString();
    QString sex = person->property("sex").toString();
    int age = person->getAge();

    ui->textEdit->append(name+","+sex+QString::asprintf(", 年龄=%d", age));
}

void ExWidget::onBtnClear(){
    ui->textEdit->clear();
}

void ExWidget::onBtnBoyInc(){
    m_boy->incAge();
}

void ExWidget::onBtnGirlInc(){
    m_girl->incAge();
}

void ExWidget::onSpinValChange(int val)
{
    Q_UNUSED(val)

    QSpinBox* spin = qobject_cast<QSpinBox *>(sender());     //类型投射
    if (spin->property("isBoy").toBool())
        m_boy->setAge(ui->spinBoy->value());
    else
        m_girl->setAge(ui->spinGirl->value());
}

void ExWidget::onClassInfo(){
    const QMetaObject* meta = m_boy->metaObject();

    ui->textEdit->clear();
    ui->textEdit->append("==元对象信息(Meta Object)===");
    ui->textEdit->append(QString("类名称: %1\n").arg(meta->className()));
    ui->textEdit->append("属性(property)");

    for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++)
    {
        QMetaProperty prop = meta->property(i);
        const char* propName = prop.name();
        QString propValue = m_boy->property(propName).toString();
        ui->textEdit->append(QString("属性名称=%1， 属性值= %2").arg(propName).arg(propValue));
    }

    ui->textEdit->append("");
    ui->textEdit->append("classInfo:");
    for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); i++)
    {
        QMetaClassInfo classInfo = meta->classInfo(i);
        ui->textEdit->append(QString("Name=%1， Value= %2").arg(classInfo.name()).arg(classInfo.value()));
    }
}

ExWidget::~ExWidget()
{
    delete ui;
}
