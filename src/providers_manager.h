#ifndef PROVIDERS_MANAGER_H
#define PROVIDERS_MANAGER_H


#include "rss_item.h"
#include "rss_channel.h"
#include "list_model.h"

#include <QObject>
#include <QThread>
#include <QSettings>


class NewsFeedProviderInterface;
class RssChannel;
class QTimer;

class ProvidersManager : public QObject
{
    Q_OBJECT
public:
    explicit ProvidersManager(QObject* parent = 0);
    ProvidersManager(const ProvidersManager&) = delete;
    ProvidersManager& operator=(const ProvidersManager&) = delete;
    ~ProvidersManager();

signals:
    void updateFeed();
    void urlIsNotValid();

public slots:
    Q_INVOKABLE void addNewUrl(const QString& newUrl);
    Q_INVOKABLE ListModel* getChannels() const;
    Q_INVOKABLE ListModel* getFeed() const;
    Q_INVOKABLE void showFeed(const QString& url);

private slots:
    void updateFeeds();
    void onGotFeed(const RssChannel& channel);

private:
    void fetchNextFeed();
    void addNewProvider(const QString& url);

private:
    QThread                           m_backgroundThread;
    QHash<QString, NewsFeedProviderInterface*> m_providers;
    QHash<QString, RssChannel>        m_channels;
    QList<NewsFeedProviderInterface*> m_providersToUpdate;
    bool                              m_isBusy;
    QSettings*                        m_settings;
    QTimer*                           m_timer;
    ListModel*                        m_channelsModel;
    ListModel*                        m_feedModel;
};

#endif // PROVIDERS_MANAGER_H
