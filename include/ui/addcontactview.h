#ifndef ADDCONTACTVIEW_H
#define ADDCONTACTVIEW_H

#include "baseview.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>

class AddContactView : public BaseView {
Q_OBJECT

public:
    explicit AddContactView(QWidget *parent = nullptr);
    ~AddContactView();

private:
    void setupUi();

    QLabel *titleLabel;
    QLineEdit *firstNameLineEdit;
    QLineEdit *lastNameLineEdit;
    QLineEdit *middleNameLineEdit;
    QLineEdit *nickNameLineEdit;
    QLineEdit *relationshipLineEdit;
    QDateEdit *birthDateEdit;
    QPushButton *submitButton;
};

#endif //  ADDCONTACTVIEW_H