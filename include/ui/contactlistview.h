#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H

#include "baseview.h"
#include <QLabel>
#include <QVBoxLayout>

class ContactListView : public BaseView {
Q_OBJECT

public:
    ContactListView(QWidget *parent = nullptr);

private:
    void setupUi();

    QLabel *titleLabel;
};

#endif // CONTACTLISTVIEW_H
