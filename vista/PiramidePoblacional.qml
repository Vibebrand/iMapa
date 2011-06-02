import QtQuick 1.0

Rectangle
{
    id: rectangulo
    property int alto: 70
    property int tamagnoLista: 360
    property int offset: 100

    width: tamagnoLista
    height: 300

    Column {
        anchors.top: parent.top
        anchors.fill: parent

        Text {
            anchors.horizontalCenter: parent.horizontalCenter

            text: titulo
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        ListView {
            id: lista

            width: tamagnoLista
            height: 100

            model: modelo
            delegate:  Row {

                Rectangle {
                    width: tamagnoLista/2 + offset - ( (numeroDeHombres * ( tamagnoLista / 2 ) ) / anchoMax)
                    height: alto

                    Text {
                        text: nombre
                    }
                    color: "transparent"
                }

                Rectangle {
                    width: ( (numeroDeHombres * ( tamagnoLista / 2 ) ) / anchoMax)
                    height: alto
                    border.color: "black"
                    color: "blue"
                }

                Rectangle {
                    width: ( (numeroDeMujeres * ( tamagnoLista / 2 ) ) / anchoMax)
                    height: alto
                    border.color: "black"
                    color: "green"
                }
            }
        }
    }
}
