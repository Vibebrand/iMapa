import Qt 4.7

Rectangle
{
    id: rectangulo

    property int alto: 10
    property int tamagnoLista: 300
    property int offset: 50

    width: tamagnoLista + offset + 100
    height: 357
    color: "#00000000"

    BorderImage {

        id: fondo
        x: -18
        y: -18
        width: 510
        height: 415
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
                opacity: 0.8
                model: modelo
                delegate:  Row {

                    property real anchoIzq : delegado.calculaAncho(numeroDeMujeres)
                    property real anchoDer : delegado.calculaAncho(numeroDeHombres)
                    property real desfase : delegado.cantidadDesface(numeroDeMujeres)

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
                        id:indicadorMujeres
                        width: anchoIzq
                        height: alto
                        border.width: 2
                        border.color: "#0b4241"
                        smooth: true
                        gradient: Gradient {
                            GradientStop {
                                position: 0
                                color: "#6ddddb"
                            }

                            GradientStop {
                                position: 1
                                color: "#093837"
                            }
                        }
                        MouseArea{
                        anchors.fill: parent
                        onClicked:
                        {
                            animacionTexto1.stop();
                            cantidadPersonas.text=numeroDeMujeres;
                            cantidadPersonas.text+=" Mujeres";
                            cantidadPersonas.opacity=1;
                            animacionTexto1.start();
                        }
                       }
                    }

                    Rectangle {
                        id:indicadorHombres
                        width: anchoDer
                        height: alto
                        border.width: 2
                        border.color: "#404040"
                        smooth: true
                        gradient: Gradient {
                            GradientStop {
                                position: 0
                                color: "#f7f7f7"
                            }

                            GradientStop {
                                position: 0.94
                                color: "#444444"
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked:
                            {
                                animacionTexto1.stop();
                                cantidadPersonas.text=numeroDeHombres;
                                cantidadPersonas.text+=" Hombres";
                                cantidadPersonas.opacity=1;
                                animacionTexto1.start();
                            }
                        }
                    }


                    PropertyAnimation
                    {
                        id:animacionTexto1
                        target:cantidadPersonas
                        property:"opacity"
                        to:"0";
                        duration:3500;
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

    Text {
        id: cantidadPersonas
        x: 335
        y: 47
        width: 100
        height: 20
        color: "white"
        text: ""
        anchors.right: parent.right
        anchors.rightMargin: 44
        horizontalAlignment: Text.AlignRight
        font.bold: true
        smooth: true
        font.pixelSize: 12
        }

        Text {
            id: porcentajeHombres
            x: 324
            y: 118
            width: 80
            height: 20
            color: "white"
            smooth: true
            text: _porcentajeHombres
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            anchors.right: parent.right
            anchors.rightMargin: 47
            font.pixelSize: 12
        }

        Text {
            id: porcentajeMujeres
            x: 136
            y: 118
            width: 80
            height: 20
            color: "white"
            text: _porcentajeMujeres
            smooth: true
            font.bold: true
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }




}
