#include "services/contact_service.h"
#include "ui/viewcontactview.h"

ViewContactView::ViewContactView(QWidget *parent)
        : BaseView(parent) {
    setupUi();
}

void ViewContactView::setupUi() {
    titleLabel = new QLabel(tr("View Contact"), this);
    titleLabel->setAlignment(Qt::AlignLeft);

    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleLabel->setFont(titleFont);


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    setLayout(layout);
}
