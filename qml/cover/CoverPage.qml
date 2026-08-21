import QtQuick 2.2
import Sailfish.Silica 1.0

CoverBackground {
    Label {
        id: label
        anchors.centerIn: parent
        text: position.cold ? qsTr("Waiting for proper GPS fix")
                            : qsTr("Hello coordinates...")
    }

}
