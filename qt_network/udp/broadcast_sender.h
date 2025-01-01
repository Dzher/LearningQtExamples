#include <QLineEdit>
#include <QPushButton>
#include <QUdpSocket>
#include <QWidget>

namespace eg_network
{
class BroadcastSender : public QWidget
{
public:
    BroadcastSender();

private:
    void initUi();
    void signalConnect();

private:
    QUdpSocket* sender_;
    QLineEdit* content_input_ = nullptr;
    QPushButton* broadcast_btn_ = nullptr;
};
}  // namespace eg_network