#ifndef MACGUFFINDELEGATE_H
#define MACGUFFINDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class MacGuffin;
class MacGuffinModelManager;

class MacGuffinDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MacGuffinDelegate(QObject *parent, MacGuffinModelManager *manager);
    ~MacGuffinDelegate();

    // API for the MVC system.
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private slots:
    void onEditorReadyToCommit(QWidget *editor);

private:
    MacGuffinModelManager *m_manager;
};

#endif
