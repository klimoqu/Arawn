#pragma once

class game : public QObject
{
    Q_OBJECT
    Map* map;
    int time;
    bool server;
    QTcpSocket server;
    QTcpSocket clients[];
public:
    game(QTcpSocket socket);

    void newGame(int id);
    void validate(Command c);
    void execute(Command c);

signals:

    void ServerValidate(Command c);
    void KlientValidate(Command c);

public slots:
    void ServerExecute(Command c);
    void KlientExecute(Command c);
};
