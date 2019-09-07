#include "skyrovertitlebar.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

skyroverTitleBar::skyroverTitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(30);
    //setStyleSheet("background-color: rgb(0,0,0)");
    //setAutoFillBackground(true);


    m_pIconLabel = new QLabel(this);

    //m_pSpaceLabel = new QLabel(this);
    m_pFly = new QPushButton(this);
    m_pPlan = new QPushButton(this);
    m_pSetting = new QPushButton(this);

    m_pMessage = new QTextBrowser(this);
    m_pSpaceing = new QTextBrowser(this);

    m_pCloseButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pMinimizeButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(74,28);
    QPixmap m_logo = QPixmap(":/image/Logo.svg");

    //QIcon icon = QIcon(":/image/Logo.svg");
    m_pIconLabel->setPixmap(m_logo.scaled(m_pIconLabel->size(),Qt::KeepAspectRatio));

    QPalette pal(m_pMessage->palette());
    pal.setColor(QPalette::Base, QColor(255,255,255,0));
    m_pMessage->setPalette(pal);
    m_pMessage->setFrameStyle(QFrame::NoFrame);
    m_pMessage->setMinimumWidth(100);

    m_pSpaceing->setPalette(pal);
    m_pSpaceing->setFrameStyle(QFrame::NoFrame);
    m_pSpaceing->setMinimumWidth(100);

    //m_pSpaceLabel->setMinimumWidth(100);

    m_pMinimizeButton->setFixedSize(28,28);
    m_pMinimizeButton->setIconSize(QSize(28,22));
    m_pMinimizeButton->setIcon(QIcon(":/image/mini.svg"));
    m_pMinimizeButton->setFlat(true);
    //m_pMinimizeButton->setAutoFillBackground(true);
        //--
    m_pMaximizeButton->setFixedSize(28,28);
    m_pMaximizeButton->setIconSize(QSize(28,22));
    m_pMaximizeButton->setIcon(QIcon(":/image/mini-max.svg"));
    m_pMaximizeButton->setFlat(true);
        //--
    m_pCloseButton->setFixedSize(28,28);
    m_pCloseButton->setIconSize(QSize(28,22));
    m_pCloseButton->setIcon(QIcon(":/image/XDelete.svg"));
    m_pCloseButton->setFlat(true);

    //m_pMessage->set

    m_pFly->setFixedSize(28,28);
    m_pFly->setIconSize(QSize(28,22));
    m_pFly->setIcon(QIcon(":/image/PaperPlane.svg"));
    m_pFly->setFlat(true);

    m_pPlan->setFixedSize(28,28);
    m_pPlan->setIconSize(QSize(28,22));
    m_pPlan->setIcon(QIcon(":/image/Plan.svg"));
    m_pPlan->setFlat(true);

    m_pSetting->setFixedSize(28,28);
    m_pSetting->setIconSize(QSize(28,22));
    m_pSetting->setIcon(QIcon(":/image/Gears.svg"));
    m_pSetting->setFlat(true);

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    QHBoxLayout *leftLayout = new QHBoxLayout();
    QHBoxLayout *rightLayout = new QHBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    leftLayout->addWidget(m_pFly);
    leftLayout->addWidget(m_pPlan);
    leftLayout->addWidget(m_pSetting);
    //pLayout->addSpacing(5);
    //pLayout->addWidget(m_pIconLabel);
    //pLayout->addWidget(m_pMessage);

    rightLayout->addWidget(m_pMinimizeButton);
    rightLayout->addWidget(m_pMaximizeButton);
    rightLayout->addWidget(m_pCloseButton);

    mainLayout->addLayout(leftLayout);
    //mainLayout->addStretch();
    mainLayout->addWidget(m_pSpaceing);
    mainLayout->addWidget(m_pIconLabel, Qt::AlignHCenter);
    mainLayout->addWidget(m_pMessage);
    mainLayout->addLayout(rightLayout);


    //pLayout->addSpacing(0);
    mainLayout->setContentsMargins(5, 0, 5, 0);
    setLayout(mainLayout);

    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

void skyroverTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaximizeButton->clicked();
}

void skyroverTitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}

bool skyroverTitleBar::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Resize:
        updateMaximize();
        return true;

    default:
        return QWidget::eventFilter(watched, event);

    }

}

void skyroverTitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());

    QWidget *pWindow = this->window();

    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void skyroverTitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();

    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();

        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pMaximizeButton->setToolTip(tr("Maximize"));
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
        }
        //m_pMaximizeButton->setStyle(QApplication::style());
    }
}

skyroverTitleBar::~skyroverTitleBar()
{

}
