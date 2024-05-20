#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QSplitter>
#include "contactlistview.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showView(QWidget *widget);

private:
    void setupUi();
    void createActions();
    void createMenus();

    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QSplitter *splitter;
    ContactListView *contactListView;

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *contactAction;
    QAction *addContactAction;
};

#endif // MAINWINDOW_H
