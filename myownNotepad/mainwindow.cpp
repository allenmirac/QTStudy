#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000, 510);
    this->setWindowTitle("无标题 - 记事本");
    setCentralWidget(ui->textEdit);
    ui->statusBar->hide();

    //文件选项槽
    QObject::connect(ui->actionNewAction, SIGNAL(triggered()), this, SLOT(newFileSlot()));
    QObject::connect(ui->actionOpenAction, SIGNAL(triggered()), this, SLOT(openFileSlot()));
    QObject::connect(ui->actionSaveAction, SIGNAL(triggered()), this, SLOT(saveFileSlot()));
    QObject::connect(ui->actionSaveAsAction, SIGNAL(triggered()), this, SLOT(saveFileAsSlot()));
    QObject::connect(ui->actionExitAction, SIGNAL(triggered()), this, SLOT(close()));

    //编辑选项槽
    QObject::connect(ui->actionDateAction, SIGNAL(triggered()), this, SLOT(currentDateTimeSlot()));
    QObject::connect(ui->actionUndoAction, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    QObject::connect(ui->actionRedoAction, SIGNAL(triggered()), ui->textEdit, SLOT(redo()));
    QObject::connect(ui->actionUndoAction, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    QObject::connect(ui->actionCutAction, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    QObject::connect(ui->actionPasteAction, SIGNAL(triggered()), ui->textEdit, SLOT(paste()));
    QObject::connect(ui->actionCopyAction, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    QObject::connect(ui->actionSelectAllAction, SIGNAL(triggered()), ui->textEdit, SLOT(selectAll()));

    //format
    QObject::connect(ui->actionColor, SIGNAL(triggered()), this, SLOT(setColorSlot()));
    QObject::connect(ui->actionFontAction, SIGNAL(triggered()), this, SLOT(setFontSlot()));
    //help
    QObject::connect(ui->actionAboutAction, SIGNAL(triggered()), qApp, SLOT(aboutSlot()));
    QObject::connect(ui->actionAboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));
    QObject::connect(ui->actionWebAction, SIGNAL(triggered()), this, SLOT(webSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
// 打印文件
void MainWindow::printFileSlot()
{

}
void MainWindow::newFileSlot(){
    if(ui->textEdit->document()->isModified()){
        ui->textEdit->clear();
        this->setWindowTitle("无标题.txt");
    }
}
void MainWindow::openFileSlot(){
    openFileName = QFileDialog::getOpenFileName(this, "Open File");
    QFileInfo fileInfo = QFileInfo(openFileName);
    QString fileName = fileInfo.fileName();
    if(fileName.isEmpty()){
        QMessageBox::information(this, "Knight", "Please select a text file");
        return ;
    }
    QFile *file = new QFile;
    file->setFileName((openFileName));
    bool ok = file->open(QIODevice::ReadOnly);//设置只读权限
    if(ok){
        this->setWindowTitle(fileName+" - 记事本");
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        file->close();
        delete file;
    }
    else{
        QMessageBox::information(this, "Knight","File open error"+file->errorString());
    }
}
void MainWindow::saveFileSlot(){
    if(saveFileName.isEmpty())
    {
        this->saveFileAsSlot();
    }else{
        QFile *file = new QFile;
        file->setFileName(saveFileName);
        bool ok = file->open(QIODevice::WriteOnly);
        if(ok){
            QTextStream out(file);
            out<< ui->textEdit->toPlainText();
            file->close();
            delete file;
        }
    }
}
void MainWindow::saveFileAsSlot(){
    QString saveFileName = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), tr("文本文档(*.txt);;所有文件(*)"));
    if(saveFileName.isEmpty()){
        QMessageBox::information(this, "Knight", "Please select a file!       ");
        return ;
    }
    QFile *file = new QFile;
    file->setFileName(saveFileName);
    bool ok = file->open(QIODevice::WriteOnly);
    if(ok){
        QTextStream out(file);
        // 将内容转化为纯文本
        out << ui->textEdit->toPlainText();
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this, "Erroe Message", "File save error"+file->errorString());
        return ;
    }
}
void MainWindow::setFontSlot(){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Times", 12), this);
    if(ok){
        ui->textEdit->setFont(font);
    }else{
//        QMessageBox::information(this, "Error message", "Error set font error");
        return ;
    }
}
void MainWindow::setColorSlot(){
    QColor color = QColorDialog::getColor(Qt::green, this, "Select color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }else{
        QMessageBox::information(this, "Error Message", "Color is unvalid");
        return ;
    }
}
void MainWindow::currentDateTimeSlot(){
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("yyyy-MM-dd hh:mm:ss");
    ui->textEdit->append(time);//追加到下一行
}
void MainWindow::aboutSlot(){
//    about *dialog = new about;

}
void MainWindow::webSlot(){
    QDesktopServices::openUrl(QUrl("http://weibo.com/qqace?is_all=1"));
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(ui->textEdit->document()->isModified()){
        QMessageBox msgbox;
        if(openFileName=="")
            openFileName = "无标题";
        QFont font("微软雅黑", 11);
        msgbox.setFont(font);
        msgbox.setWindowTitle("记事本");
        msgbox.setInformativeText("是否将文件保存到"+openFileName);
        msgbox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgbox.setButtonText(2048, "保存");
        msgbox.setButtonText(8388608,"不保存");
        msgbox.setButtonText(4194394, "取消");
        msgbox.setDefaultButton(QMessageBox::Save);
        int ret = msgbox.exec();
        switch (ret)
        {
          case QMessageBox::Save:
              // 执行保存操作
              this->saveFileSlot();
              break;
          case QMessageBox::Discard:
              // 不保存则丢弃文件，事件接受，程序关闭
              event->accept();
              break;
          case QMessageBox::Cancel:
              // 取消则忽略事件
              event->ignore();
              break;
          default:
              break;
            }
        }
        else
        {
            event->accept();
        }
}

