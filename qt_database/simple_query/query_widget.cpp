#include "query_widget.h"
#include "connection.h"

#include <QDebug>
#include <QSqlQuery>

using namespace eg_sql;

QueryWidget::QueryWidget(QWidget* parent) : QMainWindow(parent) {
    initUi();
    onSignalConnect();
}

void QueryWidget::initUi() {
    ui_.index_box = new QSpinBox;
    ui_.query_btn = new QPushButton;
    ui_.query_btn->setText("Query");
    setCentralWidget(ui_.query_btn);
}

void QueryWidget::onSignalConnect() const {
    connect(ui_.query_btn, &QPushButton::clicked, this, &QueryWidget::onQuery);
}

void QueryWidget::onQuery() {
    QSqlQuery query(getDatabase());
    query.exec("select * from student");
    while (query.next()) {
        qDebug() << query.value(0).toInt() << query.value(1).toString();
    }
}