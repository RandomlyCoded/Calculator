import QtQuick 2.15
import QtQuick.Controls

import Calculator

Window {
    visible: false

    color: mainWnd.color

    width: 400
    height: settings.height + 40

    x: mainWnd.x - width - 10
    y: mainWnd.y

    flags: Qt.Dialog

    title: "settings"

    Column {
        x: 10
        y: 10

        id: settings

        spacing: 5

        CustomCheckBox {
            id: useAnsPrim

            checked: Backend.useAnsForPrimitive

            text: "use ans in primitive calculations"

            onStateToggled: Backend.toggleAnsForPrimitive()
        }

        CustomCheckBox {
            id: showPrimOp

            checked: Settings.showPrimitiveOperations

            text: "show primitive operation overview"

            onStateToggled: Settings.showPrimitiveOperations ^= 1
        }

        CustomCheckBox {
            id: showComplexOp

            checked: Settings.showComplexOperations

            text: "show complex operation overview"

            onStateToggled: Settings.showComplexOperations ^= 1
        }

        TextInputField {
            id: backgroundColor

            tip: "enter background color"

            text: Settings.backgroundColor.toString().replace("#", "")

            onEditingFinished: Settings.backgroundColor = "#" + text
        }

        TextInputField {
            id: textColor

            tip: "enter text color"

            text: Settings.textColor.toString().replace("#", "")

            onEditingFinished: Settings.textColor = "#" + text
        }

        TextInputField {
            id: outlineColor

            tip: "enter outline color"

            text: Settings.outlineColor.toString().replace("#", "")

            onEditingFinished: Settings.outlineColor = "#" + text
        }

        CustomCheckBox {
            id: boldText

            text: "bold font"

            checked: mainWnd.bold

            onStateToggled: Settings.bold ^= 1
        }

        CustomCheckBox {
            id: italicText

            text: "italic text"

            checked: mainWnd.italic

            onStateToggled: Settings.italic ^= 1
        }

        TextInputField {
            id: fontName

            text: mainWnd.fontName

            tip: "enter font name"

            onEditingFinished: Settings.fontName = text
        }

        Column {
            spacing: parent.spacing

            CustomButton {
                id: restoreSettings

                text: "restore default settings"

                onClicked: {
                    cancel.visible = true;
                    confirm.visible = true;
                }
            }

            Row {
                spacing: parent.spacing
                CustomButton {
                    id: confirm

                    visible: false

                    text: "confirm"

                    onClicked: {
                        finalConfirm.conf = Backend.generateConfirmText()
                        finalConfirmHint.text = "to confirm, enter \"" + finalConfirm.conf + "\""
                        finalConfirm.visible = true;
                    }
                }

                Column {
                    spacing: parent.spacing

                    Text {
                        id: finalConfirmHint
                    }

                    TextInputField {
                        id: finalConfirm

                        visible: false

                        property string conf: ""

                        tip: "enter text above"

                        onEditingFinished: {
                            if(text === conf)
                                Settings.restoreDefaultSettings()

                            visible = false;
                            finalConfirmHint.visible = false;
                            cancel.visible = false;
                            confirm.visible = false;
                        }
                    }
                }
            }

            CustomButton {
                id: cancel

                visible: false

                text: "cancel"

                onClicked: {
                    confirm.visible = false;
                    visible = false;
                }
            }

        }
    }
}
