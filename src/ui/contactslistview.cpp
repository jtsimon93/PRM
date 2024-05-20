#include "ui/contactlistview.h"
#include "services/contact_service.h"
#include "singleton_injector.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QDate>

ContactListView::ContactListView(QWidget *parent)
        : BaseView(parent) {
    setupUi();
    populateTable();
}

void ContactListView::setupUi() {
    titleLabel = new QLabel("Contacts", this);
    titleLabel->setAlignment(Qt::AlignCenter); // Center align the text

    // Create a QTableWidget
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "First Name" << "Last Name" << "Middle Name" << "Nick Name" << "Birth Day" << "Relationship");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(tableWidget);
    setLayout(layout);
}

void ContactListView::populateTable() {
    // Get the ContactService from the DI container
    auto contactService = SingletonInjector::getInjector().create<std::shared_ptr<IContactService>>();

    // Retrieve all contacts
    std::vector<Contact> contacts = contactService->getAllContacts();

    // Populate the table with the contacts
    for (const Contact &contact : contacts) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(contact.firstName)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(contact.lastName)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(contact.middleName)));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(contact.nickName)));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(contact.relationship)));

        // Convert birthday for display
        QDate birthDate = QDate(contact.birthDate.tm_year + 1900, contact.birthDate.tm_mon + 1, contact.birthDate.tm_mday);
        tableWidget->setItem(row, 4, new QTableWidgetItem(birthDate.toString("yyyy-MM-dd")));
    }

    // Resize the columns to fit the content
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}