#ifndef EXQSLIDER_H
#define EXQSLIDER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQSlider; }
QT_END_NAMESPACE

class ExQSlider : public QWidget
{
    Q_OBJECT

public:
    ExQSlider(QWidget *parent = nullptr);
    ~ExQSlider();
public slots:
    void onSetColor(int val);//int是为了和QSlider的信号对应valueChanged(int value);
private:
    Ui::ExQSlider *ui;
};
#endif // EXQSLIDER_H
