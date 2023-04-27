import QtQuick
import QtQuick.Controls

import Calculator

Window {
    id: mainWnd
    width: mainContent.width + 20
    height: mainContent.height + 20
    visible: true
    title: "just a random calculator"

    property color textColor: Backend.textColor
    property color outlineColor: Backend.outlineColor
    color: Backend.backgroundColor


    property bool bold: Backend.bold
    property bool italic: Backend.italic
    property string fontName: Backend.fontName

    Column {
        id: mainContent
        x: 10
        y: 10

        spacing: 20

        CustomButton {
            text: (settingsWnd.visible ? "hide" : "show") + " settings window"

            onClicked: settingsWnd.visible ^= 1
        }

        Row {
            spacing: 10
            TextInputField {
                id: numberA

                tip: "enter number a, default: 0"
            }

            CustomButton {
                text: "set number for formula"

                onClicked: Backend.setA(Backend.convert(numberA.text))
            }

            TextInputField {
                id: numberB

                tip: "enter number b, default: 1"
            }

            CustomButton {
                text: "set number for formula"

                onClicked: Backend.setB(Backend.convert(numberB.text))
            }
        }

        Grid {
            id: primitiveOperations
            rows: 10
            columns: 5

            spacing: 10

            visible: Backend.showPrimitiveOperations

            Repeater {
                model: Backend.availableFunctions

                CustomButton {
                    width: 150
                    height: 30

                    text: modelData

                    onClicked: {
                        let a = 0;
                        let b = 1
                        if(numberA.checkedText !== "") {
                            a = Backend.convert(numberA.text, a);
                            numberA.text = a;
                        }

                        if(numberB.checkedText !== "") {
                            b = Backend.convert(numberB.text, b);
                            numberB.text = b;
                        }

                        trivialExpressionRes.text = "= " + Backend.runFunc(modelData, a, b)
                    }
                }
            }
        }

        Text {
            id: trivialExpressionRes
            font.bold: true
        }

        Column {
            id: complexOperations

            spacing: 10

            visible: Backend.showComplexOperations

            TextInputArea {
                id: formula
                tip: "enter a formula"
                minimumWidth: Math.min(300, mainWnd.width)
            }

            CustomButton {
                text: "run"

                onClicked: complexExpressionRes.text = "= " + Backend.runFormula(formula.text)
            }

            Text {
                id: complexExpressionRes
                font.bold: true
            }
        }
    }

    SettingsWindow {
        id: settingsWnd
    }
}
