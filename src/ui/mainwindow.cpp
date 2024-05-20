#include "ui/mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUi();
    createActions();
    createMenus();

    contactListView = new ContactListView(nullptr);
    addContactView = new AddContactView(nullptr);

    // Set the initial view
    showView(contactListView);

    // Connect to the signals of the child widgets
    connect(contactAction, &QAction::triggered, [this]() { showView(contactListView); });
    connect(addContactAction, &QAction::triggered, [this]() { showView(addContactView);});
    connect(addContactView, &AddContactView::contactAdded, [this]() { showView(contactListView); });

}

MainWindow::~MainWindow() {
    // Destructor implementation (if needed)
}

void MainWindow::showView(QWidget *widget) {
    if (widget) {
        QWidget *newWidget;
        if (widget == contactListView) {
            newWidget = new ContactListView(this);
        } else if (widget == addContactView) {
            newWidget = new AddContactView(this);
        } else {
            qWarning("Received an unexpected QWidget pointer");
            return;
        }

        // Check if the widget is already in the splitter
        if(splitter->count() > 0 && splitter->widget(0) == widget) {
            // The widget is already being shown, so do nothing
            qInfo("mainwindow.cpp: the widget is already being shown");
            delete newWidget;
            return;
        }
        // Remove the current widget from the splitter
        if (splitter->count() > 0) {
            QWidget *currentWidget = splitter->widget(0);
            splitter->replaceWidget(0, newWidget);
            currentWidget->deleteLater();
        } else {
            splitter->addWidget(newWidget);
        }
    } else {
        // Handle the case where the QWidget pointer is null
        qWarning("Received a null QWidget pointer");
    }
}

void MainWindow::setupUi() {

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    splitter = new QSplitter(this);
    setCentralWidget(splitter);

    // Set minimum size for the main window
    setMinimumSize(800, 600);

    // Configure Splitter
    splitter->setStyleSheet("background-color: #ffffff;");

    // Configure Status Bar
    statusBar->showMessage(tr("Welcome."));

}

void MainWindow::createActions() {
    exitAction = new QAction(tr("&Exit"), this);
    aboutAction = new QAction(tr("&About"), this);
    contactAction = new QAction(QIcon::fromTheme("view-list-details"), tr("&Contacts"), this);
    addContactAction = new QAction(QIcon::fromTheme("contact-new"), tr("&Add Contact"), this);
}

void MainWindow::createMenus() {
    // Configure Main Menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

    // Configure Tool Bar Menu
    toolBar->setMovable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->addAction(contactAction);
    toolBar->addAction(addContactAction);
}
