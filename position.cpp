#include "position.h"

#include <QDebug>

Position::Position(QObject *parent) : QObject(parent)
  ,m_available(false), m_cold(true)
{
    m_source = QGeoPositionInfoSource::createDefaultSource(0);
    if( m_source ) {
        m_source->setUpdateInterval(1000);
        m_source->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        connect(m_source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(m_warmUp(QGeoPositionInfo)));
        m_source->startUpdates();
        m_setAvailable(true);
    }
    else
    {
        qDebug() << "No GeoPosition source available";
    }
}

void Position::m_warmUp(QGeoPositionInfo geoInfo)
{
    int secLimit = -10;
    QDateTime now = QDateTime::currentDateTime();
    qint64 timeDistance = now.secsTo(geoInfo.timestamp().toLocalTime());
    if(timeDistance < secLimit) {
        qDebug() << "Timestamp older than " << secLimit << " secs... ignoring";
    } else {
        connect(m_source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(m_newGeoInfo(QGeoPositionInfo)));
        disconnect(m_source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(m_warmUp(QGeoPositionInfo)));
        m_setCold(false);
    }
}

void Position::m_newGeoInfo(QGeoPositionInfo geoinfo)
{
    qDebug() << "lat: " << geoinfo.coordinate().latitude() << " lon: " << geoinfo.coordinate().longitude();
    emit geoInfoChanged(geoinfo);
}

QGeoCoordinate Position::coordinate()
{
    return m_source->lastKnownPosition().coordinate();
}

bool Position::available()
{
    return m_available;
}
void Position::m_setAvailable(bool val)
{
    if(m_available != val){
        m_available = val;
        emit availableChanged(m_available);
    }
}

bool Position::cold()
{
    return m_cold;
}

void Position::m_setCold(bool val)
{
    if(m_cold != val) {
        m_cold = val;
        emit coldChanged(m_cold);
    }
}
