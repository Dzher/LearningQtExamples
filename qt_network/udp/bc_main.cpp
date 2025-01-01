#include <QApplication>
#include "broadcast_sender.h"
#include "broadcast_receiver.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    BroadcastSender sender;
    sender.show();

    BroadcastReceiver receiver;
    receiver.show();

    return QApplication::exec();
}