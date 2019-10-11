#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QQuickWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    ~MainWindow();

protected:
    //void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    //void showEvent(QShowEvent* event);

private:
    Ui::MainWindow *ui;

    QVBoxLayout*            _centralLayout;
    int m_nBorderWidth = 5;
    bool m_bPressed;
    QPoint pLast;
    int m_curPos;
    int titleHeight;

    void setCursorShape(int flag);
    int setCurFlag(QPoint p);


};

#endif // MAINWINDOW_H
