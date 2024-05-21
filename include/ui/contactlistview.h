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

signals:
    void contactDoubleClicked(int contactId);

private:
    void setupUi();
    void populateTable(); // Declare populateTable method
    void onItemDoubleClicked(QTableWidgetItem* item);

    QLabel *titleLabel;
    QTableWidget *tableWidget; // Add QTableWidget member
};

#endif // CONTACTLISTVIEW_H