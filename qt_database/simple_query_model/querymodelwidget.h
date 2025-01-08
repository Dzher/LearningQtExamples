#include <QMainWindow>
#include <QTableView>
#include "myquerymodel.h"

namespace eg_sql
{
class QueryModelWidget : public QMainWindow
{
public:
    explicit QueryModelWidget(QWidget* parent = nullptr);
    ~QueryModelWidget();

private:
    void initUi();

private:
    MyQueryModel* query_model_ = nullptr;
    QTableView* view_ = nullptr;
};
}  // namespace eg_sql