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


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    setLayout(layout);
    qInfo("AddContactView UI setup complete");
}
