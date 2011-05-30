import QtQuick 1.0

Rectangle {
    id: control
    width: 110
    height: 34
    radius: 17
    border.color: "#000000"


    Row {

        anchors.fill: control

        BorderImage {
            id: botonAtras
            width: 36
            height: 34
            source: "Imagenes/backButton.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {

                }
            }
        }

        BorderImage {
            id: botonPlay
            width: 36
            height: 34
            source: "Imagenes/playButton.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {

                }
            }
        }

        BorderImage {
            id: botonAdelante
            width: 36
            height: 34
            source: "Imagenes/forwardButton.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {

                }
            }
        }
    }
}
