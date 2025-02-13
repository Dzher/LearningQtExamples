#include <QApplication>
#include <QLCDNumber>
#include <QMainWindow>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

static int sec = 0;

class WatcherThread : public QThread
{
    Q_OBJECT
public:
    explicit WatcherThread(QObject* parent = nullptr) : QThread(parent) {
    }

protected:
    void run() override {
        for (int i = 0; i < 1000000000; ++i) {
        }
        emit updateTime();
    }
signals:
    void updateTime();
};

class LCDWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit LCDWidget(QWidget* parent = nullptr)
        : QMainWindow(parent), watcher_thread_(new WatcherThread(parent)), timer_(new QTimer(parent)) {
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
        main_lyt->addWidget(lcd_);
        main_lyt->addWidget(start_btn_);
    }

    void signalConnect() {
        connect(timer_, &QTimer::timeout, this, [this]() { lcd_->display(QString::number(sec++)); });
        connect(start_btn_, &QPushButton::clicked, this,
                [this]
                {
                    timer_->start(1000);
                    watcher_thread_->start();
                });
        connect(watcher_thread_, &WatcherThread::updateTime, this, [this] { timer_->stop(); });
        // connect(working_thread_, &NumberCounter::finished, working_thread_, &NumberCounter::deleteLater);
    }

private:
    QLCDNumber* lcd_ = nullptr;
    QPushButton* start_btn_ = nullptr;
    WatcherThread* watcher_thread_ = nullptr;
    QTimer* timer_ = nullptr;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* window = new LCDWidget;
    window->show();
    QApplication::exec();
}
