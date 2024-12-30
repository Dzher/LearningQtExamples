#include "broadcast_server.h"
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

BroadcastServer::BroadcastServer() {
    receiver_ = new QUdpSocket(this);
    receiver_->bind(7777, QUdpSocket::ShareAddress);

    initUi();
    signalConnect();
}

void BroadcastServer::initUi() {
    setMinimumSize(300, 220);

    content_label_ = new QLabel("Wait for broadcast data...");

    auto* main_layout = new QVBoxLayout;
    main_layout->addWidget(content_label_);

    setLayout(main_layout);
}

void BroadcastServer::signalConnect() {
    connect(receiver_, &QUdpSocket::readyRead, this,
            [this]()
            {
                while (receiver_->hasPendingDatagrams()) {
                    QByteArray received_data;
                    received_data.resize(int(receiver_->pendingDatagramSize()));
                    receiver_->readDatagram(received_data.data(), received_data.size());
                    content_label_->setText(received_data);
                }
            });
}
