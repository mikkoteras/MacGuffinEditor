#ifndef MACGUFFINEDITOR_H
#define MACGUFFINEDITOR_H

#include "macguffin.h"
#include <QObject>
#include <QSpinBox>
#include <QWidget>

class MacGuffinEditor : public QWidget
{
    Q_OBJECT

public:
    MacGuffinEditor(QWidget *parent, int row);

    MacGuffin getData() const;
    void setData(int row, const MacGuffin &data);

    void paintEvent(QPaintEvent *) override;

signals:
    void editorReadyToCommit(QWidget *editor);
    void removeItemRequested(int row);
    void addItemAboveRequested(int row);
    void moveRowUpRequested(int row);
    void moveRowDownRequested(int row);

private slots:
    void onNumberValueChanged(int value);

private:
    int m_row;
    MacGuffin m_data;

    QGridLayout *m_layout;
    QLabel *m_label;
    QSpinBox *m_numberEdit;
    QPushButton *m_addItemAboveButton;
    QPushButton *m_upButton;
    QPushButton *m_downButton;
    QPushButton *m_removeButton;
};

#endif
