#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>
#include <QUrl>
#include <QDesktopServices>     // 提供桌面所有运行程序服务
#include <QCloseEvent>
#include <QFileInfo>
#include <QSize>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::MainWindow *ui;
    QString saveFileName;
    QString openFileName;
private slots:
    void newFileSlot();
    void saveFileSlot();
    void saveFileAsSlot();
    void printFileSlot();
    void openFileSlot();
    void setFontSlot();
    void setColorSlot();
    void currentDateTimeSlot();
    void aboutSlot();
    void webSlot();
};

#endif // MAINWINDOW_H
