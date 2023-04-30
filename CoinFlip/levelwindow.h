#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include "mainmenuwindow.h"

class LevelWindow : public MainMenuWindow
{
    Q_OBJECT
public:
    explicit LevelWindow(QWidget *parent = nullptr);

signals:
    void backBtnClicked();
};

#endif // LEVELWINDOW_H
