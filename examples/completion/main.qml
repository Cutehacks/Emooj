import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

import com.cutehacks.emooj 1.0

Window {
    visible: true
    width: 480
    height: 640

    ListView {
        id: list

        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            right: parent.right
            bottom: input.top
        }

        delegate: Item {
            height: childrenRect.height + 10
            anchors {
                left: parent.left
                right: parent.right
            }

            Rectangle {
                id: rect
                color: "lightblue"
                radius: 5
                y: 10
                height: message.height * 2 + 5
                width: Math.min(parent.width - 20, message.implicitWidth + 20)
                anchors {
                    right: parent.right
                    rightMargin: 10
                }
            }

            Text {
                y: 20
                id: message
                text: content
                anchors {
                    right: parent.right
                    rightMargin: 20
                }
                wrapMode: Text.WordWrap
                textFormat: Qt.RichText
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
            }

            Text {
                text: "length: " + UnicodeUtils.length(original)
                anchors.top: rect.bottom
                anchors.right: message.right
                font.pixelSize: message.font.pixelSize * .75
                color: "darkgray"
            }

        }

        model: ListModel { id: model }
    }

    TextField {
        id: input
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: sendButton.left
        }

        ToolButton {
            id: openEmojis
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            text: "😃"
            onClicked: emojiView.visible = !emojiView.visible
        }

        EmojiView {
            id: emojiView
            visible: false
            anchors.right: openEmojis.right
            anchors.bottom: openEmojis.top
        }
    }

    Button {
        id: sendButton
        text: "Send"
        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        onClicked: {
            var item = {
                original: input.text,
                content: UnicodeUtils.replaceEmojis(input.text, function(emoji) {
                    return "<img src=\"image://com.cutehacks.emooj/"
                            + emoji.sheetX + "/"
                            + emoji.sheetY +
                            "\" style=\"width:32; height:32\" >"
                })
            };
            model.append(item);
            input.text = "";
        }
    }
}

