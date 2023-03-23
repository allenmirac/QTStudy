#ifndef EXQCOMBOBOX_H
#define EXQCOMBOBOX_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQComboBox; }
QT_END_NAMESPACE

class ExQComboBox : public QWidget
{
    Q_OBJECT

public:
    ExQComboBox(QWidget *parent = nullptr);
    ~ExQComboBox();

private slots:
    void on_btnComboInit_clicked();
    void on_btnComboClear_clicked();

    void on_btnInitNameAge_clicked();

    void on_btnPlainTxtAdd_clicked();
    void on_btnPlainTxtClear_clicked();

    void onSelectDisplay(QString str);

    void on_cbxComboIsEdit_clicked();
    void on_cbxPlainTxtOnlyRead_clicked();

private:
    Ui::ExQComboBox *ui;
};
#endif // EXQCOMBOBOX_H
