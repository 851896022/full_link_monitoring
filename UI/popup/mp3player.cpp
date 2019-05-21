#include "mp3player.h"
#include "ui_mp3player.h"

Mp3Player::Mp3Player(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Mp3Player)
{
    ui->setupUi(this);
}

Mp3Player::~Mp3Player()
{
    delete ui;
}
