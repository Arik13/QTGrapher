#include "functionlistwidget.h"

// Deletes the selected function string from the model
void FunctionListWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete) {
        auto selectionModel = this->selectionModel()->selectedIndexes();
        int selectionIndex = selectionModel.first().row();
        this->model()->removeRow(selectionIndex);
    }
}
