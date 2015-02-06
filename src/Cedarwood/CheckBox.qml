import QtQuick 2.4

Item {
    id: button
    property bool buttonEnabled: true
    width: 30
    height: 30
    x: 5
    MouseArea {
        id: mouse
        anchors.fill: parent
        onClicked: {
            if (buttonEnabled)
                buttonEnabled = false;
            else
                buttonEnabled = true;
        }
    }
    Rectangle {
        id: checkbox
        width: 30
        height: 30
        anchors.left: parent.left
        border.color: "#999999"
        border.width: 1
        antialiasing: true
        radius: 2
        color: "transparent"
        Rectangle {
            anchors.fill: parent
            anchors.margins: 5
            antialiasing: true
            radius: 1
            color: mouse.pressed || buttonEnabled ? "#999999" : "transparent"
        }
    }
}
