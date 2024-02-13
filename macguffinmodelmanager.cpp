#include "macguffin.h"
#include "macguffindelegate.h"
#include "macguffinmodelmanager.h"

MacGuffinModelManager::MacGuffinModelManager(QListView *view) :
    QObject(nullptr),
    m_model(this),
    m_delegate(new MacGuffinDelegate(view, this))
{
    view->setModel(&m_model);
    view->setItemDelegate(m_delegate.get());
}

void MacGuffinModelManager::appendItem(const MacGuffin &datum)
{
    int rowNumber = m_model.rowCount();
    m_model.insertRows(rowNumber, 1);
    QModelIndex index = m_model.index(rowNumber, 0);
    m_model.setData(index, QVariant::fromValue(datum));
    static_cast<QListView*>(m_delegate->parent())->openPersistentEditor(index);
}

void MacGuffinModelManager::onRemoveItemRequested(int row)
{
    m_model.removeRow(row);

    for (int i = row; i < m_model.rowCount(); ++i) {
        QModelIndex index = m_model.index(i, 0);
        m_model.setData(index, QVariant(), MacGuffinDataModel::RefreshRowNumberRole);
    }
}

void MacGuffinModelManager::onAddItemAboveRequested(int row)
{
    m_model.insertRows(row, 1);
    QModelIndex index = m_model.index(row, 0);
    m_model.setData(index, QVariant::fromValue(MacGuffin(false, "added", 50)));
    static_cast<QListView*>(m_delegate->parent())->openPersistentEditor(index);

    for (int i = row + 1; i < m_model.rowCount(); ++i) {
        QModelIndex index = m_model.index(i, 0);
        m_model.setData(index, QVariant(), MacGuffinDataModel::RefreshRowNumberRole);
    }
}

void MacGuffinModelManager::onMoveRowUpRequested(int row)
{
    if (row <= 0) {
        return;
    }

    QVariant temp = m_model.index(row - 1, 0).data();
    m_model.setData(m_model.index(row - 1, 0), m_model.index(row, 0).data());
    m_model.setData(m_model.index(row, 0), temp);
}

void MacGuffinModelManager::onMoveRowDownRequested(int row)
{
    if (row >= m_model.rowCount() - 1) {
        return;
    }

    QVariant temp = m_model.index(row, 0).data();
    m_model.setData(m_model.index(row, 0), m_model.index(row + 1, 0).data());
    m_model.setData(m_model.index(row + 1, 0), temp);
}
