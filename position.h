#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QGeoPositionInfoSource>

class Position : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate NOTIFY geoInfoChanged)
    Q_PROPERTY(bool cold READ cold NOTIFY coldChanged)
    Q_PROPERTY(bool available READ available NOTIFY availableChanged())
public:
    explicit Position(QObject *parent = nullptr);
    QGeoCoordinate coordinate();
    bool cold();
    bool available();

signals:
    void geoInfoChanged(QGeoPositionInfo geoInfo);
    void coldChanged(bool);
    void availableChanged(bool);

private slots:
    void m_newGeoInfo(QGeoPositionInfo);
    void m_warmUp(QGeoPositionInfo);

private:
    QGeoPositionInfoSource *m_source;

    bool m_available;
    bool m_cold;
    void m_setAvailable(bool val);
    void m_setCold(bool);
};

#endif // POSITION_H
