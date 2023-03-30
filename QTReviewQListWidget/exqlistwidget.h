#ifndef EXQLISTWIDGET_H
#define EXQLISTWIDGET_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQListWidget; }
QT_END_NAMESPACE

class ExQListWidget : public QMainWindow
{
    Q_OBJECT

public:
    ExQListWidget(QWidget *parent = nullptr);
    ~ExQListWidget();

private slots:
    void on_toolBtnInit_clicked();

    void on_toolBtnClear_clicked();

    void on_toolBtnInsert_clicked();

    void on_toolBtnAdd_clicked();

    void on_toolBtnDelete_clicked();

private:
    Ui::ExQListWidget *ui;
};
#endif // EXQLISTWIDGET_H
