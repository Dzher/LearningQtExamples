#include <QApplication>
#include "base_info.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    BaseInfoWidget base_info_wgt;
    base_info_wgt.show();
    // base_info_wgt.getInfosByHostName("www.baidu.com");

    return QApplication::exec();
}