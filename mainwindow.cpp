#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabBar>
#include <QTimer>
#include <QTimeEdit>
#include <QFrame>
#include <QMouseEvent>
#include <QLabel>
#include "styl.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tabWidget, &MainWindow::customContextMenuRequested, [&](const QPoint& pos) {
        static QMenu* menu = nullptr;

        if (!menu) {
            menu = new QMenu();
            this->restartTimerAction = new QAction("Запустить счетчик ", this);
            this->stopTimerAction = new QAction("Остановить счетчик", this);

            menu->addAction(restartTimerAction);
            menu->addAction(stopTimerAction);

            connect(restartTimerAction, &QAction::triggered, this, &MainWindow::restartTimer);
            connect(stopTimerAction, &QAction::triggered, this, &MainWindow::stopTimer);
        }
        menu->popup(mapToGlobal(pos));
    });

    timer = new QTimer(ui->widget);
    timer->start(20);

    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    setInterfaceStyle();
    this->current_picture = "";
    this->difficulte = "";

    timeEdit = new QTimeEdit();
    timeEdit->setDisplayFormat("hh:mm:ss");
    timeEdit->setTime(QTime(0, 0, 0));
    timeEdit->setReadOnly(true);
    connect(timer, &QTimer::timeout, this, [=]() {
        QTime currentTime = timeEdit->time().addSecs(1);
        timeEdit->setTime(currentTime);
    });
    ui->layout->addWidget(timeEdit);
    this->timeEdit->hide();

    this->isOnSecondClick = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        close();
    }
}

void MainWindow::setInterfaceStyle()
{
    ui->centralwidget->setStyleSheet(Styl::getStartWindowStyle());
    ui->pushButton_2->setStyleSheet(Styl::getStartButtonsStyle());
    ui->pushButton->setStyleSheet(Styl::getStartButtonsStyle());
    ui->pushButton_12->setStyleSheet(Styl::getStartButtonsStyle());
    ui->pushButton_7->setStyleSheet(Styl::getStartButtonsStyle());
    ui->pushButton_4->setStyleSheet(Styl::getStartButtonsStyle());
}

void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
    this->current_picture = "";
    this->difficulte = "";
}

void MainWindow::on_pushButton_4_clicked()
{
    if(this->current_picture == "" || this->difficulte == ""){
        return;
    }
    else{
        if(this->field != nullptr){
            ui->gridLayout_4->removeWidget(this->field);
        }
        this->timeEdit->show();

        this->ui->tabWidget->setCurrentIndex(0);
        this->field = new PuzzleWindow(this->current_picture);
        this->ui->gridLayout_4->addWidget(this->field);

        timeEdit->setTime(QTime(0, 0, 0));
        timer->setInterval(1000);
        timer->start();
        this->timer = timer;
        isOnSecondPage = false;
        this->isOnSecondClick = true;
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    if (this->isOnSecondClick)
    {
        if (!isOnSecondPage)
        {
            this->timer->stop();
            QString result = timeEdit->time().toString("hh:mm:ss");
            ui->listWidget->addItem(result);
            ui->tabWidget->setCurrentIndex(1);
        }
        else
        {
            ui->tabWidget->setCurrentIndex(0);
            this->timer->start();
        }
        isOnSecondPage = !isOnSecondPage;
    }
}

void MainWindow::restartTimer()
{
    timer->stop();
    QTimeEdit* timeEdit = new QTimeEdit();
    timeEdit->setTime(QTime(0, 0, 0));
    timer->start();
}

void MainWindow::stopTimer()
{
    timer->stop();
}

void MainWindow::MakePuzzle()
{
    ui->tabWidget->setCurrentIndex(0);
    return;
}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->quit();
}

void MainWindow::on_label_19_mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QLabel* clickedLabel = qobject_cast<QLabel*>(sender());
        if(clickedLabel) {
            QPixmap image = clickedLabel->pixmap(Qt::ReturnByValue);
            if (!image.isNull()) {
                QFrame* frame = new QFrame;
                QHBoxLayout* layout = new QHBoxLayout;
                QLabel* imageLabel = new QLabel;
                imageLabel->setPixmap(image);
                layout->addWidget(imageLabel);
                frame->setLayout(layout);
            }
        }
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    this->difficulte = "medium";
}

void MainWindow::on_pushButton_3_clicked()
{
    this->current_picture = "barb";
}

void MainWindow::on_pushButton_8_clicked()
{
    this->current_picture = "bird";
}

void MainWindow::on_pushButton_9_clicked()
{
    this->current_picture = "rap";
}

void MainWindow::on_pushButton_10_clicked()
{
    this->current_picture = "zebra";
}

void MainWindow::on_pushButton_11_clicked()
{
    this->current_picture = "nusha";
}




