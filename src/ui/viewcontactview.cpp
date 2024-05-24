#include <QFormLayout>
#include <QPushButton>
#include "services/contact_service.h"
#include "ui/viewcontactview.h"
#include "singleton_injector.h"
#include <sstream>
#include <iomanip>

ViewContactView::ViewContactView(int contactId, QWidget *parent)
        : BaseView(parent),
          contactService(SingletonInjector::getInjector().create<std::shared_ptr<IContactService>>()),
          addressService(SingletonInjector::getInjector().create<std::shared_ptr<IAddressService>>()),
          contactId(contactId) {
    setupUi();
}

void ViewContactView::setupUi() {
    auto *layout = new QVBoxLayout(this);
    setupTitle(layout);
    setupContactInformation(layout);
    layout->addSpacing(20);
    setupAddresses(layout);
    layout->addStretch(1);
    setLayout(layout);
}

void ViewContactView::setupTitle(QVBoxLayout *mainLayout) {
    titleLabel = new QLabel(tr("View Contact"), this);
    titleLabel->setAlignment(Qt::AlignLeft);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);

    mainLayout->addWidget(titleLabel);
}

void ViewContactView::setupContactInformation(QVBoxLayout * mainLayout) {
    QFont subTitleFont;
    subTitleFont.setPointSize(14);

    // Retrieve the contact details
    const Contact contact = contactService->getContactById(contactId);

    // Bold font
    QFont boldFont;
    boldFont.setBold(true);

    // Create QLabel for each field in the Contact model
    auto *contactFirstNameLabel = new QLabel(QString::fromStdString(contact.firstName), this);
    auto *contactLastNameLabel = new QLabel(QString::fromStdString(contact.lastName), this);
    auto *contactMiddleNameLabel = new QLabel(QString::fromStdString(contact.middleName ? contact.middleName.value() : ""), this);
    auto *contactNickNameLabel = new QLabel(QString::fromStdString(contact.nickName ? contact.nickName.value() : ""), this);
    auto *contactRelationshipLabel = new QLabel(QString::fromStdString(contact.relationship ? contact.relationship.value() : ""), this);

    // Handle birthdate
    QLabel *contactBirthDateLabel;
    if (contact.birthDate.has_value()) {
        const std::tm birthDate = *contact.birthDate;
        std::stringstream ss;
        ss << std::put_time(&birthDate, "%m-%d-%Y");
        const std::string birthDateString = ss.str();
        contactBirthDateLabel = new QLabel(QString::fromStdString(birthDateString), this);
    } else {
        contactBirthDateLabel = new QLabel("", this);
    }

    // Create labels for the columns
    auto *firstNameLabel = new QLabel(tr("First Name:"));
    auto *lastNameLabel = new QLabel(tr("Last Name:"));
    auto *middleNameLabel = new QLabel(tr("Middle Name:"));
    auto *nickNameLabel = new QLabel(tr("Nick Name:"));
    auto *relationshipLabel = new QLabel(tr("Relationship:"));
    auto *birthDateLabel = new QLabel(tr("Birthday"));

    // Set the font for the labels
    firstNameLabel->setFont(boldFont);
    lastNameLabel->setFont(boldFont);
    middleNameLabel->setFont(boldFont);
    nickNameLabel->setFont(boldFont);
    relationshipLabel->setFont(boldFont);
    birthDateLabel->setFont(boldFont);

    // Create a grid layout and add the fields
    auto *contactGridLayout = new QGridLayout();
    contactGridLayout->addWidget(firstNameLabel, 0, 0);
    contactGridLayout->addWidget(contactFirstNameLabel, 0, 1);
    contactGridLayout->addWidget(lastNameLabel, 0, 2);
    contactGridLayout->addWidget(contactLastNameLabel, 0, 3);
    contactGridLayout->addWidget(middleNameLabel, 1, 0);
    contactGridLayout->addWidget(contactMiddleNameLabel, 1, 1);
    contactGridLayout->addWidget(nickNameLabel, 1, 2);
    contactGridLayout->addWidget(contactNickNameLabel, 1, 3);
    contactGridLayout->addWidget(relationshipLabel, 2, 0);
    contactGridLayout->addWidget(contactRelationshipLabel, 2, 1);
    contactGridLayout->addWidget(birthDateLabel, 2, 2);
    contactGridLayout->addWidget(contactBirthDateLabel, 2, 3);

    mainLayout->addLayout(contactGridLayout);
}

void ViewContactView::setupAddresses(QVBoxLayout *mainLayout) {
    QFont subTitleFont;
    subTitleFont.setPointSize(14);

    // Get the addresses for the contact
    const std::vector<Address> addresses = addressService->getAddressesByContactId(contactId);

    // Create a container for the addresses
    auto *addressLabel = new QLabel(tr("Addresses"), this);
    addressLabel->setFont(subTitleFont);
    auto *addressesContainer = new QWidget(this);
    auto *addressesLayout = new QGridLayout(addressesContainer);

    QFont boldFont;
    boldFont.setBold(true);

    if (!addresses.empty()) {
        int row = 0;

        // Add headers
        auto *header1 = new QLabel(tr("Street Address 1"), this);
        header1->setFont(boldFont);
        auto *header2 = new QLabel(tr("Street Address 2"), this);
        header2->setFont(boldFont);
        auto *header3 = new QLabel(tr("City"), this);
        header3->setFont(boldFont);
        auto *header4 = new QLabel(tr("State"), this);
        header4->setFont(boldFont);
        auto *header5 = new QLabel(tr("Zip"), this);
        header5->setFont(boldFont);
        auto *headerEdit = new QLabel(tr("Edit"), this);
        headerEdit->setFont(boldFont);
        auto *headerDelete = new QLabel(tr("Delete"), this);
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
            auto *streetAddress1Label = new QLabel(QString::fromStdString(address.streetAddress1), this);
            auto *streetAddress2Label = new QLabel(QString::fromStdString(address.streetAddress2 ? address.streetAddress2.value() : ""), this);
            auto *cityLabel = new QLabel(QString::fromStdString(address.city ? address.city.value() : ""), this);
            auto *stateLabel = new QLabel(QString::fromStdString(address.state ? address.state.value() : ""), this);
            auto *zipLabel = new QLabel(QString::fromStdString(address.zip ? address.zip.value() : ""), this);

            auto *editButton = new QPushButton(tr("Edit"), this);
            auto *deleteButton = new QPushButton(tr("Delete"), this);

            // TODO: Connect edit and delete buttons

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
        auto *noAddressesLabel = new QLabel(tr("No addresses found for this contact."), this);
        addressesLayout->addWidget(noAddressesLabel, 0, 0);
    }

    mainLayout->addWidget(addressLabel);
    mainLayout->addWidget(addressesContainer);
}
