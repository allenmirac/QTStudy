# QComboBox

QComboBox 主要的功能是提供一个下拉列表供选择输入，也可以直接当作一个 QLineEdit 用作输入（`ui->comboBox->setEditable(true);`）。

## 添加项

```c++
void ExQComboBox::on_btnInitNameAge_clicked()
{
    QIcon ico;
    ico.addFile(":/girl.ico");

    QMap<QString, QString> map;
    map.insert("张投", "16岁");
    map.insert("张我", "17岁");
    map.insert("张以", "18岁");
    map.insert("张木", "19岁");
    map.insert("张李", "20岁");
    map.insert("张，", "21岁");
    map.insert("张报", "22岁");

    ui->comboBoxRight->clear();
    foreach(const QString &str, map.keys()){
        ui->comboBoxRight->addItem(ico, str, map.value(str));
    }
}
```

这里用了foreach遍历map。

添加具有用户数据的项 QComboBox::addltem() 函数的两种参数的原型定义如下：

```c++
void addItem (const QString &text, const QVariant &userData = QVariant())
void addItem (const QIcon &icon, const QString &text, const QVariant &userData = QVariant())
```

## 常用函数

QComboBox 存储的项是一个列表，但是 QComboBox 不提供整个列表用于访问，可以通过索引访问某个项。访问项的一些函数主要有以下几种：

- int currentlndex()：返回当前项的序号，第一个项的序号为0。
- QString currentText()：返回当前项的文字。
- QVariant currentData(int role = Qt::UserRole)：返回当前项的关联数据，数据的缺省角色为 role = Qt::UserRole，角色的意义在后续章节会详细介绍。
- QString itemText(int index)：返回指定索引号的项的文字。
- QVariant itemData(int index, int role = Qt%:UserRole)：返回指定索引号的项的关联数据。
- int count()：返回项的个数。


在一个 QComboBox 组件上选择项发生变化时，会发射如下两个信号：

```c++
void currentlndexChanged(int index)
void currentlndexChanged(const QString &text)
```

# QPlainTextEdit

QPlainTextEdit 是一个多行文本编辑器，用于显示和编辑多行简单文本。

QPlainTextEdit 提供**cut( )、copy( )、paste( )、undo( )、redo( )、clear( )、selectAll( )**等标准编辑功
能的槽函数，QPlainTextEdit还提供一个标准的右键快捷菜单。

QPlainTextEdit的文字内容以QTextDocument类型存储，函数document()返回这个文档对象的指针。

QTextDocument是内存中的文本对象，以文本块的方式存储，一个文本块就是一个段落，每个段落以回车符结束。QTextDocument提供一些函数实现对文本内容的存取。

## 使用方法

| 常用函数                                      | 含义()                                                |
| --------------------------------------------- | ----------------------------------------------------- |
| appendPlainText()                             | 向QPlain TextEdit添加一行话                           |
| int blockCount()                              | 获得文本块个数                                        |
| QTextBlock findBlockByNumber(int blockNumber) | 读取某一个文本块，序号从0开始，至blockCount()-1结束。 |

## 示例

```c++
void ExQComboBox::onSelectDisplay(QString str){
    QString strData = ui->comboBoxRight->currentData().toString();
    ui->plainTextEdit->appendPlainText(str + " " + strData);
}
```