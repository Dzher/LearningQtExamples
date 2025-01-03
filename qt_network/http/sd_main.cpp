#include <QApplication>
#include "simple_downloader.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    SimpleDownloader downloader;
    downloader.show();
    return QApplication::exec();
}