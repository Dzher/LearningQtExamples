#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTextBrowser>

namespace eg_network
{
class SimplyWebBrowser : public QMainWindow
{
public:
    SimplyWebBrowser();
    void get(const QString& url = "http://www.qter.org");

private:
    void initUi();
    void signalConnect();
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager_;
    QTextBrowser* text_browser_;
};
}  // namespace eg_network