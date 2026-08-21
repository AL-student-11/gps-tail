import QtQuick 2.2
import Sailfish.Silica 1.0
import MapboxMap 1.0

Page
{
    id: page

    MapboxMap {
        id: map
        anchors.fill: parent
        center: position.coordinate
        zoomLevel: 12.0
        minimumZoomLevel: 0
        maximumZoomLevel: 20
        pixelRatio: 3.0
        apiBaseUrl: "127.0.0.1:8553"
        accessToken: ""
        cacheDatabaseMaximalSize: 20*1024*1024
        cacheDatabasePath: "/tmp/mbgl-cache.db"
        styleUrl: "127.0.0.1:8553/v1/mbgl/style?style=osmbright-car"

        MapboxMapGestureArea {
            id: mouseArea
            map: map
            activeClickedGeo: true
            activeDoubleClickedGeo: true
            activePressAndHoldGeo: true

            onClicked: console.log("Click: " + mouse)
            onDoubleClicked: console.log("Double click: " + mouse)
            onPressAndHold: console.log("Press and hold: " + mouse)

            onClickedGeo: console.log("Click geo: " + geocoordinate + " sensitivity: " + degLatPerPixel + " " + degLonPerPixel)
            onDoubleClickedGeo: console.log("Double click geo: " + geocoordinate + " sensitivity: " + degLatPerPixel + " " + degLonPerPixel)
            onPressAndHoldGeo: console.log("Press and hold geo: " + geocoordinate + " sensitivity: " + degLatPerPixel + " " + degLonPerPixel)

        }

        Component.onCompleted: {
            addSourcePoints("tailPosition", positionList.coordinates)
            addImagePath("positionImage", Qt.resolvedUrl("/usr/share/harbour-mrsafe/icons/position/position@1.00.png"))
            addLayer("tailLayer", {"type": "symbol", "source": "tailPosition"})
            setLayoutProperty("tailLayer", "icon-image", "positionImage")
            setLayoutProperty("tailLayer", "icon-size", 1.0 / map.pixelRatio)
            setLayoutProperty("tailLayer", "icon-allow-overlap", true)
        }
    }

    Connections{
        target: positionList
        onCoordinatesChanged:{
            console.log("LiveView Coordinate Changed")
            map.updateSourcePoints("tailPosition", positionList.coordinates)
        }
    }
}
