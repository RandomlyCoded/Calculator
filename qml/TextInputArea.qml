import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    width: Math.max(minimumWidth, input.width + spacing * 2)
    height: input.height + spacing * 2
    border.color: mainWnd.outlineColor
    color: mainWnd.color

    property int minimumWidth: 20
    property int spacing: 2
    property string tip: "insert text"
    property string checkedText: ""

    property alias length: input.length
    property alias text: input.text
    property alias pixelSize: input.font.pixelSize

    TextArea {
        id: input

        placeholderText: tip
        placeholderTextColor: mainWnd.textColor

        color: mainWnd.textColor
        font.family: mainWnd.fontName
        font.bold: mainWnd.bold
        font.italic: mainWnd.italic

        TextMetrics {
            id: spacer
            font: input.font
            text: " "
        }

        background: Rectangle {
            color: mainWnd.color
        }

        tabStopDistance: spacer.advanceWidth * 4

        x: spacing
        y: spacing
    }

    MouseArea { // need to use MouseArea, otherwise QML detects a binding loop and width/height breaks
        anchors.fill: parent
        onClicked: input.focus = true;
    }
}
