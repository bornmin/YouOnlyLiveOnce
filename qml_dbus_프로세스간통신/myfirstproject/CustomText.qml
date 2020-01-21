import QtQuick 2.0

Item
{
    id:customtext
    property rect rTextGeometry
    property alias text: text.text
    property bool bold: true
    property var pixelSize: 30

    Text {
        anchors.fill: parent
        id : text
        text: ""
        font.bold: bold
        font.pixelSize: pixelSize
    }

    onRTextGeometryChanged:
    {
        customtext.x = rTextGeometry.x
        customtext.y = rTextGeometry.y
        customtext.width = rTextGeometry.width
        customtext.height = rTextGeometry.height
    }
}
