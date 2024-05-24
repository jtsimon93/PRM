#include <QFormLayout>
#include "services/contact_service.h"
#include "ui/viewcontactview.h"
#include "singleton_injector.h"

ViewContactView::ViewContactView(int contactId, QWidget *parent)
        : BaseView(parent), contactService(SingletonInjector::getInjector().create<std::shared_ptr<IContactService>>()),
          addressService(SingletonInjector::getInjector().create<std::shared_ptr<IAddressService>>()) {
    this->contactId = contactId;
    setupUi();
}

void ViewContactView::setupUi() {
    titleLabel = new QLabel(tr("View Contact"), this);
    titleLabel->setAlignment(Qt::AlignLeft);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);

    // Retrieve the contact details
    Contact contact = contactService->getContactById(contactId);

    // Create QLabel for each field in the Contact model
    QLabel *firstNameLabel = new QLabel(QString::fromStdString(contact.firstName), this);
    QLabel *lastNameLabel = new QLabel(QString::fromStdString(contact.lastName), this);
    QLabel *middleNameLabel = new QLabel(QString::fromStdString(contact.middleName ? contact.middleName.value() : ""), this);
    QLabel *nickNameLabel = new QLabel(QString::fromStdString(contact.nickName ? contact.nickName.value() : ""), this);
    QLabel *relationshipLabel = new QLabel(QString::fromStdString(contact.relationship ? contact.relationship.value() : ""), this);

    // Handle birthdate
    QLabel *birthDateLabel;

    if(contact.birthDate.has_value()) {
        std::tm birthDate = *contact.birthDate;
        std::stringstream ss;
        ss << std::put_time(&birthDate, "%m-%d-%Y");
        std::string birthDateString = ss.str();

        birthDateLabel = new QLabel(QString::fromStdString(birthDateString), this);
    } else {
        birthDateLabel = new QLabel("", this);
    }

    // Create a form layout and add the fields
    QFormLayout *contactFormLayout = new QFormLayout();
    contactFormLayout->addRow(tr("First Name:"), firstNameLabel);
    contactFormLayout->addRow(tr("Last Name:"), lastNameLabel);
    contactFormLayout->addRow(tr("Middle Name:"), middleNameLabel);
    contactFormLayout->addRow(tr("Nick Name:"), nickNameLabel);
    contactFormLayout->addRow(tr("Relationship:"), relationshipLabel);
    contactFormLayout->addRow(tr("Birth Date:"), birthDateLabel);

    // Get the addresses for the contact
    std::vector<Address> addresses = addressService->getAddressesByContactId(contactId);

    // Create a container for the addresses
    QWidget *addressesContainer = new QWidget(this);
    QVBoxLayout *addressesLayout = new QVBoxLayout(addressesContainer);
    addressesLayout->setContentsMargins(0,0,0,0);

    // If there are addresses, add them to the addressesLayout
    if(!addresses.empty()) {
        for(const Address& address : addresses) {
            QLabel *streetAddress1Label = new QLabel(QString::fromStdString(address.streetAddress1), this);
            QLabel *streetAddress2Label = new QLabel(QString::fromStdString(address.streetAddress2 ? address.streetAddress2.value() : ""), this);
            QLabel *cityLabel = new QLabel(QString::fromStdString(address.city ? address.city.value() : ""), this);
            QLabel *stateLabel = new QLabel(QString::fromStdString(address.state ? address.state.value() : ""), this);
            QLabel *zipLabel = new QLabel(QString::fromStdString(address.zip ? address.zip.value() : ""), this);

            QFormLayout *addressFormLayout = new QFormLayout();
            addressFormLayout->setContentsMargins(0,0,0,0);
            addressFormLayout->addRow(tr("Street Address 1:"), streetAddress1Label);
            addressFormLayout->addRow(tr("Street Address 2:"), streetAddress2Label);
            addressFormLayout->addRow(tr("City:"), cityLabel);
            addressFormLayout->addRow(tr("State:"), stateLabel);
            addressFormLayout->addRow(tr("Zip:"), zipLabel);

            QWidget *addressContainer = new QWidget(this);
            addressContainer->setLayout(addressFormLayout);
            addressesLayout->addWidget(addressContainer);
        }
    } else {
        QLabel *noAddressesLabel = new QLabel(tr("No addresses found for this contact."), this);
        addressesLayout->addWidget(noAddressesLabel);

    }


    // Layout for the contact view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);

    // Add contact form layout to the main layout
    layout->addLayout(contactFormLayout);

    // Add addresses container to the main layout
    layout->addWidget(addressesContainer);

    layout->addStretch(1);
    setLayout(layout);
}
