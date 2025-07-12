#include "mainwindow.h"
#include "lgwidget.h"
#include <QApplication>
#include <QThread>
#include <QTimer>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    LWidget loadingWidget;  // Теперь в стеке
    loadingWidget.setProgressBarSize(1000, 25);
    loadingWidget.showFullScreen();

    QTimer::singleShot(4000, [&] {
        loadingWidget.hide();
        w.show();
    });

    return a.exec();
}
