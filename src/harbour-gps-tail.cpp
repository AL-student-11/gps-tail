#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

#include <sailfishapp.h>
#include <position.h>
#include <positionlist.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("org.gps-tail");
    QCoreApplication::setApplicationName("gps-tail");
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    Position position;
    PositionList positionList;

    QObject::connect(&position, &Position::geoInfoChanged, &positionList, &PositionList::addPositionInfo);
    view->rootContext()->setContextProperty("position", &position);
    view->rootContext()->setContextProperty("positionList", &positionList);

    view->setSource(SailfishApp::pathTo("qml/harbour-gps-tail.qml"));
    view->show();
    return app->exec();
}
