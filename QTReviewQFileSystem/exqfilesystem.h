#ifndef EXQFILESYSTEM_H
#define EXQFILESYSTEM_H

#include <QMainWindow>
#include <QLabel>
#include <QCheckBox>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQFileSystem; }
QT_END_NAMESPACE

class ExQFileSystem : public QMainWindow
{
    Q_OBJECT

public:
    ExQFileSystem(QWidget *parent = nullptr);
    ~ExQFileSystem();

    void init();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::ExQFileSystem *ui;

    QLabel *m_labFileName;
    QLabel *m_labFileSize;
    QLabel *m_labFileType;
    QLabel *m_labFilePath;
    QCheckBox *m_cbxBoxIsFile;
    QFileSystemModel *m_model;
};
#endif // EXQFILESYSTEM_H
