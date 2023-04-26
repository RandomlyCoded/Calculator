import QtQuick 2.15

Rectangle {
    width: Math.max(Math.max(tipText.width + spacing * 2, minimumWidth), input.width + spacing * 2)
    height: input.height + spacing * 2
    border.color: "black"

    property int minimumWidth: 20
    property int spacing: 2
    property string tip: "insert text"
    property string checkedText: ""

    property alias maximumLength: input.maximumLength
    property alias length: input.length
    property alias text: input.text
    property alias pixelSize: input.font.pixelSize

    TextInput {
        id: input

        x: spacing
        y: spacing
    }

    Text {
        id: tipText

        x: spacing
        y: spacing

        color: "gray"

        font.pixelSize: pixelSize
        visible: maybeShow()

        function maybeShow() {
            let text = input.text;
            text = text.replace(/ /g, "");

            checkedText = text;
            return text === ""
        }

        text: tip
    }

    MouseArea { // need to use MouseArea, otherwise QML detects a binding loop and width/height breaks
        anchors.fill: parent
        onClicked: input.focus = true;
    }
}
