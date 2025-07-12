#include "lgwidget.h"
#include<QMovie>
#include<QTimer>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPalette>
#include<QResizeEvent>
LWidget::LWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    QPixmap bkgnd(":/resources/resources/hand-drawn-zoo-map-illustration_23-2149424705.jpg");
       bkgnd=bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
   QPalette p=palette();
    p.setBrush(QPalette::Window,bkgnd);
    setPalette(p);
    setAutoFillBackground(true);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    layout->addWidget(progressBar,0, Qt::AlignCenter);
    setLayout(layout);
 timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LWidget::updateProgress);
    timer->start(50);
}

void LWidget::resizeEvent(QResizeEvent *event)
{
    QPixmap bkgnd(":/resources/resources/hand-drawn-zoo-map-illustration_23-2149424705.jpg");
    bkgnd = bkgnd.scaled(event->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);

    QWidget::resizeEvent(event);
}
void LWidget::updateProgress() {
    int currentValue = progressBar->value();
    if (currentValue < 100) {
        progressBar->setValue(currentValue + 1);
    }
}
void LWidget::setProgressBarSize(int width, int height)
{
    progressBar->setFixedSize(width, height);
}
