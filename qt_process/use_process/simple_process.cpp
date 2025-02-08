#include <qlist.h>
#include <qprocess.h>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QTextCodec>

void openNotepad() {
    QProcess process;
    process.setProgram("notepad.exe");
    process.start();
    process.waitForFinished();
    process.close();
}

void useCmd() {
    QProcess process;
    QStringList args{"/c", "dir C:"};
    process.setProgram("cmd.exe");
    process.setArguments(args);

    qDebug() << process.state();
    QObject::connect(&process, &QProcess::readyRead,
                     [&process]()
                     {
                         QTextCodec* codec = QTextCodec::codecForName("GBK");
                         QString all_info = codec->toUnicode(process.readAll());
                         QStringList infos = all_info.split('\n');
                         for (auto& each : infos) {
                             qDebug() << each;
                         }
                     });
    process.start();
    qDebug() << process.state();
    process.waitForFinished();
}

int main(int argc, char* argv[]) {
    // openNotepad();
    useCmd();

    return 0;
}