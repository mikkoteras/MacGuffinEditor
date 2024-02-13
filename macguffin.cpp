#include "macguffin.h"

MacGuffin::MacGuffin(bool b, const QString &s, int n) :
    m_isSelected(b),
    m_stringDataMember(s),
    m_numericDataMember(n)
{
}
