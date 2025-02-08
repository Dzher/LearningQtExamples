#include <QApplication>
#include <QBuffer>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QPalette>

void readWriteBuffer() {
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);

    buffer.write("hello qbuffer!");
    buffer.seek(0);  // attention here, must do this step!
    QByteArray data = buffer.readAll();
    buffer.close();

    qDebug() << "The buffer data is" << data;
}

void serialization() {
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);

    QDataStream write(&buffer);
    write << QString("First") << int(2);
    buffer.seek(0);

    QDataStream read(&buffer);
    QString first;
    int second;
    read >> first >> second;

    buffer.close();

    qDebug() << "First data is" << first << "second data is" << second;
}

void writeToByteArray(QByteArray& data) {
    // QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);

    QDataStream write(&buffer);
    write << QApplication::palette();
    buffer.close();

    qDebug() << "The read data is" << data;
}

void readFromByteArray(QByteArray& data) {
    // QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);

    QPalette palette;
    QDataStream read(&buffer);
    read >> palette;

    buffer.close();
}

int main() {
    readWriteBuffer();
    serialization();

    QByteArray data;
    writeToByteArray(data);
    readFromByteArray(data);
    return 0;
}