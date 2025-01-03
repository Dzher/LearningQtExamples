#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QStringList>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    qDebug() << "Support Database Drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    // constexpr QStringView tab{u"      "};
    for (auto& each : drivers) {
        qDebug() << "\t" << each;
    }

    return QApplication::exec();
}