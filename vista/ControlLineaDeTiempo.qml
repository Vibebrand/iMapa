import Qt 4.7

Rectangle {
    id:control
    width:280
    height:300
    color: "#00000000"
    smooth: true

   BorderImage {
        id: barra
        opacity: 0.8
        source: "Imagenes/barra.png"
        scale: 0.5
        smooth: true
        x: 54
        y: 17
        width: 305
        height: 310

        Column
        {
            x: 0
            spacing:20
            anchors.top: parent.top
            anchors.topMargin: 50
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.centerIn: parent.anchors
            Text {
                id: nombreEntidad
                text: _nombreEntidad
                font.bold: true
                font.pointSize: 20
                smooth: true
                horizontalAlignment: Text.AlignRight
                color: "white"
            }

            Text {
                id: porcentajeNacional
                color: "white"
                text: _porcentajeNacional
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.pointSize: 20
                smooth: true
                horizontalAlignment: Text.AlignRight
            }

            Text {
                id: numeroHabitantes
                text: _numeroPoblacion
                color: "white"
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.pointSize: 20
                smooth: true
                horizontalAlignment: Text.AlignRight
            }
        }
    }

    BorderImage {
        id: fondo
        scale: 0.5
        source: "Imagenes/fondo.png"
        smooth: true
        x: -138
        y: -153
        opacity: 0.90
    }
    BorderImage {
        id: anios
        scale: 0.5
        source: "Imagenes/anios.png"
        smooth: true
        x: -68
        y: -34
        rotation: rotacion
        opacity: 0.8

        Behavior on rotation
        {
            NumberAnimation
            { duration: 1500}
        }
    }
    BorderImage {
        id: medio
        scale: 0.5
        smooth: true
        x: -75
        y: 117
        width: 416
        height: 202
        source: "Imagenes/medio.png"
        opacity: 0.8
    }

    BorderImage {
        id: mediocirclo
        scale: 0.5
        smooth: true
        source: "Imagenes/mediocirclo.png"
        x: -149
        y: -13
        opacity: 0.8
    }

    BorderImage {
        id: nxt
        scale: 0.5
        smooth: true
        source: "Imagenes/nxt.png"
        x: 118
        y: 136
        opacity: 1
        MouseArea {
            x: -1
            y: 0
            anchors.rightMargin: 2
            anchors.bottomMargin: 0
            anchors.leftMargin: -2
            anchors.topMargin: 0
            anchors.fill: parent
            onClicked: {
                delegado.adelanteClicked();
            }
        }
    }
    BorderImage {
        id: rturn
        scale: 0.5
        smooth: true
        source: "Imagenes/rtrn.png"
        x: 28
        y: 136
        opacity: 1

        MouseArea {
            x: 0
            y: -2
            anchors.rightMargin: 0
            anchors.bottomMargin: 1
            anchors.leftMargin: 0
            anchors.topMargin: -1
            anchors.fill: parent
            onClicked: {
                delegado.atrasClicked();
                animacionBarra2.start();
                animacionBarra3.start();
            }
        }
    }
    BorderImage {
        id: paly
        scale: 0.5
        smooth: true
        source: "Imagenes/paly.png"
        x: 80
        y: 114
        opacity: 1

        MouseArea {
            anchors.fill: parent
            onClicked: {
                delegado.playClicked();
                animacionBarra.start();
                animacionBarra1.start();
            }
        }
    }

    NumberAnimation {
        id: animacionBarra1;
        targets: control;
        property: "width";
        to:420;
        duration: 1500 }

    NumberAnimation {
        id: animacionBarra;
        targets: barra;
        property: "width";
        to:500;
        duration: 1500 }

    NumberAnimation {
        id: animacionBarra2;
        targets: barra;
        property: "width";
        to:305;
        duration: 1500 }

    NumberAnimation {
        id: animacionBarra3;
        targets: control;
        property: "width";
        to:280;
        duration: 1500 }

}
