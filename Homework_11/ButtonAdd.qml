import QtQuick 2.0

BorderImage {
    property alias text: _buttonAdd.text
    signal clicked
    source: "qrc:///icons_png/icons_png/buttonAdd_released.png"
    width: 763
    height: 300
    Text
    {
        id: _buttonAdd
        color: "black"
        anchors.centerIn: parent
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: parent.clicked()
        onPressed: {parent.source = "qrc:///icons_png/icons_png/buttonAdd_pressed.png"}
        onReleased: {parent.source = "qrc:///icons_png/icons_png/buttonAdd_released.png"}
    }
}
