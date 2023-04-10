#include "exqtablewidget.h"
#include "ui_exqtablewidget.h"

ExQTableWidget::ExQTableWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ExQTableWidget)
{
    ui->setupUi(this);
    setWindowTitle(QString("QTReviewQTableWidget，QTableWidget的练习"));
    setWindowIcon(QIcon(":/image/qt.ico"));

    m_labCellIndex  = new QLabel("当前的单元格坐标：", this);        //状态栏初始化
    m_labCellIndex->setMinimumWidth(250);
    m_labCellType = new QLabel("当前的单元格类型：", this);
    m_labCellType->setMinimumWidth(200);
    m_labStudID = new QLabel("学生ID：", this);
    m_labStudID->setMinimumWidth(200);

    ui->statusbar->addWidget(m_labCellIndex);
    ui->statusbar->addWidget(m_labCellType);
    ui->statusbar->addWidget(m_labStudID);

    ui->cbxTableIsEditable->setChecked(Qt::Unchecked);

//    setCentralWidget();
    on_ptnSetHeader_clicked();
}

ExQTableWidget::~ExQTableWidget()
{
    delete ui;
}

//创建一行
void ExQTableWidget::createItemARow(int row, QString name, QString sex, QDate birth, QString nation, int score, bool isAnime){
    QTableWidgetItem *item = nullptr;
    int stuID = 20230407;
    QString str="";

    item = new QTableWidgetItem(name, cellType::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);    //和下面是一样的效果
    // item->setTextAlignment(Qt::AlignCenter);
    stuID += row;
    //关于Qt::UserRole的解释：存储和读取有键值对关系，即一个value对应一个role。当以setData(Qt::UserRole + 3, info)时，必须使用data(Qt::UserRole+3)读取出来
    item->setData(Qt::UserRole, QVariant(stuID));                   //setdata()存储数据,data()是取出数据，是一对操作
    ui->tableWidget->setItem(row, fieldColNum::colName, item);      //行不同是row，列相同是.h里面的一个enum

    item = new QTableWidgetItem(sex, cellType::ctSex);
    QIcon icon;
    if(sex=="男"){
        icon.addFile(":/image/man.ico");
    }else{
        icon.addFile(":/image/woman.ico");
    }
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, fieldColNum::colSex, item);

    item = new QTableWidgetItem(birth.toString("yyyy-MM-dd"), cellType::ctBirth);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, fieldColNum::colBirth, item);

    item = new QTableWidgetItem(nation, cellType::ctNation);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, fieldColNum::colNation, item);

    item = new QTableWidgetItem(str.setNum(score), cellType::ctScore);
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, fieldColNum::colScore, item);

    item = new QTableWidgetItem("是否喜欢", cellType::ctLikeAnime);
    if(isAnime){
        item->setCheckState(Qt::Checked);
    }else{
        item->setCheckState(Qt::Unchecked);
    }
    item->setTextAlignment(Qt::AlignCenter);
    item->setBackground(Qt::lightGray);
    ui->tableWidget->setItem(row, fieldColNum::colLikeAnime, item);
}

void ExQTableWidget::on_ptnSetHeader_clicked()
{
    QTableWidgetItem *item = nullptr;
    QStringList list;
    list << "姓名" << "性别" << "出生日期" << "籍贯" << "分数" << "是否喜欢二次元";

    ui->tableWidget->setColumnCount(list.count());
    for(int i=0; i< ui->tableWidget->columnCount(); i++){
        item = new QTableWidgetItem(list.at(i));            //表头从list一个一个取出来
        QFont font;
        font.setBold(true);
        font.setPointSize(12);
        item->setFont(font);                                //设置字体的粗细、大小
        ui->tableWidget->setHorizontalHeaderItem(i, item);  //添加水平表头
    }
}

