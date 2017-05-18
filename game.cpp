#include "game.h"
#include "snake.h"

void Game::placeBorders()
{
    for (auto &p : map.front())
        p.type = PTYPE_BORDER;
    for (auto &p : map.back())
        p.type = PTYPE_BORDER;
    for (auto &l : map)
    {
        l.front().type = PTYPE_BORDER;
        l.back().type = PTYPE_BORDER;
    }

}

void Game::placeSnack()
{
    int x,y;
    if (snack)
        swallowed.push_front(snack);
    do {
        x = rand()%MAP_W;
        y = rand()%MAP_H;
    } while (map[x][y].type != PTYPE_NOTHING);
    snack = &map[x][y];
    snack->type = PTYPE_SNACK;
}

Game::Game(bool borders)
{
    map.resize(MAP_W);
    for (int x = 0; x < map.size(); x++)
        for (int y = 0; y < MAP_H; y++)
            map[x].push_back({x, y, PTYPE_NOTHING});
    if (borders)
        placeBorders();
    snake = new Snake(map);
    placeSnack();
}

Game::~Game()
{
    if (snake)
        delete snake;
}

int Game::nextFrame()
{
    int size;
    int ret = snake->nextFrame();
    if (snack && snack->type != PTYPE_SNACK) {
        score++;
        placeSnack();
    }
    size = swallowed.size();

    for (int i = 0; i < size; i++)
    {
        if (swallowed.back()->type == PTYPE_NOTHING)
            swallowed.pop_back();
        else
            break;
    }
    return ret;
}

Point *Game::getSnack()
{
    return snack;
}

std::list<Point *> Game::getSwallowed()
{
    return swallowed;
}

int Game::getScore()
{
    return score;
}

Snake *Game::getSnake()
{
    return snake;
}
