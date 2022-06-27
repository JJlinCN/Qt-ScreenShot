import QtQuick
import QtQuick.Controls as QQC
import Qt.labs.platform



Item {

    Column {
        id: leftside
        height: parent.height
        //width采用的是组件内部的隐式大小
        Grid {

            id: grid

            padding: 15
            spacing: 15
            columns: 2

            //裁剪图片
            QQC.Button{
                id:shotImg
                width: 40
                height: 40
                icon.source: "qrc:/icons/cut.png"
            }

            QQC.Button{
                id:cutImgConfirm
                width: 40
                height: 40
                visible: false
                Text{
                    anchors.centerIn: parent
                    text: qsTr("OK")
                }
            }
            //画笔
            QQC.Button {
                id: painter

                width: 40
                height: 40
                icon.source: "qrc:/icons/paint.png"
            }

            //文本
            QQC.Button {
                id: text

                width: 40
                height: 40
                icon.source: "qrc:/icons/draw-text.png"
            }

            //画框
            QQC.Button {
                id: drawframe
                icon.source: "qrc:/icons/rectangle.png"
                width: 40
                height: 40
                onClicked:drawMenu.popup(0,40)
                    QQC.Menu {
                    id:drawMenu
                    QQC.MenuItem {
                            text: qsTr("Rectangle")
                            icon.source: "qrc:/icons/rectangle.png"
                    }
                    QQC.MenuItem {
                            text: qsTr("circle")
                            icon.source: "qrc:/icons/draw-ellipse.png"
                    }

                    QQC.MenuItem {
                        text: qsTr("Line(L)")
                        icon.source: "qrc:/icons/line.png"
                    }
                }
            }

            //马赛克
            QQC.Button{
                id:btn_mosaic
                icon.source: "qrc:/icons/mosaic.png"
                width: 40
                height: 40
            }

            //滤镜
            QQC.Button{
                id:btn_filter
                icon.source: "qrc:/icons/filter.png"
                width: 40
                height: 40
            }

            //撤销
            QQC.Button{
                id:undo
                icon.source: "qrc:/icons/revoke.png"
                width: 40
                height: 40
            }

            //清除
            QQC.Button{
                id:clear
                icon.source: "qrc:/icons/clear.png"
                width: 40
                height: 40
            }
        }

        //画笔颜色选择
        Row {
            id: selectColor

            padding: 10

            Image {
                source: "qrc:/icons/color.png"
            }

            ColorDialog {
                id: colordialog
                onAccepted: {
                    rect.color = color
                }
            }

            QQC.Button {
                id: colorbutton
                width: 80
                height: 30

                Rectangle {
                    id: rect
                    width: colorbutton.width - 20
                    height: colorbutton.height - 10
                    anchors.centerIn: colorbutton
                }
                onClicked: {
                    colordialog.open()
                }
            }
        }

        //画笔宽度3
        Row {
            id: width

            padding: 10
            Image {
                width: 24
                height: 24
                source: "qrc:/icons/width.png"
            }
            QQC.SpinBox {
                id: paintSpinBox
                width: colorbutton.width
                height: 30
                from: 1
                to: 32
                value:1
                //                decimals : 3
            }
        }

        //文字颜色选择
        Row {
            id: textcolor

            padding: 10

            Image {
                source: "qrc:/icons/textcolor.png"
            }

            ColorDialog {
                id: textcolordialog
                onAccepted: {
                    rect1.color = color
                }
            }

            QQC.Button {
                id: textcolorbutton
                width: 80
                height: 30

                Rectangle {
                    id: rect1
                    width: textcolorbutton.width - 20
                    height: textcolorbutton.height - 10
                    anchors.centerIn: textcolorbutton
                }
                onClicked: {
                    textcolordialog.open()
                }
            }
        }

        //字号大小
        Row {
            id: fontsize

            padding: 10
            Image {
                width: 24
                height: 24
                source: "qrc:/icons/fontsize.png"
            }
            QQC.SpinBox {
                id: fontSpinBox
                width: textcolorbutton.width
                height: textcolorbutton.height
                stepSize: 10
                from: 10
                to: 320
            }
        }
    }
    QQC.ScrollView {
        id: scrollview
        anchors.left: leftside.right
        anchors.leftMargin: 20
        width: parent.width - leftside.width
        height: parent.height
        focus: true
        clip:false
        contentChildren:Image {
            id: scrollimg
            cache: false
            fillMode: Image.PreserveAspectFit
            WheelHandler{
                acceptedModifiers: Qt.ControlModifier //按下controls键才响应滚轮事件
                property: "scale" //设置滚动缩放
            }
            DragHandler{ //设置可拖拽
            }
          }
        }
    Connections {
        target: capture
        function onCallImageChanged() {
            scrollimg.source = ""
            scrollimg.source = "image://screen"
        }
    }
}
