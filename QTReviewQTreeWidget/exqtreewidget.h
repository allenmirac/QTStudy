#ifndef EXQTREEWIDGET_H
#define EXQTREEWIDGET_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QFileDialog>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class ExQTreeWidget; }
QT_END_NAMESPACE

class ExQTreeWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExQTreeWidget(QWidget *parent = nullptr);
    ~ExQTreeWidget();

    enum treeItemType{
        itemRoot,
        itemFile,
        itemImage
    };

    enum treeColNum{
        colItem=0,
        colItemType=1
    };

    void initTree();
    void addFolderItem(QTreeWidgetItem *item, QString dirName);
    void addImageItem(QTreeWidgetItem *item, QString fileName);
    QString getFinalFolderName(const QString &pathName);
    void changeItemCaption(QTreeWidgetItem *item);
    void displayImage(QTreeWidgetItem *item);


private slots:
    void on_actAddFolder_triggered();

    void on_actAddFile_triggered();

    void on_actDelFile_triggered();

    void on_actThroughFile_triggered();

    void on_actEnlarge_triggered();

    void on_actShrink_triggered();

    void on_actFitHeight_triggered();

    void on_actFitWidth_triggered();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actFloat_triggered(bool check);

    void on_actHide_triggered(bool check);

    void on_actExit_triggered();

private:
    Ui::ExQTreeWidget *ui;

    QLabel *m_labFile;
    QPixmap m_curPixmap;
    float m_radio;
};
#endif // ExQTreeWidget_H
