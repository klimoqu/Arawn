#ifndef PLAYERBONUS_HPP
#define PLAYERBONUS_HPP

#include <QObject>

class Player;

class PlayerBonus : public QObject
{
    Q_OBJECT
public:
    explicit PlayerBonus(QObject *parent = 0, Player *player);
    virtual void execute();

protected:
    Player *player;

signals:

public slots:

};

#endif // PLAYERBONUS_HPP
