#include "tablemodelwidget.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include <qsqltablemodel.h>
#include <qtableview.h>
#include <qwidget.h>
#include "connection.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>

using namespace eg_sql;

TableModelWidget::TableModelWidget(QWidget* parent) : QMainWindow(parent) {
    initTable();
    initUi();
    connectSignals();
}

void TableModelWidget::initUi() {
    setMinimumSize(400, 300);

    auto* up_main_layout = new QHBoxLayout;

    view_ = new QTableView;
    view_->setModel(table_model_);
    view_->hideColumn(0);
    view_->setWindowTitle("Grade3 Class1 Students Table");
    view_->show();

    auto* up_func_btns_layout = new QVBoxLayout;
    ui_.show_all_btn_ = new QPushButton("Show All Table");
    ui_.increase_sort_by_id_btn_ = new QPushButton("Sort Increase By Id");
    ui_.decrease_sort_by_id_btn_ = new QPushButton("Sort Decrease By Id");
    ui_.commit_modified_btn_ = new QPushButton("Commit Modified");
    ui_.cancel_modified_btn_ = new QPushButton("Cancel Modified");
    ui_.add_record_btn_ = new QPushButton("Add Records");
    ui_.delete_select_row_btn_ = new QPushButton("Delete Selected Row");
    up_func_btns_layout->addWidget(ui_.show_all_btn_);
    up_func_btns_layout->addWidget(ui_.increase_sort_by_id_btn_);
    up_func_btns_layout->addWidget(ui_.decrease_sort_by_id_btn_);
    up_func_btns_layout->addWidget(ui_.commit_modified_btn_);
    up_func_btns_layout->addWidget(ui_.cancel_modified_btn_);
    up_func_btns_layout->addWidget(ui_.add_record_btn_);
    up_func_btns_layout->addWidget(ui_.delete_select_row_btn_);

    up_main_layout->addWidget(view_);
    up_main_layout->addLayout(up_func_btns_layout);

    auto* name_input_h_layout = new QHBoxLayout;
    auto* name_lbl = new QLabel("Input Name");
    ui_.name_input_ = new QLineEdit;
    ui_.query_btn_ = new QPushButton("Query");
    name_input_h_layout->addWidget(name_lbl);
    name_input_h_layout->addWidget(ui_.name_input_);
    name_input_h_layout->addWidget(ui_.query_btn_);

    auto* main_widget = new QWidget;
    auto* main_layout = new QVBoxLayout;
    main_layout->addLayout(up_main_layout);
    main_layout->addLayout(name_input_h_layout);
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);
}

void TableModelWidget::initTable() {
    table_model_ = new QSqlTableModel(this, getDatabase());  //!Attention give the database obj!
    table_model_->setTable("student");
    // table_model_->setHeaderData(0, Qt::Horizontal, tr("Id"));
    table_model_->setHeaderData(1, Qt::Horizontal, tr("Name"));
    table_model_->setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);
    table_model_->select();
}

void TableModelWidget::connectSignals() const {
    connect(ui_.query_btn_, &QPushButton::clicked, this, &TableModelWidget::onQuery);
    connect(ui_.show_all_btn_, &QPushButton::clicked, this, &TableModelWidget::onShowAll);
    connect(ui_.commit_modified_btn_, &QPushButton::clicked, this, &TableModelWidget::onCommit);
    connect(ui_.cancel_modified_btn_, &QPushButton::clicked, this, &TableModelWidget::onCancel);
    connect(ui_.add_record_btn_, &QPushButton::clicked, this, &TableModelWidget::onAddRecord);
    connect(ui_.delete_select_row_btn_, &QPushButton::clicked, this, &TableModelWidget::onDeleteRow);
    connect(ui_.increase_sort_by_id_btn_, &QPushButton::clicked, this, &TableModelWidget::onSortInc);
    connect(ui_.decrease_sort_by_id_btn_, &QPushButton::clicked, this, &TableModelWidget::onSortDec);
}

void TableModelWidget::onQuery() {
    QString input_name = ui_.name_input_->text();
    table_model_->setFilter(QString("name = %1").arg(input_name));
    table_model_->select();
}

void TableModelWidget::onShowAll() {
    table_model_->setTable("student");
    table_model_->select();
}

void TableModelWidget::onCommit() {
    table_model_->database().transaction();
    if (table_model_->submitAll()) {
        table_model_->database().commit();
    }
    else {
        table_model_->database().rollback();
        QMessageBox::warning(this, "Commit Failed", table_model_->lastError().text());
    }
}

void TableModelWidget::onCancel() {
    table_model_->revertAll();
}

void TableModelWidget::onAddRecord() {
    int row_count = table_model_->rowCount();
    int id = 10;
    table_model_->insertRow(row_count);
    table_model_->setData(table_model_->index(row_count, 0), id);
    //model->submitAll(); // or just use this
}

void TableModelWidget::onDeleteRow() {
    int current_row = view_->currentIndex().row();

    table_model_->removeRow(current_row);

    int ok = QMessageBox::warning(this, tr("Delete Current Row?!"),
                                  tr("Are you sure"
                                     "Delete Current Row?"),
                                  QMessageBox::Yes, QMessageBox::No);
    if (ok == QMessageBox::No) {
        table_model_->revertAll();
    }
    else {
        table_model_->submitAll();
    }
}

void TableModelWidget::onSortInc() {
    table_model_->setSort(0, Qt::SortOrder::AscendingOrder);
    table_model_->select();
}

void TableModelWidget::onSortDec() {
    table_model_->setSort(0, Qt::SortOrder::DescendingOrder);
    table_model_->select();
}