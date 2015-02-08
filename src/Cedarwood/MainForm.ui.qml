import QtQuick 2.4
import QtQml.Models 2.1

Rectangle {
    id: mainRect
    width: 800
    height: 600
    visible: true

    property int listViewActive: 0

    Rectangle {
        id: banner
        height: 80
        anchors.top: parent.top
        width: parent.width
        color: "#000000"

        Image {
            id: arrowLeft
            source: "/resources/left.png"
            anchors.left: banner.left
            anchors.leftMargin: 20
            anchors.verticalCenter: banner.verticalCenter
            visible: (root.currentIndex == 1)

            MouseArea {
                anchors.fill: parent
                onClicked: listViewActive = 1;
            }
        }

        Image {
            id: arrowRight
            source: "/resources/left.png"
            anchors.left: banner.right
            anchors.leftMargin: -100
            anchors.verticalCenter: banner.verticalCenter
            visible: (root.currentIndex != 1)

            MouseArea {
                anchors.fill: parent
                onClicked: listViewActive = 0;
            }
        }

        Item {
            id: textItem
            width: stocText.width + qtText.width
            height: stocText.height + qtText.height
            anchors.horizontalCenter: banner.horizontalCenter
            anchors.verticalCenter: banner.verticalCenter

            Text {
                id: stocText
                anchors.verticalCenter: textItem.verticalCenter
                color: "#ffffff"
                font.family: "Abel"
                font.pointSize: 40
                text: "Cedarwood"
            }
            Text {
                id: qtText
                anchors.verticalCenter: textItem.verticalCenter
                anchors.left: stocText.right
                color: "#5caa15"
                font.family: "Abel"
                font.pointSize: 40
                text: "Qt"
            }
        }
    }

    ListView {
        id: root
        width: parent.width
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250
        focus: false
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        currentIndex: listViewActive == 0 ? 1 : 0
        onCurrentIndexChanged:
            if (currentIndex == 1)
                listViewActive = 0;

        StockModel {
            id: stock
            stockId: listView.currentStockId
            stockName: listView.currentStockName
        }

        model: ObjectModel {
            StockListView {
                id: listView
                width: root.width
                height: root.height - 15
            }
            StockView {
                id: stockView
                width: root.width
                height: root.height - 15
                stocklist: listView
                stock: stock
            }
        }
    }
}
