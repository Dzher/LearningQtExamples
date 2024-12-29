#include "simply_downloader.h"
#include <QBoxLayout>
#include <QFileInfo>
#include <QLabel>
#include <QWidget>

using namespace eg_network;

SimplyDownloader::SimplyDownloader() {
    manager_ = new QNetworkAccessManager(this);
    initUi();
    signalConnect();
}

void SimplyDownloader::initUi() {
    setMinimumSize(600, 150);

    auto* main_widget = new QWidget();

    auto* h_url_lyt = new QHBoxLayout();
    auto* url_input_label = new QLabel("Please Input the download Url:");
    h_url_lyt->addWidget(url_input_label);
    h_url_lyt->addSpacing(20);

    auto* h_input_lyt = new QHBoxLayout();
    url_input_ = new QLineEdit();
    download_btn_ = new QPushButton("Download");
    h_input_lyt->addWidget(url_input_);
    h_input_lyt->addWidget(download_btn_);

    download_progress_ = new QProgressBar();
    auto* main_layout = new QVBoxLayout();
    main_layout->addLayout(h_url_lyt);
    main_layout->addLayout(h_input_lyt);
    main_layout->addWidget(download_progress_);
    download_progress_->setVisible(false);
    auto* v_spacing = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Expanding);
    main_layout->addSpacerItem(v_spacing);

    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);
}

void SimplyDownloader::signalConnect() {
    connect(download_btn_, &QPushButton::clicked, this, &SimplyDownloader::onDownload);
}

void SimplyDownloader::onDownload() {
    url_ = url_input_->text();

    QFileInfo info(url_.path());
    QString file_name(info.fileName());
    if (file_name.isEmpty()) {
        file_name = "index.html";
    }
    download_file_ = new QFile(file_name);
    if (!download_file_->open(QIODevice::WriteOnly)) {
        qDebug() << "file open error";
        delete download_file_;
        download_file_ = nullptr;
        return;
    }
    reply_ = manager_->get(QNetworkRequest(url_));
    connect(reply_, &QNetworkReply::readyRead, this, &SimplyDownloader::onHttpReadyRead);
    connect(reply_, &QNetworkReply::downloadProgress, this, &SimplyDownloader::onUpdateProgress);
    connect(reply_, &QNetworkReply::finished, this, &SimplyDownloader::onDownloadFinished);

    download_progress_->setValue(0);
    download_progress_->show();
}

void SimplyDownloader::onDownloadFinished() {
    download_progress_->hide();

    download_file_->flush();
    download_file_->close();
    delete download_file_;
    download_file_ = nullptr;

    reply_->deleteLater();
    reply_ = nullptr;
}

void SimplyDownloader::onHttpReadyRead() {
    if (download_file_) {
        download_file_->write(reply_->readAll());
    }
}

void SimplyDownloader::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal) {
    download_progress_->setMaximum(int(bytesTotal));
    download_progress_->setValue(int(bytesReceived));
}