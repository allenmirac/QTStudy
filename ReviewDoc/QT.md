# QT初识

## 第一个QT程序

https://www.xinbaoku.com/archive/dec4s2cz.html

## 项目的目录结构

在项目名称节点下面，分组管理着项目内的各种源文件，几个文件及分组分别为以下几项：

- Demo.pro 是项目管理文件，包括一些对项目的设置项。
- Headers 分组，该节点下是项目内的所有头文件（.h），图 5 中所示项目有一个头文件 mainwindow.h，是主窗口类的头文件。
- Sources 分组：该节点下是项目内的所有 C++源文件（.cpp），图 5 中所示项目有两个 C++ 源文件，mainwindow.cpp 是主窗口类的实现文件，与 mainwindow.h 文件对应。main.cpp 是主函数文件，也是应用程序的入口。
- Forms 分组：该节点下是项目内的所有界面文件（.ui）。图 5 中所示项目有一个界面文件mainwindow.ui，是主窗口的界面文件。界面文件是文本文件，使用 XML 语言描述界面的组成。

### .pro文件详解

https://www.xinbaoku.com/archive/2AcqsKcv.html

**存储项目的基本配置**

```properties
QT       += core gui
```

在项目中添加适当的类库模块支持，core gui 是 Qt 用于 GUI 设计的类库模块

如果要使用`sql`模块：`QT += sql`；

第 2 行是：

```properties
greaterThan(Qt_MAJOR_VERSION, 4): Qt += widgets
```

这是个条件执行语句，表示当 Qt 主版本大于 4 时，才加入 widgets 模块。

```properties
# Qt是 工程模块变量，引入了 qt的core 和 gui模块
QT       += core gui

#如果qt版本号大于4，就引入widgets模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#指定目标，生成可执行程序的名字.exe
TARGET = 01_hello
#模板，生成什么文件，app表示应用程序exe,lib 就是生成库
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.'
# 如果你用了过时的api，就会报warning
DEFINES += QT_DEPRECATED_WARNINGS
```



### .ui 文件详解

https://www.xinbaoku.com/archive/8yc8sMF5.html

**窗体界面定义文件，利用XML的语法来配置窗口上面的组件。**

但是在设计界面时，不用管 widget.ui文件是怎么生成的，由QT自己解析。

属性编辑器（Property Editor）：窗口右下方是属性编辑器，是界面设计时最常用到的编辑器。属性编辑器的内容分为两列，分别为属性的名称和属性的值。属性又分为多个组，实际上表示了类的**继承关系**。

