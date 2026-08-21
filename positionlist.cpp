#include "positionlist.h"
#include <QDebug>
#include <QGeoAreaMonitorSource>

PositionList::PositionList(QObject *parent) : QObject(parent)
  ,m_lenghtLimit(1000), m_length(0)
{
    connect(this, SIGNAL(coordinatesChanged()), this, SLOT(m_measure()));
    connect(this, SIGNAL(lengthChanged()), this, SLOT(m_trimList()));
}

void PositionList::addPositionInfo(QGeoPositionInfo newPosInfo)
{
    if( ! newPosInfo.isValid()) {
        return;
    }

    unsigned char tooClose = 10;
    int count = m_positionList.count();

    if(count < 1)
    {
        m_positionList.append(newPosInfo);
    }
    else
    {
        int distance = newPosInfo.coordinate().distanceTo(m_positionList.at(count-1).coordinate());
        qDebug() << "Distance to previous coordinate: " << distance << " meters";
        if( distance > tooClose)
        {
            m_positionList.append(newPosInfo);
            qDebug() << "geoinfo Count: " << m_positionList.count();
        }
        else
        {
            qDebug() << "Distance to previous coordinate less than " << tooClose << " meters... ignoring";
        }
    }

    if(count < m_positionList.count())
    {
        emit coordinatesChanged();
    }
}

void PositionList::m_trimList()
{
    if(m_length >= m_lenghtLimit)
    {
        qDebug() << "Length: " << m_length << " trail length longer than length limit removing one";
        m_positionList.removeFirst();
        emit coordinatesChanged();
    }
}

void PositionList::m_measure()
{
    if(m_positionList.count() > 1)
    {
        qreal len = 0;
        for(int i = 1; i < m_positionList.count(); i++) {
            len += m_positionList.at(i).coordinate().distanceTo(m_positionList.at(i-1).coordinate());
        }
        m_setLength(static_cast<int>(len));
    }
    qDebug() << "Trail length: " << m_length;
}

void PositionList::m_setLength(int newVal)
{
    if( newVal != m_length)
    {
        m_length = newVal;
        emit lengthChanged();
    }
}

QVariantList PositionList::coordinates()
{
    QVariantList coords;
    int i = 0;
    while (i < m_positionList.count()) {
        coords << QVariant::fromValue(m_positionList.at(i++).coordinate());
    }
    return coords;
}

QGeoCoordinate PositionList::coordinate()
{
    int last_idx = m_positionList.count() - 1;
    return m_positionList.at(last_idx).coordinate();
}
