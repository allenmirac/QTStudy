# QT 元对象系统

QT 的元对象系统（The Meta-Object System）由它的元对象编译器（Meta-Object Compiler，moc）帮忙实现，moc 通过读取头文件中的 Q_OBJCET 宏来判断是否需要生成元对象代码。如果需要，则生成以 moc_ 开头的源文件，在链接（Linking）时会和源文件一起生成可执行文件。

## 从四个方面来介绍元对象系统的奥秘

## 是什么

- 从 QT 新增的关键字（signals、slots、emit）可以看出 QT 并不是标准的 C++ 语言，而是对其进行了一定程度的扩展。
- 元对象系统是 QT 核心的一部分，用于支持 QT 的 C++ 扩展（QT’s C++ extensions），它提供了用于对象间通信的信号与槽、运行时类型信息以及动态属性系统。

## 为什么

由于 QT 是标准 C++ 的一个扩展，所以编译源代码时就需要将这些扩展的语法去掉，然后交给标准 C++ 编译器，诸如 GCC、MinGW、Clang 等。

## 怎么实现

元对象系统基于以下 3 件事：

1. `QObject`类为使用元对象系统的 QT 对象提供了一个基类。
2. `Q_OBJECT` 宏用来在类中启用元对象特性，例如动态属性、信号、槽。
3. `moc` 为每个 QObject 子类提供实现元对象特性所需要的代码。

moc 工具读取 C++ 源文件。如果发现源文件中有一个类或者多个类的声明中包含 Q_OBJECT 宏，它就生成一个包含了这些类所需要的元对象代码的源文件。这个新源文件的文件名为源文件名前加上 moc_。**新生成的源文件必须被 #include 到源文件中，或者更常见的是编译和连接到类的实现中。**

## 怎么用

元对象系统有以下特性：

- `signals and slots` 一个用于对象间通信的信号与槽机制（QT 引入元对象系统最主要的原因）。
- `QObject::metaObject()` 用来返回类关联的元对象。
- `QMetaObject::className()` 用来在运行时获取类名，**这个方法不需要原生 C++ 编译器的运行时类型信息（Runtime type information，RTTI）支持**。
- `QObject::inherits()` 用来判别一个对象是否是 QObject 继承树中的特定类的对象。
- `QObject::tr()` 和 `QObject::trUtf8()` 提供 QT 国际化中翻译字符串的支持。
- `QObject::setProperty()` 和 `QObject::property()` 提供动态地设置和获取属性名。
- `QMetaObject::newInstance()` 用于构造一个类的新实例。
- `qobject_cast` 处理继承自 QObject 类的动态转换。它不需要 RTTI 支持，并且支持跨动态库转换。转换成功返回非零指针，失败返回 nullptr。

在 QObject 的派生类中，不使用 Q_OBJECT 宏以及没有元对象代码，上述元对象系统特性也能用。需要注意的是，QMetaObject::className() 只会返回离它最近且拥有元对象代码的祖先（即最近一个声明 Q_OBJECT 的祖先）的类名。所以建议 QObject 的派生类一律添加 Q_OBJECT 宏！

## moc 使用

在这个案例中的使用：

```c++
#ifndef EXPERSION_H
#define EXPERSION_H

#include <QObject>

class ExPersion : public QObject
{
    Q_OBJECT
	//Connected to the property system is an additional macro, Q_CLASSINFO(), that can be used to attach additional name--value pairs to a class's meta-object
    Q_CLASSINFO("author","hzy");
    Q_CLASSINFO("version", "1.1.1");
    Q_CLASSINFO("info", "QT5 Meta Object and Property Example");
	//A property behaves like a class data member, but it has additional features accessible through the Meta-Object System.
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged);
    Q_PROPERTY(QString name MEMBER m_name);
    Q_PROPERTY(int score MEMBER m_score);
public:
    explicit ExPersion(QString name, QObject *parent = nullptr);

public:
    int getAge();
    void setAge(int value);

    void incAge();

signals:
    void ageChanged(int value);

private:
    int m_age = 5;
    QString m_name;
    int m_score = 50;
};

#endif // EXPERSION_H
```

官方文档的Example：

```c++
class MyClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)

public:
    MyClass(QObject *parent = nullptr);
    ~MyClass();

    enum Priority { High, Low, VeryHigh, VeryLow };
    Q_ENUM(Priority)

    void setPriority(Priority priority)
    {
        m_priority = priority;
        emit priorityChanged(priority);
    }
    Priority priority() const
    { return m_priority; }

signals:
    void priorityChanged(Priority);

private:
    Priority m_priority;
};
```

## 引用

https://beyondyuanshu.github.io/2019/09/03/qt-core-the-meta-object-system.html

https://doc.qt.io/qt-6/qobject.html#Q_PROPERTY