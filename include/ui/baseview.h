#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QWidget>

class BaseView : public QWidget {
Q_OBJECT

public:
    BaseView(QWidget *parent = nullptr) : QWidget(parent) {}

signals:
    void switchView(QWidget *widget);
};

#endif // BASEVIEW_H
