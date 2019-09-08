#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skyrovertitlebar.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif

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

/*
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG *param = static_cast<MSG *>(message);

    switch (param->message)
    {
    case WM_NCHITTEST:
    {
        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

        // 如果鼠标位于子控件上，则不进行处理
        if (childAt(nX, nY) != nullptr)
            return QWidget::nativeEvent(eventType, message, result);

        *result = HTCAPTION;

        // 鼠标区域位于窗体边框，进行缩放
        if ((nX > 0) && (nX < m_nBorderWidth))
            *result = HTLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width()))
            *result = HTRIGHT;

        if ((nY > 0) && (nY < m_nBorderWidth))
            *result = HTTOP;

        if ((nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOM;

        if ((nX > 0) && (nX < m_nBorderWidth) && (nY > 0)
                && (nY < m_nBorderWidth))
            *result = HTTOPLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
                && (nY > 0) && (nY < m_nBorderWidth))
            *result = HTTOPRIGHT;

        if ((nX > 0) && (nX < m_nBorderWidth)
                && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOMLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
                && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOMRIGHT;

        return true;
    }
    }

    return QWidget::nativeEvent(eventType, message, result);
}
*/

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
    QApplication::restoreOverrideCursor();
    event->ignore();

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
         case 31:
            {
                QPoint pos = wid.bottomLeft();

                if(wid.width() > minWidth || ptemp.x() < 0)
                    pos.rx() = pos.rx() + ptemp.x();
                if(wid.height() > minHeight || ptemp.y() > 0)
                    pos.ry() = pos.ry() + ptemp.y();

                wid.setBottomLeft(pos);
                break;
            }
        case 33:
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
            {
                int leftX = wid.left();

                if(wid.width() > minWidth || ptemp.x() < 0)
                    leftX = leftX + ptemp.x();

                wid.setLeft(leftX);
                break;
            }
        case 23:
            {
                int rightX = wid.right();

                if(wid.width() > minWidth || ptemp.x() > 0)
                    rightX = rightX + ptemp.x();

                wid.setRight(rightX);
                break;
            }
        case 32:
            {
                int botY = wid.bottom();
                if(wid.height() > minHeight || ptemp.y() > 0)
                    botY = botY + ptemp.y();

                wid.setBottom(botY);
                break;
            }
        }
        setGeometry(wid);

        pLast = event->globalPos();
    }
    event->ignore();
}
/*
int MainWindow::setCursorStyle(const QPoint &curPoint)
{
    int nCurWidth = this->width();
    int nCurHeight = this->height();

}
*/
int MainWindow::setCurFlag(QPoint p)
{
    int row;
    if (p.x() < MARGIN)
        row = 1;
    else if (p.x() < (this->frameGeometry().width() - MARGIN))
        row = 2;
    else
        row = 3;

    int column;
    if (p.y() < MARGIN)
        column = 10;
    else if (p.y() < (this->frameGeometry().height() - MARGIN))
        column = 20;
    else
        column = 30;
    return row + column;
}

void MainWindow::setCursorShape(int flag)
{
    Qt::CursorShape cursorShape;
    switch(flag)
    {
    case 11:
    case 33:
        cursorShape = Qt::SizeFDiagCursor;break;
    case 13:
    case 31:
        cursorShape = Qt::SizeBDiagCursor;break;
    case 21:
    case 23:
        cursorShape = Qt::SizeHorCursor;break;
    case 12:
    case 32:
        cursorShape = Qt::SizeVerCursor;break;
    case 22:
        //cursorShape = Qt::ArrowCursor;break;
    default:
         QApplication::restoreOverrideCursor();//恢复鼠标指针性状
         break;

    }
    setCursor(cursorShape);
}

