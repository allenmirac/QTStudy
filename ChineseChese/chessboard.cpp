#include "chessboard.h"
#include "ui_chessboard.h"

ChessBoard::ChessBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChessBoard)
{
    ui->setupUi(this);

    init();
}

ChessBoard::~ChessBoard()
{
    delete ui;
}

void ChessBoard::init(){
    for(int i=0; i<32; i++){
        m_chessPieces[i].init(i);
    }
    m_chessSteps.clear();
    m_selectID = -1;
    m_checkedID = -1;
    m_isTcpServer = true;
    m_isRed = true;
    m_isOver = false;
    m_isShowStep = true;
}

void ChessBoard::reset()
{
    m_Chessvoice.voiceWin();
    m_isOver = true;
    if(m_isStart){
        m_timer->stop();
        m_isStart = false;
    }

}

bool ChessBoard::isRed(int id)
{
    return m_chessPieces[id].m_isRed;
}

bool ChessBoard::isDead(int id)
{
    return m_chessPieces[id].m_isDead;
}

void ChessBoard::killStone(int id)
{
    if(id== -1)
        return;
    m_chessPieces[id].m_isDead= true;
}

void ChessBoard::reviveStone(int id)
{
    if(id== -1)
        return;
    m_chessPieces[id].m_isDead= false;
}

void ChessBoard::moveStone(int moveid, int row, int col)
{
    m_chessPieces[moveid].m_row= row;
    m_chessPieces[moveid].m_col= col;

    m_isRed= !m_isRed;
}

bool ChessBoard::sameColor(int moveId, int killId)
{
    if(moveId== -1 || killId== -1)
        return false;

    return isRed(moveId) == isRed(killId);
}

int ChessBoard::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if((m_chessPieces[i].m_row==row) && (m_chessPieces[i].m_col==col) && !isDead(i))
            return i;
    }

    return -1;
}

int ChessBoard::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;
    if(row1 == row2)
    {
        int min  = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1)
                ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1)
                ++ret;
        }
    }

    return ret;
}

void ChessBoard::whoWin()
{
    if(m_chessPieces[4].m_isDead && !m_chessPieces[20].m_isDead)
    {
        reset();
        winMessageBox("提示", "本局结束，红方胜利.");
    }

    if(!m_chessPieces[4].m_isDead && m_chessPieces[20].m_isDead)
    {
        reset();
        winMessageBox("提示", "本局结束，黑方胜利.");
    }
}

bool ChessBoard::isChecked(QPoint pt, int &row, int &col)
{
    for(row = 0; row <= 9; row++)
    {
        for(col = 0; col <= 8; col++)
        {
            QPoint temp = center(row, col);
            int x = temp.x()-pt.x();
            int y = temp.y()-pt.y();

            if(x*x+y*y < m_radius*m_radius)
                return true;
        }
    }

    return false;
}

int ChessBoard::relation(int row1, int col1, int row2, int col2)
{
    // 两个坐标：原坐标(row1,col1)，目标坐标(row2,col2)的关系
    // 使用原坐标与目标坐标的行相减的绝对值乘以10 加上原坐标与目标坐标的列相减的绝对值
    // 作为关系值
    // 关系值用于判断是否符合棋子移动规则
    return abs(row1-row2)*10+ abs(col1-col2);
}

QPoint ChessBoard::getRealPoint(QPoint pt)
{
    int side = qMin(int((ui->centralwidget->width() - ui->rightWidget->width() / 0.9)), ui->label->height());
    QPoint ret;

    ret.setX(pt.x() / double(side) * 960.0);
    ret.setY(pt.y() / double(side) * 960.0);

    return ret;
}

void ChessBoard::winMessageBox(QString title, QString msg)
{
    QMessageBox message(QMessageBox::Information, title, msg);
    message.setIconPixmap(QPixmap(":/images/win.jpg"));
    message.setFont(QFont("FangSong", 16, QFont::Bold));
    message.exec();
}

QPoint ChessBoard::center(int row, int col)
{
    QPoint rePoint;
    rePoint.ry() = row*m_distance+m_offset;
    rePoint.rx() = col*m_distance+m_offset;

    return rePoint;
}

QPoint ChessBoard::center(int id)
{
    return center(m_chessPieces[id].m_col, m_chessPieces[id].m_col);
}

void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//渲染提示
    int side = qMin(int(ui->centralwidget->width() - ui->rightWidget->width()), ui->label->height());
    m_offset = 60;              //距离界面的边距
    m_distance = 90;            //间距为90px
    m_radius = m_distance/2;    //棋子半径为d/2

    for(int i = 0; i <10; i++){
        painter.drawLine(QPoint(m_offset, m_offset+i*m_distance), QPoint(m_offset+8*m_distance, m_offset+i*m_distance));
    }
    for(int i=0; i<9; i++){
        if(i==0 || i==8){
            painter.drawLine(QPoint(m_offset+i*m_distance, m_offset), QPoint(m_offset+i*m_distance, m_offset+9*m_distance));
        }else{
            painter.drawLine(QPoint(m_offset+i*m_distance, m_offset), QPoint(m_offset+i*m_distance, m_offset+4*m_distance));
            painter.drawLine(QPoint(m_offset+i*m_distance, m_offset+5*m_distance), QPoint(m_offset+i*m_distance, m_offset+9*m_distance));
        }
    }

    painter.drawLine(QPoint(m_offset+3*m_distance, m_offset), QPoint(m_offset+5*m_distance, m_offset+2*m_distance));
    painter.drawLine(QPoint(m_offset+3*m_distance, m_offset+2*m_distance), QPoint(m_offset+5*m_distance, m_offset));
    painter.drawLine(QPoint(m_offset+3*m_distance, m_offset+7*m_distance), QPoint(m_offset+5*m_distance, m_offset+9*m_distance));
    painter.drawLine(QPoint(m_offset+3*m_distance, m_offset+9*m_distance), QPoint(m_offset+5*m_distance, m_offset+7*m_distance));

    QRect rect1(m_offset+m_distance,   m_offset+4*m_distance, m_distance, m_distance);
    QRect rect2(m_offset+2*m_distance, m_offset+4*m_distance, m_distance, m_distance);
    QRect rect3(m_offset+5*m_distance, m_offset+4*m_distance, m_distance, m_distance);
    QRect rect4(m_offset+6*m_distance, m_offset+4*m_distance, m_distance, m_distance);
    painter.setFont(QFont("FangSong", m_radius * 5 / 6, 800));
    painter.drawText(rect1, "楚", QTextOption(Qt::AlignCenter));
    painter.drawText(rect2, "河", QTextOption(Qt::AlignCenter));
    painter.drawText(rect3, "汉", QTextOption(Qt::AlignCenter));
    painter.drawText(rect4, "界", QTextOption(Qt::AlignCenter));

    //*******************绘画棋子*******************
    //绘制上次移动棋子的起止位置
    if(m_isShowStep)
        drawLastStep(painter,m_chessSteps);

    for(int i = 0; i < 32; i++)
        drawChessPieces(painter, i);

    //绘制文本棋谱
    drawTextStep();
}




