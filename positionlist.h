#ifndef POSITIONLIST_H
#define POSITIONLIST_H

#include <QObject>
#include <QList>
#include <QGeoPositionInfo>
#include <QVariantList>

class PositionList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList coordinates READ coordinates NOTIFY coordinatesChanged)
    Q_PROPERTY(QGeoCoordinate coordinate READ coordinate NOTIFY coordinatesChanged)

public:
    explicit PositionList(QObject *parent = nullptr);

    QVariantList coordinates();
    QGeoCoordinate coordinate();

signals:
    void coordinatesChanged();
    void lengthChanged();

public slots:
    void addPositionInfo(QGeoPositionInfo);

private slots:
    void m_measure();
    void m_trimList();


private:
    void m_setLength(int newVal);
    QList<QGeoPositionInfo> m_positionList;

    unsigned short int m_lenghtLimit;
    int m_length;

};


#endif // POSITIONLIST_H
