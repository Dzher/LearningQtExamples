#include <QTextCodec>
#include "simple_web_browser.h"

#include <QVBoxLayout>

using namespace eg_network;

SimpleWebBrowser::SimpleWebBrowser() {
    manager_ = new QNetworkAccessManager(this);
    text_browser_ = new QTextBrowser(this);

    initUi();
    signalConnect();
}

void SimpleWebBrowser::initUi() {
    setFixedSize(800, 600);
    setCentralWidget(text_browser_);
}

void SimpleWebBrowser::signalConnect() {
    connect(manager_, &QNetworkAccessManager::finished, this, &SimpleWebBrowser::replyFinished);
}

void SimpleWebBrowser::get(const QString& url) {
    manager_->get(QNetworkRequest(QUrl(url)));
}

void SimpleWebBrowser::replyFinished(QNetworkReply* reply) {
    QTextCodec* codec = QTextCodec::codecForName("utf8");
    QString content = codec->toUnicode(reply->readAll());
    text_browser_->setText(content);
    reply->deleteLater();
}