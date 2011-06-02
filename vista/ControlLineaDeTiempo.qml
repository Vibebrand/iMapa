import Qt 4.7

Rectangle {
    id: control
    width: 110
    height: 34
    radius: 10
    color: "white"
    border.color: "#000000"

    Row {
        BorderImage {
            id: botonAtras
            width: 36
            height: 34
            source: "Imagenes/backButton.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    delegado.atrasClicked();
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
                    delegado.playClicked();
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
                    delegado.adelanteClicked();
                }
            }
        }
    }
}
