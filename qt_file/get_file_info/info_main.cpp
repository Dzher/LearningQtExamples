#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QStringList>

int main(int argc, char* argv[]) {
    QStringList infos = {R"(C:\Users\Bob\untabify.lnk)", R"(Bob\\zipfile.tar.gz)", "/tmp/share/7zfile.tar.7z"};

    for (auto& each : infos) {
        qDebug() << "file full name" << each;

        QFileInfo info{each};
        qDebug() << "Is File?" << info.isFile();
        qDebug() << "Is Dir?" << info.isDir();
        qDebug() << "Is Relative?" << info.isRelative();
        qDebug() << "Is Absolute?" << info.isAbsolute();
        qDebug() << "Is Symlink?" << info.isSymLink();
        qDebug() << "File Name:" << info.fileName();
        qDebug() << "Base Name:" << info.baseName();
        qDebug() << "Complete Base Name:" << info.completeBaseName();
        qDebug() << "File Suffix:" << info.suffix();
        qDebug() << "File Complete Suffix:" << info.completeSuffix();
        qDebug() << '\n';
    }

    return 0;
}