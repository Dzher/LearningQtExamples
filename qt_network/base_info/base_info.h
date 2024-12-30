#include <QTextBrowser>
#include <QWidget>

namespace eg_network
{
class BaseInfoWidget : public QWidget
{
public:
    BaseInfoWidget();
    void getInfosByHostName(const QString& host_name);

private:
    void initUi();
    void getLocalHostInfos();

private:
    QTextBrowser* text_browser_ = nullptr;
};
}  // namespace eg_network