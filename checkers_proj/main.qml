import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import TableModel 1.0
import QtQuick.Layouts 1.15

Window {
    id : mainwindow
    width: 640
    height: 740
    visible: true
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    color: "green"
    ColumnLayout
    {
        id: layout_my
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.topMargin: 150
        height: 300
        visible: true
        Button {
                id : testButton
                text: "Начать игру !"
                onClicked:
                {
                    my_table_view.visible = true;
                    layout_my.visible = false;
                    blueRectangle.visible = true;
                    if (black_button.border.width === 5){boardmodel.setBoard("black");}
                    else{boardmodel.setBoard("white");}
                }
                contentItem: Text {
                    text: testButton.text
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 10
                    font.bold: true
                }
                background: Rectangle {
                                property string normalColor: "#005291"
                                property string hoveredColor: "#4587ba"
                                property string pressedColor: "#002948"
                                implicitWidth: 300
                                implicitHeight: 100
                                color: testButton.pressed ? pressedColor :
                                       testButton.hovered ? hoveredColor :
                                                            normalColor
                            }
                }
        RowLayout{
            id: my_row
            Layout.alignment: Qt.AlignTop
            width: 300
            height: 50
            spacing: 50
            Rectangle
            {
                id: black_button
                width: 125
                height: 50
                color: "black"
                border.width: 0
                border.color: "red"
                Text
                {
                    anchors.centerIn: parent
                    text: "black"
                    color: "white"
                }
                TapHandler {
                    onTapped: {
                        black_button.border.width = 5
                        white_button.border.width = 0
                        }
                }
            }
            Rectangle
            {
                id: white_button
                width: 125
                height: 50
                color: "white"
                border.width: 5
                border.color: "red"
                Text
                {
                    anchors.centerIn: parent
                    text: "white"
                    color: "black"
                }
                TapHandler {
                    onTapped: {
                        black_button.border.width = 0
                        white_button.border.width = 5
                    }
                }
            }

        }

    }


    TableView {
        id: my_table_view
        anchors.fill: parent
        topMargin: 100
        clip: true
        visible: false

        model: TableModel
        {
        id: boardmodel
        }
        delegate: Rectangle {
            id: rect
            border.color: "green"
            border.width: bordwidth
            implicitWidth: parent.width / 8
            implicitHeight: parent.height / 8
            color: myColor
            Canvas {
                    id: canvas
                    visible: visibility
                    anchors.fill: parent
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();
                        var centreX = rect.width / 2;
                        var centreY = rect.height / 2;
                        ctx.fillStyle = figcolor;
                        ctx.arc(centreX, centreY, 30, 0, 360, 0);
                        ctx.fill();
                    }
                }
            Canvas {
                    id: star_canvas
                    visible: starvisibility
                    anchors.fill: parent
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();
                        var centreX = rect.width / 2;
                        var centreY = rect.height / 2;
                        ctx.fillStyle = "yellow";
                        ctx.beginPath();
                        ctx.moveTo(25,50);
                        ctx.lineTo(55,50);
                        ctx.lineTo(55, 30);
                        ctx.lineTo(45, 40);
                        ctx.lineTo(40, 30);
                        ctx.lineTo(35, 40);
                        ctx.lineTo(25, 30);
                        ctx.fill();
                    }
                }
            TapHandler {
                onTapped: {
                    if (boardmodel.can_move(index)){boardmodel.move(index);}
                    else{boardmodel.show_places(index);}
                    }
            }

        }
    }
    Rectangle {
            id: blueRectangle
            color: "#008080"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 100
            visible: false
            Text{
                id: first_string
                anchors.centerIn: parent
                text: "Player 1 " + boardmodel.score_of_first + " : " + boardmodel.score_of_second +  " Player 2"
                color: "black"
            }
        }
    Dialog {
        visible: boardmodel.end_of_game
        anchors.centerIn: parent
        id: dialog
        title: "Хотите сыграть еще раз ?"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {my_table_view.visible = false;
                    layout_my.visible = true;
                    blueRectangle.visible = false;
                    }
        onRejected: mainwindow.close()
    }
}
