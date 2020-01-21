import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    width: 640
    height: 480
    objectName: "screen2"//이전화면에 대한 정보를 얻기위해 설정하는 값
    CustomTwoButtonPopup
    {
        id:customPopup
        onButton1Onclicked: //custom type에서 설정한 signal이 발생되었을때 동작하는 함수(button1Onclicked)
        {
            stackView.pop()
        }
        onButton2Onclicked: //custom type에서 설정한 signal이 발생되었을때 동작하는 함수(button2Onclicked)
        {
            customPopup.closeCustomTwoButtonPopup()
        }
    }
    Component.onCompleted: {
        var previousItem = stackView.get(StackView.index - 1);//stackview의 이전 index의 objectName을 가져온다.

        console.log("previousItem:" + previousItem);

        if(previousItem.objectName === "mainscreen"){//index의 objectName을 비교해서 이전 화면이 무엇인지 알수있다.
            console.log("previousItem === mainscreen")
            testData.text = "previous screen is mainscreen"
        }else if(previousItem.objectName === "screen1"){
            console.log("previousItem === screen1")
            testData.text = "previous screen is screen1"
        }else
             console.log("else!!")
    }

    Rectangle
    {
        anchors.fill: parent
        color:"blue"
    }
    Text
    {
        id:testData
        anchors.horizontalCenter: parent.horizontalCenter
        text:"screen2 testData"
        font.pixelSize: 30
        font.bold: true
    }
    Text
    {
        id:testText
        anchors.centerIn: parent
        text:"screen2!!"
        font.pixelSize: 50
        font.bold: true
    }
    Button
    {
        id:previousButton
        anchors.top:testText.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text:"open popup"
        onClicked: {
            customPopup.openCustomTwoButtonPopup("screen2 popup","go previous","close popup");
            //stackView.pop();//이전화면을 호출하기위해 stack의 제일 위에 화면을 밖으로 빼주어 두번째 화면을 보여준다.
        }
    }
}
