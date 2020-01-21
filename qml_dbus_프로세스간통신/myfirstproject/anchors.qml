import QtQuick 2.0

Item {
    width: 640
    height: 480
    Rectangle
    {
        anchors.fill: parent
        color:"gray"
    }
    Rectangle
    {
        width:text1.paintedWidth + text2.paintedWidth//paintedwidth를 사용해야 실제로 그려지는 넓이로 구현이 가능 합니다.
        //아래처럼 텍스트의 넓이를 넓게 잡아 놓아도 실제로 그려지능 만큼만 설정이 가능합니다.
        anchors.horizontalCenter:parent.horizontalCenter

        Text
        {
            id: text1
            //텍스트의 넓이에서의 가운데 정렬
            //부모의 넓이 이므로 부모의 넓이의 가운데 정렬
            text: "걸음:"
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                //border.color: "red"
            }

        }
        Text
        {
            id: text2
            text: "100000000000"
            height:text1.paintedHeight
            width:500
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 17
            anchors.left: text1.right//text1의 오른쪽에 위치하도록 설정
            anchors.leftMargin:5
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                //border.color: "red"
            }
        }
    }

    Rectangle
    {
        id:rect1
        width:100
        height:100
        anchors.centerIn: parent
        color:"green"
        Text {
            id: res1_text1
            text: qsTr("rect1_text1")
            anchors.centerIn: parent
        }
    }

}
