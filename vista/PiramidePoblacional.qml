import Qt 4.7

Rectangle
{
    id: rectangulo

    property int alto: 20
    property int tamagnoLista: 400
    property int offset: 50

    width: tamagnoLista + offset + 10
    height: 300

    Text
    {
        id: texto
        anchors.horizontalCenter: parent.horizontalCenter

        height: 30
        text: titulo
        style: Text.Raised
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
    }

    ListView {
        id: lista

        anchors.top: texto.bottom
        height: parent.height - texto.height
        width: parent.width

        model: modelo
        delegate:  Row {

            property real anchoIzq : delegado.calculaAncho(numeroDeHombres)
            property real anchoDer : delegado.calculaAncho(numeroDeMujeres)
            property real desfase : delegado.cantidadDesface(numeroDeHombres)

            Text {
                text: nombre
                width: desfase
                font.bold: true
                verticalAlignment: Text.AlignVCenter
            }

            Rectangle {
                width: 10
                height: alto
                color: "transparent"
            }

            Rectangle {
                width: anchoIzq
                height: alto
                border.color: "black"
                color: "blue"
            }

            Rectangle {
                width: anchoDer
                height: alto
                border.color: "black"
                color: "green"
            }
        }
    }
}
