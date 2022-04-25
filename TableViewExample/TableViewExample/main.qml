import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import TableModel 1.0


Window {
    id : mainwindow
    width: 640
    height: 640
    visible: true
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    TableView {
        anchors.fill: parent
        clip: true

        model: TableModel{
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
            TapHandler {
                    onTapped: boardmodel.outIndex(index);
                }
        }
    }
}
