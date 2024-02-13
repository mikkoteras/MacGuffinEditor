#include "macguffindatamodel.h"

MacGuffinDataModel::MacGuffinDataModel(MacGuffinModelManager *manager) :
    m_manager(manager)
{
}

bool MacGuffinDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();

    if (role == Qt::EditRole) {
        m_data[row] = qvariant_cast<MacGuffin>(value);
        emit dataChanged(this->index(row, 0), this->index(row, 0));
        return true;
    } else if (role == MacGuffinDataModel::RefreshRowNumberRole) {
        // This might be a little unclear, so: RefreshRowNumberRole means
        // value is garbage and can be ignored. The correct value is already
        // in m_data. However, the row number is no longer correct and
        // the real value is inside index.
        emit dataChanged(this->index(row, 0), this->index(row, 0));
    }

    return false;
}

QVariant MacGuffinDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant::fromValue(m_data[index.row()]);
    if (role == Qt::SizeHintRole)
        return QVariant(QSize(200, 70));
    else
        return QVariant();
}

QVariant MacGuffinDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool MacGuffinDataModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row > m_data.size())
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);
    m_data.insert(m_data.begin() + row, count, MacGuffin());
    endInsertRows();
    return true;
}

bool MacGuffinDataModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row + count > m_data.size())
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);
    auto first = m_data.begin() + row;
    m_data.erase(first, first + count);
    endRemoveRows();
    return true;
}
