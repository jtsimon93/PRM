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
    birthDateEdit->setDisplayFormat("MM/dd/yyyy");

    // Create QPushButton for the submit button
    submitButton = new QPushButton(tr("Submit"), this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(new QLabel(tr("First Name:"), this));
    layout->addWidget(firstNameLineEdit);
    layout->addWidget(new QLabel(tr("Last Name:"), this));
    layout->addWidget(lastNameLineEdit);
    layout->addWidget(new QLabel(tr("Middle Name:"), this));
    layout->addWidget(middleNameLineEdit);
    layout->addWidget(new QLabel(tr("Nick Name:"), this));
    layout->addWidget(nickNameLineEdit);
    layout->addWidget(new QLabel(tr("Relationship:"), this));
    layout->addWidget(relationshipLineEdit);
    layout->addWidget(new QLabel(tr("Birth Date:"), this));
    layout->addWidget(birthDateEdit);
    layout->addWidget(submitButton);

    setLayout(layout);

    qInfo("AddContactView UI setup complete");
}
