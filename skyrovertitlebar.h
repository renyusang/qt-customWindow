#ifndef SKYROVERTITLEBAR_H
#define SKYROVERTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>

class skyroverTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit skyroverTitleBar(QWidget *parent = nullptr);
    ~skyroverTitleBar();

protected:

    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    //virtual void mousePressEvent(QMouseEvent *event);

    virtual bool eventFilter(QObject *watched, QEvent *event);

signals:

public slots:

private slots:
    void onClicked();


private:
    QLabel *m_pIconLabel;
    //QLabel *m_pSpaceLabel;
    QPushButton *m_pFly;
    QPushButton *m_pPlan;
    QPushButton *m_pSetting;
    QLabel *m_pMessage;
    QLabel *m_pSpaceing;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;

    void updateMaximize();
};

#endif // SKYROVERTITLEBAR_H
