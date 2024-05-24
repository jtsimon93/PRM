#include <QFormLayout>
#include <QPushButton>
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

    QFont subTitleFont;
    subTitleFont.setPointSize(14);

    QFont boldFont;
    boldFont.setBold(true);

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
    QLabel *addressLabel = new QLabel(tr("Addresses"), this);
    addressLabel->setFont(subTitleFont);
    QWidget *addressesContainer = new QWidget(this);
    QGridLayout *addressesLayout = new QGridLayout(addressesContainer);

    if (!addresses.empty()) {
        int row = 0;

        // Add headers
        QLabel *header1 = new QLabel(tr("Street Address 1"), this);
        header1->setFont(boldFont);
        QLabel *header2 = new QLabel(tr("Street Address 2"), this);
        header2->setFont(boldFont);
        QLabel *header3 = new QLabel(tr("City"), this);
        header3->setFont(boldFont);
        QLabel *header4 = new QLabel(tr("State"), this);
        header4->setFont(boldFont);
        QLabel *header5 = new QLabel(tr("Zip"), this);
        header5->setFont(boldFont);
        QLabel *headerEdit = new QLabel(tr("Edit"), this);
        headerEdit->setFont(boldFont);
        QLabel *headerDelete = new QLabel(tr("Delete"), this);
        headerDelete->setFont(boldFont);

        addressesLayout->addWidget(header1, row, 0);
        addressesLayout->addWidget(header2, row, 1);
        addressesLayout->addWidget(header3, row, 2);
        addressesLayout->addWidget(header4, row, 3);
        addressesLayout->addWidget(header5, row, 4);
        addressesLayout->addWidget(headerEdit, row, 5);
        addressesLayout->addWidget(headerDelete, row, 6);

        row++;

        for (const Address& address : addresses) {
            QLabel *streetAddress1Label = new QLabel(QString::fromStdString(address.streetAddress1), this);
            QLabel *streetAddress2Label = new QLabel(QString::fromStdString(address.streetAddress2 ? address.streetAddress2.value() : ""), this);
            QLabel *cityLabel = new QLabel(QString::fromStdString(address.city ? address.city.value() : ""), this);
            QLabel *stateLabel = new QLabel(QString::fromStdString(address.state ? address.state.value() : ""), this);
            QLabel *zipLabel = new QLabel(QString::fromStdString(address.zip ? address.zip.value() : ""), this);

            QPushButton *editButton = new QPushButton(tr("Edit"), this);
            QPushButton *deleteButton = new QPushButton(tr("Delete"), this);

            // Connect the buttons to appropriate slots
            // connect(editButton, &QPushButton::clicked, this, &YourClass::editAddress);
            // connect(deleteButton, &QPushButton::clicked, this, &YourClass::deleteAddress);

            addressesLayout->addWidget(streetAddress1Label, row, 0);
            addressesLayout->addWidget(streetAddress2Label, row, 1);
            addressesLayout->addWidget(cityLabel, row, 2);
            addressesLayout->addWidget(stateLabel, row, 3);
            addressesLayout->addWidget(zipLabel, row, 4);
            addressesLayout->addWidget(editButton, row, 5);
            addressesLayout->addWidget(deleteButton, row, 6);

            row++;
        }
    } else {
        QLabel *noAddressesLabel = new QLabel(tr("No addresses found for this contact."), this);
        addressesLayout->addWidget(noAddressesLabel, 0, 0);
    }




    // Layout for the contact view
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);

    // Add contact form layout to the main layout
    layout->addLayout(contactFormLayout);

    // Add addresses container to the main layout
    layout->addWidget(addressLabel);
    layout->addWidget(addressesContainer);

    layout->addStretch(1);
    setLayout(layout);
}
