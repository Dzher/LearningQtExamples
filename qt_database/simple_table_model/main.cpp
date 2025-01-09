#include <QApplication>
#include "connection.h"
#include "tablemodelwidget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if (!eg_sql::createConnection()) {
        return -1;
    }

    auto widget = eg_sql::TableModelWidget();
    widget.show();

    return QApplication::exec();
}