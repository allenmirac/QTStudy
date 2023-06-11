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
    if(id == -1)
        return;
    m_chessPieces[id].m_isDead= true;
}

void ChessBoard::reviveStone(int id)
{
    if(id == -1)
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
    return abs(row1-row2)*10 + abs(col1-col2);
}

QPoint ChessBoard::getRealPoint(QPoint pt)
{
    int side = qMin(int((ui->centralwidget->width() - ui->rightWidget->width() / 0.9)), ui->label->height());
    QPoint ret;

    ret.setX(pt.x() / double(side) * 960.0);
    ret.setY(pt.y() / double(side) * 960.0);

    return ret;
}

bool ChessBoard::hongMenFeast()
{
    if(m_chessPieces[4].m_isDead || m_chessPieces[20].m_isDead)
        return false;

    int colBlack = m_chessPieces[4].m_col;
    int colRed = m_chessPieces[20].m_col;
    int rowBlack = m_chessPieces[4].m_row;
    int rowRed = m_chessPieces[20].m_row;

    bool isColEmpty = true;
    if (colBlack == colRed){
        for (int row = rowBlack + 1; row < rowRed ; ++row) {
            if (havePieces(row, colBlack))
                isColEmpty = false;  // 将之间有棋子；非此列为空
        }
    } else {
        isColEmpty = false;
    }

    return isColEmpty;
}

bool ChessBoard::havePieces(int row, int col)
{
    for (auto pieces : m_chessPieces) {
        if (pieces.m_isDead)
            continue;

        if (pieces.m_row == row && pieces.m_col == col)
            return true;
    }

    return false;
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
    return center(m_chessPieces[id].m_row, m_chessPieces[id].m_col);
}

void ChessBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//渲染提示
    int side = qMin(int(ui->centralwidget->width() - ui->rightWidget->width()), ui->label->height());
    painter.scale(side / 960.0, side / 960.0);
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

void ChessBoard::drawChessPieces(QPainter &painter, int id)
{
    if(m_chessPieces[id].m_isDead)
        return ;
    QPoint temp = center(id);
    QRect rect(temp.x()-m_radius, temp.y()-m_radius, m_distance, m_distance);
    if(m_selectID == id){
        painter.setBrush(QBrush(QColor(64, 64, 196, 80)));
    }else {
        painter.setBrush(QBrush(QColor(64, 64, 196, 10)));
    }

    painter.setPen(QColor(0, 0, 0));
    painter.drawEllipse(center(id), m_radius, m_radius);
    painter.setFont(QFont("FangSong", m_radius*5/6, 2700));

    if(id<16){
        painter.setPen(QColor(0, 0, 0));
    }else{
        painter.setPen(QColor(255, 0, 0));
    }
    painter.drawText(rect, m_chessPieces[id].getName(m_chessPieces[id].m_isRed), QTextOption(Qt::AlignCenter));
}

void ChessBoard::drawLastStep(QPainter &painter, QVector<ChessStep *> &steps)
{
    if(this->m_chessSteps.size() == 0)
        return ;
    QPoint stepFrom = center(steps.last()->m_rowFrom, steps.last()->m_colFrom);
    QRect rectFrom(stepFrom.x()-m_radius, stepFrom.y()-m_radius, m_distance, m_distance);
    painter.setBrush(QColor(0, 0, 0, 0.3*255));
    QPen pen(Qt::SolidLine);
    painter.setPen(pen);
    painter.drawRect(rectFrom);

    QPoint stepTo = center(steps.last()->m_rowTo, steps.last()->m_colTo);
    QRect rectTo(stepTo.x()-m_radius, stepTo.y()-m_radius, m_distance, m_distance);
    painter.setBrush(QColor(0, 0, 0, 0.2*255));
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.drawRect(rectTo);
}

void ChessBoard::drawTextStep()
{
    ui->labelStepRecord->setText(textStepsRecord);
}

bool ChessBoard::canMove(int moveId, int killId, int row, int col)
{
    if(sameColor(killId, moveId)){
        m_selectID=killId;
        update();
        return false;
    }

    switch (m_chessPieces[moveId].m_emType)
    {
    case ChessPieces::JIANG:
        return canMoveJIANG(moveId, killId, row, col);

    case ChessPieces::SHI:
        return canMoveSHI(moveId, killId, row, col);

    case ChessPieces::XIANG:
        return canMoveXIANG(moveId, killId, row, col);

    case ChessPieces::MA:
        return canMoveMA(moveId, killId, row, col);

    case ChessPieces::CHE:
        return canMoveCHE(moveId, killId, row, col);

    case ChessPieces::PAO:
        return canMovePAO(moveId, killId, row, col);

    case ChessPieces::BING:
        return canMoveBING(moveId, killId, row, col);

    default: break;
    }

    return true;
}

bool ChessBoard::canMoveJIANG(int moveId, int killId, int row, int col)
{
    if (killId != -1 && m_chessPieces[killId].m_emType == m_chessPieces->JIANG)
        return canMoveCHE(moveId, killId, row, col);

    if(isRed(moveId)){
        if(row < 7 || col < 3 || col > 5) return false;
    }else{
        if(row > 2 || col < 3 || col > 5) return false;
    }
    int d=relation(m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col, row, col);
    if(d==1 || d==10){
        return true;
    }
    return false;
}

bool ChessBoard::canMoveSHI(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    if(isRed(moveId)){
        if(row < 7 || col < 3 || col > 5) return false;
    }else{
        if(row > 2 || col < 3 || col > 5) return false;
    }

    int d=relation(m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col, row, col);
    if(d == 11)
        return true;

    return false;
}

