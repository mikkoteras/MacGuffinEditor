#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListView>
#include <QMainWindow>
#include "macguffin.h"
#include "macguffinmodelmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddRowButtonClicked();
    void onOutputDataButtonClicked();

private:
    QListView *m_view;
    MacGuffinModelManager m_manager;
    QPushButton *m_outputDataButton;
    QPushButton *m_addRowButton;
};

#endif
