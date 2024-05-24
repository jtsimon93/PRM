#ifndef VIEWCONTACTVIEW_H
#define VIEWCONTACTVIEW_H

#include "baseview.h"
#include "icontact_service.h"
#include "iaddress_service.h"
#include <QLabel>
#include <QVBoxLayout>

class ViewContactView : public BaseView {
Q_OBJECT

public:
    explicit ViewContactView(int contactId, QWidget *parent = nullptr);


private:
    void setupUi();

    QLabel *titleLabel;
    int contactId;


    std::shared_ptr<IContactService> contactService;
    std::shared_ptr<IAddressService> addressService;
};

#endif //  VIEWCONTACTVIEW_H