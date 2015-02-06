import QtQuick 2.4

Rectangle {
    id: root
    width: 440
    height: 160
    color: "transparent"

    property var stock: null

    Text {
        id: stockIdText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 38
        font.weight: Font.DemiBold
        text: root.stock.stockId
    }

    Text {
        id: stockNameText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: priceChangePercentage.bottom
        anchors.right: priceChangePercentage.left
        anchors.rightMargin: 15
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 16
        elide: Text.ElideRight
        text: root.stock.stockName
    }

    Text {
        id: price
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        horizontalAlignment: Text.AlignRight
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 30
        font.weight: Font.DemiBold
        text: root.stock.stockPrice
    }

    Text {
        id: priceChange
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: price.bottom
        anchors.topMargin: 5
        horizontalAlignment: Text.AlignRight
        color: root.stock.stockPriceChanged < 0 ? "#d40000" : "#328930"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        text: root.stock.stockPriceChanged
    }

    Text {
        id: priceChangePercentage
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: priceChange.bottom
        anchors.topMargin: 5
        horizontalAlignment: Text.AlignRight
        color: root.stock.stockPriceChanged < 0 ? "#d40000" : "#328930"
        font.family: "Open Sans"
        font.pointSize: 18
        font.weight: Font.Bold
        text: Math.abs(Math.round(root.stock.stockPriceChanged/(root.stock.stockPrice - root.stock.stockPriceChanged) * 100))/100  +"%"
    }
}

