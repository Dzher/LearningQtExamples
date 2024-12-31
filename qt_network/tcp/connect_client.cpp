#include "connect_client.h"
#include <qglobal.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtcpsocket.h>
#include <QHBoxLayout>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
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

                if (data_block_size_ == 0) {
                    if (connecter_->bytesAvailable() < (int)sizeof(quint16)) {
                        return;
                    }
                    in >> data_block_size_;
                }
                if (connecter_->bytesAvailable() < data_block_size_) {
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
            });
}
