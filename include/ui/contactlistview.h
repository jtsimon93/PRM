#ifndef CONTACTLISTVIEW_H
#define CONTACTLISTVIEW_H

#include "baseview.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget> // Include QTableWidget

class ContactListView : public BaseView {
Q_OBJECT

public:
    ContactListView(QWidget *parent = nullptr);

public slots:
    void refreshData();

private:
    void setupUi();
    void populateTable(); // Declare populateTable method

    QLabel *titleLabel;
    QTableWidget *tableWidget; // Add QTableWidget member
};

#endif // CONTACTLISTVIEW_H