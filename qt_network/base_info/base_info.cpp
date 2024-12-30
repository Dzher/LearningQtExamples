#include "base_info.h"
#include <qboxlayout.h>
#include <qhostaddress.h>
#include <qnetworkinterface.h>
#include <QDebug>
#include <QHostInfo>
#include <QNetworkInterface>

using namespace eg_network;

BaseInfoWidget::BaseInfoWidget() {
    initUi();
    getLocalHostInfos();
}

void BaseInfoWidget::initUi() {
    setMinimumSize(300, 120);

    auto* main_layout = new QVBoxLayout;
    text_browser_ = new QTextBrowser;
    main_layout->addWidget(text_browser_);
    setLayout(main_layout);
}

void BaseInfoWidget::getLocalHostInfos() {
    QString content;
    // by QHostInfo
    QString local_host_name = QHostInfo::localHostName();
    content = content + "Local Host Name: " + local_host_name + '\n';

    QHostInfo info = QHostInfo::fromName(local_host_name);
    QList<QHostAddress> addresses = info.addresses();
    for (auto& each : addresses) {
        if (each.protocol() == QAbstractSocket::IPv4Protocol) {
            content = content + "IPV4 Address: " + each.toString() + '\n';
            continue;
        }
        if (each.protocol() == QAbstractSocket::IPv6Protocol) {
            content = content + "IPV6 Address: " + each.toString() + '\n';
            continue;
        }
    }
    content += '\n';

    // by interface
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (auto& each_if : interfaces) {
        content = content + "Device Name: " + each_if.name() + '\n';
        content = content + "Hardware Address: " + each_if.hardwareAddress() + '\n';
        for (auto& each_ae : each_if.addressEntries()) {
            content = content + "IP Address: " + each_ae.ip().toString() + '\n';
            content = content + "Net Mask: " + each_ae.netmask().toString() + '\n';
            content = content + "Broadcast Address: " + each_ae.broadcast().toString() + '\n';
        }
        content += '\n';
    }

    text_browser_->setText(content);
}

void BaseInfoWidget::getInfosByHostName(const QString& host_name) {
    QHostInfo::lookupHost(host_name,
                          [host_name, this](const QHostInfo& info)
                          {
                              QString content;
                              QList<QHostAddress> addresses = info.addresses();
                              for (auto& each : addresses) {
                                  content = content + host_name + " Address is: " + each.toString() + '\n';
                              }
                              text_browser_->setText(content);
                          });
}