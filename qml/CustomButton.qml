import QtQuick
import QtQuick.Controls

Button {
    background: Rectangle {
        border.color: mainWnd.outlineColor
        radius: 5
        color: mainWnd.color
    }

    contentItem: Text {
        color: mainWnd.textColor
        text: parent.text

        font.bold: mainWnd.bold
        font.italic: mainWnd.italic
        font.family: mainWnd.fontName
    }
}
