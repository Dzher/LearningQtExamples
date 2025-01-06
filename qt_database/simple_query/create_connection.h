#include <qsqldatabase.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtWidgets/QMessageBox>

namespace eg_sql
{

inline QString getDatabaseName() {
    return "MyFirstDb";
}

inline QString getConnectionName() {
    return "FirstConnection";
}

inline QSqlDatabase getDatabase() {
    return QSqlDatabase::database(getConnectionName());
}

inline bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", getConnectionName());
    db.setDatabaseName("MyFirstDb");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot Open Database", "Unable to establisha database connection.",
                              QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query(db);
    query.exec("create table student(id int primary key, name varchar)");

    query.exec("insert into student values(1, 'xiaopeng')");
    query.exec("insert into student values(2, 'xiaomi')");
    query.exec("insert into student values(3, 'xiaoai')");
    query.exec("insert into student values(4, 'xiaokang')");
    query.exec("insert into student values(5, 'xiaoxin')");

    return true;
}
}  // namespace eg_sql