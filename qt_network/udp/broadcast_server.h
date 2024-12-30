#include <QLabel>
#include <QPushButton>
#include <QUdpSocket>
#include <QWidget>

namespace eg_network
{
class BroadcastServer : public QWidget
{
public:
    BroadcastServer();

private:
    void initUi();
    void signalConnect();
    void processPendingDatagram();

private:
    QUdpSocket* receiver_;
    QLabel* content_label_ = nullptr;
    QPushButton* broadcast_btn_ = nullptr;
};
}  // namespace eg_network