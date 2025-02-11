#include <qchar.h>
#include <qmutex.h>
#include <QApplication>
#include <QLCDNumber>
#include <QMainWindow>
#include <QMutexLocker>
#include <QPushButton>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class WatcherThread : public QThread
{
    Q_OBJECT
public:
    explicit WatcherThread(QObject* parent = nullptr) : QThread(parent), is_running_(false) {
    }

    void startWatcher() {
        QMutexLocker locker(&mutex_);
        is_running_ = true;
        start();
    }

    void stopWatcher() {
        QMutexLocker locker(&mutex_);
        is_running_ = false;
    }

protected:
    void run() override {
        while (true) {
            if (!is_running_) {
                break;
            }

            emit updateTime();
            msleep(100);
        }
    }
signals:
    void updateTime();

private:
    QMutex mutex_;
    bool is_running_;
};

class LCDWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit LCDWidget(QWidget* parent = nullptr) : QMainWindow(parent), watcher_thread_(new WatcherThread(parent)) {
        watcher_thread_->start();
        initUi();
        signalConnect();
    }

private:
    void initUi() {
        auto* widget = new QWidget;
        setCentralWidget(widget);
        auto* main_lyt = new QVBoxLayout;
        widget->setLayout(main_lyt);

        lcd_ = new QLCDNumber;
        start_btn_ = new QPushButton("Start");
        stop_btn_ = new QPushButton("Stop");
        main_lyt->addWidget(lcd_);
        main_lyt->addWidget(start_btn_);
        main_lyt->addWidget(stop_btn_);
    }

    void signalConnect() {
        connect(start_btn_, &QPushButton::clicked, this,
                [this]
                {
                    watcher_thread_->startWatcher();
                    start_btn_->setEnabled(false);
                    stop_btn_->setEnabled(true);
                });
        connect(stop_btn_, &QPushButton::clicked, this,
                [this]
                {
                    watcher_thread_->stopWatcher();
                    start_btn_->setEnabled(true);
                    stop_btn_->setEnabled(false);
                });
        connect(watcher_thread_, &WatcherThread::updateTime, this,
                [this]
                {
                    QTime time = QTime::currentTime();
                    QString time_str = time.toString("hh:mm:ss");
                    lcd_->display(time_str);
                });
    }

private:
    QLCDNumber* lcd_ = nullptr;
    QPushButton* start_btn_ = nullptr;
    QPushButton* stop_btn_ = nullptr;
    WatcherThread* watcher_thread_ = nullptr;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* window = new LCDWidget;
    window->show();
    QApplication::exec();
}
