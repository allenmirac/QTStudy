#include "exqfilesystem.h"
#include "ui_exqfilesystem.h"

ExQFileSystem::ExQFileSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ExQFileSystem)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/qt.ico"));

    init();
    connect(ui->treeView, &QTreeView::clicked, ui->listView, &QListView::setRootIndex);
    connect(ui->treeView, &QTreeView::clicked, ui->tableView, &QTableView::setRootIndex);
}

ExQFileSystem::~ExQFileSystem()
{
    delete ui;
}

void ExQFileSystem::init(){
    m_model = new QFileSystemModel(this);
    QString currPath = QDir::currentPath();
    m_model->setRootPath(currPath);
    ui->treeView->setModel(m_model);
    ui->listView->setModel(m_model);
    ui->tableView->setModel(m_model);
    ui->columnView->setModel(m_model);

    m_labFileName = new QLabel("文件名称: ", ui->statusbar);
    m_labFileName->setMinimumWidth(188);

    m_labFileSize = new QLabel("文件大小: ", ui->statusbar);
    m_labFileSize->setFixedWidth(150);

    m_labFileType = new QLabel("文件类型: ", ui->statusbar);
    m_labFileType->setFixedWidth(150);

    m_labFilePath = new QLabel("文件路径: " + currPath, ui->statusbar);

    m_cbxBoxIsFile = new QCheckBox("当前为文件夹", ui->statusbar);
    m_cbxBoxIsFile->setFixedWidth(150);


    ui->statusbar->addWidget(m_labFileName);
    ui->statusbar->addWidget(m_labFileSize);
    ui->statusbar->addWidget(m_labFileType);
    ui->statusbar->addWidget(m_labFilePath);
    ui->statusbar->addWidget(m_cbxBoxIsFile);
}

void ExQFileSystem::on_treeView_clicked(const QModelIndex &index)
{
    m_cbxBoxIsFile->setChecked(m_model->isDir(index));
    m_labFileName->setText("文件名称: " + m_model->fileName(index));

    double size = m_model->size(index) / 1024.0;
    if(size < 1024) {
        m_labFileSize->setText("文件大小: " + QString::number(size, 'f', 2) + "KB");
    } else if(size < 1024*1024){
        m_labFileSize->setText("文件大小: " + QString::number(size / 1024, 'f', 2) + "MB");
    } else {
        m_labFileName->setText("文件大小: " + QString::number(size / (1024*1024), 'f', 2) + "GB");
    }

    m_labFilePath->setText("文件路径: " + m_model->filePath(index));
    m_labFileType->setText("文件类型: " + m_model->type(index));
}
