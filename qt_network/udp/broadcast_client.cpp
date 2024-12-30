#include "broadcast_client.h"
#include <qobject.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QVBoxLayout>

using namespace eg_network;

BroadcastClient::BroadcastClient() {
    sender_ = new QUdpSocket(this);
    initUi();
    signalConnect();
}

void BroadcastClient::initUi() {
    setMinimumSize(300, 120);

    auto* input_h_layout = new QHBoxLayout;
    content_input_ = new QLineEdit;
    broadcast_btn_ = new QPushButton;
    broadcast_btn_->setText("Broadcast");
    input_h_layout->addWidget(content_input_);
    input_h_layout->addWidget(broadcast_btn_);

    auto* main_layout = new QVBoxLayout;
    main_layout->addLayout(input_h_layout);

    setLayout(main_layout);
}

void BroadcastClient::signalConnect() {
    connect(broadcast_btn_, &QPushButton::clicked, this,
            [this]()
            {
                QString broadcast_content = content_input_->text();
                QByteArray send_data = broadcast_content.toLocal8Bit();
                sender_->writeDatagram(send_data.data(), send_data.size(), QHostAddress::Broadcast, 7777);
            });
}
