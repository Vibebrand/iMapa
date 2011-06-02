import QtQuick 1.0

ListView {
    id: lista

    property int alto: 70
    property int tamagnoLista: 360
    property int offset: 100

    width: tamagnoLista
    height: 360

    model: modelo
    delegate:  Row {

        Rectangle {
            width: tamagnoLista/2 - izq + offset
            height: alto

            Text {
                text: nombre
            }
            color: "transparent"
        }

        Rectangle {
            width: izq
            height: alto
            border.color: "black"
            color: "blue"
        }

        Rectangle {
            width: der
            height: alto
            border.color: "black"
            color: "green"
        }
    }
}
