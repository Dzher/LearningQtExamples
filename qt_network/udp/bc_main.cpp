#include <QApplication>
#include "broadcast_client.h"
#include "broadcast_server.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    BroadcastClient client;
    client.show();

    BroadcastServer server;
    server.show();

    return QApplication::exec();
}