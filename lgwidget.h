#ifndef LGWIDGET_H
#define LGWIDGET_H
#include <QMainwindow>
#include <QWidget>
#include <QProgressBar>
#include <QLabel>
class LWidget : public QWidget
{
public:
    explicit LWidget(QWidget *parent = nullptr);

signals:
    void updateProgress();
    void setProgressBarSize(int width,int height);
    void  resizeEvent(QResizeEvent *event);
private:
    QProgressBar *progressBar;
    QTimer*timer;
    QMainWindow*w;
};

#endif
