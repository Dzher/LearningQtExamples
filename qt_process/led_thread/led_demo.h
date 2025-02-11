#include <QApplication>
#include <QLCDNumber>
#include <QMainWindow>
#include <QPushButton>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
class ClockTickTock;
class ClockTickTock : public QThread
{
    Q_OBJECT
public:
    explicit ClockTickTock(QObject* parent = nullptr) : QThread(parent) {
    }

protected:
    void run() override {
        for (int i = 0; i < 1000000000; ++i) {
        }
        emit done();
    }
signals:
    void done();
};

class LCDWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit LCDWidget(QWidget* parent = nullptr)
        : QMainWindow(parent), working_thread_(new ClockTickTock(parent)), timer_(new QTimer(parent)) {
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
        connect(timer_, &QTimer::timeout, this,
                [this]()
                {
                    static int sec = 0;
                    lcd_->display(QString::number(sec++));
                });
        connect(start_btn_, &QPushButton::clicked, this,
                [this]
                {
                    timer_->start(1);
                    working_thread_->start();
                });
        connect(working_thread_, &ClockTickTock::finished, working_thread_, &ClockTickTock::deleteLater);
        connect(working_thread_, &ClockTickTock::done, this, [this] { timer_->stop(); });
    }

private:
    QLCDNumber* lcd_ = nullptr;
    QPushButton* start_btn_ = nullptr;
    ClockTickTock* working_thread_ = nullptr;
    QTimer* timer_ = nullptr;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* window = new LCDWidget;
    window->show();
    QApplication::exec();
}
