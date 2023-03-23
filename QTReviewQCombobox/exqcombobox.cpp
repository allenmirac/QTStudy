#include "exqcombobox.h"
#include "ui_exqcombobox.h"

#include <QMap>
#include <QTextBlock>
#include <QDebug>

ExQComboBox::ExQComboBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExQComboBox)
{
    ui->setupUi(this);
    setWindowTitle(QString("QComboBox和QPlainTextEdit的用法"));

    connect(ui->comboBoxRight, &QComboBox::currentTextChanged, this, &ExQComboBox::onSelectDisplay);
}

ExQComboBox::~ExQComboBox()
{
    delete ui;
}


void ExQComboBox::on_btnInitNameAge_clicked()
{
    QIcon ico;
    ico.addFile(":/girl.ico");

    QMap<QString, QString> map;
    map.insert("张投", "16岁");
    map.insert("张我", "17岁");
    map.insert("张以", "18岁");
    map.insert("张木", "19岁");
    map.insert("张李", "20岁");
    map.insert("张，", "21岁");
    map.insert("张报", "22岁");

    ui->comboBoxRight->clear();
    foreach(const QString &str, map.keys()){
        ui->comboBoxRight->addItem(ico, str, map.value(str));
    }
}

void ExQComboBox::on_btnComboInit_clicked()
{
    QIcon ico;
    ico.addFile(":/github.ico");

    ui->comboBoxLeft->clear();
    for(int i=0; i<10; i++){
        ui->comboBoxLeft->addItem(ico, QString("第%1个item项").arg(i));
    }
}

void ExQComboBox::on_btnComboClear_clicked()
{
    ui->comboBoxLeft->clear();
}

void ExQComboBox::on_btnPlainTxtAdd_clicked()
{
    QTextDocument* doc = ui->plainTextEdit->document();
    int cnt = doc->blockCount();
    QIcon ico;
    ico.addFile(":/github.ico");

    ui->comboBoxLeft->clear();
    ui->comboBoxRight->clear();

    for(int i=0; i<cnt; i++){
        QTextBlock text = doc->findBlockByNumber(i);
        ui->comboBoxLeft->addItem(ico, text.text());
        ui->comboBoxRight->addItem(ico, text.text(), QString("附加内容：%1").arg(1));
    }
}

void ExQComboBox::on_btnPlainTxtClear_clicked()
{
    ui->plainTextEdit->clear();
}

void ExQComboBox::onSelectDisplay(QString str){
    QString strData = ui->comboBoxRight->currentData().toString();
    ui->plainTextEdit->appendPlainText(str + " " + strData);
}

void ExQComboBox::on_cbxComboIsEdit_clicked()
{
    if(ui->cbxComboIsEdit->isChecked()){
        ui->comboBoxLeft->setEditable(true);
    }else{
        ui->comboBoxLeft->setEditable(false);
    }
}

void ExQComboBox::on_cbxPlainTxtOnlyRead_clicked()
{
    if(ui->cbxPlainTxtOnlyRead->isChecked()){
        ui->plainTextEdit->setEnabled(true);
    }else{
        ui->plainTextEdit->setEnabled(false);
    }
}
