#include "ui/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setupUi();

    // Connect to the signals of the child widgets
    connect(contactListView, &ContactListView::switchView, this, &MainWindow::showView);

}

MainWindow::~MainWindow() {
    // Destructor implementation (if needed)
}

void MainWindow::showView(QWidget *widget) {
    if (widget) {
        // Remove the current widget from the splitter
        if (splitter->count() > 0) {
            QWidget *currentWidget = splitter->widget(0);
            splitter->replaceWidget(0, widget);
            currentWidget->deleteLater();
        } else {
            splitter->addWidget(widget);
        }
    } else {
        // Handle the case where the QWidget pointer is null
        qWarning("Received a null QWidget pointer");
    }
}

void MainWindow::setupUi() {
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    splitter = new QSplitter(this);
    setCentralWidget(splitter);

    contactListView = new ContactListView(this);
    splitter->addWidget(contactListView);
}