//初始化
void ExQTableWidget::on_ptnInitTable_clicked()
{
    QTime time;
    time = QTime::currentTime();
    srand(static_cast<uint>(time.msec() + time.second() * 1000));

    QString name = "学生";
    QString sex = "未知";
    QDate birth(2022, 9, 10);
    QString nation = "Africa";
    int score = 85;
    bool isAnime = true;

    ui->tableWidget->clearContents();       //Removes all items not in the headers from the view.
    int row = ui->tableWidget->rowCount();  //注意最开始的row=0

    for(int i=0; i<row; i++){
        if(i%2==1){
            name = QString("学生%1").arg(i);
        }else{
            name = QString("老师%2").arg(i);
        }
        int n=qrand()%2;
        if(n==0){
            sex="男";
            isAnime = true;
        }else{
            sex = "女";
            isAnime = false;
        }

        score += 10;
        birth = birth.addDays(30);
        createItemARow(i, name, sex, birth, nation, score, isAnime);
    }
}

//设置表格行数
void ExQTableWidget::on_ptnSetRowNum_clicked()
{
    int value = ui->spinBox->value();
    ui->tableWidget->setRowCount(value);
}

void ExQTableWidget::on_ptnInsertRow_clicked()
{
    int currRow = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(currRow);
    QString sex;
    if(currRow%2==1)    sex="男";
    else                sex="女";
    createItemARow(currRow, "插入学生", sex, QDate(2023, 2, 10), "America", 99, true);
}

void ExQTableWidget::on_ptnAddRow_clicked()
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    createItemARow(row, "添加学生", "男", QDate(2023, 04, 17), "France", 59, true);
}

void ExQTableWidget::on_ptnDelRow_clicked()
{
    int currRow = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(currRow);
}

//将表格转为文字
void ExQTableWidget::on_ptnTableToString_clicked()
{
    QTableWidgetItem *item = nullptr;
    QString str="";

    for(int i=0; i<ui->tableWidget->rowCount(); i++){
        str="";
        for(int j=0; j<ui->tableWidget->columnCount(); j++){
            item = ui->tableWidget->item(i, j);             //直接用(row, colunum)，坐标获取item
            str += item->text() + " ";
        }
        item = ui->tableWidget->item(i, fieldColNum::colLikeAnime);
        if(item->checkState()==Qt::Checked){
            str += "喜欢二次元";
        }else {
            str += "不喜欢二次元";
        }

        ui->plainTextEdit->appendPlainText(str);
    }
}

//自适应行高
void ExQTableWidget::on_ptnAutoRowHeight_clicked()
{
    ui->tableWidget->resizeRowsToContents();
}

//自适应列宽
void ExQTableWidget::on_ptnAutoColHeight_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}

//表格可编辑
void ExQTableWidget::on_cbxTableIsEditable_clicked(bool checked)
{
    if(checked){
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    }else {
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    }
}

//显示列表头
void ExQTableWidget::on_cbxRowColor_clicked(bool checked)
{
    ui->tableWidget->setAlternatingRowColors(checked);
}

//显示行表头
void ExQTableWidget::on_cbxHeadRow_clicked(bool checked)
{
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}


//单元格选择
void ExQTableWidget::on_cbxHeadCol_clicked(bool checked)
{
    ui->tableWidget->verticalHeader()->setVisible(checked);
}


//单元格选择
void ExQTableWidget::on_rbtnSelectItem_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}

//行选择
void ExQTableWidget::on_rbtnSelectRow_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

//获取当前的item和前一个点击item的行列号，即坐标
void ExQTableWidget::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    m_labCellIndex->setText("当前的单元格坐标: [" + QString::number(current->row()) + "行, " + QString::number(current->column()) + "]");

    QTableWidgetItem *item = nullptr;
    item = current;
    int type = current->type();
    m_labCellType->setText("当前的单元格列类型: " + QString::number(type));
    QTableWidgetItem* item2 = ui->tableWidget->item(current->row(), fieldColNum::colName);
    m_labStudID->setText("当前学生ID: " + item2->data(Qt::UserRole).toString());
}
