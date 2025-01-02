#include "connect_client.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace eg_network;

ConnectClient::ConnectClient() : data_block_size_(0) {
    connecter_ = new QTcpSocket(this);
    initUi();
    signalConnect();
}

void ConnectClient::initUi() {
    setMinimumSize(300, 120);

    auto* input_host_h_layout = new QHBoxLayout;
    auto* host_label = new QLabel("Host:");
    host_input_ = new QLineEdit;
    input_host_h_layout->addWidget(host_label);
    input_host_h_layout->addWidget(host_input_);

    auto* input_port_h_layout = new QHBoxLayout;
    auto* port_label = new QLabel("Port:");
    port_input_ = new QLineEdit;
    input_port_h_layout->addWidget(port_label);
    input_port_h_layout->addWidget(port_input_);

    auto* button_h_layout = new QHBoxLayout;
    connect_btn_ = new QPushButton;
    connect_btn_->setText("Connect...");
    button_h_layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Expanding));
    button_h_layout->addWidget(connect_btn_);

    content_label_ = new QLabel("Waiting...");

    auto* main_layout = new QVBoxLayout;
    main_layout->addLayout(input_host_h_layout);
    main_layout->addLayout(input_port_h_layout);
    main_layout->addLayout(button_h_layout);
    main_layout->addWidget(content_label_);

    setLayout(main_layout);
}

void ConnectClient::signalConnect() {
    connect(connecter_, &QTcpSocket::readyRead, this,
            [this]()
            {
                QDataStream in{connecter_};
                in.setVersion(QDataStream::Qt_5_13);

                qint64 incoming_data_size = connecter_->bytesAvailable();
                if (data_block_size_ == 0) {
                    // data block size is less than data block header size
                    if (incoming_data_size < sizeof(quint16)) {
                        qDebug() << "Error: the number of incoming bytes that are waiting to be read is too less";
                        return;
                    }
                    in >> data_block_size_;
                    qDebug() << "block size is " << data_block_size_;
                }
                // data size is less than the size recorded in data block header
                if (incoming_data_size < data_block_size_) {
                    qDebug() << "Error: the number of incoming bytes you transfor is incompleted";
                    return;
                }

                QString message;
                in >> message;
                content_label_->setText(message);
            });
    // QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error) is deprecation
    connect(connecter_, &QTcpSocket::errorOccurred, this,
            [this](QAbstractSocket::SocketError error)
            {
                qDebug() << "Error: " << error;
                qDebug() << "Error: " << connecter_->errorString();
            });
    connect(connect_btn_, &QPushButton::clicked, this,
            [this]()
            {
                data_block_size_ = 0;

                connecter_->abort();
                connecter_->connectToHost(host_input_->text(), port_input_->text().toInt());
                // connecter_.bind()
            });
}
