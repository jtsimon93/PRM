#ifndef VIEWCONTACTVIEW_H
#define VIEWCONTACTVIEW_H

#include "baseview.h"
#include "icontact_service.h"
#include "iaddress_service.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <memory>

class ViewContactView : public BaseView {
Q_OBJECT

public:
    explicit ViewContactView(int contactId, QWidget *parent = nullptr);

private:
    void setupUi();
    void setupTitle(QVBoxLayout *mainLayout);
    void setupContactInformation(QVBoxLayout *mainLayout);
    void setupAddresses(QVBoxLayout *mainLayout);

    QLabel *titleLabel;
    int contactId;

    std::shared_ptr<IContactService> contactService;
    std::shared_ptr<IAddressService> addressService;
};

#endif //  VIEWCONTACTVIEW_H
