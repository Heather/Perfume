import QtQuick 2.4

Rectangle {
    id: root
    width: 440
    height: 160
    color: "transparent"

    property bool drawOpenPrice: openButton.buttonEnabled
    property bool drawClosePrice: closeButton.buttonEnabled
    property bool drawHighPrice: highButton.buttonEnabled
    property bool drawLowPrice: lowButton.buttonEnabled

    property string openColor: "#face20"
    property string closeColor: "#14aaff"
    property string highColor: "#80c342"
    property string lowColor: "#f30000"
    property string volumeColor: "#14aaff"

    Text {
        id: openText
        anchors.left: root.left
        anchors.top: root.top
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 19
        text: "Open"
    }

    Text {
        id: closeText
        anchors.left: root.left
        anchors.top: openText.bottom
        anchors.topMargin: 10
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 19
        text: "Close"
    }

    Text {
        id: highText
        anchors.left: root.left
        anchors.top: closeText.bottom
        anchors.topMargin: 10
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 19
        text: "High"
    }

    Text {
        id: lowText
        anchors.left: root.left
        anchors.top: highText.bottom
        anchors.topMargin: 10
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 19
        text: "Low"
    }

    Rectangle {
        height: 4
        anchors.left: root.left
        anchors.leftMargin: 114
        anchors.right: openButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: openText.verticalCenter
        color: openColor
    }

    Rectangle {
        height: 4
        anchors.left: root.left
        anchors.leftMargin: 114
        anchors.right: closeButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: closeText.verticalCenter
        color: closeColor
    }

    Rectangle {
        height: 4
        anchors.left: root.left
        anchors.leftMargin: 114
        anchors.right: highButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: highText.verticalCenter
        color: highColor
    }

    Rectangle {
        height: 4
        anchors.left: root.left
        anchors.leftMargin: 114
        anchors.right: lowButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: lowText.verticalCenter
        color: lowColor
    }

    CheckBox {
        id: openButton
        buttonEnabled: false
        anchors.verticalCenter: openText.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: 40
    }

    CheckBox {
        id: closeButton
        buttonEnabled: false
        anchors.verticalCenter: closeText.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: 40
    }

    CheckBox {
        id: highButton
        buttonEnabled: true
        anchors.verticalCenter: highText.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: 40
    }

    CheckBox {
        id: lowButton
        buttonEnabled: true
        anchors.verticalCenter: lowText.verticalCenter
        anchors.right: root.right
        anchors.rightMargin: 40
    }
}
