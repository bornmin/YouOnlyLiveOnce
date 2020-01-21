
import QtQuick.Window 2.2
import QtQuick 2.5
import QtQuick.Controls 2.0
import ConnectEvent 1.0//등록한 클래스 타입을 import해준다.
Item {
    width: 800
    height: 600

    Component.onCompleted://view가 처음 실행될때 제일 처음으로 불려지는곳
    {

    }

    Image
    {
        id : conciergeLoadingImage
        visible:true
        x:100
        y:100
        width: 50
        height:80
        source:"./image/scrollbarimage.png"
        RotationAnimator on rotation {
            id:roationAnimator
            running: true
            loops: Animation.Infinite
            duration: 2000//2초주기
            from:0; to:360//0에서부터 360
        }//rotaion end
    }//rotaionimage end

    Image
    {
        id : conciergeLoadingImage1
        visible:true
        x:400
        y:400
        width: 50
        height:80
        source:"./image/scrollbarimage.png"
        RotationAnimator on rotation {
            id:roationAnimator1
            running: true
            loops: Animation.Infinite
            duration: 2000//2초주기
            from:360; to:0//0에서부터 360
        }//rotaion end
    }//rotaionimage end
}
