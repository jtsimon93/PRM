#include "ui/contactlistview.h"

ContactListView::ContactListView(QWidget *parent)
        : BaseView(parent) {
    setupUi();
}

void ContactListView::setupUi() {
    titleLabel = new QLabel("Contacts", this);
    titleLabel->setAlignment(Qt::AlignCenter); // Center align the text

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    setLayout(layout);
}
