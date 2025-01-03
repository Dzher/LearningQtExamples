#include <QFile>
#include <QLineEdit>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProgressBar>
#include <QPushButton>

namespace eg_network
{
class SimpleDownloader : public QMainWindow
{
public:
    SimpleDownloader();

private:
    void initUi();
    void signalConnect();
    void onDownload();
    void onDownloadFinished();
    void onHttpReadyRead();
    void onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager* manager_;
    QNetworkReply* reply_ = nullptr;
    QUrl url_;
    QFile* download_file_ = nullptr;
    QLineEdit* url_input_ = nullptr;
    QPushButton* download_btn_ = nullptr;
    QProgressBar* download_progress_ = nullptr;
};
}  // namespace eg_network