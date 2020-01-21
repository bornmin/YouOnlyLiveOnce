import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import ConnectEvent 1.0//등록한 클래스 타입을 import해준다.
Item {
    width: 800
    height: 600    

    Component.onCompleted://view가 처음 실행될때 제일 처음으로 불려지는곳
    {
        console.log("connectEvent.getListSize():" + connectEvent.getListSize())
        for(var i = 0; i < connectEvent.getListSize(); i++){//리스트의 개수만큼 for문을 돌린다.
            listView.model.append({"list_text": connectEvent.getListTitle(i),//모델에 리스트의 데이터값을 넣어준다.
                                   "list_button_text": connectEvent.getListButtonText(i),
                                   "checkValue": false})//listview에 선언한 임의의 모델 안에 데이터를 넣어준다.
        }

    }
    Component {//리스트 뷰의 틀을 만든다.
        id: contactDelegate
        Item {
            width: 800
            height: 100
            CheckBox
            {
                id:checkbox
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                checked: checkValue
            }

            Text//리스트에 텍스트를 넣어주기 위해 텍스트 객체를 만들어준다.
            {
                id:listView_Text
                anchors.left: parent.left
                anchors.leftMargin: 100
                anchors.verticalCenter:  parent.verticalCenter
                text:list_text//모델에 매칭이될 변수 listview에 원하는 값을 넣기위해서 설정하는 값
            }

            Rectangle//리스트의 구분선
            {
                id:line
                width:parent.width
                anchors.bottom:parent.bottom//현재 객체의 아래 기준점을 부모객체의 아래로 잡아주어서 위치가 아래로가게 설정
                height:1
                color:"black"
            }
            MouseArea
            {
                id:listMouseArea
                anchors.fill: parent
                onClicked:
                {
                    if(listView.model.get(index).checkValue){
                        listView.model.get(index).checkValue = false
                    }else
                        listView.model.get(index).checkValue = true
                }
            }
        }
    }
    ListView {
        id:listView
        width:parent.width
        height:parent.height - 100//리스트 뷰 밑에 버튼을 만들기위해 리스트뷰의 크기를 설정하는 것
        clip:true//true 하면 리스트의 높이 보다 커도 리스트가 보여지는 것처럼 됨
                //false 하면 리스트의 높이만 큼만 deletegate가 보여짐
        model: ListModel{}//임으로 만들 모델을 넣어준다.
        delegate: contactDelegate//delegate란 리스트 한개의 틀(틀을 하나 만들어서 그것들을 여러개 붙여놓은것이 리스트 뷰이다.)
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
    Button
    {
        id:deleteButton
        width:200
        height:50;
        anchors.top: listView.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter:parent.horizontalCenter
        text:"delete"
        onClicked: {
            for(var i = listView.count - 1; i >= 0; i--){
                if(listView.model.get(i).checkValue){
                    connectEvent.deleteListItem(i);
                    listView.model.remove(i);
                }
            }
            mainWindow.qmlSignalListUpdate();//삭제 완료후 리스트가 업데이트 되었다는 것을 알려주기 위해 시그널을 호출 해준
        }
    }
    Button
    {
        id:allSelectButton
        width:200
        height:50;
        anchors.top: listView.bottom
        anchors.topMargin: 30
        anchors.left: deleteButton.right
        anchors.leftMargin: 20
        text:"all Select"
        onClicked: {
            for(var i = 0; i < listView.count; i++){
                if(!listView.model.get(i).checkValue){
                    listView.model.get(i).checkValue = true
                }

            }
        }
    }
    Button
    {
        id:backbutton
        width:200
        height:50;
        anchors.top: listView.bottom
        anchors.topMargin: 30
        anchors.right: deleteButton.left
        anchors.rightMargin: 20
        text:"back"
        onClicked: {
            stackView.pop();
        }
    }
}
