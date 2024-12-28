#include "simply_web_browser.h"
#include <QTextCodec>

#include <QVBoxLayout>

using namespace eg_network;

SimplyWebBrowser::SimplyWebBrowser() {
    manager_ = new QNetworkAccessManager(this);
    text_browser_ = new QTextBrowser(this);

    initUi();
    signalConnect();
}

void SimplyWebBrowser::initUi() {
    setFixedSize(800, 600);
    setCentralWidget(text_browser_);
}

void SimplyWebBrowser::signalConnect() {
    connect(manager_, &QNetworkAccessManager::finished, this, &SimplyWebBrowser::replyFinished);
}

void SimplyWebBrowser::get(const QString& url) {
    manager_->get(QNetworkRequest(QUrl(url)));
}

void SimplyWebBrowser::replyFinished(QNetworkReply* reply) {
    QTextCodec* codec = QTextCodec::codecForName("utf8");
    QString content = codec->toUnicode(reply->readAll());
    text_browser_->setText(content);
    reply->deleteLater();
}