#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenuWindow; }
QT_END_NAMESPACE

class MainMenuWindow : public QDialog
{
    Q_OBJECT

public:
    MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

private:
    Ui::MainMenuWindow *ui;
};
#endif // MAINMENUWINDOW_H
