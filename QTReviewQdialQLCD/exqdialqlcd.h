#ifndef EXQDIALQLCD_H
#define EXQDIALQLCD_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQdialQLCD; }
QT_END_NAMESPACE

class ExQdialQLCD : public QWidget
{
    Q_OBJECT

public:
    ExQdialQLCD(QWidget *parent = nullptr);
    ~ExQdialQLCD();

public slots:
    void onDisplayLCD(int);
private slots:
    void on_radioBtn2_clicked();
    void on_radioBtn8_clicked();
    void on_radioBtn10_clicked();
    void on_radioBtn16_clicked();

private:
    Ui::ExQdialQLCD *ui;
};
#endif // EXQDIALQLCD_H
