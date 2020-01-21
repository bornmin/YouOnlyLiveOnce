import QtQuick 2.0
import QtQuick.Controls 2.0
import "./style" 1.0

Item {
    width: 640
    height: 480

     TESTSTYLE //qmldir파일에 등록한 TESTSTYLE를 실제 사용할 qml에 객체로 만들어 준다.
     {
         id:testStyle //스타일 파일을 id로 등록
     }

     Image
     {
         x:testStyle.rectImagePauseButton.x//teststyle.qml 파일 안의 변수이름이 rectImagePauseButton인 변수의 x로 선언되어 있는 값을 가저온다.
         y:testStyle.rectImagePauseButton.y//teststyle.qml 파일 안의 변수이름이 rectImagePauseButton인 변수의 y로 선언되어 있는 값을 가저온다.
         width:testStyle.rectImagePauseButton.width//teststyle.qml 파일 안의 변수이름이 rectImagePauseButton인 변수의 width로 선언되어 있는 값을 가저온다.
         height:testStyle.rectImagePauseButton.height//teststyle.qml 파일 안의 변수이름이 rectImagePauseButton인 변수의 height로 선언되어 있는 값을 가저온다.
         source:"./image/" + testStyle.imagePauseButton //teststyle.qml 파일 안의 변수이름이 imagePauseButton인 변수의 값을 가져온다.
     }

     Image
     {
         x:testStyle.rectImagePlayButton.x
         y:testStyle.rectImagePlayButton.y
         width:testStyle.rectImagePlayButton.width
         height:testStyle.rectImagePlayButton.height
         source:"./image/" + testStyle.imagePlayButton
     }



}
