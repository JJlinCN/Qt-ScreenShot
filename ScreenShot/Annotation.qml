//author：pengyueting 2020051615252
import QtQuick
import QtQuick.Controls as QQC
import Qt.labs.platform
import painteditem

Item {
    function selectImage() {
        scrollimg.source = arguments[0]
    } //选择图片

    property alias paint1: paint

    property alias img_paint: scrollimg
    property bool counter: false
    //设置画笔颜色，画笔粗细
    property string painterColor: "red"

    //设置文字颜色，文字粗细
    property string textpaintColor: "black"

    //设置剪切后的图片位置
    property int rectX: 0
    property int rectY: 0

    //剪切矩形的大小
    property int rectWidth: scrollimg.width
    property int rectHeight: scrollimg.height

    //记录剪切次数，目的是将第一次的矩形大小与位置传递
    property int rectClick: 0

    //撤销是判断最近一次操作是否是裁剪
    property bool isCut: false

    //重新设置img的大小、位置
    function reUpdate() {
        paint.destroyRect()
        rectX = 0
        rectY = 0
        rectWidth = scrollimg.width
        rectHeight = scrollimg.height
        rectClick = 0
    }

    //根据undo或clear取重新设置img特定的大小、位置
    function backImg() {
        rectX = arguments[0].x
        rectY = arguments[0].y
        rectWidth = arguments[0].width
        rectHeight = arguments[0].height
    }

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
            QQC.Button {
                id: shotImg
                width: 40
                height: 40
                icon.source: "qrc:/icons/cut.png"
                onClicked: {
                    cutImgConfirm.visible = true
                    cutImage.visible = true
                    rectClick++
                    //第一次裁剪之前需要将最开始的图片大小位置传递
                    if (rectClick == 1) {
                        paint.sendRectNumber(0, 0, scrollimg.width,
                                             scrollimg.height)
                    }
                    //剪切操作，向painteditem里的m_sequence里push_back(6)
                    paint.pressCutSequence()
                    shotImg.visible = false
                    draghandler.enabled = false //进行操作时禁用拖拽区
                }
            }

            QQC.Button {
                id: cutImgConfirm
                width: 40
                height: 40
                visible: false
                Text {
                    anchors.centerIn: parent
                    text: qsTr("OK")
                }
                onClicked: {
                    shotImg.visible = true
                    //获取剪切矩形的位置、大小
                    cutImage.cut()
                    //传递剪切矩形的位置、大小
                    paint.sendRectNumber(rectX, rectY, rectWidth, rectHeight)
                    cutImgConfirm.visible = false
                    cutImage.visible = false
                    draghandler.enabled = true
                }
            }
            //画笔
            QQC.Button {
                id: painter

                width: 40
                height: 40
                icon.source: "qrc:/icons/paint.png"
                onClicked: {
                    paint.enabled = true
                    paint.flag = 5
                    draghandler.enabled = false
                }
            }

            //文本
            QQC.Button {
                id: text

                width: 40
                height: 40
                icon.source: "qrc:/icons/draw-text.png"
                onClicked: {
                    paint.enabled = true
                    console.log("1")
                    paint.flag = 1
                    textedit.focus = true
                    draghandler.enabled = false
                }
            }

            //画框
            QQC.Button {
                id: drawframe
                icon.source: "qrc:/icons/rectangle.png"
                width: 40
                height: 40
                onClicked: drawMenu.popup(0, 40)
                QQC.Menu {
                    id: drawMenu
                    QQC.MenuItem {
                        text: qsTr("Rectangle")
                        icon.source: "qrc:/icons/rectangle.png"
                        onTriggered: {
                            drawframe.icon.source = icon.source
                            paint.enabled = true
                            paint.flag = 3
                            draghandler.enabled = false
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("circle")
                        icon.source: "qrc:/icons/draw-ellipse.png"
                        onTriggered: {
                            drawframe.icon.source = icon.source
                            paint.enabled = true
                            console.log("2")
                            paint.flag = 2
                            draghandler.enabled = false
                        }
                    }

                    QQC.MenuItem {
                        text: qsTr("Line(L)")
                        icon.source: "qrc:/icons/line.png"
                        onTriggered: {
                            drawframe.icon.source = icon.source
                            paint.enabled = true
                            paint.flag = 4
                            draghandler.enabled = false
                        }
                    }
                }
            }

            //马赛克
            QQC.Button {
                id: btn_mosaic
                icon.source: "qrc:/icons/mosaic.png"
                width: 40
                height: 40
                onClicked: {
                    mosaic.show()
                }
            }

            //滤镜
            QQC.Button {
                id: btn_filter
                icon.source: "qrc:/icons/filter.png"
                width: 40
                height: 40
                onClicked: filterMenu.popup(0, 40)
                QQC.Menu {
                    id: filterMenu
                    QQC.MenuItem {
                        text: qsTr("灰度")
                        onTriggered: {
                            capture.filterGrey()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("老照片")
                        onTriggered: {
                            capture.filterOld()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("暖调")
                        onTriggered: {
                            capture.filterWarm()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("冷调")
                        onTriggered: {
                            capture.filterCool()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("模糊")
                        onTriggered: {
                            capture.filterVague()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("反色")
                        onTriggered: {
                            capture.filterReverse()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("锐化")
                        onTriggered: {
                            capture.filterSharpen()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("柔化")
                        onTriggered: {
                            capture.filterSoften()
                        }
                    }
                    QQC.MenuItem {
                        text: qsTr("返回")
                        onTriggered: {
                            capture.filterUndo()
                        }
                    }
                }
            }

            //撤销
            QQC.Button {
                id: undo
                icon.source: "qrc:/icons/revoke.png"
                width: 40
                height: 40
                onClicked: {
                    paint.enabled = false
                    isCut = paint.isdoCut("undo")
                    paint.undo()
                    if (isCut) {
                        backImg(paint.undo_backRect("undo"))
                    }
                    draghandler.enabled = true
                }
            }

            //清除
            QQC.Button {
                id: clear
                icon.source: "qrc:/icons/clear.png"
                width: 40
                height: 40
                onClicked: {
                    paint.enabled = false
                    isCut = paint.isdoCut("clear")
                    paint.clear()
                    if (isCut) {
                        backImg(paint.undo_backRect("clear"))
                    }
                    cutImage.cutreUpdate(scrollimg.width, scrollimg.height)
                    draghandler.enabled = true
                }
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
                    painterColor = color
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
                value: 1
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
                    textpaintColor = color
                    console.log(textcolor)
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
        //anchors.right: parent.right
        width: parent.width - leftside.width
        height: parent.height
        focus: true
        clip: false
        contentChildren: Rectangle {
            id: rec
            //            width: scrollview.width
            //            height: scrollview.height
            anchors.fill: parent //照片容器填充整个视图
            clip: true
            Image {
                id: scrollimg
                cache: false
                fillMode: Image.PreserveAspectFit
                x: rectX
                y: rectY
                WheelHandler {
                    acceptedModifiers: Qt.ControlModifier //按下controls键才响应滚轮事件
                    property: "scale" //设置滚动缩放
                }
                DragHandler {
                    //设置可拖拽
                    id: draghandler
                }
                TextEdit {
                    id: textedit
                    x: paint.printPoint.x
                    y: paint.printPoint.y
                    focus: false
                    //设置键盘事件
                    Keys.onPressed: {
                        if (event.modifiers === Qt.ControlModifier
                                && event.key === Qt.Key_Z) {
                            console.log("ctrl+z键盘事件被触发")
                            isCut = paint.isdoCut()
                            paint.undo()
                            if (isCut) {
                                backImg(paint.undo_backRect("undo"))
                            }
                        } else {
                            event.accepted = false
                        }
                    }

                    //                    height: paint.rectLength
                    //将其设置为paint.textEdit的原因是避免上次编辑造成的影响
                    text: paint.textEdit
                    font.pixelSize: paint.textFont
                    color: textpaintColor
                    onTextChanged: {
                        if (paint.flag == 1) {
                            textedit.focus = true
                            console.log("setTextEdit")
                            console.log(textedit.text)
                            paint.settextEdit(textedit.text)
                            textedit.visible = true
                        }
                        console.log("qml中文字区域的长度是：" + textedit.width)
                    }
                    //当字体颜色改变时
                    onColorChanged: {
                        if (paint.flag === 1) {
                            paint.setTextColor(color)
                        }
                    }
                    //当字体的大小改变时
                    onFontChanged: {
                        if (paint.flag === 1) {
                            paint.setTextFont(textedit.font.pixelSize)
                        }
                    }

                    visible: false
                }

                //涂鸦类
                PaintedItem {
                    id: paint
                    anchors.fill: scrollimg
                    enabled: false
                    penColor: painterColor
                    penWidth: paintSpinBox.value
                    textColor: textpaintColor
                    textFont: fontSpinBox.value
                    onClearSignal: {
                        console.log("clearsignal")
                        textedit.text = ""
                        //                        paint.settextEdit(textedit.text)
                    }
                    onUndoSignal: {
                        textedit.text = ""
                    }
                }
                CutImageRect {
                    id: cutImage
                    imgWidth: scrollimg.width
                    imgHeight: scrollimg.height
                    visible: false
                }
            }
        }
    }
    Connections {
        target: capture
        function onCallImageChanged() {
            scrollimg.source = ""
            scrollimg.source = "image://screen"
            //每次截取新的图片都需要将之前所裁剪矩形（图片）设置成当前图片的大小
            reUpdate()
            //重新设置裁剪框的大小
            cutImage.cutreUpdate(scrollimg.width, scrollimg.height)
        }
    }
}
