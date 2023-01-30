import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Tascs 1.0

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Органайзер")

    Tascs
    {
        id: _tascs
    }
    ButtonAdd
    {
        id: buttonQuit
        height: 30
        width: buttonQuit.height*763/300
        text: qsTr("Выход")
        onClicked: Qt.quit()
    }
    ButtonAdd
    {
        anchors.top: buttonQuit.bottom
        height: 30
        width: buttonAdd.height*763/300
        id: buttonAdd
        text: qsTr("Добавить")
        onClicked: (tf1.text == "") ? (statusLine1.text = "Введите значение") : (tf2.text == "") ? (statusLine2.text = "Введите значение") : (tf3.text == "") ? (statusLine3.text = "Введите значение") : (parseInt(tf3.text) > 10) ? (statusLine3.text = "Значение больше 10") : _tascs.addTasc(tf1.text + " - " + tf2.text + " - " + tf3.text)
    }
    ButtonAdd
    {
        anchors.top: buttonAdd.bottom
        id: buttonSaveAs
        height: 30
        width: buttonQuit.height*763/300
        text: qsTr("Сохр. как")
        onClicked: _tascs.save_as()
    }
    ButtonAdd
    {
        anchors.top: buttonSaveAs.bottom
        id: buttonOpen
        height: 30
        width: buttonQuit.height*763/300
        text: qsTr("Открыть")
        onClicked: _tascs.save_as()
    }
    Text
    {
        x: buttonAdd.width
        id: t1
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        text: qsTr("Название задачи")
    }
    Text
    {
        anchors.left: t1.right
        id: t2
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        text: qsTr("Дата окончания")
    }
    Text
    {
        anchors.left: t2.right
        id: t3
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        text: qsTr("Текущий прогресс")
    }
    TextField
    {
        anchors.top: buttonAdd.top
        anchors.left: buttonAdd.right
        id: tf1
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        placeholderText: qsTr("Введите название")
        onTextChanged: tf1.text == "" ? statusLine1.text = qsTr("") : statusLine1.text = qsTr("OK")
    }
    TextField
    {
        anchors.top: tf1.top
        anchors.left: tf1.right
        id: tf2
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        placeholderText: qsTr("дд.мм.гггг")
        validator: RegularExpressionValidator { regularExpression: /([0]{1}[1-9]{1}|[1-2]{1}[0-9]{1}|[3]{1}[0-1]{1})\.([0]{1}[1-9]{1}|[1]{1}[0-2]{1})\.[0-9]{4}/ }
        onTextChanged: acceptableInput ? statusLine2.text = qsTr("OK") : statusLine2.text = qsTr("")
    }
    TextField
    {
        anchors.top: tf2.top
        anchors.left: tf2.right
        id: tf3
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        placeholderText: qsTr("0 - 10")
        validator: IntValidator {bottom: 0; top: 10;}
        onTextChanged: acceptableInput ? statusLine3.text = qsTr("OK") : statusLine3.text = qsTr("")
//        validator: RegularExpressionValidator { regularExpression: /[0-9]{1}|[1]{1}[0]{1}/ }
    }
    Text
    {
        x: buttonAdd.width
        y: 60
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        id: statusLine1
        text: qsTr("")
    }
    Text
    {
        anchors.top: statusLine1.top
        anchors.left: statusLine1.right
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        id: statusLine2
        text: qsTr("")
    }
    Text
    {
        anchors.top: statusLine2.top
        anchors.left: statusLine2.right
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        id: statusLine3
        text: qsTr("")
    }
    Text
    {
        x: window.width/2
        y: 90
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        id: numOfTascs
        text: qsTr("Всего задач: " + _tascs.getTascsCount())
    }
}
