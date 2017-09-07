import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    title: qsTr("15Puzzle")
    width: 600
    height: 400

    visible: true
    color: "black"


    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: parent.width / logic.boardSize
        cellHeight: parent.height / logic.boardSize

        interactive: false

        model: logic
        delegate:
            Component {
            Rectangle {
                height: grid.cellHeight
                width: grid.cellWidth
                color: "skyblue"
                border.color: "black"
                border.width: 1
                radius: 10

                visible: (number != 0) ? true : false

                Text {
                    anchors.centerIn: parent
                    text: number
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        logic.move(index);
                        if (logic.checkWin())
                            endGameDialog.visible = true;
                    }
                }
            }
        }
    }

    Dialog {
        id: endGameDialog
        visible: false
        title: qsTr("Game over")
        contentItem:
        Rectangle {
            color: "white"
            implicitWidth: 300
            implicitHeight: 200

            Text {
                id: endGameText
                text: "YOU WIN!"
                color: "black"
                font.pixelSize: 40
                font.bold: true
                anchors.centerIn: parent
            }

            Button {
                anchors.top: endGameText.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 10
                height: 50

                text: qsTr("OK")
                onClicked: {
                    endGameDialog.close()
                    grid.enabled = false
                }
            }
        }
    }
}

