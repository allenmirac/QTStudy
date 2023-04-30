#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "mainmenuwindow.h"
#include "levelwindow.h"

class StartWindow : public MainMenuWindow
{
    Q_OBJECT
public:
    explicit StartWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
private:
    LevelWindow levelWindow;
signals:

};

#endif // STARTWINDOW_H
