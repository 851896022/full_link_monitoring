#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include <QFrame>

namespace Ui {
class Mp3Player;
}

class Mp3Player : public QFrame
{
    Q_OBJECT

public:
    explicit Mp3Player(QWidget *parent = 0);
    ~Mp3Player();

private:
    Ui::Mp3Player *ui;
};

#endif // MP3PLAYER_H
