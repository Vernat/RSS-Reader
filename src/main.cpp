#include "core.h"

#include "rss_news_providers_test.h"
#include <QtGui/QGuiApplication>
#include <QtTest/QTest>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    RssNewsProvidersTest test1;
    QTest::qExec(&test1);

    Core* core = new Core();

    int r = app.exec();


    delete core;

    return r;
}
