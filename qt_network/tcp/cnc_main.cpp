#include <QApplication>
#include "connect_client.h"
#include "connect_server.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ConnectServer server;
    server.show();
    
    ConnectClient client;
    client.show();


    return QApplication::exec();
}