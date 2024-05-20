#ifndef VIEWCONTACTVIEW_H
#define VIEWCONTACTVIEW_H

#include "baseview.h"
#include "icontact_service.h"
#include <QLabel>
#include <QVBoxLayout>

class ViewContactView : public BaseView {
Q_OBJECT

public:
    explicit ViewContactView(QWidget *parent = nullptr);


private:
    void setupUi();

    QLabel *titleLabel;

    std::shared_ptr<IContactService> contactService;
};

#endif //  VIEWCONTACTVIEW_H