#ifndef MYTREEWIGGET_H
#define MYTREEWIGGET_H

#include <QTreeWidget>
#include <QHeaderView>

class MyTreeWigget : public QTreeWidget
{
    Q_OBJECT
public:
    MyTreeWigget(QWidget* parent = 0)
        : QTreeWidget(parent){
        setSortingEnabled(false);
        header()->setSortIndicatorShown(true);
        header()->setSectionsClickable(true);
        header()->
        connect(header(), SIGNAL(sectionClicked(int)), this, SLOT());
    }

public slots:
    void customSortByColumn(int column){
        Qt::SortOrder order = header()->sortIndicatorOrder();
        sortItems(column, order);
    }

};

#endif // MYTREEWIGGET_H
