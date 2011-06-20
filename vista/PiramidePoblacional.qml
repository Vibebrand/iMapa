import Qt 4.7

Rectangle
{
    id: rectangulo

    property int alto: 10
    property int tamagnoLista: 300
    property int offset: 50

    width: tamagnoLista + offset + 100
    height: 326
    color: "#00000000"

    BorderImage {

        id: fondo
        x: -18
        y: -18
        width: 510
        height: 382
        anchors.rightMargin: -32
        anchors.bottomMargin: -19
        anchors.leftMargin: -18
        anchors.topMargin: -18
       // anchors.fill: parent
        source: "Imagenes/fondo_piramide.png"
        smooth: true
        opacity: 1
        border.left: 5; border.top: 5
        border.right: 5; border.bottom: 5

        BorderImage {
            id: transparencia
            source: "Imagenes/transparencia_piramide.png"
            x: 36
            y: 89
            width: 415
            height: 239
            anchors.rightMargin: 59
            anchors.bottomMargin: 54
            anchors.leftMargin: 36
            anchors.topMargin: 89
            anchors.fill: parent
            sourceSize.width: 764
            smooth: true
            opacity: 1
            border.left: 5; border.top: 5
            border.right: 5; border.bottom: 5


            ListView {
                id: lista
                x: 0
                y: 6
                anchors.rightMargin: 10
                anchors.leftMargin: 35
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                anchors.fill: parent
                opacity: 0.9
                model: modelo
                delegate:  Row {

                    property real anchoIzq : delegado.calculaAncho(numeroDeHombres)
                    property real anchoDer : delegado.calculaAncho(numeroDeMujeres)
                    property real desfase : delegado.cantidadDesface(numeroDeHombres)

                    Text {
                        text: nombre
                        width: desfase
                        color: "white"
                        smooth: true
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
    }

    Text
    {
        id: texto
        anchors.bottomMargin:50
        height: 30
        color: "white"
        text: titulo
        smooth: true
        anchors.top: parent.top
        anchors.topMargin: 21
        anchors.horizontalCenter: parent.horizontalCenter
        style: Text.Raised
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 12
    }




}
