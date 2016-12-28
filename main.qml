import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import ZHWidget 1.0
import QtQuick.Window 2.2

Window {
    visible:true
    visibility: Window.FullScreen
    width:Screen.width
    height:Screen.height

    AppWorkArea{
        id:mainWindow
        objectName: "mainWin"
        anchors.fill: parent

        property double viewScaleX: width / 480
        property double viewScaleY: height / 800
        property double viewScale:{
            if(width / 480 < height / 800){
                return width / 480
            }else{
                return height / 800
            }
        }





    }
}
