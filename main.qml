import QtQuick
import QtQuick.Controls

import Calculator

Window {
    id: wnd
    width: 640
    height: 480
    visible: true
    title: "moin"

    Column {
        spacing: 20

        Row {
            spacing: 10
            TextInputField {
                id: numberA

                tip: "enter number a, default: 0"
            }

            Button {
                text: "set number for formula"

                onClicked: Backend.setA(Backend.convert(numberA.text))
            }

            TextInputField {
                id: numberB

                tip: "enter number b, default: 1"
            }

            Button {
                text: "set number for formula"

                onClicked: Backend.setB(Backend.convert(numberB.text))
            }
        }

        Grid {
            rows: 10
            columns: 5

            spacing: 10

            Repeater {
                model: Backend.availableFunctions

                Button {
                    width: 100
                    height: 30

                    Text{
                        anchors.centerIn: parent
                        textFormat: Text.RichText

                        text: modelData
                    }

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
            spacing: 10
            TextInputArea {
                id: formula
                tip: "enter a formula"
                minimumWidth: wnd.width
            }

            Button {
                text: "run"
                onClicked: complexExpressionRes.text = "= " + Backend.runFormula(formula.text)
            }

            Text {
                id: complexExpressionRes
                font.bold: true
            }
        }
    }
}
