#include "macguffineditor.h"
#include <QBrush>
#include <QColor>
#include <QListView>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPen>

MacGuffinEditor::MacGuffinEditor(QWidget *parent, int row) :
    QWidget(parent),
    m_row(row)
{
    setFixedSize(QSize(400, 70));

    m_layout = new QGridLayout;
    m_layout->setContentsMargins(QMargins(5, 5, 5, 5));

    m_label = new QLabel("label");
    m_label->setFixedSize(QSize(100, 30));

    m_numberEdit = new QSpinBox;
    m_numberEdit->setRange(0, 500);
    m_numberEdit->setFixedSize(75, 30);
    connect(m_numberEdit, &QSpinBox::valueChanged, this, &MacGuffinEditor::onNumberValueChanged );

    m_addItemAboveButton = new QPushButton("Add");
    m_addItemAboveButton->setFixedSize(QSize(60, 30));
    connect(m_addItemAboveButton, &QPushButton::clicked, this, [this]() { emit addItemAboveRequested(m_row); });

    m_upButton = new QPushButton("up");
    m_upButton->setFixedSize(QSize(30, 30));
    connect(m_upButton, &QPushButton::clicked, this, [this]() { emit moveRowUpRequested(m_row); });

    m_downButton = new QPushButton("dn");
    m_downButton->setFixedSize(QSize(30, 30));
    connect(m_downButton, &QPushButton::clicked, this, [this]() { emit moveRowDownRequested(m_row); });

    m_removeButton = new QPushButton("X");
    m_removeButton->setFixedSize(QSize(30, 30));
    connect(m_removeButton, &QPushButton::clicked, this, [this]() { emit removeItemRequested(m_row); });

    m_layout->addWidget(m_label, 0, 0, 2, 1, Qt::AlignCenter);
    m_layout->addWidget(m_numberEdit, 0, 1, 2, 1, Qt::AlignCenter);
    m_layout->addWidget(m_addItemAboveButton, 0, 2, 2, 1, Qt::AlignCenter);
    m_layout->addWidget(m_upButton, 0, 3, 1, 1, Qt::AlignCenter);
    m_layout->addWidget(m_downButton, 1, 3, 1, 1, Qt::AlignCenter);
    m_layout->addWidget(m_removeButton, 0, 4, 2, 1, Qt::AlignCenter);

    setLayout(m_layout);
}

MacGuffin MacGuffinEditor::getData() const
{
    return m_data;
}

void MacGuffinEditor::setData(int row, const MacGuffin &data)
{
    m_row = row;
    m_data = data;

    m_label->setText(m_data.getString());
    m_numberEdit->setValue(data.getNumber());
}

void MacGuffinEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath path;
    path.addRoundedRect(event->rect(), 10, 10);
    painter.setPen(QPen(QColor::fromRgb(140, 150, 195), 3));
    painter.fillPath(path, QBrush(QColor::fromRgb(150, 160, 200)));
    QWidget::paintEvent(event);
}

void MacGuffinEditor::onNumberValueChanged(int value)
{
    m_data.setNumber(value);
    emit editorReadyToCommit(this);
}
