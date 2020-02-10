#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*
 * The main window, communicates
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addFunction();
    void deleteFunction(const QModelIndex &parent, int first, int last);

private:
    Ui::MainWindow *ui;
    QStringListModel functionList;
};

#endif // MAINWINDOW_H
