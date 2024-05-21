#include "ui/addcontactview.h"
#include "services/contact_service.h"
#include "singleton_injector.h"
#include <QHeaderView>
#include <QDate>

AddContactView::AddContactView(QWidget *parent)
        : BaseView(parent), contactService(SingletonInjector::getInjector().create<std::shared_ptr<IContactService>>()) {
    setupUi();
}

AddContactView::~AddContactView() {
}

void AddContactView::setupUi() {
    qInfo("Setting up AddContactView UI");

    titleLabel = new QLabel(tr("Add Contact"), this);
    titleLabel->setAlignment(Qt::AlignLeft);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);

    // Create QLineEdit for each field in the Contact model
    firstNameLineEdit = new QLineEdit(this);
    lastNameLineEdit = new QLineEdit(this);
    middleNameLineEdit = new QLineEdit(this);
    nickNameLineEdit = new QLineEdit(this);
    relationshipLineEdit = new QLineEdit(this);

    // Create QDateEdit for the birthDate field
    birthDateEdit = new QDateEdit(this);
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setDateRange(QDate(1900, 1, 1), QDate::currentDate());
    birthDateEdit->setDisplayFormat("MM-dd-yyyy");

    // Create QPushButton for the submit button
    submitButton = new QPushButton(tr("Submit"), this);

    formLayout = new QFormLayout();
    formLayout->addRow(new QLabel(tr("First Name:"), this), firstNameLineEdit);
    formLayout->addRow(new QLabel(tr("Last Name:"), this), lastNameLineEdit);
    formLayout->addRow(new QLabel(tr("Middle Name:"), this), middleNameLineEdit);
    formLayout->addRow(new QLabel(tr("Nick Name:"), this), nickNameLineEdit);
    formLayout->addRow(new QLabel(tr("Relationship:"), this), relationshipLineEdit);
    formLayout->addRow(new QLabel(tr("Birth Date:"), this), birthDateEdit);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addLayout(formLayout);
    layout->addWidget(submitButton);
    layout->addStretch(1); // Add stretch to push the form to the top

    setLayout(layout);

    // Connect the button click signal to the slot
    connect(submitButton, &QPushButton::clicked, this, &AddContactView::onSubmitButtonClicked);

    qInfo("AddContactView UI setup complete");
}

void AddContactView::onSubmitButtonClicked() {
    Contact contact;
    contact.firstName = firstNameLineEdit->text().toStdString();
    contact.lastName = lastNameLineEdit->text().toStdString();
    contact.middleName = middleNameLineEdit->text().toStdString();
    contact.nickName = nickNameLineEdit->text().toStdString();
    contact.relationship = relationshipLineEdit->text().toStdString();

    // Convert QDate to std::tm
    QDate birthDate = birthDateEdit->date();
    std::tm tm = {};
    tm.tm_year = birthDate.year() - 1900;  // years since 1900
    tm.tm_mon = birthDate.month() - 1;     // months since January [0-11]
    tm.tm_mday = birthDate.day();          // day of the month [1-31]

    contact.birthDate = tm;

    int insertedContactId = 0;
    insertedContactId = contactService->addContact(contact);
    qInfo("Contact added with ID: %d", insertedContactId);

    // Clear the form fields
    firstNameLineEdit->clear();
    lastNameLineEdit->clear();
    middleNameLineEdit->clear();
    nickNameLineEdit->clear();
    relationshipLineEdit->clear();
    birthDateEdit->setDate(QDate::currentDate());

    // Direct the user to the contact list view
    emit contactAdded(insertedContactId);
}
