#ifndef ADDCONTACTVIEW_H
#define ADDCONTACTVIEW_H

#include "baseview.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget> // Include QTableWidget

class AddContactView : public BaseView {
Q_OBJECT

public:
    AddContactView(QWidget *parent = nullptr);
    ~AddContactView();

private:
    void setupUi();

    QLabel *titleLabel;
};

#endif //  ADDCONTACTVIEW_H