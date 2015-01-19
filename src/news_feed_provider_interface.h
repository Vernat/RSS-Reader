#ifndef NEWS_FEED_PROVIDER_INTERFACE_H
#define NEWS_FEED_PROVIDER_INTERFACE_H

#include <QObject>

class RssChannel;
class QNetworkReply;

class NewsFeedProviderInterface : public QObject
{
    Q_OBJECT
public:
    explicit NewsFeedProviderInterface(QObject* parent = 0);

signals:
    void gotFeed(const RssChannel& channel);

public slots:
    virtual void updateFeed() = 0;

protected slots:
    virtual void onFinished(QNetworkReply*) = 0;
};

#endif // NEWS_FEED_PROVIDER_INTERFACE_H
