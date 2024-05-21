#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QSplitter>
#include "contactlistview.h"
#include "addcontactview.h"
#include "viewcontactview.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showView(QWidget *widget);

signals:
    void switchedToContactListView();

private:
    void setupUi();
    void createActions();
    void createMenus();

    QStatusBar *statusBar;
    QToolBar *toolBar;
    QSplitter *splitter;
    ContactListView *contactListView;
    AddContactView *addContactView;
    ViewContactView *viewContactView;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *contactAction;
    QAction *addContactAction;
};

#endif // MAINWINDOW_H