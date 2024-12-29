#include <QApplication>
#include "simply_downloader.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    SimplyDownloader downloader;
    downloader.show();
    return QApplication::exec();
}