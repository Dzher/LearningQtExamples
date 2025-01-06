#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>

namespace eg_sql
{
class QueryWidget : public QMainWindow
{
public:
    explicit QueryWidget(QWidget* parent = nullptr);

private:
    void initUi();
    void onSignalConnect() const;
    void onQuery();

private:
    struct
    {
        QPushButton* query_btn = nullptr;
        QSpinBox* index_box = nullptr;
    } ui_;
};
}  // namespace eg_sql