import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: window
    title: qsTr("15Puzzle")
    width: 600
    height: 400

    visible: true

    Rectangle {
        id: game

        color: "lightgray"
        width: parent.height
        height: parent.height

        enabled: false

        GridView {
            id: grid
            anchors.fill: parent

            cellWidth: parent.width / logic.boardSize
            cellHeight: parent.height / logic.boardSize

            interactive: false

            model: logic
            delegate:
            Rectangle {
                id: cell
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
                    id: mouseArea
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if (logic.move(index))
                        {
                            if (logic.checkWin())
                            {
                                game.enabled = false
                                endGameDialog.open()
                            }
                        }
                    }
                }
            }
        }
    }

    Button {
        id: newGameButton
        anchors { left: game.right; right: parent.right; top: parent.top }
        anchors { leftMargin: parent.width / 30; rightMargin: parent.width / 30; topMargin: parent.height / 10 }

        height: parent.height / 4
        width: parent.width / 4

        Text {
            anchors.centerIn: parent
            text: qsTr("New Game")
            font.bold: true
        }
        onClicked: {
            logic.newGame()
            game.enabled = true
        }
    }

    Button {
        id: quitGameButton
        anchors { left: game.right; right: parent.right;
            top: newGameButton.bottom; bottom: parent.bottom;
            leftMargin: parent.width / 30; rightMargin: parent.width / 30;
            topMargin: parent.height / 2.5; bottomMargin: parent.height / 10 }

        height: parent.height / 8
        width: parent.width / 4

        Text {
            anchors.centerIn: parent
            text: qsTr("Quit")
        }
        onClicked: {
            Qt.quit()
        }
    }

    Dialog {
        id: endGameDialog
        title: qsTr("Game over")
        contentItem:
            Rectangle {
            color: "white"
            implicitWidth: 300
            implicitHeight: 200

            Text {
                id: endGameText
                text: qsTr("YOU WIN!")
                color: "black"
                font.pixelSize: parent.height / 5
                font.bold: true
                font.family: "Helvetica"

                anchors { top: parent.top; left: parent.left; right: parent.right;
                    topMargin: parent.height / 5; leftMargin: parent.width / 5; rightMargin: parent.width / 5 }
            }
            Button {
                id: okDialogButton
                anchors { top: endGameText.bottom; left: parent.left; right: parent.right;
                    topMargin: parent.height / 7; leftMargin: parent.width / 5; rightMargin: parent.width / 5 }

                height: parent.height / 5

                text: qsTr("OK")
                onClicked: {
                    endGameDialog.close()
                }
            }
        }
    }
}

