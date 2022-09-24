#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <list>
#include <map>
#include "discobject.h"
#include "filediscobject.h"
#include "pathdiscobject.h"
#include <iterator>
#include <QDebug>

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
    void load_settings();
    void show_path(QTreeWidgetItem *pTWItem, DiscObject *pathDisc);

    PathDiscObject *pathDisc = nullptr;
    std::string str_pathDisc = "C:/Users/pp/Desktop/build-DuplicateFinder-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug";

    int countGroup = 0;
    std::map<string, int> duplicate_files;

    void setGroup(std::list<FileDiscObject> &all_files, std::map<string, int> &dup_files){
        std::list<FileDiscObject>::iterator it1 = all_files.begin();
        std::list<FileDiscObject>::iterator it2 = all_files.begin();
        std::map<string, int>::iterator mit1, mit2;
        while(it1 != all_files.end()){
            //qDebug() << "1: " << ((*it1).getRoot() + "/" + (*it1).getName()).data();
            it2 = it1;
            it2++;            
            while(it2 != all_files.end()){
                //qDebug() << "2: " << ((*it2).getRoot() + "/" + (*it2).getName()).data();
                if((*it1) == (*it2)){
                    mit1 = dup_files.find((*it1).getRoot() + "/" + (*it1).getName());
                    mit2 = dup_files.find((*it2).getRoot() + "/" + (*it2).getName());
                    if ((mit1 == dup_files.end()) && (mit2 == dup_files.end())){
                        dup_files[(*it2).getRoot() + "/" + (*it2).getName()] = ++countGroup;
                        dup_files[(*it1).getRoot() + "/" + (*it1).getName()] = countGroup;
                    } else if(mit1 != dup_files.end())
                        dup_files[(*it2).getRoot() + "/" + (*it2).getName()] = (*mit1).second;
                    else if (mit2 != dup_files.end())
                        dup_files[(*it1).getRoot() + "/" + (*it1).getName()] = (*mit2).second;
                }
                it2++;
            }
            it1++;
        }
    }

};
#endif // MAINWINDOW_H
