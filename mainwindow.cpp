#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skyrovertitlebar.h"
#include <QDebug>

#define MARGIN 5

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Setup central widget with a layout to hold the views

    m_curPos = 0;
    m_bPressed = false;
    this->setMinimumSize(800,600);
    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);

    skyroverTitleBar *pTitleBar = new skyroverTitleBar(this);
    QPalette backPal(pTitleBar->palette());
    backPal.setColor(QPalette::Background, Qt::black);
    pTitleBar->setAutoFillBackground(true);
    pTitleBar->setPalette(backPal);

    titleHeight = pTitleBar->height();

    pTitleBar->setMouseTracking(true);

    QQuickWidget *pWidget = new QQuickWidget();
    pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    pWidget->setSource(QUrl::fromUserInput("qrc:/qml/mainPage.qml"));

    _centralLayout = new QVBoxLayout();
    _centralLayout->addWidget(pTitleBar);
    _centralLayout->setSpacing(0);
    _centralLayout->addWidget(pWidget);
    _centralLayout->setContentsMargins(0, 0, 0, 0);
    centralWidget()->setLayout(_centralLayout);

    //centralWidget()->setLayout(_centralLayout);
    statusBar()->setVisible(false);
    menuBar()->setVisible(false);

    setWindowFlags(Qt::FramelessWindowHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    if (Qt::LeftButton == event->button() && 0 == (Qt::WindowMaximized & this->windowState()))
    {
        QPoint temp = event->globalPos();
        pLast = temp;
        m_curPos = setCurFlag(event->pos());
        event->ignore();
    }
    m_bPressed = true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    int poss = setCurFlag(event->pos());
    setCursorShape(poss);
    event->ignore();
    qDebug() <<"Released";
    m_bPressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (this->isMaximized())
        return;

    int poss = setCurFlag(event->pos());
    if(!event->buttons())
        setCursorShape(poss);

    if ((event->buttons() & Qt::LeftButton) && m_bPressed)
    {
        QPoint ptemp = event->globalPos();
        ptemp = ptemp - pLast;


        if(m_curPos == 22)
        {
            ptemp = ptemp+pos();
            move(ptemp);
        }
        else
        {
            QRect wid = geometry();
            int minWidth = this->minimumWidth();
            int minHeight = this->minimumHeight();

        switch (m_curPos)
        {
        case 11:
            {
                QPoint pos = wid.topLeft();

                if(wid.width() > minWidth || ptemp.x() < 0)
                    pos.rx() = pos.rx() + ptemp.x();
                if(wid.height() > minHeight || ptemp.y() < 0)
                    pos.ry() = pos.ry() + ptemp.y();

                wid.setTopLeft(pos);
                break;
            }
        case 13:
            {
                QPoint pos = wid.topRight();

                if(wid.width() > minWidth || ptemp.x() > 0)
                    pos.rx() = pos.rx() + ptemp.x();
                if(wid.height() > minHeight || ptemp.y() < 0)
                    pos.ry() = pos.ry() + ptemp.y();

                wid.setTopRight(pos);
                break;
            }
         case 41:
            {
                QPoint pos = wid.bottomLeft();

                if(wid.width() > minWidth || ptemp.x() < 0)
                    pos.rx() = pos.rx() + ptemp.x();
                if(wid.height() > minHeight || ptemp.y() > 0)
                    pos.ry() = pos.ry() + ptemp.y();

                wid.setBottomLeft(pos);
                break;
            }
        case 43:
            {
                QPoint pos = wid.bottomRight();

                if(wid.width() > minWidth || ptemp.x() > 0)
                    pos.rx() = pos.rx() + ptemp.x();
                if(wid.height() > minHeight || ptemp.y() > 0)
                    pos.ry() = pos.ry() + ptemp.y();

                wid.setBottomRight(pos);
                break;
            }
        case 12:
            {
                int topY = wid.top();
                if(wid.height() > minHeight || ptemp.y() < 0)
                    topY = topY + ptemp.y();

                wid.setTop(topY);
                break;
            }
        case 21:
        case 31:
            {
                int leftX = wid.left();

                if(wid.width() > minWidth || ptemp.x() < 0)
                    leftX = leftX + ptemp.x();

                wid.setLeft(leftX);
                break;
            }
        case 23:
        case 33:
            {
                int rightX = wid.right();

                if(wid.width() > minWidth || ptemp.x() > 0)
                    rightX = rightX + ptemp.x();

                wid.setRight(rightX);
                break;
            }
        case 42:
            {
                int botY = wid.bottom();
                if(wid.height() > minHeight || ptemp.y() > 0)
                    botY = botY + ptemp.y();

                wid.setBottom(botY);
                break;
            }
        case 22:
            {

            }
        }
        setGeometry(wid);

        }
        pLast = event->globalPos();
    }
    event->ignore();
}

int MainWindow::setCurFlag(QPoint p)
{
    int column;
    if (p.x() < MARGIN)
        column = 1;
    else if (p.x() < (this->frameGeometry().width() - MARGIN))
        column = 2;
    else
        column = 3;

    int row;
    if (p.y() < MARGIN)
        row = 10;
    else if (p.y() < titleHeight)
        row = 20;
    else if (p.y() < (this->frameGeometry().height() - MARGIN))
        row = 30;
    else
        row = 40;
    return row + column;
}

void MainWindow::setCursorShape(int flag)
{
    Qt::CursorShape cursorShape;
    switch(flag)
    {
    case 11:
    case 43:
        cursorShape = Qt::SizeFDiagCursor;break;
    case 13:
    case 41:
        cursorShape = Qt::SizeBDiagCursor;break;
    case 21:
    case 23:
    case 31:
    case 33:
        cursorShape = Qt::SizeHorCursor;break;
    case 12:
    case 42:
        cursorShape = Qt::SizeVerCursor;break;
    case 22:
        //cursorShape = Qt::ArrowCursor;break;
    default:
         QApplication::restoreOverrideCursor();//恢复鼠标指针性状
         break;

    }
    setCursor(cursorShape);
}

