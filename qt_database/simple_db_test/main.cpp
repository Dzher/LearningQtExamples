#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString db_name = "DemoDb";
    db.setDatabaseName(db_name);
    if (!db.open()) {
        qDebug() << "Failed to open the db: " << db_name;
        return -1;
    }

    QSqlQuery query;
    query.exec("create table student(id int primary key, name varchar)");

    query.exec("insert into student values(1, 'xiaopeng')");
    query.exec("insert into student values(2, 'xiaomi')");
    query.exec("insert into student values(3, 'xiaoai')");

    query.exec("select id, name from student where id >= 2");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        qDebug() << "id:" << id << "name:" << name;
    }

    return QCoreApplication::exec();
}