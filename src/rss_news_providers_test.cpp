#include "rss_news_providers_test.h"
#include "rss_news_feed_provider.h"

RssNewsProvidersTest::RssNewsProvidersTest(QObject* parent)
    : QObject(parent)
    , m_provider1(nullptr)
    , m_channel1("")
    , m_provider2(nullptr)
    , m_channel2("")
{

}

void RssNewsProvidersTest::onGotFeed(const RssChannel &channel)
{
    m_channel1 = channel;
}

void RssNewsProvidersTest::initTestCase()
{
    m_provider1 = new RssNewsFeedProvider("wrong url", this);

    connect(m_provider1, SIGNAL(gotFeed(const RssChannel&)),
            this,        SLOT(onGotFeed(const RssChannel&)));

    m_provider1->updateFeed();
    while (m_channel1.url().isEmpty())
        QTest::qWait(250);

    m_provider2 = new RssNewsFeedProvider("url2", this);
    QByteArray xml("<?xml version=\"1.0\" encoding=\"utf-8\"?>" \
                     "<rss version=\"2.0\">" \
                       "<channel>" \
                        " <title>Яндекс.Новости: Главные новости</title>" \
                         "<link>http://news.yandex.ru/index.html</link>" \
                         "<description>" \
                         "  Первая в России служба автоматической обработки и систематизации новостей. Сообщения ведущих российских и мировых СМИ. Обновление в режиме реального времени 24 часа в сутки." \
                         "</description>" \
                         "<image>" \
                         "  <url>http://company.yandex.ru/i/50x23.gif</url>" \
                         "  <link>http://news.yandex.ru/index.html</link>" \
                         "  <title>Яндекс.Новости: Главные новости</title>" \
                         "</image>" \
                         "<lastBuildDate>19 Jan 2015 08:53:05 +0300</lastBuildDate>" \
                         "<item>" \
                         "  <title>Сегодня православные отмечают Крещение Господне</title>" \
                         "  <link>http://news.yandex.ru/yandsearch?cl4url=www.regnum.ru%2Fnews%2Fsociety%2F1885562.html</link>" \
                         "  <description>19 января православные христиане отмечают один из 12 главных церковных праздников — Крещение Господне, или Богоявление. В этот день вспоминают крещение Иисуса Христа в реке Иордан. В этот день Патриарх Кирилл проведет в московском Богоявленском соборе в Елохове торжественную литургию.</description>" \
                         "  <pubDate>19 Jan 2015 08:40:00 +0300</pubDate>" \
                         "  <guid>http://news.yandex.ru/yandsearch?cl4url=www.regnum.ru%2Fnews%2Fsociety%2F1885562.html</guid>" \
                         "</item>" \
                         "<item>" \
                         "  <title>Сегодня истекает срок погашения долгов перед Капелло</title>" \
                         "  <link>http://news.yandex.ru/yandsearch?cl4url=sport.rbc.ru%2Fnews%2F247512%2F</link>" \
                         "  <description>В понедельник 19 января заканчивается срок предписания РФС о погашении долгов по зарплате перед главным тренером сборной России Фабио Капелло. Отметим, сумма долга перед итальянцем составляет около 400 миллионов рублей.</description>" \
                         "  <pubDate>19 Jan 2015 08:01:00 +0300</pubDate>" \
                         "  <guid>http://news.yandex.ru/yandsearch?cl4url=sport.rbc.ru%2Fnews%2F247512%2F</guid>" \
                         " </item>" \
                         " <item>" \
                         "  <title>Заморозку пенсионных накоплений предложено продлить до 2018 года</title>" \
                         "  <link>http://news.yandex.ru/yandsearch?cl4url=lenta.ru%2Fnews%2F2015%2F01%2F19%2Fpension%2F</link>" \
                         "  <description>Подготовленный Минэкономразвития России антикризисный план, который будет рассматриваться в понедельник, 19 января, на совещании у премьер-министра Дмитрия Медведева, предусматривает продление заморозки пенсионных накоплений и возобновлении дискуссии об увеличении пенсионного возраста.</description>" \
                         "  <pubDate>19 Jan 2015 05:14:41 +0300</pubDate>" \
                         "  <guid>http://news.yandex.ru/yandsearch?cl4url=lenta.ru%2Fnews%2F2015%2F01%2F19%2Fpension%2F</guid>" \
                         "</item>" \
                       "</channel>"\
                       "</rss>");
    m_channel2 = m_provider2->parseData(xml);

}

void RssNewsProvidersTest::checkEmptyChannelTest()
{
    QCOMPARE(m_channel1.items().size(), 0);
}

void RssNewsProvidersTest::checkParsingXML()
{
    QCOMPARE(m_channel2.url(), QString("url2"));
    QCOMPARE(m_channel2.imageSource(), QString("http://company.yandex.ru/i/50x23.gif"));
    QCOMPARE(m_channel2.items().size(), 3);
    RssItem item = m_channel2.items().first();
    QCOMPARE(item.link(), QString("http://news.yandex.ru/yandsearch?cl4url=www.regnum.ru%2Fnews%2Fsociety%2F1885562.html"));
    item = m_channel2.items().last();
    QCOMPARE(item.description(), QString("Подготовленный Минэкономразвития России антикризисный план, который будет рассматриваться в понедельник, 19 января, на совещании у премьер-министра Дмитрия Медведева, предусматривает продление заморозки пенсионных накоплений и возобновлении дискуссии об увеличении пенсионного возраста."));
    QCOMPARE(item.title(), QString("Заморозку пенсионных накоплений предложено продлить до 2018 года"));
}

void RssNewsProvidersTest::cleanupTestCase()
{
    delete m_provider1;
    delete m_provider2;
}
