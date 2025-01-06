#include <QApplication>
#include "create_connection.h"
#include "query_widget.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if (!eg_sql::createConnection()) {
        return -1;
    }

    auto widget = eg_sql::QueryWidget();
    widget.show();

    return QApplication::exec();
}