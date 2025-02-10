#include <QApplication>
#include <QBuffer>
#include <QDataStream>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QSharedMemory>
#include <QVBoxLayout>

const char* kSharedMemory = "shared_photo_memory";

class PhotoSharer : public QMainWindow
{
public:
    explicit PhotoSharer(QWidget* parent = nullptr)
        : QMainWindow(parent) {  // do not use shared_memory_(new QSharedMemory(kSharedMemory, this))
        initUi();
        signalConnect();
    }

private:
    void initUi() {
        auto* main_widget = new QWidget;
        setCentralWidget(main_widget);
        auto* main_lyt = new QVBoxLayout;
        main_widget->setLayout(main_lyt);

        save_btn_ = new QPushButton("Save");  //save to shared memory
        load_btn_ = new QPushButton("Load");  //load from shared memory
        pic_lbl_ = new QLabel;
        main_lyt->addWidget(save_btn_);
        main_lyt->addWidget(load_btn_);
        main_lyt->addWidget(pic_lbl_);
    }

    void signalConnect() {
        connect(save_btn_, &QPushButton::clicked, this,
                [this]
                {
                    auto* save_shared_memory_ = new QSharedMemory(this);
                    save_shared_memory_->setKey(kSharedMemory);
                    if (save_shared_memory_->isAttached()) {
                        save_shared_memory_->detach();
                        qDebug() << "detach last shared memory";
                    }

                    QString photo_name = QFileDialog::getOpenFileName(this);
                    QPixmap photo(photo_name);
                    // pic_lbl_->setPixmap(photo);

                    QBuffer buffer;
                    QDataStream data(&buffer);
                    buffer.open(QIODevice::ReadWrite);
                    data << photo;

                    int size = int(buffer.size());
                    if (!save_shared_memory_->create(size)) {
                        qDebug() << "Create Error:" << save_shared_memory_->errorString();
                    }
                    else {
                        save_shared_memory_->lock();
                        const char* from = buffer.data().constData();
                        char* to = static_cast<char*>(save_shared_memory_->data());
                        memcpy(to, from, std::min(size, save_shared_memory_->size()));
                        save_shared_memory_->unlock();
                        qDebug() << "save finished";
                    }
                    buffer.close();
                });
        connect(load_btn_, &QPushButton::clicked, this,
                [this]
                {
                    auto* load_shared_memory_ = new QSharedMemory(this);
                    load_shared_memory_->setKey(kSharedMemory);

                    if (!load_shared_memory_->attach()) {
                        qDebug() << "Attach Error:" << load_shared_memory_->errorString();
                        return;
                    }

                    // 在QBuffer使用setData之前，不需要调用open()
                    // QBuffer的setData()函数会直接将数据设置到缓冲区中，并自动调整缓冲区的大小
                    // open()函数主要用于打开设备进行读写操作，而setData()已经完成了数据的写入，因此不需要再打开缓冲区
                    QBuffer buffer;
                    QDataStream data(&buffer);
                    load_shared_memory_->lock();
                    buffer.setData(static_cast<const char*>(load_shared_memory_->constData()),
                                   load_shared_memory_->size());
                    load_shared_memory_->unlock();
                    load_shared_memory_->detach();

                    buffer.open(QIODevice::ReadWrite);
                    QPixmap photo;
                    data >> photo;
                    pic_lbl_->setPixmap(photo);
                    buffer.close();
                });
    }

private:
    // different funcs or processes should use different qsharedmemory objects, 
    // and attention have at least one shared memory is alive for the special key when need shared
    // QSharedMemory* shared_memory_ = nullptr;
    QPushButton* save_btn_ = nullptr;
    QPushButton* load_btn_ = nullptr;
    QLabel* pic_lbl_ = nullptr;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* window = new PhotoSharer;
    window->show();
    QApplication::exec();
}