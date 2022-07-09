//author：pengyueting 2020051615252
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    property alias check_3: check_3
    signal refreshImage
    onRefreshImage: () => {
                        img.source = ""
                        img.source = "image://screen"
                        /*img.source = "image://screen?id=" + count*/ //布尔值只是为了循环刷新路径触发provider中的requestimage函数返回缓存中的image图片到qml端显示
                    }
    function selectImage() {
        img.source = arguments[0]
    } //选择图片

    Image {
        id: img
        width: parent.width - recright.width
        height: parent.height
        anchors.left: parent.left
        anchors.right: recright.left
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        //指定是否应该缓存图像。默认值为true。当处理大图像时，将cache设置为false是很有用的，以确保它们不会以牺牲小的“ui元素”图像为代价进行缓存。
        cache: false
        //        source: "file:///tmp/1.jpg"
        source: "./icons/logo.png"
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: recright
        width: 250
        height: parent.height
        anchors.right: parent.right
        ColumnLayout {
            id: column1
            x: 0
            y: 0
            width: 250
            height: 289
            RowLayout {
                id: row
                Layout.topMargin: 5
                Text {
                    text: qsTr("截取方式")
                    font.pixelSize: 16
                }
            }
            RowLayout {
                id: row1
                Layout.preferredWidth: 210
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Label {
                    id: lab_1
                    text: qsTr("区域：")
                }
                ComboBox {

                    id: cbb
                    Layout.preferredWidth: 171
                    model: ListModel {
                        id: model
                        ListElement {
                            text: qsTr("全屏截取")
                        }
                        ListElement {
                            text: qsTr("矩形截取")
                        }
                        ListElement {
                            text: qsTr("不规则截取")
                        }
                        ListElement {
                            text: qsTr("活动窗口截取")
                        }
                        ListElement {
                            text: qsTr("连续截取")
                        }
                        ListElement {
                            text: qsTr("钉在桌面")
                        }
                        ListElement {
                            text: qsTr("长截图")
                        }
                    }
                }
            }
            RowLayout {
                id: row2
                Layout.preferredWidth: 210
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Label {
                    id: lab_2
                    text: qsTr("延迟：")
                }
                SpinBox {
                    id: spinBox
                    editable: true
                    Layout.preferredWidth: 82
                    //                    minimumValue: 0
                    value: 0
                    //                    suffix: "秒"
                    //                    decimals: 0
                    stepSize: 1
                }
                CheckBox {
                    id: checkBox
                    text: qsTr("点击截图")
                    onCheckedChanged: {
                        if (checkBox.checked) {
                            spinBox.enabled = false
                        } else {
                            spinBox.enabled = true
                        }
                    }
                }
            }
            RowLayout {
                id: row3
                Layout.topMargin: 5
                Text {
                    text: qsTr("选项")
                    font.pixelSize: 16
                }
            }
            ColumnLayout {
                spacing: 0
                layoutDirection: Qt.LeftToRight
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                CheckBox {
                    id: check_2
                    text: qsTr("隐藏当前窗口")
                }
                CheckBox {
                    id: check_3
                    text: qsTr("手动保存或复制后退出")
                }
            }
        }
        Button {
            id: shotBtn
            x: 75
            y: 369
            width: 100
            height: 50
            anchors.bottom: parent.bottom
            checked: false
            anchors.bottomMargin: 61
            text: qsTr("截取屏幕")
            icon.source: "./icons/logo.png"
            Shortcut {
                sequence: "Ctrl+Alt+P"
                onActivated: shotBtn.clicked()
            }
            onClicked: {
                if (spinBox.value === 0) {
                    if (cbb.displayText === qsTr("全屏截取")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                capture.startFullShot()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 600)
                        } else {
                            capture.startFullShot()
                        }
                    }
                    if (cbb.displayText === qsTr("矩形截取")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                capture.startRectShot()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 600)
                        } else {
                            capture.startRectShot()
                        }
                    }
                    if (cbb.displayText === qsTr("不规则截取")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                capture.startFreeShot()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 600)
                        } else {
                            capture.startFreeShot()
                        }
                    }
                    if (cbb.displayText === qsTr("连续截取")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                capture.startContinueShot()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 600)
                        } else {
                            capture.startContinueShot()
                        }
                    }
                    if (cbb.displayText === qsTr("钉在桌面")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                capture.nailedToTable()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 600)
                        } else {
                            capture.nailedToTable()
                        }
                    }
                    if (cbb.displayText === qsTr("活动窗口截取")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                capture.startActiveShot()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 500)
                        } else {
                            capture.startActiveShot()
                        }
                    }
                    if (cbb.displayText === qsTr("长截图")) {
                        if (check_2.checked == true) {
                            root.hide()
                            timer.setTimeout(function () {
                                longshot.show()
                            }, 500)
                            timer.setTimeout(function () {
                                root.show()
                            }, 500)
                        } else {
                            longshot.show()
                        }
                    }
                } else {
                    countDown.start()
                }
            }
        }
        Connections {
            target: capture
            function onCallImageChanged() {
                img.source = ""
                img.source = "image://screen"
            }
        }
        Connections {
            target: capture
            function onFinishCapture() {
                root.showNormal()
            }
        }
        Timer {
            //延时触发回调函数
            id: timer
            //triggered即使在触发一次之后回调也会保持与信号的连接。
            //这意味着如果再次使用该延迟功能，定时器将再次触发所有连接的回调。所以你应该在触发后断开回调。
            function setTimeout(cb, delayTime) {
                timer.interval = delayTime //根据客户代码确定延迟时间
                timer.repeat = false //不重复，只触发一次
                timer.triggered.connect(cb) //触发信号连接回调函数
                timer.triggered.connect(function release() {
                    //断开连接
                    timer.triggered.disconnect(cb) // This is important
                    timer.triggered.disconnect(
                                release) // This is important as well
                })
                timer.start() //开始计时
            }
        }

        Timer {
            id: countDown
            interval: 1000
            repeat: true
            onTriggered: {
                console.log(spinBox.value)
                spinBox.value -= 1
                if (spinBox.value === 0 && cbb.currentText === qsTr("全屏截取")) {
                    countDown.stop()
                    if (check_2.checked == true) {
                        root.hide()
                        timer.setTimeout(function () {
                            capture.startFullShot()
                        }, 500)
                        timer.setTimeout(function () {
                            root.show()
                        }, 600)
                    } else {
                        capture.startFullShot()
                    }
                } else if (spinBox.value === 0 && cbb.currentText === qsTr(
                               "矩形截取")) {
                    countDown.stop()
                    if (check_2.checked == true) {
                        root.hide()
                        timer.setTimeout(function () {
                            capture.startRectShot()
                        }, 500)
                    } else {
                        capture.startRectShot()
                    }
                } else if (spinBox.value === 0 && cbb.currentText === qsTr(
                               "不规则截取")) {
                    countDown.stop()
                    if (check_2.checked == true) {
                        root.hide()
                        timer.setTimeout(function () {
                            capture.startFreeShot()
                        }, 500)
                    } else {
                        capture.startFreeShot()
                    }
                } else if (spinBox.value === 0 && cbb.currentText === qsTr(
                               "连续截取")) {

                    //                countDown.stop()
                    //                if(check_2.checked == true){
                    //                    root.hide()
                    //                    timer.setTimeout(function(){ capture.startContinueShot() },500)
                    //                }else{
                    //                    capture.startContinueShot()
                    //                }
                } else if (spinBox.value === 0 && cbb.currentText === qsTr(
                               "钉在桌面")) {
                    countDown.stop()
                    if (check_2.checked == true) {
                        root.hide()
                        timer.setTimeout(function () {
                            capture.nailedToTable()
                        }, 500)
                        timer.setTimeout(function () {
                            root.show()
                        }, 600)
                    } else {
                        capture.nailedToTable()
                    }
                } else if (spinBox.value === 0 && cbb.currentText === qsTr(
                               "活动窗口截取")) {
                    countDown.stop()
                    if (check_2.checked == true) {
                        root.hide()
                        timer.setTimeout(function () {
                            capture.startActiveShot()
                        }, 500)
                    } else {
                        capture.startActiveShot()
                    }
                } else if (spinBox.value === 0
                           && cbb.currentText === qsTr("长截图")) {
                    countDown.stop()
                    if (check_2.checked == true) {
                        root.hide()
                        timer.setTimeout(function () {
                            longshot.show()
                        }, 500)
                    } else {
                        longshot.show()
                    }
                }
            }
        }
    }
}
/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