![信号与槽编辑器中设计信号与槽的关联](https://www.xinbaoku.com/uploads/allimg/181229/2-1Q229103100196.gif)

**信号与槽编辑器的工具栏**：信号与槽编辑器的工具栏上单击“Add”按钮，在出现的条目中，Sender 选择 btnClose，Signal 选择 clicked()，Receiver 选择窗体 Widget，Slot 选择 close()。这样设置表示当按钮 btnClose 被单击时，**就执行 Widget 的 close() 函数，实现关闭窗口的功能。**

## main主函数及其作用

https://www.xinbaoku.com/archive/B6cBs0F0.html

```c++
#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //定义并创建应用程序
    Widget w; //定义并创建窗口
    w.show(); //显示窗口
    return a.exec(); //应用程序运行
}
```

利用`a.exec()`来开始应用程序的消息循环和事件处理。

## 信号与槽机制

https://www.xinbaoku.com/archive/zbcNsMF8.html

https://www.cnblogs.com/QG-whz/p/4995938.html

**信号与槽机制实际上都是函数，当一个事件触发之后，会发送一个信号，与这个信号连接的槽函数接受这个信号之后，作出反应。**

> 信号：各种事件
>
> 槽：响应信号的动作

**没有使用C++的回调函数的原因是C++这种方法不是类型安全的，所以QT采用了信号与槽这种类型安全的方式。**

信号与槽关联是用 QObject::connect() 函数实现的，其基本格式是：

```c++
QObject::connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
```

conncet(信号发送者，信号，信号接收者，槽)



connect里边4个参数都是指针

```c++
connect(btn,&QPushButton::clicked,this,&Widget::hide);
```

使用connect的时候保留&符号
    1 提高代码可读性
    2 自动提示

connect() 是 QObject 类的一个静态函数，而 QObject 是所有 Qt 类的基类，在实际调用时可以忽略前面的限定符，所以可以直接写为：

```c++
connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
```

其中，sender 是发射信号的对象的名称，signal() 是信号名称。信号可以看做是特殊的函数，需要带括号，有参数时还需要指明参数。receiver 是接收信号的对象名称，slot() 是槽函数的名称，需要带括号，有参数时还需要指明参数。

信号与槽的规则：**一对多，多对一**

* 一个信号可以连接多个槽，这个时候连接connect函数里面要指定参数的类型

* * ```C++
        connect(spinNum, SIGNAL(valueChanged(int)), this, SLOT(addFun(int))
    ```

* 多个信号可以连接同一个槽。

* 一个信号可以连接另外一个信号。

* 在使用信号与槽的类中，必须在类的定义中加入宏 Q_OBJECT。



### 自定义信号和槽

​	自定义信号
​		1 函数声明在类头文件的signals 域下面
​		2 void 类型的函数，没有返回值
​		3 可以有参数，也可以重载
​		4 只有声明，没有实现定义
​		5 触发信号 emit obj->sign(参数...)

自定义槽
	1 函数声明在类头文件的public/private/protected slots域下面（qt4以前的版本）
		qt5 就可以声明在类的任何位置，还可以是静态成员函数、全局函数、lambda表达式
	2 void 类型的函数，没有返回值
	3 可以有参数，也可以重载
	4 不仅有声明，还得有实现
	
场景：下课了，老师说他饿了，学生就请吃饭
	信号发送者：老师
	信号：老师饿了
	信号接收者：学生
	槽：请吃饭
创多少个类：Teacher Student
信号： hungry 1个 Teacher
槽：treat 1个 Student 	

带参数的自定义信号和槽，就声明函数的时候就带上参数就行
老师说他饿了，说要吃黄焖鸡，学生就请吃黄焖鸡

调用带参数的信号函数 emit pTeacher->hungry("黄焖鸡");

参数二义性问题：
	1 使用函数指针赋值，让编译器自动挑选符合类型的函数
	2 使用static_cast 强制转换 ，让编译器自动挑选符合类型的函数	

## Qt纯代码设计UI实例分析

https://www.xinbaoku.com/archive/K6cKs9FE.html

使用起来比较繁琐。

## Qt Creator使用技巧

https://www.xinbaoku.com/archive/w9cws6Fx.html

ctrl+i，对齐

ctrl+/，注释

F1			帮助文档

F4			头文件和源文件之间跳转

快捷键。

## QT父子关系

```c++
    //添加按钮 会在顶层显示
    //    QPushButton btn;
    //    btn.setText("按钮1");
    //    //将按钮显示出来
    //    btn.show();


    //默认情况下没有建立父子关系，显示的都是顶层窗口
    //要建立父子关系

    //1 setParent函数
    QPushButton btn;
    btn.setText("按钮1");
    btn.setParent(&w);

    //2 构造函数传参
    QPushButton btn2("按钮2",&w);
    //移动以下按钮位置
    btn2.move(100,100);
    //重新设置窗口大小
    btn2.resize(400,400);

    //按钮3，和按钮2建立父子关系
    QPushButton btn3("按钮3",&btn2);
    btn3.move(100,100);
    //设置窗口标题
    w.setWindowTitle("HelloWorld");


    //设置窗口的固定大小
	//w.setFixedSize(800,600);
    //同时设置窗口对的位置和大小
    w.setGeometry(400,400,500,500);
    w.show();
    //顶层窗口移动到200,100
	//w.move(200,100);
```

## QT常用API

move 移动窗口到父窗口某个坐标
resize 重新设置窗口的大小
setFixedSize 设置窗口的固定大小
setWindowTitle 设置窗口标题
setGeometry 同时设置窗口位置和大小，相当于move和resize的结合体

# 对象树

概念：各个窗口对象通过建立父子关系构造的一个关系树
内存管理：
		父对象释放的时候会自动释放各个子对象（使用children列表，自动添加孩子）
以后基本都是用new的方式来创建窗口对象
注意点：
	1 父对象能够被释放
	2 父对象、子对象，直接或者间接继承自QObject



# QTNetwork

## QTcpSocket

https://blog.csdn.net/gongjianbo1992/article/details/107743780

## QUdpSocket

https://hyw-zero.github.io/2019/02/11/Qt%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0%E4%B9%8Bsocket%E9%80%9A%E4%BF%A1/#1-2-UDP%E9%80%9A%E4%BF%A1%E6%B5%81%E7%A8%8B%E5%9B%BE



# Qt 的元对象系统

Qt 的元对象系统（Meta-Object System）提供了对象之间通信的信号与槽机制、运行时类型信息和动态属性系统。

元对象系统由以下三个基础组成：

1. QObject 类是所有使用元对象系统的类的基类。
2. 在一个类的 private 部分**声明 Q_OBJECT宏**，使得类可以使用元对象的特性，如动态属性、信号与槽。
3. MOC（元对象编译器）为每个 QObject 的子类提供必要的代码来实现元对象系统的特性。

构建项目时，MOC 工具读取 C++ 源文件，当它发现类的定义里有 Q_OBJECT 宏时，它就会为这个类生成另外一个包含有元对象支持代码的 C++ 源文件，这个生成的源文件连同类的实现文件一起被编译和连接。

https://xmuli.blog.csdn.net/article/details/105925608

元对象有许多接口提供给子类使用，如`qobject_cast()` 函数进行动态投射(dynamic cast)。

# QLCDNumber属性：

QLCDNumber是模拟LCD显示数字的组件，可以显示整数或小数，但就如实际的LCD一样，要设定显示数字的个数。显示整数时，还可以选择以不同进制来显示，如十进制、二进制、十六进制。其主要属性如下。

| 属性              | 含义                                                         |
| ----------------- | ------------------------------------------------------------ |
| digitCount        | 显示的数的位数，如果是小数，小数点也算一个数位               |
| smallDecimalPoint | 是否有小数点，如果有小数点，就可以显示小数                   |
| mode              | 数的显示进制，通过调用函数setDecMode）、setBinMode（）、setOctMode）、setHexMode（）可以设置为常用的十进制、二进制、八进制、十六进制格式 |
| value             | 返回显示值，浮点数。若设置为显示整数，会自动四舍五入后得到整数，设置为intValue的值。如果smallDecimalPoint=true，设置value时可以显示小数，但是数的位数不能超过digitCount |
| intValue          | 返回显示的整数值                                             |

例如，若smallDecimalPoint-true，digitCount=3，设置value=2.36，则界面上LCDNumber组件会显示为2.4；若设置value=1456.25，则界面上LCDNumber组件只会显示145。所以，用QLCDNumber作为显示组件时，应注意这些属性的配合。

# QIcon的用法

```c++
QIcon *icon = new QIcon(":/icon/qt.ico");
this->setWindowIcon(*icon);
```





