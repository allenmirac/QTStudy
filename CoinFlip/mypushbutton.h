#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushbutton(QWidget *parent = nullptr);
    explicit MyPushbutton(QString str, QWidget *parent = nullptr);
    void animationUp();
    void animationDown();
    void setBtnPix(QString url);
protected:
    void paintEvent(QPaintEvent *) override;
signals:
private:
    QString btnPix;

};

#endif // MYPUSHBUTTON_H
