#ifndef MACGUFFINMODELMANAGER_H
#define MACGUFFINMODELMANAGER_H

#include "macguffindelegate.h"
#include "macguffindatamodel.h"
#include <QListView>
#include <QObject>

class MacGuffinModelManager : public QObject
{
    Q_OBJECT

public:
    MacGuffinModelManager(QListView *view);

    MacGuffinDataModel &model() { return m_model; }
    const MacGuffinDataModel &model() const { return m_model; }
    
    void appendItem(const MacGuffin &datum);

public slots:
    void onRemoveItemRequested(int row);
    void onAddItemAboveRequested(int row);
    void onMoveRowUpRequested(int row);
    void onMoveRowDownRequested(int row);

private:
    QListView *m_view;
    MacGuffinDataModel m_model;
    std::unique_ptr<MacGuffinDelegate> m_delegate;
};

#endif
