#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QAudioOutput>
#include <QByteArray>
#include <QTimer>
#include <QDebug>
class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    QAudioOutput* audioOutput;
    QIODevice * streamOut;
    QByteArray tempBuffer;
    QTimer *timer;

signals:

public slots:
    void slotTimeout();
};

#endif // PLAYER_H
