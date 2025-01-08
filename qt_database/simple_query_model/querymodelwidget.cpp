#include "querymodelwidget.h"
#include <qtableview.h>
#include "connection.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>

using namespace eg_sql;

QueryModelWidget::QueryModelWidget(QWidget* parent) : QMainWindow(parent) {
    initUi();
}

QueryModelWidget::~QueryModelWidget() {
    delete query_model_;
}

void QueryModelWidget::initUi() {
    setMinimumSize(400, 300);

    query_model_ = new MyQueryModel(this);
    query_model_->setQuery("select * from student", getDatabase());
    query_model_->setHeaderData(0, Qt::Orientation::Horizontal, "id");
    query_model_->setHeaderData(1, Qt::Orientation::Horizontal, "name");

    view_ = new QTableView;
    setCentralWidget(view_);
    view_->setModel(query_model_);
    view_->setWindowTitle("Grade3 Class1 Students Table");
    view_->show();
}
