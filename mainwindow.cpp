#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_view(new QListView),
    m_manager(m_view)
{
    // Configure the view.
    m_view->setSpacing(4);

    // Initialize the rest of the window.
    m_outputDataButton = new QPushButton("Print debug data");
    m_outputDataButton->setFixedSize(150, 30);
    connect(m_outputDataButton, &QPushButton::clicked, this, &MainWindow::onOutputDataButtonClicked);

    m_addRowButton = new QPushButton("Add Item");
    m_addRowButton->setFixedSize(150, 30);
    connect(m_addRowButton, &QPushButton::clicked, this, &MainWindow::onAddRowButtonClicked);

    QWidget *centralWidget = new QWidget;
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(QMargins(5, 5, 5, 5));
    layout->addWidget(m_view, 0, 0, 1, 2);
    layout->addWidget(m_outputDataButton, 1, 0);
    layout->addWidget(m_addRowButton, 1, 1);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Populate the list with a couple of items.
    for (int i = 0; i < 10; ++i) {
        MacGuffin m(true, QString("macguffin #%1").arg(i), 5 * i);
        m_manager.appendItem(m);
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::onAddRowButtonClicked()
{
    MacGuffin m(false, QString("extra row"), 0);
    m_manager.appendItem(m);
}

void MainWindow::onOutputDataButtonClicked()
{
    MacGuffinDataModel &model = m_manager.model();

    for (int i = 0; i < model.rowCount(); ++i) {
        MacGuffin datum = qvariant_cast<MacGuffin>(model.index(i, 0).data());
        std::cout << "row " << i << ": " << datum.getString().toStdString() << " = " << datum.getNumber() << std::endl;
    }
}
