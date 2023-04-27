import QtQuick 2.15
import QtQuick.Controls

import Calculator

Window {
    visible: false

    color: mainWnd.color

    width: 400
    height: settings.height + 30

    flags: Qt.SubWindow

    title: "settings"

    Column {
        x: 10
        y: 10

        id: settings

        spacing: 5

        CheckBox {
            id: useAnsPrim

            checked: Backend.useAnsForPrimitive

            text: "use ans in primitive calculations"

            onToggled: Backend.toggleAnsForPrimitive()

            spacing: 5

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
                    visible: useAnsPrim.checked
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

        CheckBox {
            id: showPrimOp

            checked: Backend.showPrimitiveOperations

            text: "show primitive operation overview"

            onToggled: Backend.showPrimitiveOperations ^= 1

            spacing: 5

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
                    visible: showPrimOp.checked // TODO:: background text textInput
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

        CheckBox {
            id: showComplexOp

            checked: Backend.showComplexOperations

            text: "show complex operation overview"

            onToggled: Backend.showComplexOperations ^= 1

            spacing: 5

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
                    visible: showComplexOp.checked
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

        TextInputField {
            id: backgroundColor

            tip: "enter background color"

            onEditingFinished: Backend.backgroundColor = "#" + text
        }

        TextInputField {
            id: textColor

            tip: "enter text color"

            onEditingFinished: Backend.textColor = "#" + text
        }

        TextInputField {
            id: outlineColor

            tip: "enter outline color"

            onEditingFinished: Backend.outlineColor = "#" + text
        }

        CheckBox {
            id: boldText

            text: "bold font"

            checked: mainWnd.bold

            onToggled: Backend.bold ^= 1

            spacing: 5

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
                    visible: boldText.checked
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

        CheckBox {
            id: italicText

            text: "italic text"

            checked: mainWnd.italic

            onToggled: Backend.italic ^= 1

            spacing: 5

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
                    visible: italicText.checked
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

        TextInputField {
            id: fontName

            text: mainWnd.fontName

            onEditingFinished: Backend.fontName = text
        }
    }
}
