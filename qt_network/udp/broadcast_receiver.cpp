#include "broadcast_receiver.h"

#include <QVBoxLayout>

using namespace eg_network;

BroadcastReceiver::BroadcastReceiver() {
    receiver_ = new QUdpSocket(this);
    receiver_->bind(7777, QUdpSocket::ShareAddress);

    initUi();
    signalConnect();
}

void BroadcastReceiver::initUi() {
    setMinimumSize(300, 220);

    content_label_ = new QLabel("Wait for broadcast data...");

    auto* main_layout = new QVBoxLayout;
    main_layout->addWidget(content_label_);

    setLayout(main_layout);
}

void BroadcastReceiver::signalConnect() {
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
