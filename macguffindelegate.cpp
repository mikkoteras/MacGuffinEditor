#include "macguffin.h"
#include "macguffindelegate.h"
#include "macguffineditor.h"
#include "macguffinmodelmanager.h"

MacGuffinDelegate::MacGuffinDelegate(QObject *parent, MacGuffinModelManager *manager) :
    QStyledItemDelegate(parent),
    m_manager(manager)
{
}

MacGuffinDelegate::~MacGuffinDelegate()
{
}

QSize MacGuffinDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *MacGuffinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    int row = index.row();
    MacGuffinEditor *editor = new MacGuffinEditor(parent, row);

    connect(editor, &MacGuffinEditor::editorReadyToCommit, this, &MacGuffinDelegate::onEditorReadyToCommit);
    connect(editor, &MacGuffinEditor::removeItemRequested, m_manager, &MacGuffinModelManager::onRemoveItemRequested);
    connect(editor, &MacGuffinEditor::addItemAboveRequested, m_manager, &MacGuffinModelManager::onAddItemAboveRequested);
    connect(editor, &MacGuffinEditor::moveRowUpRequested, m_manager, &MacGuffinModelManager::onMoveRowUpRequested);
    connect(editor, &MacGuffinEditor::moveRowDownRequested, m_manager, &MacGuffinModelManager::onMoveRowDownRequested);

    return editor;
}

void MacGuffinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    MacGuffinEditor *widget = static_cast<MacGuffinEditor*>(editor);
    MacGuffin macguffin = qvariant_cast<MacGuffin>(index.data());

    widget->blockSignals(true);
    widget->setData(index.row(), macguffin);
    widget->blockSignals(false);
}

void MacGuffinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const
{
    MacGuffinEditor *widget = static_cast<MacGuffinEditor*>(editor);
    model->setData(index, QVariant::fromValue(widget->getData()), Qt::EditRole);
    model->setData(index, widget->sizeHint(), Qt::SizeHintRole);
}

#include <QItemEditorFactory>
void MacGuffinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void MacGuffinDelegate::onEditorReadyToCommit(QWidget *editor) {
    emit commitData(editor);
}
