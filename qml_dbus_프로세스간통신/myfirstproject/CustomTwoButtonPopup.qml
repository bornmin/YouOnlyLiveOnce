import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Item {    
    x:0
    y:0
    width: 640
    height: 480
    visible:false

    signal button1Onclicked()//각 화면의 2버튼 팝업을 출력했을때 각 화면마다 버튼의 동작을 다르게 하도록 시그널을 설정해줌 (button1의 동작을 설저하기 위한 signal)
    signal button2Onclicked()//각 화면의 2버튼 팝업을 출력했을때 각 화면마다 버튼의 동작을 다르게 하도록 시그널을 설정해줌 (button2의 동작을 설저하기 위한 signal)
    Popup//팝업을 만들어 주기 위한 팝업 객체 선언
    {
        id:twoButtonPopup
        width: 640
        height: 480
        leftPadding: 0// popup 만들시 기본적으로 설정되는 각 영역들을 모두 없앰
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        background:Rectangle//팝업 dimming 처리를 해주시 위해서 배경화면을 검정색 약간 투명으로 설정해줌
        {
            color:"black"
            opacity:0.7//배경색의 투명도를 설정 해줌
        }
        MouseArea//팝업을 전체 화면으로 설장한 후 파란색 영역 이외의 부분을 클릭했을때 팝업이 닫히도록 설정하는 부분
        {
            anchors.fill: parent
            onClicked:
            {
                closeCustomTwoButtonPopup();
            }
        }

        Rectangle
        {
            x:(parent.width - width) / 2 //팝업의 영역이 현재 화면의 중앙에 오도록 지정
            y:(parent.height - height) / 2  //팝업의 영역이 현재 화면의 중앙에 오도록 지정
            width:400
            height:250
            color:"blue"
            MouseArea//팝업의 파란색 영역을 클릭했을때 팝업 종료 이벤트가 발생되지 안도록 선언만 시켜주는 부분
            {
                anchors.fill: parent
            }
            Text
            {
                id:popupInfo
                anchors.centerIn: parent
                text:"test popup"
                color:"black"
                font.pixelSize: 30
                font.bold:true
            }

            Button
            {
                id:button1
                anchors.bottom:parent.bottom
                anchors.left: parent.left
                width:190
                height:50
                text:"go next screen"
                onClicked:
                {
                    closeCustomTwoButtonPopup()//각 버튼을 누르면 각자의 동작을 하도록 시그널을 발생시킴
                    button1Onclicked()
                }
            }
            Button
            {
                id:button2
                anchors.bottom:parent.bottom
                anchors.left: button1.right
                anchors.leftMargin: 20
                width:190
                height:50
                text:"close"
                onClicked: {
                    closeCustomTwoButtonPopup()//각 버튼을 누르면 각자의 동작을 하도록 시그널을 발생시킴
                    button2Onclicked()
                }
            }
        }
    }
    function openCustomTwoButtonPopup(info,button1text,button2text){//각 화면의 버튼 팝업의 텍스트를 달리 주기위해서 설정하는 함수
        console.log("openCustomTwoButtonPopup info:" + info + "button1text:" + button1text + "button2text:" + button2text)
        popupInfo.text = info
        button1.text = button1text
        button2.text = button2text
        visible = true;
        twoButtonPopup.open()
    }
    function closeCustomTwoButtonPopup()
    {
        console.log("closeCustomTwoButtonPopup")
        visible = false;
        twoButtonPopup.close();
    }

}
