#ifndef MACGUFFINDATAMODEL_H
#define MACGUFFINDATAMODEL_H

#include "macguffin.h"
#include <QObject>
#include <QAbstractListModel>
#include <vector>

class MacGuffinModelManager;

class MacGuffinDataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    // Role to give setData() to signal the editor widget, via
    // setEditorData(), that its row number is no longer valid
    // and needs to be reset from the QModelIndex argument.
    enum { RefreshRowNumberRole = Qt::UserRole + 1 };

    MacGuffinDataModel(MacGuffinModelManager *manager);

    MacGuffinDataModel() = delete;
    MacGuffinDataModel(const MacGuffinDataModel&) = delete;
    MacGuffinDataModel(MacGuffinDataModel&&) = delete;
    MacGuffinDataModel &operator=(MacGuffinDataModel&) = delete;
    const MacGuffinDataModel &operator=(const MacGuffinDataModel&&) = delete;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override { return m_data.size(); }
    Qt::ItemFlags flags(const QModelIndex&) const override { return Qt::ItemIsEditable | Qt::ItemIsEnabled; }

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    MacGuffinModelManager *m_manager;
    std::vector<MacGuffin> m_data;
};

#endif
