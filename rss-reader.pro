# Add more folders to ship with the application, here
folder_01.source = qml/rss-reader
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

CONFIG += c++11

QT += network xml testlib

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += src/main.cpp \
    src/core.cpp \
    src\news_feed_provider_interface.cpp \
    src/rss_item.cpp \
    src/rss_channel.cpp \
    src/rss_news_feed_provider.cpp \
    src/list_model.cpp \
    src/providers_manager.cpp \
    src/rss_news_providers_test.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

INCLUDEPATH += src\
DEPENDPATH += $$INCLUDEPATH

HEADERS += \
    src/core.h \
    src/rss_item.h \
    src/rss_channel.h \
    src/news_feed_provider_interface.h \
    src/rss_news_feed_provider.h \
    src/list_model.h \
    src/abstract_list_item.h \
    src/providers_manager.h \
    src/rss_news_providers_test.h

OTHER_FILES += \
    qml/rss-reader/RssChannelViewDelegate.qml \
    qml/rss-reader/RssItemViewDelegate.qml \
    qml/rss-reader/ScrollIndicator.qml



