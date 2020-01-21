import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    width: 640
    height: 480
    objectName: "screen1"//이전화면에 대한 정보를 얻기위해 설정하는 값

    Component.onCompleted: {//화면이 집입되고 item이 생성될때 처음으로 불려지는 함수
        console.log("screen1  Component.onCompleted")        
        testData.text = "screen1 Data"//화면이 집입되고 id가 testData인 텍스트를 변경 시킨다.
    }
    Component.onDestruction: {
        console.log("screen1 Component.onDestroyed")
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

    Rectangle//배경 색을 지정하는 부분
    {
        anchors.fill: parent
        color:"green"
    }
    Text
    {
        id:testData
        anchors.horizontalCenter: parent.horizontalCenter
        text:"screen1 testData"
        font.pixelSize: 30
        font.bold: true
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
        id:nextButton
        anchors.top:testText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text:"go next screen"
        onClicked: {
             customPopup.openCustomTwoButtonPopup("screen2 popup","go screen2","go previous")
             //stack에 메인화면 두번째화면 세번째 화면이 쌓이게 된다.
        }
    }
    Button
    {
        id:previousButton
        anchors.top:testText.bottom
        anchors.right: nextButton.left
        anchors.rightMargin: 30
        text:"open popup"
        onClicked: {
            console.log("pop screen1")
            stackView.pop();//이전화면을 호출하기위해 stack의 제일 위에 화면을 밖으로 빼주어 첫화면을 보여준다.
        }
    }
}
