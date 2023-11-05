#include "CursorLine.h"
OverlayFactoryFilter::OverlayFactoryFilter(QWidget *p, QObject *parent) : QObject(parent) {
//OverlayFactoryFilter::OverlayFactoryFilter(QTreeWidget *p, QObject *parent) : QObject(parent) {
    if (!m_overlay) m_overlay = new CursorLine;
    m_overlay->setParent(p);

    m_overlay->show();

}
