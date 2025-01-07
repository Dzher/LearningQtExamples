#include "query_widget.h"
#include <qboxlayout.h>
#include <qdebug.h>
#include <qsqlquery.h>
#include <qwidget.h>
#include "connection.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>

using namespace eg_sql;

QueryWidget::QueryWidget(QWidget* parent) : QMainWindow(parent) {
    initUi();
    onSignalConnect();
}

void QueryWidget::initUi() {
    setMinimumWidth(300);
    auto* main_widget = new QWidget;

    auto* query_h_lyt = new QHBoxLayout;
    ui_.index_box = new QSpinBox;
    ui_.query_btn = new QPushButton;
    ui_.query_btn->setText("Query");
    ui_.insert_btn = new QPushButton;
    ui_.insert_btn->setText("Insert");
    ui_.debug_btn = new QPushButton;
    ui_.debug_btn->setText("Debug");
    ui_.debug_btn->setHidden(true);

    query_h_lyt->addWidget(ui_.index_box);
    query_h_lyt->addWidget(ui_.query_btn);
    query_h_lyt->addWidget(ui_.insert_btn);
    query_h_lyt->addWidget(ui_.debug_btn);

    main_widget->setLayout(query_h_lyt);

    setCentralWidget(main_widget);
}

void QueryWidget::onSignalConnect() const {
    connect(ui_.query_btn, &QPushButton::clicked, this, &QueryWidget::onQuery);
    connect(ui_.insert_btn, &QPushButton::clicked, this, &QueryWidget::onInsert);
    connect(ui_.debug_btn, &QPushButton::clicked, this, &QueryWidget::onDebug);
}

void QueryWidget::onDebug() {
    QSqlQuery query(getDatabase());
    query.exec("select * from student");
    while (query.next()) {
        // method 1: remember the index of each col
        qDebug() << query.value(0).toInt() << query.value(1).toString();

        // method 2: remember the keyword of each col
        int id_index = query.record().indexOf("id");
        int name_index = query.record().indexOf("name");
        qDebug() << query.value(id_index).toInt() << query.value(name_index).toString();

        // method 3: just use keyword
        int query_row = query.at();
        int count = query.record().count();
        int id = query.record().value("id").toInt();
        QString name = query.record().value("name").toString();

        qDebug() << "Result at row" << query_row << "has" << count << "records"
                 << "id" << id << "name" << name;
    }
}

void QueryWidget::onQuery() const {
    int id = ui_.index_box->value();
    QSqlQuery query(getDatabase());

    // method 1: use QString arg
    // QString val = "name";
    // query.exec(QString("select %1 from student where id = %2").arg(val).arg(id));

    // method 2: use Orcale Style
    query.prepare("select name from student where id = ?");
    query.addBindValue(id);
    query.exec();

    while (query.next()) {
        // !Attention here, index cannot be 1, because of record count = 1
        qDebug() << query.value(0).toString();
        // qDebug() << query.value("name").toString();
    }
}

void QueryWidget::onInsert() const {
    QSqlQuery query(getDatabase());

    int new_id = ui_.index_box->value();
    QString new_val = "xiaobie";
    // method 1: use QString arg
    // query.exec(QString("insert into student values(%1, '%2')").arg(new_id).arg(new_val + QString::number(new_id)));
    // new_id++;

    // method 2: use ODBC style placeholder, with bindValue index
    // query.prepare("insert into student (id, name) values (:id, :name)");
    // query.bindValue(0, new_id);
    // query.bindValue(1, new_val + QString::number(new_id));
    // query.exec();
    // new_id++;

    // method 3: use ODBC style placeholder, with bindValue keyword
    // query.prepare("insert into student (id, name) values (:id, :name)");
    // query.bindValue(":id", new_id);
    // query.bindValue(":name", new_val + QString::number(new_id));
    // query.exec();
    // new_id++;

    // method 4: use ODBC style placeholder, with addBindValue
    // query.prepare("insert into student (id, name) values (:id, :name)");
    // query.addBindValue(new_id);
    // query.addBindValue(new_val + QString::number(new_id));
    // query.exec();

    // method 5: use Orcale style placeholder, with addBindValue
    // query.prepare("insert into student (id, name) values (?, ?)");
    query.prepare("insert into student values (?, ?)");
    query.addBindValue(new_id);
    query.addBindValue(new_val + QString::number(new_id));
    query.exec();
}
