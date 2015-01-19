#ifndef RSS_NEWS_PROVIDERS_TEST_H
#define RSS_NEWS_PROVIDERS_TEST_H

#include <QtTest/QtTest>
#include <QObject>
#include "rss_news_feed_provider.h"


class RssNewsProvidersTest : public QObject
{
    Q_OBJECT
public:
    explicit RssNewsProvidersTest(QObject* parent = 0);

public slots:
    void onGotFeed(const RssChannel& channel);

private slots:
    void initTestCase();
    void checkEmptyChannelTest();
    void checkParsingXML();
    void cleanupTestCase();

private:
    RssNewsFeedProvider*  m_provider1;
    RssChannel            m_channel1;
    RssNewsFeedProvider*  m_provider2;
    RssChannel            m_channel2;
};

#endif // RSS_NEWS_PROVIDERS_TEST_H
