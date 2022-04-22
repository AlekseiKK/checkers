import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import TableModel 1.0

Window {
    width: 400
    height: 400
    visible: true
    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel {}

        delegate: Rectangle {
            id: rect
            implicitWidth: parent.width / 8
            implicitHeight: parent.height / 8
            color: myColor
            Canvas {
                    visible: false
                    anchors.fill: parent
                    onPaint: {
                        var ctx = getContext("2d");
                        ctx.reset();
                        var centreX = rect.width / 2;
                        var centreY = rect.height / 2;
                        ctx.fillStyle = "brown";
                        ctx.arc(centreX, centreY, 30, 0, 360, 0);
                        ctx.fill();
                    }
                }
        }
    }
}
