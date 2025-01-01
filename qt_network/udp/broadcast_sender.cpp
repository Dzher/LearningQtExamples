#include "broadcast_sender.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace eg_network;

BroadcastSender::BroadcastSender() {
    sender_ = new QUdpSocket(this);
    initUi();
    signalConnect();
}

void BroadcastSender::initUi() {
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

void BroadcastSender::signalConnect() {
    connect(broadcast_btn_, &QPushButton::clicked, this,
            [this]()
            {
                QString broadcast_content = content_input_->text();
                QByteArray send_data = broadcast_content.toLocal8Bit();
                sender_->writeDatagram(send_data.constData(), QHostAddress::Broadcast, 7777);
                // or you can use the method below
                // sender_->writeDatagram(send_data.data(), send_data.size(), QHostAddress::Broadcast, 7777);
            });
}
