#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QIcon>
#include <QKeyEvent>
#include <QString>
#include "ui_mainwindow.h"

struct FileInfo {
    QString name;
    QString path;
    qreal   sizeKb;
    QIcon   icon;
};

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_loadSizeButton_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void onListContextMenu(const QPoint &pos);

    void on_sortButton_clicked();
private:
    QList<FileInfo> fileList;

    void updateList();
    void updateTable();
    void addFile(const QString &filePath);
    void removeSelectedItems();
};

#endif
