import QtQuick 2.4
import QtQuick.Window 2.2

Rectangle {
    id: root
    width: 320
    height: 480
    color: "transparent"

    property var stock: null
    property var stocklist: null
    signal settingsClicked

    function update() {
        chart.update()
    }

    Rectangle {
        id: mainRect
        color: "transparent"
        anchors.fill: parent

        StockInfo {
            id: stockInfo
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 15
            height: 160
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left
            anchors.rightMargin: 20
            stock: root.stock
        }

        StockChart {
            id: chart
            anchors.bottom: Screen.primaryOrientation === Qt.PortraitOrientation ? settingsPanel.top : parent.bottom
            anchors.bottomMargin: 20
            anchors.top : Screen.primaryOrientation === Qt.PortraitOrientation ? stockInfo.bottom : parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.width - 40 : 0.6 * parent.width
            stockModel: root.stock
            settings: settingsPanel
        }

        StockSettingsPanel {
            id: settingsPanel
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            onDrawOpenPriceChanged: root.update()
            onDrawClosePriceChanged: root.update();
            onDrawHighPriceChanged: root.update();
            onDrawLowPriceChanged: root.update();
        }
    }
}
