#include <QFormLayout>
#include "services/contact_service.h"
#include "ui/viewcontactview.h"
#include "singleton_injector.h"

ViewContactView::ViewContactView(int contactId, QWidget *parent)
        : BaseView(parent), contactService(SingletonInjector::getInjector().create<std::shared_ptr<IContactService>>()) {
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
    QLabel *nickNameLabel = new QLabel(QString::fromStdString(contact.nickName ? contact.middleName.value() : ""), this);
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
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("First Name:"), firstNameLabel);
    formLayout->addRow(tr("Last Name:"), lastNameLabel);
    formLayout->addRow(tr("Middle Name:"), middleNameLabel);
    formLayout->addRow(tr("Nick Name:"), nickNameLabel);
    formLayout->addRow(tr("Relationship:"), relationshipLabel);
    formLayout->addRow(tr("Birth Date:"), birthDateLabel);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addLayout(formLayout);
    layout->addStretch(1);
    setLayout(layout);
}
