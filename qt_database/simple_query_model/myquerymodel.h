#include <qsqlquerymodel.h>
#include <qwidget.h>
#include <QSqlQueryModel>

namespace eg_sql
{
class MyQueryModel : public QSqlQueryModel
{
public:
    explicit MyQueryModel(QObject* parent = nullptr);

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const override;
    [[nodiscard]] QVariant data(const QModelIndex& item, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

private:
    void refresh();
    static bool setName(int id, const QString& name);
};
}  // namespace eg_sql