import QtQuick
import QtQuick.Controls

CheckBox {
    id: control
    spacing: 5

    signal stateToggled()

    onToggled: stateToggled()

    indicator: Rectangle {
        width: 15
        height: width
        y: parent.height / 2 - height / 2
        border.color: mainWnd.outlineColor
        color: mainWnd.color

        Rectangle {
            radius: 1

            x: 4
            y: 4
            width: parent.width - 8
            height: width
            color: mainWnd.outlineColor
            visible: control.checked
        }

        radius: 3
    }

    contentItem: Text {
        text: parent.text

        leftPadding: parent.indicator.width + parent.spacing

        font.family: mainWnd.fontName
        font.bold: mainWnd.bold
        font.italic: mainWnd.italic

        color: mainWnd.textColor
    }
}
