// Copyright 2016 Cutehacks AS. All rights reserved.
// License can be found in the LICENSE file.
import QtQuick 2.0

import com.cutehacks.emooj 1.0

Rectangle {
    property int cellWidth: 32
    property int columnCount: 10
    property int rowCount: 10
    width: cellWidth * columnCount + grid.anchors.margins * 2
    height: cellWidth * rowCount + grid.anchors.margins * 2
    radius: 5
    border.color: "black"

    GridView {
        id: grid
        anchors.fill: parent
        clip: true
        cellWidth: 32
        cellHeight: 32
        anchors.margins: 10

        model: EmojiDataModel {
            id: emojiModel
        }

        delegate: Rectangle {
            width: 32
            height: 32

//            Text {
//                anchors.fill: parent
//                text: unicode
//            }
            Image {
                anchors.fill: parent
                source: decoration
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    emojiModel.emitIMEvent(index);
                }
            }
        }
    }

}

