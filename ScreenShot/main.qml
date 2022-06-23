import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    property int count: 0
    id: rootApp
    title: qsTr("麒麟截屏")
    width: 900
    height: 480
    minimumHeight: 480
    minimumWidth: 680
    visible: true
    header: ToolBar {
        RowLayout {
            ToolButton {
                id: button1
                icon.source: "qrc:/icons/logo.png"
                onClicked: {
                    count++
                    rootApp.hide()
                    capture.startRectShot()
                }
            }
            ToolButton {
                id: button2
                text: qsTr("全屏截图")
                //icon.source: "qrc:/icons/logo.png"
                onClicked: {
                    fullshot.show()
                    //rootApp.visible=false;
                }
            }
            ToolButton{
                id:button3
                text:qsTr("长截图")
                onClicked:{
                    LongShot.show()
                }
            }
        }
    }
    Image {
        id: captureImage
        anchors.fill: parent
    }
    Connections {
        target: capture
        function onFinishCapture() {
            captureImage.source = "file://temp/" + count + ".jpg"
            rootApp.showNormal()
        }
    }
}
