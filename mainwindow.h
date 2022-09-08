#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <list>
#include "discobject.h"
#include "filediscobject.h"
#include "pathdiscobject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void init_treewidget();
    void show_path(QTreeWidgetItem *pTWItem, DiscObject *pathDisc);

    PathDiscObject *pathDisc = nullptr;
};
#endif // MAINWINDOW_H
