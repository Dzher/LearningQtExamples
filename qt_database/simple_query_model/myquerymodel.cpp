#include "myquerymodel.h"
#include <qnamespace.h>
#include <qobject.h>
#include <qsqlquerymodel.h>
#include "connection.h"

using namespace eg_sql;

MyQueryModel::MyQueryModel(QObject* parent) : QSqlQueryModel(parent) {
}

Qt::ItemFlags MyQueryModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    return flags.setFlag(Qt::ItemFlag::ItemIsEditable, index.column() != 0);
}

QVariant MyQueryModel::data(const QModelIndex& item, int role) const {
    if (item.column() == 0 && role == Qt::ForegroundRole) {
        return QVariant::fromValue(QColor{Qt::red});
    }
    return QSqlQueryModel::data(item, role);
}

bool MyQueryModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    QModelIndex id_index = QSqlQueryModel::index(index.row(), 0);
    int id = data(id_index, Qt::EditRole).toInt();

    clear();

    bool ok = false;
    if (index.column() == 1) {
        ok = setName(id, value.toString());
    }
    refresh();
    return ok;
}

void MyQueryModel::refresh() {
    setQuery("select * from student", getDatabase());
    setHeaderData(0, Qt::Orientation::Horizontal, "id");
    setHeaderData(1, Qt::Orientation::Horizontal, "name");
}

bool MyQueryModel::setName(int id, const QString& name) {
    QSqlQuery query(getDatabase());
    query.prepare("update student set name = ? where id = ?");
    query.addBindValue(name);
    query.addBindValue(id);
    return query.exec();
}