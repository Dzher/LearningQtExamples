#include "connect_server.h"
#include <QHBoxLayout>
#include <QHostAddress>
#include <QTcpSocket>
#include <QVBoxLayout>

using namespace eg_network;

ConnectServer::ConnectServer() {
    tcp_server_ = new QTcpServer(this);
    if (!tcp_server_->listen(QHostAddress::LocalHost, 6666)) {
        qDebug() << "Error: " << tcp_server_->errorString();
        close();
    }

    initUi();
    signalConnect();
}

void ConnectServer::initUi() {
    setMinimumSize(300, 220);

    content_label_ = new QLabel("Wait for connect...");

    auto* main_layout = new QVBoxLayout;
    main_layout->addWidget(content_label_);

    setLayout(main_layout);
}

void ConnectServer::signalConnect() {
    connect(tcp_server_, &QTcpServer::newConnection, this,
            [this]()
            {
                QByteArray data_block;
                QDataStream out(&data_block, QIODevice::WriteOnly);

                out.setVersion(QDataStream::Qt_5_13);

                out << quint16(0);
                out << QString{"Hello New Connection!!!"}; //Must use QString, just "" will cause garbled issue.
                out.device()->seek(0);
                out << quint16(data_block.size() - sizeof(quint16));

                QTcpSocket* client_connection = tcp_server_->nextPendingConnection();

                connect(client_connection, &QTcpSocket::disconnected, client_connection, &QTcpSocket::deleteLater);
                client_connection->write(data_block);
                client_connection->disconnectFromHost();

                content_label_->setText("send message successful!!!");
            });
}
