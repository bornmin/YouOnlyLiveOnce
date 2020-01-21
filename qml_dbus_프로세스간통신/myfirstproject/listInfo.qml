import QtQuick 2.0
import QtQuick.Controls 2.0
import ConnectEvent 1.0
Item {
    width: 800
    height: 600

    ConnectEvent//클래스를 qml 타입으로 지정
    {
        id:connectEvent
    }
    Component.onCompleted: {
        testText.text = connectEvent.getListInfomation(mListClickIndex);
     }
     Component.onDestruction: {

     }

    Rectangle//배경 색을 지정하는 부분
    {
        anchors.fill: parent
        color:"green"
    }
    Text
    {
        id:testText
        anchors.centerIn: parent
        text:"screen1!!"
        font.pixelSize: 50
        font.bold: true
    }
    Button
    {
        id:previousButton
        anchors.top:testText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text:"go previous screen"
        onClicked: {
            console.log("pop screen1")
            stackView.pop();//이전화면을 호출하기위해 stack의 제일 위에 화면을 밖으로 빼주어 첫화면을 보여준다.
        }
    }
}
