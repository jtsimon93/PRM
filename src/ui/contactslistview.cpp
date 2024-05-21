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
    titleLabel = new QLabel(tr("Contacts"), this);
    titleLabel->setAlignment(Qt::AlignLeft);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);

    // Create a QTableWidget
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels(QStringList() << tr("First Name") << tr("Last Name") << tr("Middle Name") << tr("Nick Name") << tr("Birth Day") << tr("Relationship"));
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(tableWidget);
    setLayout(layout);

    connect(tableWidget, &QTableWidget::itemDoubleClicked, this, &ContactListView::onItemDoubleClicked);
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
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(contact.middleName ? contact.middleName.value() : "")));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(contact.nickName ? contact.nickName.value() : "")));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(contact.relationship ? contact.relationship.value() : "")));

        // Store the contact ID in the first column
        tableWidget->item(row, 0)->setData(Qt::UserRole, contact.id);

        // Convert birthday for display
        QDate birthDate;
        if(contact.birthDate.has_value()) {
            birthDate = QDate(contact.birthDate->tm_year + 1900, contact.birthDate->tm_mon + 1,
                              contact.birthDate->tm_mday);
            tableWidget->setItem(row, 4, new QTableWidgetItem(birthDate.toString("yyyy-MM-dd")));
        }
        else {
            tableWidget->setItem(row, 4, new QTableWidgetItem(""));
        }
    }
}

void ContactListView::refreshData() {
    // Clear the table
    tableWidget->clearContents();
    tableWidget->setRowCount(0);

    // Repopulate the table
    populateTable();
}

void ContactListView::onItemDoubleClicked(QTableWidgetItem *item) {
    int row = item->row();
    int contactId = tableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    emit contactDoubleClicked(contactId);
}