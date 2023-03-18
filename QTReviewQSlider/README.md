# QT QSlider

## 是什么

滑块是控制有界值的经典小部件。它允许用户沿着水平或垂直槽移动滑块手柄，并将手柄的位置转换为合法范围内的整数值。

`QSlider` 自己的功能很少，大部分功能都继承于 `QAbstractSlider `。最常用的函数是 `setValue ()` ，它可以将滑块直接设置为某个值; `triggerAction ()`可以模拟单击的效果(对快捷键有用) ;`setSingleStep () `，`setPageStep ()`可以设置步骤; `setMinimum() `和 `setMaximum()`可以定义滚动条的范围。

## 怎么用

**继承的属性：**

- `minimum`、`maximum`：设置输入范围的最小值和最大值，例如，用红、绿、蓝配色时，每
    种基色的大小范围是0~255，所以设置**minimum**为0，**maximum**为255。

- `singlestep`:单步长，拖动标尺上的滑块，或按下左/右光标键时的最小变化数值。

- `pageStep`:在**Slider**上输入焦点，按**PgUp**或**PgDn**键时变化的数值。

- `value`：组件的当前值，拖动滑块时自动改变此值，并限定在**minimum**和**maximum**定义的
    范围之内。

- `sliderPosition`:滑块的位置，若**tracking**属性设置为true，**sliderPosition**就等于value。

- **`tracking`：sliderPosition**是否等同于**value**，如果**tracking**=true，改变value时也同时改变
    sliderPosition。

- `orientation`: **Slider**的方向，可以设置为水平或垂直。方向参数是Qt的枚举类型enum

- `Qt::Orientation`：取值包括以下两种。

    | 枚举           | 含义     |
    | -------------- | -------- |
    | Qt::Horizontal | 水平方向 |
    | Qt::Vertical   | 垂直方向 |

- `invertedAppearance`:显示方式是否反向，**invertedAppearance**=false时，水平的Slider由左向右数值增大，否则反过来。

- `invertedControls`：反向按键控制，若**invertedControls**=true，则按下**PgUp**或**PgDn**按键时调整数值的反向相反。

- **属于QSlider的专有属性有两个，如下：**

- `tickPosition`:标尺刻度的显示位置，使用枚举类型**QSlider:TickPosition**，取值包括以下6种

    | 枚举                    | 含义               |
    | ----------------------- | ------------------ |
    | QSlider::NoTicks        | 不显示刻度         |
    | QSlider::TicksBothSides | 标尺两侧都显示刻度 |
    | QSlider::TicksAbove     | 标尺上方显示刻度   |
    | QSlider::TicksBelow     | 标尺下方显示刻度   |
    | QSlider::TicksLeft      | 标尺左侧显示刻度   |
    | QSlider::TicksRight     | 标尺右侧显示刻度   |

- `ticklnterval`：标尺刻度的间隔值，若设置为0，会在**singleStep**和**pageStep**之间自动选择。

## 案例

```c++
#include "exqslider.h"
#include "ui_exqslider.h"

ExQSlider::ExQSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExQSlider)
{
    ui->setupUi(this);
    setWindowTitle(QString("QSlider的用法"));

    //QSlider控件，设置最大值为255,初始范围是0-100;
    ui->sliderRed->setMaximum(255);
    ui->sliderGreen->setMaximum(255);
    ui->sliderBlue->setMaximum(255);
    ui->sliderAlpha->setMaximum(255);

    //QSlider控件，设置初值
    ui->sliderRed->setValue(145);
    ui->sliderGreen->setValue(190);
    ui->sliderBlue->setValue(251);
    ui->sliderAlpha->setValue(255);

    //QTextEdit控件，设置初试颜色
    QColor color;
    color.setRgb(145, 190, 251, 255);
    QPalette palette = ui->textColor->palette();//拿到调色板
    palette.setColor(QPalette::Base, color);	//设置背景颜色
    ui->textColor->setPalette(palette);

    connect(ui->sliderRed, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
    connect(ui->sliderGreen, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
    connect(ui->sliderBlue, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
    connect(ui->sliderAlpha, &QSlider::valueChanged, this, &ExQSlider::onSetColor);
}

ExQSlider::~ExQSlider()
{
    delete ui;
}

void ExQSlider::onSetColor(int val){
    Q_UNUSED(val);

    int nRed = ui->sliderRed->value();
    int nGreen = ui->sliderGreen->value();
    int nBlue = ui->sliderBlue->value();
    int nAlpha = ui->sliderAlpha->value();

    QColor color;
    color.setRgb(nRed, nGreen, nBlue, nAlpha);
    QPalette palette = ui->textColor->palette();
    palette.setColor(QPalette::Base, color);
    ui->textColor->setPalette(palette);

    ui->labRGBVal->setText(QString("RGB(%1, %2, %3, %4)").arg(nRed).arg(nGreen).arg(nBlue).arg(nAlpha));

}
```

