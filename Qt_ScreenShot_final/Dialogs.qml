//author：pengyueting 2020051615252
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item {
    property alias fileOpenDialog: fileOpen
    property alias fileSaveDialog: fileSave
    property alias aboutDialog: about

    function openFileDialog() { fileOpen.open(); }
    function saveFileDialog() { fileSave.open(); }
    function openAboutDialog()  {about.open()}

    FileDialog{
        id:fileOpen
        title:"Open A Picture"
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)" ]
        fileMode:FileDialog.OpenFile
    }

    FileDialog{
        id:fileSave
        title:"Save A Picture"
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)"]
        fileMode:FileDialog.SaveFile
        defaultSuffix: ".jpg"
    }


    MessageDialog{
        id:about
        buttons:MessageDialog.Ok
        title: qsTr("About")
        text:qsTr("本截图软件由重庆师范大学软件工程系黄义宏，龙心萍，彭粤庭开发。\n")
    }
}
