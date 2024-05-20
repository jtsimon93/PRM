#include "ui/addcontactview.h"
#include "services/contact_service.h"
#include <QHeaderView>
#include <QDate>

AddContactView::AddContactView(QWidget *parent)
        : BaseView(parent) {
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
    birthDateEdit->setDisplayFormat("yyyy-MM-dd");

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

    qInfo("AddContactView UI setup complete");
}
