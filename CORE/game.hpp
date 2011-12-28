#pragma once

class game
{
    Map* map;
    int time;
public:
    game();
    void validate();
    void execute();
};
