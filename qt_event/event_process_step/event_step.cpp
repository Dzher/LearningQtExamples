#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QObject>
#include <QWidget>

class MyWidget : public QWidget
{
public:
    explicit MyWidget(QWidget* parent = nullptr) : QWidget(parent) {
        installEventFilter(this);
    }

    bool eventFilter(QObject* watched, QEvent* event) override {
        if (watched == this) {
            if (event->type() == QEvent::MouseButtonPress) {
                qDebug() << "eventFilter's MouseButtonPress Event";
                return false;
            }
        }
        return false;
    }

protected:
    bool event(QEvent* e) override {
        if (e->type() == QEvent::MouseButtonPress) {
            qDebug() << "event's MouseButtonPress Event";
        }
        return QWidget::event(e);
    }

    void mousePressEvent(QMouseEvent* e) override {
        qDebug() << "mousePressEvent's MouseButtonPress Event";
        return QWidget::mousePressEvent(e);
    }
};

class GlobalEventFilter : public QObject
{
public:
    explicit GlobalEventFilter(QObject* watched, QObject* parent = nullptr) : QObject(parent), watched_(watched) {
    }

    bool eventFilter(QObject* watched, QEvent* event) override {
        if (watched == watched_) {
            if (event->type() == QEvent::MouseButtonPress) {
                qDebug() << "QApplication's MouseButtonPress Event";
                return false;
            }
        }
        return false;
    }

private:
    QObject* watched_;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MyWidget widget;
    widget.installEventFilter(new GlobalEventFilter(&widget, &widget));
    widget.show();
    return QApplication::exec();
}