bool ChessBoard::canMoveXIANG(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col, row, col);
    if(d!= 22)
        return false;

    int row_eye= (m_chessPieces[moveId].m_row + row)/ 2;
    int col_eye= (m_chessPieces[moveId].m_col + col)/ 2;

    if(getStoneId(row_eye,col_eye)!= -1)
        return false;

    if(isRed(moveId)){
        if(row< 4)
            return false;
    }else{
        if(row> 5)
            return false;
    }

    return true;
}

bool ChessBoard::canMoveMA(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col, row, col);
    if(d!=12 && d!=21)
        return false;

    if(d==12){
        if(getStoneId(m_chessPieces[moveId].m_row, (m_chessPieces[moveId].m_col+ col) /2) != -1)
            return false;
    }else{
        if(getStoneId((m_chessPieces[moveId].m_row+ row) /2 ,m_chessPieces[moveId].m_col) != -1)
            return false;
    }

    return true;
}

bool ChessBoard::canMoveCHE(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int ret = getStoneCountAtLine(m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col, row, col);
    if(ret == 0)
        return true;

    return false;
}

bool ChessBoard::canMovePAO(int moveId, int killId, int row, int col)
{
    int ret = getStoneCountAtLine(row, col, m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col);
    if(killId != -1){
        if(ret == 1)
            return true;
    }else{
        if(ret == 0)
            return true;
    }
    return false;
}

bool ChessBoard::canMoveBING(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_chessPieces[moveId].m_row, m_chessPieces[moveId].m_col, row, col);
    if(d!= 1 && d!= 10)
        return false;

    if(isRed(moveId)){
        if(row> m_chessPieces[moveId].m_row)
            return false;

        if(m_chessPieces[moveId].m_row>= 5 && m_chessPieces[moveId].m_row== row)
            return false;
    }else{
        if(row< m_chessPieces[moveId].m_row)
            return false;
        if(m_chessPieces[moveId].m_row<= 4 && m_chessPieces[moveId].m_row== row)
            return false;
    }

    return true;
}

bool ChessBoard::canSelect(int id)
{
    return m_isRed == m_chessPieces[id].m_isRed;
}

void ChessBoard::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton || m_isOver== true) {
        return;
    }
    QPoint pt= ev->pos();
    pt=getRealPoint(pt);
    click(pt);
}

void ChessBoard::click(QPoint pt)
{
    int row, col;
    bool isClicked = isChecked(pt, row, col);
    if (!isClicked) {
        return;
    }

    int id = getStoneId(row, col);
    clickPieces(id, row, col);
}

void ChessBoard::clickPieces(int id, int row, int col)
{
    if (this->m_selectID == -1) {   //点击而不拖动
        trySelectStone(id);
    } else {                        //点击后拖动，是点击两下还是拖动？
        tryMoveStone(id, row, col);
    }
}

void ChessBoard::trySelectStone(int id)
{
    if (id == -1) {
        return;
    }

    if (!canSelect(id)) {
        return;
    }

    m_selectID = id;
    update();
    m_Chessvoice.voiceSelect();
}

void ChessBoard::tryMoveStone(int killid, int row, int col)
{
    if (killid != -1 && sameColor(killid, m_selectID)) {    //同阵营，相当于点击另外一个棋子
        trySelectStone(killid);
        return;
    }

    bool ret = canMove(m_selectID, killid, row, col);
    if (ret) {
        doMoveStone(m_selectID, killid, row, col);
        m_selectID = -1;
        update();
    }
}

void ChessBoard::doMoveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid, killid, row, col, m_chessSteps);

    killStone(killid);
    moveStone(moveid, row, col);
    whoWin();

    if(killid== -1)
        m_Chessvoice.voiceMove();
    else
        m_Chessvoice.voiceEat();

    if(isGeneral())
        m_Chessvoice.voiceGeneral();
}

void ChessBoard::saveStep(int moveid, int killid, int row, int col, QVector<ChessStep *> &steps)
{
    ChessStep* step = new ChessStep;
    step->m_colFrom = m_chessPieces[moveid].m_col;
    step->m_colTo = col;
    step->m_rowFrom = m_chessPieces[moveid].m_row;
    step->m_rowTo = row;
    step->m_moveID = moveid;
    step->m_killID = killid;

    steps.append(step);
    textStepsRecord = textStep(moveid, row, col);
}

QString ChessBoard::textStep(int id, int row, int col)
{
    int rowFrom= m_chessPieces[id].m_row;
    int rowTo= row;
    int colFrom= m_chessPieces[id].m_col;
    int colTo= col;

    QString temp="";
    QString name=m_chessPieces[id].getName(m_chessPieces[id].m_isRed);
    QString textCol= m_chessPieces[id].getColText(colFrom);
    QString textRow= m_chessPieces[id].getRowText(rowTo);
    temp.append(name).append(textCol).append(textRow);

    //兵炮车将
    if(m_chessPieces[id].m_emType==6 || m_chessPieces[id].m_emType==5 || m_chessPieces[id].m_emType==4 || m_chessPieces[id].m_emType==0)
    {
        //行相等
        if(rowFrom== rowTo)
        {
            temp.append(m_chessPieces[id].getColText(colTo));
            return temp;
        }
        //移动的格数
        temp.append(m_chessPieces[id].getMoveText(rowFrom, rowTo));
    }
    else    //马相士
    {
        //移动后所在列
        temp.append(m_chessPieces[id].getColText(colTo));
    }
    return temp;
}








