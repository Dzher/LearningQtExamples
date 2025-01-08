#include <QApplication>
#include "connection.h"
#include "querymodelwidget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if (!eg_sql::createConnection()) {
        return -1;
    }

    auto widget = eg_sql::QueryModelWidget();
    widget.show();

    return QApplication::exec();
}