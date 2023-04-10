#ifndef EXQTABLEWIDGET_H
#define EXQTABLEWIDGET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQTableWidget; }
QT_END_NAMESPACE

class ExQTableWidget : public QMainWindow
{
    Q_OBJECT

private:
    enum cellType{      //自定义表格的单元格的内容的Type，便于创建Item，存储自己命名的数据
        ctName,         //姓名
        ctSex,          //性别
        ctBirth,        //生日
        ctNation,       //籍贯
        ctScore,        //分数
        ctLikeAnime     //是否喜欢二次元
    };

    enum fieldColNum {  //列号
        colName,
        colSex,
        colBirth,
        colNation,
        colScore,
        colLikeAnime
    };

public:
    ExQTableWidget(QWidget *parent = nullptr);
    ~ExQTableWidget();
    //创建一行数据，item
    void createItemARow(int row, QString name, QString sex, QDate birth, QString nation, int score, bool isAnime);

private slots:
    void on_ptnSetHeader_clicked();

    void on_ptnInitTable_clicked();

    void on_ptnSetRowNum_clicked();

    void on_ptnInsertRow_clicked();

    void on_ptnAddRow_clicked();

    void on_ptnDelRow_clicked();

    void on_ptnTableToString_clicked();

    void on_ptnAutoRowHeight_clicked();

    void on_ptnAutoColHeight_clicked();

    void on_cbxTableIsEditable_clicked(bool checked);

    void on_cbxRowColor_clicked(bool checked);

    void on_cbxHeadRow_clicked(bool checked);

    void on_cbxHeadCol_clicked(bool checked);

    void on_rbtnSelectItem_clicked();

    void on_rbtnSelectRow_clicked();

    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

private:
    Ui::ExQTableWidget *ui;

    QLabel *m_labCellIndex;         //状态栏，显示行号、列号
    QLabel *m_labCellType;          //状态栏，显示单元格type
    QLabel *m_labStudID;            //状态栏，显示学号
};
#endif // EXQTABLEWIDGET_H
