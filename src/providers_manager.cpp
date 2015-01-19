#include "providers_manager.h"
#include "news_feed_provider_interface.h"
#include "rss_news_feed_provider.h"
#include "rss_channel.h"
#include "list_model.h"

#include <QSettings>
#include <QUrl>
#include <QTimer>
#include <QVariant>


const int DEFAULT_UPDATE_INTERVAL = 10;
const QString DEFAULT_PROVIDER = "RSS2_0";
const QString URLS_SECTION_NAME = "Urls";
const QString URL_PARAMETER_NAME = "Url";

ProvidersManager::ProvidersManager(QObject* parent)
    : QObject(parent)
    , m_isBusy(false)
    , m_settings(new QSettings("TopTal", "RssReader", this))
    , m_timer(new QTimer(this))
    , m_channelsModel(new ListModel(new RssChannel(""), this))
    , m_feedModel(new ListModel(new RssItem, this))
{
    auto size = m_settings->beginReadArray(URLS_SECTION_NAME);
    for (int i = 0; i < size; ++i) {
        m_settings->setArrayIndex(i);
        const auto url = m_settings->value(URL_PARAMETER_NAME).toByteArray();
        addNewProvider(url);
    }
    m_settings->endArray();
    auto updateInterval = m_settings->value("update_interval", DEFAULT_UPDATE_INTERVAL).toInt();
    m_backgroundThread.start(QThread::LowestPriority);

    m_timer->setSingleShot(true);
    m_timer->setInterval(updateInterval * 60000);
    connect(m_timer, SIGNAL(timeout()),
            this,    SLOT(updateFeeds()));

    updateFeeds();
}

ProvidersManager::~ProvidersManager()
{
    auto providers = m_providers.values();
    for (auto provider : providers) {
        delete provider;
    }
}

void ProvidersManager::addNewUrl(const QString &newUrl)
{
    QUrl url(newUrl);
    if (!url.isValid()) {
        emit urlIsNotValid();
    } else {
        const QString encoded = url.toPercentEncoding(newUrl);
        if (!m_providers.contains(encoded)) {
            m_settings->beginWriteArray(URLS_SECTION_NAME);
            m_settings->setArrayIndex(m_providers.size());
            m_settings->setValue(URL_PARAMETER_NAME, encoded);
            m_settings->endArray();
            m_settings->sync();
        }
        addNewProvider(encoded);
        m_providersToUpdate << m_providers[encoded];
        updateFeeds();
    }
}

ListModel* ProvidersManager::getChannels() const
{
    return m_channelsModel;
}

ListModel* ProvidersManager::getFeed() const
{
    return m_feedModel;
}

void ProvidersManager::showFeed(const QString &url)
{
    m_feedModel->clear();
    auto channel = m_channels.find(url);
    if (channel != m_channels.end()) {
        QList<RssItem>& items = channel->items();
        if (!items.isEmpty()) {
            QList<AbstractListItem*> itemsToAdd;
            for (auto item = items.begin(); item != items.end(); ++item) {
                itemsToAdd << &(*item);
            }
            m_feedModel->appendRows(itemsToAdd);
        }
    }
}

void ProvidersManager::updateFeeds()
{
    if (!m_isBusy) {
        m_timer->stop();
        m_backgroundThread.start();
        m_providersToUpdate << m_providers.values();
        if (!m_providersToUpdate.isEmpty()) {
            fetchNextFeed();
        }
    }
}

void ProvidersManager::fetchNextFeed()
{
    if (!m_providersToUpdate.isEmpty()) {
        auto provider = m_providersToUpdate[0];

        connect(this, SIGNAL(updateFeed()),
                provider, SLOT(updateFeed()));

        connect(provider, SIGNAL(gotFeed(const RssChannel&)),
                this,     SLOT(onGotFeed(const RssChannel&)));

        provider->updateFeed();
    } else {
        m_backgroundThread.quit();
        m_backgroundThread.wait();
        m_isBusy = false;
        m_timer->start();
    }
}

void ProvidersManager::addNewProvider(const QString& url)
{
    NewsFeedProviderInterface* provider = new RssNewsFeedProvider(url);
    provider->moveToThread(&m_backgroundThread);
    m_providers.insert(url, provider);
}

void ProvidersManager::onGotFeed(const RssChannel& channel)
{
    auto provider = m_providersToUpdate.takeFirst();

    disconnect(this, SIGNAL(updateFeed()),
               provider, SLOT(updateFeed()));

    disconnect(provider, SIGNAL(gotFeed(const RssChannel&)),
               this,     SLOT(onGotFeed(const RssChannel&)));

    if (channel.isOkToShow()) {
        m_channels.insert(channel.url(), channel);
        const auto index = m_channelsModel->getIdIndex(channel.url());
        if (index != -1) {
            m_channelsModel->removeRow(index);
            m_channelsModel->insertRow(index, &(*m_channels.find(channel.url())));
        } else {
            m_channelsModel->remove(channel.url());
            m_channelsModel->appendRow(&(*m_channels.find(channel.url())));
        }
    }
    fetchNextFeed();
}


