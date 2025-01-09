
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableView>

namespace eg_sql
{
class TableModelWidget : public QMainWindow
{
public:
    explicit TableModelWidget(QWidget* parent = nullptr);

private:
    void initUi();
    void initTable();

    void connectSignals() const;
    void onQuery();
    void onShowAll();
    void onCommit();
    void onCancel();
    void onAddRecord();
    void onDeleteRow();
    void onSortInc();
    void onSortDec();

private:
    struct
    {
        QLineEdit* name_input_ = nullptr;
        QPushButton* query_btn_ = nullptr;
        QPushButton* show_all_btn_ = nullptr;
        QPushButton* commit_modified_btn_ = nullptr;
        QPushButton* cancel_modified_btn_ = nullptr;
        QPushButton* add_record_btn_ = nullptr;
        QPushButton* delete_select_row_btn_ = nullptr;
        QPushButton* increase_sort_by_id_btn_ = nullptr;
        QPushButton* decrease_sort_by_id_btn_ = nullptr;
    } ui_;
    QSqlTableModel* table_model_ = nullptr;
    QTableView* view_ = nullptr;
};
}  // namespace eg_sql