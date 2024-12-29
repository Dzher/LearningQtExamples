#include <QApplication>
#include "simply_web_browser.h"

using namespace eg_network;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    SimplyWebBrowser browser;
    browser.show();
    browser.get("https://github.com/Dzher/LearningQtExamples");
    return QApplication::exec();
}