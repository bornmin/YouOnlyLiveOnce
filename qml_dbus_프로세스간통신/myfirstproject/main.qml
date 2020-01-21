import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import "./"
import "./style" 1.0

Window {
    property bool mbImageClicked : true
    property int mCount : 0
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    function qmlSlotCommonapiBroadCastEvent(value){//서버에서 브로드캐스트 함수가 호출되면 cpp시그널이 발생되면서 이 함수가 호출이 된다.
        console.log("value: " + value);

        if(customPopup.visible){
            customPopup.closeCustomTwoButtonPopup()
        }
        else
             customPopup.openCustomTwoButtonPopup("screen2 popup","go screen2","go previous")

    }
    CustomTwoButtonPopup
    {
        id:customPopup

        onButton1Onclicked: //custom type에서 설정한 signal이 발생되었을때 동작하는 함수(button1Onclicked)
        {
            stackView.push(Qt.resolvedUrl("qrc:/screen2.qml"))
        }
        onButton2Onclicked: //custom type에서 설정한 signal이 발생되었을때 동작하는 함수(button2Onclicked)
        {
            stackView.pop();
        }
    }

    StackView
    {
        id:stackView
        anchors.fill: parent
        initialItem: Item  //제일 첫화면을 설정하는 것으로 설정을 안하면 되돌아오기가 안된다.
        {
            Rectangle//배경 색을 지정하는 부분
            {
                id:background
                anchors.fill: parent
                color:"red"
            }
            Text
            {
                id:testData
                anchors.horizontalCenter: parent.horizontalCenter
                text:"main screen testData"
                font.pixelSize: 30
                font.bold: true
            }

            Text
            {
                id:testText
                anchors.centerIn: parent
                text:"main screen"
                font.pixelSize: 50
                font.bold: true
            }
            Button
            {
                anchors.top:testText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text:"open popup"
                onClicked:
                {                     
                    stackView.push(Qt.resolvedUrl("qrc:/anchors.qml"))
                }
            }
        }
    }
}
