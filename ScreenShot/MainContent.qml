//author：pengyueting 2020051615252
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    property alias img:img
    property alias shotBtn: shotBtn
    property alias cbb:cbb
    id:contentleft

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

    Item{
        id:recright
        width: 250
        height: parent.height
        anchors.right: parent.right
        ColumnLayout{
            id:column1
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
                        ListElement{
                            text: qsTr("不规则截取")
                        }
                        ListElement {
                            text: qsTr("活动窗口截取")
                        }
                        ListElement{
                            text:qsTr("连续截取")
                        }
                        ListElement{
                            text:qsTr("钉在桌面")
                        }
                        ListElement{
                            text:qsTr("长截图")
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
                      value:0
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
                    id:check_2
                    text: qsTr("隐藏当前窗口")
                }
                CheckBox {
                    text: qsTr("手动保存或复制后退出")
                }
            }
        }
        Button {
            id:shotBtn
            x: 75
            y: 369
            width: 100
            height: 50
            anchors.bottom: parent.bottom
            checked: false
            rotation: 0
            anchors.bottomMargin: 61
            text:qsTr("截取屏幕")
            icon.source: "./icons/logo.png"
            Shortcut{
                sequence: "Ctrl+Alt+P"
                onActivated: shotBtn.clicked()
            }
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
