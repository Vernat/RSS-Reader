#ifndef CORE_H
#define CORE_H

#include "qtquick2applicationviewer.h"

#include <QObject>

class ProvidersManager;

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = 0);
    ~Core();

public:
    void init();

private:
    QtQuick2ApplicationViewer*        m_gui;
    ProvidersManager*                 m_providersManager;
};

#endif // CORE_H
