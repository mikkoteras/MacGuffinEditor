#ifndef MACGUFFIN_H
#define MACGUFFIN_H

#include <QAbstractListModel>
#include <QObject>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QString>
#include <QStyledItemDelegate>
#include <QWidget>
#include <memory>

class MacGuffinEditorWidget;
class MacGuffinModelManager;

class MacGuffin
{
public:
    MacGuffin() = default;
    MacGuffin(bool b, const QString &s, int n);
    MacGuffin(const MacGuffin&) = default;
    MacGuffin &operator=(const MacGuffin&) = default;

    bool getIsSelected() const { return m_isSelected; }
    void setIsSelected(bool x) { m_isSelected = x; }
    QString getString() const { return m_stringDataMember; }
    void setString(const QString &x) { m_stringDataMember = x; }
    double getNumber() const { return m_numericDataMember; }
    void setNumber(double x) { m_numericDataMember = x; }

private:
    bool m_isSelected;
    QString m_stringDataMember;
    int m_numericDataMember;
};

#endif
