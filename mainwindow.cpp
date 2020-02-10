#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlineedit.h>
#include "graphwidget.h"
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->functionListView->setModel(&functionList);
    connect(ui->functionEdit, &QLineEdit::returnPressed, this, &MainWindow::addFunction);
    connect(&functionList, &QAbstractItemModel::rowsRemoved, this, &MainWindow::deleteFunction);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addFunction() {
    std::string fs = ui->functionEdit->text().toStdString();
    try {
        ui->openGLWidget->addFunction(fs);
        QString qfs = QString::fromUtf8(fs.data(), fs.size());
        functionList.insertRow(functionList.rowCount());
        QModelIndex index = functionList.index(functionList.rowCount() - 1, 0);
        functionList.setData(index, qfs);
    } catch (std::string ex) {
        std::cout << ex << "\n";
        QMessageBox messageBox(QMessageBox::Warning, QString("Error"), QString::fromUtf8(ex.c_str()));
        messageBox.exec();
        return;
    }

    ui->functionEdit->clear();

}

void MainWindow::deleteFunction(const QModelIndex &parent, int first, int last) {
    ui->openGLWidget->deleteFunction(first);
}

