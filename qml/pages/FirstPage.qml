import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        PullDownMenu {
            enabled: ! position.cold
            MenuItem {
                text: qsTr("Show LiveView")
                onClicked: pageStack.animatorPush(Qt.resolvedUrl("LiveView.qml"))
            }
        }
        contentHeight: column.height

        Column {
            id: column
            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("GPS tail")
            }
            Label {
                id: label
                x: Theme.horizontalPageMargin
                text: position.available ?
                          position.cold ?
                              qsTr("Waiting for proper GPS fix")
                              : qsTr("Hello coordinates...")
                          : qsTr("GPS not available")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
                opacity: 1.0
                Behavior on opacity { FadeAnimator {duration: 500} }
                Timer {
                    interval: 500
                    running: position.cold
                    repeat: true
                    onTriggered: label.opacity = label.opacity === 0.0 ? 1.0 : 0.0
                    onRunningChanged: label.opacity = 1.0

                }
            }
        }
    }
}
