#include "connect_server.h"
#include <qhostaddress.h>
#include <qlabel.h>
#include <qobject.h>
#include <qudpsocket.h>
#include <QHBoxLayout>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
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

    content_label_ = new QLabel("Wait for broadcast data...");

    auto* main_layout = new QVBoxLayout;
    main_layout->addWidget(content_label_);

    setLayout(main_layout);
}

void ConnectServer::signalConnect() {
    connect(tcp_server_, &QTcpServer::newConnection, this,
            [this]()
            {
                
            });
}
