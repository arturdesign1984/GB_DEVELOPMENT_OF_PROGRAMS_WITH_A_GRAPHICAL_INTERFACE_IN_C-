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
    Text
    {
        x: buttonAdd.width
        id: t1
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        text: qsTr("название задачи")
    }
    Text
    {
        anchors.left: t1.right
        id: t2
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        text: qsTr("дата окончания")
    }
    Text
    {
        anchors.left: t2.right
        id: t3
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
        text: qsTr("текущий прогресс")
    }
    ButtonAdd
    {
        y: 30
        height: 30
        width: buttonAdd.height*763/300
        id: buttonAdd
        text: qsTr("Добавить")
        onClicked: _tascs.addTasc(tf1.text + " - " + tf2.text + " - " + tf3.text)
    }
    TextField
    {
        anchors.top: buttonAdd.top
        anchors.left: buttonAdd.right
        id: tf1
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        placeholderText: qsTr("введите название")
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
//        inputMask: "99.99.9999"
//        inputMethodHints: Qt.ImhDigitsOnly
//        validator: Qt.ImhDate
    }
    TextField
    {
        anchors.top: tf2.top
        anchors.left: tf2.right
        id: tf3
        width: (window.width-buttonAdd.width)/3
        height: buttonAdd.height
        placeholderText: qsTr("0 - 10")
        validator: RegularExpressionValidator { regularExpression: /[0-9]{1}|[1]{1}[0]{1}/ }
    }
}
