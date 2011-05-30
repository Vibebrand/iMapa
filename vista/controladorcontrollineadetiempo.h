#ifndef CONTROLADORCONTROLLINEADETIEMPO_H
#define CONTROLADORCONTROLLINEADETIEMPO_H

#include <QObject>
#include <QWidget>
#include <QDeclarativeView>

class ControladorControlLineaDeTiempo : public QObject
{
    Q_OBJECT
public:
    explicit ControladorControlLineaDeTiempo(QObject *parent = 0);

    Q_INVOKABLE void atrasClicked();
    Q_INVOKABLE void playClicked();
    Q_INVOKABLE void adelanteClicked();


    QWidget * widget();
signals:

public slots:

private:
    QDeclarativeView view;

};

#endif // CONTROLADORCONTROLLINEADETIEMPO_H
