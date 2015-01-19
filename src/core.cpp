#include "core.h"
#include "providers_manager.h"

#include <QSettings>
#include <QQmlContext>


Core::Core(QObject *parent)
    : QObject(parent)
    , m_gui(nullptr)
    , m_providersManager(nullptr)
{
    init();
}

Core::~Core()
{
    delete m_gui;
}

void Core::init()
{
    m_providersManager = new ProvidersManager(this);
    m_gui = new QtQuick2ApplicationViewer();
    m_gui->rootContext()->setContextProperty("Core", this);
    m_gui->rootContext()->setContextProperty("Provider", m_providersManager);
    m_gui->rootContext()->setContextProperty("ChannelsModel", m_providersManager->getChannels());
    m_gui->rootContext()->setContextProperty("FeedModel", m_providersManager->getFeed());
    m_gui->setMainQmlFile(QStringLiteral("qml/rss-reader/main.qml"));
    m_gui->showExpanded();
}







