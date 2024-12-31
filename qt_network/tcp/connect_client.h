#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QWidget>

namespace eg_network
{
class ConnectClient : public QWidget
{
public:
    ConnectClient();

private:
    void initUi();
    void signalConnect();

private:
    QTcpSocket* connecter_;
    QLineEdit* host_input_ = nullptr;
    QLineEdit* port_input_ = nullptr;
    QPushButton* connect_btn_ = nullptr;
    QLabel* content_label_ = nullptr;
    int data_block_size_;
};
}  // namespace eg_network