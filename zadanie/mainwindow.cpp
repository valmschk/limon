#include "mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QMenu>
#include <QInputDialog>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    tableWidget->setColumnCount(4);
    tableWidget->setHorizontalHeaderLabels(
        {"Название", "Путь", "Размер (КБ)", "Изображение"});

    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget, &QListWidget::customContextMenuRequested,
            this, &MainWindow::onListContextMenu);

    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_comboBox_currentIndexChanged);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    keyLabel->setText(
        QString("Нажата клавиша: %1").arg(event->text()));
    QMainWindow::keyPressEvent(event);
}

void MainWindow::on_loadSizeButton_clicked()
{
    bool ok;
    int size = sizeInput->text().toInt(&ok);
    if (ok) {
        keyLabel->setText(
            QString("Размер массива: %1").arg(size));
        return;
    }

    QString fname = QFileDialog::getOpenFileName(
        this, "Файл со списком", {}, "Text Files (*.txt)");
    if (fname.isEmpty()) return;

    QFile f(fname);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&f);
    while (!in.atEnd()) {
        QString path = in.readLine().trimmed();
        if (!path.isEmpty()) addFile(path);
    }
    f.close();

    updateList();
    updateTable();
}

void MainWindow::on_addButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this, "Выберите файлы", {},
        "Images (*.png *.jpg *.bmp);;All Files (*)");
    for (const auto &f : files) addFile(f);
    updateList();
    updateTable();
}

void MainWindow::on_removeButton_clicked()
{
    removeSelectedItems();
    updateList();
    updateTable();
}

void MainWindow::addFile(const QString &filePath)
{
    QFileInfo fi(filePath);
    if (!fi.exists()) return;

    FileInfo info;
    info.name   = fi.fileName();
    info.path   = fi.absoluteFilePath();
    info.sizeKb = fi.size() / 1024.0;
    info.icon   = QIcon(info.path);

    for (const auto &e : fileList)
        if (e.path == info.path)
            return;

    fileList.append(info);
}

void MainWindow::removeSelectedItems()
{
    for (auto *it : listWidget->selectedItems()) {
        QString nm = it->text();
        for (int i = 0; i < fileList.size(); ++i) {
            if (fileList[i].name == nm) {
                fileList.removeAt(i);
                break;
            }
        }
    }
}

void MainWindow::updateList()
{
    listWidget->clear();
    for (const auto &f : fileList) {
        listWidget->addItem(new QListWidgetItem(f.icon, f.name));
    }
}

void MainWindow::updateTable()
{
    tableWidget->setRowCount(fileList.size());
    for (int i = 0; i < fileList.size(); ++i) {
        const auto &f = fileList[i];
        tableWidget->setItem(i, 0, new QTableWidgetItem(f.name));
        tableWidget->setItem(i, 1, new QTableWidgetItem(f.path));
        tableWidget->setItem(i, 2,
                             new QTableWidgetItem(QString::number(f.sizeKb, 'f', 2)));
        auto *iconItem = new QTableWidgetItem;
        iconItem->setIcon(f.icon);
        tableWidget->setItem(i, 3, iconItem);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        std::sort(fileList.begin(), fileList.end(),
                  [](auto &a, auto &b){ return a.name < b.name; });
    } else {
        std::sort(fileList.begin(), fileList.end(),
                  [](auto &a, auto &b){ return a.name > b.name; });
    }
    updateList();
    updateTable();
}

void MainWindow::onListContextMenu(const QPoint &pos)
{
    QPoint gp = listWidget->mapToGlobal(pos);
    QMenu menu;
    menu.addAction("Удалить", this, [&](){
        removeSelectedItems();
        updateList();
        updateTable();
    });
    menu.exec(gp);
}

void MainWindow::on_sortButton_clicked()
{
    bool ok;
    int N = QInputDialog::getInt(
        this,
        "Размерность массива",
        "Введите N:",
        fileList.size(), 1, fileList.size(), 1, &ok
        );
    if (!ok) return;
for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            if (fileList[j].name < fileList[j+1].name) {
                std::swap(fileList[j], fileList[j+1]);
            }
        }
    }

    updateList();
    updateTable();
}
