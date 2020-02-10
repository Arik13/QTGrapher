#ifndef FUNCTIONLISTWIDGET_H
#define FUNCTIONLISTWIDGET_H

#include <QObject>
#include <QListView>
#include <QStringListModel>
#include <iostream>
#include <QKeyEvent>

/*
 * A Qt Widget that shows a list of mathematical functions as strings
 */
class FunctionListWidget : public QListView {
public:
    FunctionListWidget(QWidget *parent) : QListView(parent) {
        setSelectionMode(QAbstractItemView::SingleSelection);
    }
    void keyPressEvent(QKeyEvent *event) override;
private:
    QStringListModel *functionListModel;
};

#endif // FUNCTIONLISTWIDGET_H
