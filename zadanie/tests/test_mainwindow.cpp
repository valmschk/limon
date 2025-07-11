#include "test_mainwindow.h"
#include <QtTest>
#include <QApplication>
#include <QTemporaryFile>
#include <QListWidgetItem>

static QApplication *app = nullptr;
static MainWindow    *mw  = nullptr;

void TestMainWindow::initTestCase()
{
    int argc = 0;
    app = new QApplication(argc, nullptr);
    mw  = new MainWindow();
}

void TestMainWindow::cleanupTestCase()
{
     delete mw;
    mw = nullptr;
}

void TestMainWindow::testAddFile_data()
{
    QTest::addColumn<QString>("path");
    QTest::addColumn<bool>("exists");

    QTemporaryFile tmp;
    tmp.setAutoRemove(false);
    QVERIFY(tmp.open());
    QString realPath = tmp.fileName();
    tmp.close();

    QTest::newRow("real") << realPath << true;
    QTest::newRow("fake") << QString("/no/such/file") << false;
}

void TestMainWindow::testAddFile()
{
    QFETCH(QString, path);
    QFETCH(bool, exists);

    int before = mw->fileList.size();
    mw->addFile(path);
    int after  = mw->fileList.size();

    if (exists) {
        QCOMPARE(after, before + 1);
        QCOMPARE(mw->fileList.last().path, path);
    } else {
        QCOMPARE(after, before);
    }
}

void TestMainWindow::testRemoveSelected_data()
{
    QTest::addColumn<int>("n");
    QTest::newRow("three") << 3;
}

void TestMainWindow::testRemoveSelected()
{
    QFETCH(int, n);

    mw->fileList.clear();
    for (int i = 0; i < n; ++i) {
        FileInfo fi;
        fi.name   = QString("f%1.txt").arg(i);
        fi.path   = "";
        fi.sizeKb = 0;
        fi.icon   = QIcon();
        mw->fileList.append(fi);
    }
    mw->updateList();
    QCOMPARE(mw->listWidget->count(), n);

    mw->listWidget->item(1)->setSelected(true);
    mw->removeSelectedItems();
    mw->updateList();

    QCOMPARE(mw->fileList.size(), n - 1);
}

void TestMainWindow::testSortComboBox()
{
    mw->fileList.clear();
    for (auto name : {"c","a","b"}) {
        FileInfo fi;
        fi.name   = name;
        fi.path   = "";
        fi.sizeKb = 0;
        fi.icon   = QIcon();
        mw->fileList.append(fi);
    }

    mw->on_comboBox_currentIndexChanged(0);
    QStringList asc;
    for (auto &fi : mw->fileList) asc << fi.name;
    QCOMPARE(asc, (QStringList{"a","b","c"}));

    mw->on_comboBox_currentIndexChanged(1);
    QStringList desc;
    for (auto &fi : mw->fileList) desc << fi.name;
    QCOMPARE(desc, (QStringList{"c","b","a"}));
}

QTEST_MAIN(TestMainWindow)

