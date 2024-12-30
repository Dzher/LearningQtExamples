#include <qtcpserver.h>
#include <QLabel>
#include <QPushButton>
#include <QTcpServer>
#include <QWidget>

namespace eg_network
{
class ConnectServer : public QWidget
{
public:
    ConnectServer();

private:
    void initUi();
    void signalConnect();
    void processPendingDatagram();

private:
    QTcpServer* tcp_server_;
    QLabel* content_label_ = nullptr;
    QPushButton* connect_btn_ = nullptr;
};
}  // namespace eg_network