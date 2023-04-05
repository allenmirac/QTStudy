#include "exqtreewidget.h"
#include "ui_exqtreewidget.h"

ExQTreeWidget::ExQTreeWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ExQTreeWidget)
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("QTreeWidget和QDockWidget的讲解和使用"));
    setWindowIcon(QIcon(":/image/Image013.ico"));
    setCentralWidget(ui->scrollArea);
    initTree();

    m_labFile = new QLabel("当前文件的路径", this);
    ui->statusbar->addWidget(m_labFile);
}

ExQTreeWidget::~ExQTreeWidget()
{
    delete ui;
}

void ExQTreeWidget::initTree(){
    ui->treeWidget->clear();
    QString dataStr = "";
    QIcon ico;
    ico.addFile(":/image/Image001.jpg");

    //创建唯一的root节点
    QTreeWidgetItem *root = new QTreeWidgetItem(treeItemType::itemRoot);
    root->setIcon(treeColNum::colItem, ico);
    root->setText(treeColNum::colItem, QString("相册"));
    root->setText(treeColNum::colItemType, QString("treeItemType"));
    root->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    root->setCheckState(treeColNum::colItem, Qt::Unchecked);
    root->setData(treeColNum::colItem, Qt::UserRole, QVariant(dataStr));

    ui->treeWidget->addTopLevelItem(root);
}

void ExQTreeWidget::addFolderItem(QTreeWidgetItem *item, QString dirName){
    QIcon icon;
    icon.addFile(":/image/Image006.jpg");

    QTreeWidgetItem* newItem = new QTreeWidgetItem(treeItemType::itemFile);
    QString folderName = getFinalFolderName(dirName);
    newItem->setIcon(treeColNum::colItem, icon);
    newItem->setText(treeColNum::colItem, folderName);
    newItem->setText(treeColNum::colItemType, QString("treeItemType"));
    newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    newItem->setCheckState(treeColNum::colItem, Qt::Unchecked);
    newItem->setData(treeColNum::colItem, Qt::UserRole, QVariant(dirName));

    if(item->type()==treeItemType::itemFile){
        item->addChild(newItem);
    }else if(item->type()==treeItemType::itemRoot){
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(0);
        root->addChild(newItem);
    }
}

void ExQTreeWidget::addImageItem(QTreeWidgetItem *item, QString fileName){
    if(item==nullptr) return ;

    QIcon icon;
    icon.addFile(":/image/Image014.jpg");

    QTreeWidgetItem* newItem = new QTreeWidgetItem(treeItemType::itemImage);
    QString folderName = getFinalFolderName(fileName);
    newItem->setIcon(treeColNum::colItem, icon);
    newItem->setText(treeColNum::colItem, folderName);
    newItem->setText(treeColNum::colItemType, QString("treeItemType"));
    newItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    newItem->setCheckState(treeColNum::colItem, Qt::Unchecked);
    newItem->setData(treeColNum::colItem, Qt::UserRole, QVariant(fileName));

    if (item->type() == treeItemType::itemFile) {
        item->addChild(item);
    } else if (item->type() == treeItemType::itemRoot) {
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(0);
        root->addChild(newItem);
    }
}

QString ExQTreeWidget::getFinalFolderName(const QString &pathName){
    QString path = pathName;
    int cnt = pathName.count();
    int i = pathName.lastIndexOf("/");
    QString str = pathName.right(cnt -i -1);
    return str;
}

void ExQTreeWidget::changeItemCaption(QTreeWidgetItem *item){
    QString str = "# " + item->text(treeColNum::colItem);
    item->setText(treeColNum::colItem, str);

    if (item->childCount() < 0)
        return;

    for (int i = 0; i < item->childCount(); i++) {
        changeItemCaption(item->child(i));
    }
}

void ExQTreeWidget::displayImage(QTreeWidgetItem *item){
    if(item->type()==treeItemType::itemImage){
        QString fileName = item->data(treeColNum::colItem, Qt::UserRole).toString();
        m_labFile->setText(fileName);
        m_curPixmap.load(fileName);
        on_actFitHeight_triggered();

        ui->actEnlarge->setEnabled(true);
        ui->actShrink->setEnabled(true);
        ui->actFitWidth->setEnabled(true);
        ui->actFitHeight->setEnabled(true);
    }
}


void ExQTreeWidget::on_actAddFolder_triggered()
{
    QString path = QFileDialog::getExistingDirectory();

    if(!path.isEmpty()){
        QTreeWidgetItem *item = ui->treeWidget->currentItem();
        if(item!=nullptr){
            addFolderItem(item, path);
        }
    }
}


void ExQTreeWidget::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current !=nullptr && previous != nullptr){
        displayImage(current);
    }
}

void ExQTreeWidget::on_actAddFile_triggered()
{
    QStringList list = QFileDialog::getOpenFileNames(this, "选择多个将要加载的图片", "", "Image(*.jpg, *.png, *.*)");
    if(!list.empty()){
        QTreeWidgetItem *item = nullptr;
        QTreeWidgetItem *currItem = ui->treeWidget->currentItem();
        if(currItem==nullptr) return ;
        //找到父亲元素
        if(currItem->type() == treeItemType::itemImage){
            item = currItem->parent();
        }else{
            item = currItem;
        }
        for(int i=0; i<list.size(); i++){
            QString strName = list.at(i);
            addImageItem(item, strName);
        }
    }
}



void ExQTreeWidget::on_actDelFile_triggered()
{
    QTreeWidgetItem *item = nullptr;
    QTreeWidgetItem *currItem = ui->treeWidget->currentItem();
    //找到父亲元素
    if(currItem->type()!=treeItemType::itemRoot){
        item=currItem->parent();
    }

    if(currItem==nullptr || item==nullptr){
        return ;
    }
    item->removeChild(currItem);
}

//遍历所有顶层节点
void ExQTreeWidget::on_actThroughFile_triggered()
{
    for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++){
        QTreeWidgetItem *currItem = ui->treeWidget->topLevelItem(i);
        changeItemCaption(currItem);
    }
}


void ExQTreeWidget::on_actEnlarge_triggered()
{
    m_radio *=1.2;
    int height = m_curPixmap.height()*m_radio;
    int width = m_curPixmap.width()*m_radio;

    QPixmap pix = m_curPixmap.scaled(width, height);
    ui->label->setPixmap(pix);
}

void ExQTreeWidget::on_actShrink_triggered()
{
    m_radio *=0.8;
    int height = m_curPixmap.height()*m_radio;
    int width = m_curPixmap.width()*m_radio;

    QPixmap pix = m_curPixmap.scaled(width, height);
    ui->label->setPixmap(pix);
}



void ExQTreeWidget::on_actFitHeight_triggered()
{
    int height = ui->scrollArea->height();
    int realHeight = m_curPixmap.height();
    m_radio = height*1.0 / realHeight;

    QPixmap pixmap = m_curPixmap.scaledToHeight(height-50);
    ui->label->setPixmap(pixmap);
}



void ExQTreeWidget::on_actFitWidth_triggered()
{
    int width = ui->scrollArea->width();
    int realWidth = m_curPixmap.width();
    m_radio = width*1.0 / realWidth;

    QPixmap pixmap = m_curPixmap.scaledToHeight(width-50);
    ui->label->setPixmap(pixmap);
}

void ExQTreeWidget::on_actFloat_triggered(bool check)
{
    ui->dockWidget->setFloating(check);
}

void ExQTreeWidget::on_actHide_triggered(bool check)
{
    ui->dockWidget->setVisible(check);
}

void ExQTreeWidget::on_actExit_triggered()
{
    close();
}
