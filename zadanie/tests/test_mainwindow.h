#ifndef TEST_MAINWINDOW_H
#define TEST_MAINWINDOW_H

#include <QObject>

#define private public
#include "../mainwindow.h"
#undef private

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testAddFile_data();
    void testAddFile();

    void testRemoveSelected_data();
    void testRemoveSelected();

    void testSortComboBox();
};

#endif
