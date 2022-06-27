//author：pengyueting 2020051615252
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: root
    title: qsTr("麒麟截屏")
    width: 900
    height: 480
    minimumHeight: 480
    minimumWidth: 680
    visible: true
    //property int count: 0
    MainContent {
        id: maincontent
        anchors.fill: parent
        Connections {
            target: capture
            function onImageCopied() {//
                loadMessage.source="MessageBox.qml"
                //Loader 的 item 属性指向它加载的组件的顶层 item 对于 Loader 加载的 item ，它暴露出来的接口，如属性、信号等，都可以通过 Loader 的 item 属性来访问。
            }
        }
    }
    Annotation{
        id:annotation
        anchors.fill: parent
        visible: false
    }

    Loader {
        id: loadMessage
        anchors.bottom: footer.top
        width: parent.width
        height: 45
        onLoaded: ()=>{
            loadMessage.item.title="a image has been copied!"
        }
    }
    footer: ToolBar {
        id:footer
        height: row.height + 20

        RowLayout {
            //最外层布局item
            id: row
            width: parent.width
            anchors.verticalCenter: parent.verticalCenter //采用相对（基线）定位方式，垂直居中父元素
            RowLayout {
                id: row1
                Layout.alignment: Qt.AlignLeft //左布局item
                Button {
                    Layout.preferredWidth: 100
                    text: qsTr("帮助(H)")
                    icon.name: "system-help"
                    icon.source: "./icons/help.png"
                    onClicked: menu1.popup(0, -90)
                    Menu {
                        id: menu1
                        MenuItem {
                            id: btn_help
                            text: qsTr("这是什么?(?)")
                            icon.name: "help-faq"
                            icon.source: "./icons/help.png"
                            Shortcut {
                                sequence: "Ctrl+?"
                                onActivated: btn_help.triggered()
                            }
                        }
                        MenuItem {
                            id: btn_error
                            text: qsTr("报告程序缺陷(Tab)...")
                            icon.name: "help-contents"
                            icon.source: "./icons/face-sad.png"
                            Shortcut {
                                sequence: "Ctrl+Tab"
                                onActivated: btn_error.triggered()
                            }
                        }
                        MenuItem {
                            id: btn_about
                            text: qsTr("关于麒麟截屏(H)")
                            icon.name: "help-about"
                            icon.source: "./icons/logo.png"
                            Shortcut {
                                sequence: "Ctrl+Shift+H"
                                onActivated: btn_about.triggered()
                            }
                        }
                    }
                }
                Button {
                    id: btn_open
                    text: qsTr("打开本地图片(O)")
                    icon.name: "document-open"
                    icon.source: "./icons/open.png"
                    Shortcut {
                        sequence: "Ctrl+O"
                        onActivated: btn_open.clicked()
                    }
                }
            }

            RowLayout {
                //右布局
                id: row2
                Layout.alignment: Qt.AlignRight

                Button {
                    id: btn
                    icon.source: "./icons/edit.png"
                    icon.name: "borderpainter"
                    text: qsTr("注释(E)")
                    Shortcut {
                        sequence: "Ctrl+E"
                        onActivated: btn.clicked()
                    }
                    onClicked: ()=>{
                                   if(btn.text==="注释(E)"){
                                       btn_1.enabled=false
                                       btn_2.enabled=false
                                       btn_4.enabled=false
                                       btn_3.enabled=true
                                       btn.text="注释完成"
                                       maincontent.visible=false
                                       annotation.visible=true //不用Loader的原因是该组件中的图片依赖根环境中的c++数据对象，使用Loader会新建一个环境，就不在根环境中了
                                   }else{
                                       //将修改过后的涂鸦内容保存 *
                                       maincontent.refreshImage();//发射信号通知主界面刷新涂鸦后的图片 利用provider从缓存中读取
                                       btn.text="注释(E)"
                                       btn_1.enabled=true
                                       btn_2.enabled=true
                                       btn_3.enabled=true
                                       btn_4.enabled=true
                                       maincontent.visible=true
                                       annotation.visible=false
                                   }
                               }
                }
                Button {
                    id: btn_1
                    text: qsTr("打印(P)")
                    icon.name: "printer"
                    icon.source: "./icons/print.png"
                    Shortcut {
                        sequence: "Ctrl+P"
                        onActivated: btn_1.clicked()
                    }
                }

                Button {
                    id: btn_2
                    icon.source: "./icons/send.png"
                    icon.name: "send-to-symbolic"
                    text: qsTr("导出")
                    onClicked: menu2.popup(0, -60)
                    Menu {

                        id: menu2

                        Menu {
                            title: qsTr("分享")

                            //点击分享 图片会自动保存至剪贴板 然后分享
                            MenuItem {
                                id: btn_qq
                                text: qsTr("发送到QQ")
                                icon.source: "./icons/qq.png"
                            }
                            MenuItem {
                                text: qsTr("发送到微信")
                                icon.source: "./icons/wexin.png"
                            }
                            MenuItem {
                                text: qsTr("通过电子邮件发送...")
                                icon.source: "./icons/mail.png"
                            }
                            MenuItem {
                                text: qsTr("发送到设备")
                                icon.source: "./icons/phone.png"
                            }
                        }
                        Menu {
                            title: qsTr("更多")
                            MenuItem {
                                id: btn_record
                                text: qsTr("全屏录制(R)")
                                icon.source: "./icons/recoder.png"
                                Shortcut {
                                    sequence: "Ctrl+Shift+R"
                                    onActivated: btn_record.triggered()
                                }
                            }
                            MenuItem {
                                id: btn_areaRecord
                                text: qsTr("区域录屏(A)")
                                icon.source: "./icons/record.png"
                                Shortcut {
                                    sequence: "Ctrl+Shift+A"
                                    onActivated: btn_areaRecord.triggered()
                                }
                            }
                        }
                    }
                }
                Button {
                    id: btn_4
                    icon.source: "./icons/clip.png"
                    icon.name: "edit-copy"
                    text: qsTr("复制到剪贴板(C)")
                    Shortcut {
                        sequence: "Ctrl+Shift+C"
                        onActivated: btn_4.clicked()
                    }
                }
                Button {
                    id: btn_3
                    text: qsTr("保存(S)")
                    icon.name: "document-save"
                    icon.source: "./icons/document-save.png"
                    onClicked: menu3.popup(0, -60)
                    Menu {
                        id: menu3
                        MenuItem {
                            id: save
                            text: qsTr("保存(S)")
                            icon.name: "document-save"
                            icon.source: "./icons/document-save.png"
                            Shortcut {
                                sequence: "Ctrl+S"
                                onActivated: save.triggered()
                            }
                        }
                        MenuItem {
                            id: save_as
                            text: qsTr("另存为")
                            icon.name: "document-save-as"
                            icon.source: "./icons/document-save-as.png"
                            Shortcut {
                                sequence: "Ctrl+Shift+S"
                                onActivated: save_as.triggered()
                            }
                        }
                    }
                }
            }
        }
    }
}
