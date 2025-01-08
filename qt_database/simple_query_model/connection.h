#include <qsqldatabase.h>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QVariantList>

namespace eg_sql
{

inline QString getDatabaseName() {
    return "MyQueryModelDb.db";
}

inline QString getConnectionName() {
    return "FirstConnection";
}

inline QSqlDatabase getDatabase() {
    return QSqlDatabase::database(getConnectionName());
}

inline bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", getConnectionName());

    bool db_exist = false;
    QString database_name = getDatabaseName();
    if (QFile::exists(database_name)) {
        qDebug() << database_name << "has been already inited...";
        db_exist = true;
    }

    // if not exist, create it
    db.setDatabaseName(database_name);

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Cannot Open Database", "Unable to establish a database connection.",
                              QMessageBox::Cancel);
        return false;
    }

    if (db_exist) {
        return true;
    }

    QSqlQuery query(db);
    query.exec("create table student(id int primary key, name varchar)");
    query.prepare("insert into student values(?, ?)");

    QVariantList ids;
    ids << 1 << 2 << 3 << 4 << 5;
    QVariantList names;
    names << "xiaopeng"
          << "xiaomi"
          << "xiaoai"
          << "xiaokang"
          << "xiaoxin";
    query.addBindValue(ids);
    query.addBindValue(names);

    if (!query.execBatch()) {
        QMessageBox::critical(nullptr, "Cannot Init Database", query.lastError().text(), QMessageBox::Cancel);
        return false;
    }
    return true;
}
}  // namespace eg_sql