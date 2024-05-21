#ifndef ADDCONTACTVIEW_H
#define ADDCONTACTVIEW_H

#include "baseview.h"
#include "icontact_service.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QFormLayout>

class AddContactView : public BaseView {
Q_OBJECT

public:
    explicit AddContactView(QWidget *parent = nullptr);
    ~AddContactView();

private slots:
    void onSubmitButtonClicked();

signals:
    void contactAdded(int contactId);

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
    QFormLayout *formLayout;

    std::shared_ptr<IContactService> contactService;
};

#endif //  ADDCONTACTVIEW_H