#include <X11/Xlib.h>
#include <unistd.h>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>
#define KEY_UP 111
#define KEY_DOWN 116
#define KEY_LEFT 113
#define KEY_RIGHT 114
#define KEY_QUIT 9
#define KEY_SPACE 65
typedef struct Rect Rect;
typedef struct Food Food;
typedef struct Point Point;
typedef struct Size Size;
typedef struct Ghost Ghost;
typedef struct Follower Follower;
namespace my_game

{
    class Time
    {
    public:
        Time()
        {
            start = std::chrono ::high_resolution_clock::now();
        }
        long elapsed()
        {
            std::chrono ::duration<long, std::nano> elap = std::chrono ::high_resolution_clock::now() - start;
            return elap.count();
        }

    private:
        std::chrono::high_resolution_clock::time_point start;
    };
    struct Point
    {
        int x;
        int y;
    };
    struct Size
    {
        int width;
        int height;
    };
    struct Rect
    {
        long x, y;
        long width, height;
        inline struct Point tl() const
        {
            struct Point p;
            p.x = x;
            p.y = y;
            return p;
        }
        inline struct Point tr() const
        {
            struct Point p;
            p.x = x + width;
            p.y = y;
            return p;
        }
        inline struct Point bl() const
        {
            struct Point p;
            p.x = x;
            p.y = y + height;
            return p;
        }
        inline struct Point br() const
        {
            struct Point p;
            p.x = x + width;
            p.y = y + height;
            return p;
        }
    };
    inline bool PointInside(const Point &p, const Rect &r)
    {
        if (p.x >= r.tl().x && p.x <= r.tr().x && p.y >= r.tl().y && p.y <= r.bl().y)
        {
            return true;
        }
        return false;
    }
    inline bool inRange(int coord, int mini, int maxi)
    {
        return (coord >= mini && coord <= maxi);
    }
    inline bool Intersecting(const Rect &r1, const Rect &r2)
    {
        // Case 1 point inside
        if (PointInside(r1.tl(), r2) || PointInside(r1.tr(), r2) || PointInside(r1.bl(), r2) || PointInside(r1.br(), r2))
        {
            return true;
        }
        // Case 2  lying inside
        if (inRange(r1.tl().x, r2.tl().x, r2.tr().x) || inRange(r1.tr().x, r2.tl().x, r2.tr().x))
        {
            if (r1.tl().y <= r2.tl().y && r1.br().y >= r2.br().y)
                return true;
        }
        if (inRange(r1.tl().y, r2.tl().y, r2.tr().y) || inRange(r1.tr().y, r2.tl().y, r2.tr().y))
        {
            if (r1.tl().x <= r2.tl().x && r1.br().x >= r2.br().x)
                return true;
        }
        return false;
    }
    class GameDisplay
    {
    public:
        const int DEFAULT_WIDTH = 800;
        const int DEFAULT_HEIGHT = 600;
        GameDisplay();
        ~GameDisplay();
        Display *getDisplay();
        void drawRect(unsigned long long colour, int x, int y, int width, int height);
        void displayIntroText(int x, int y, std::string text);
        void displayIntroText(int x, int y, std::string text, int eaten);
        void redraw();
        struct Rect getGeometry();
        void gameEnd();

    private:
        int screen;
        Display *display;
        Window window;
    };

    GameDisplay::GameDisplay()
    {
        display = XOpenDisplay(NULL);
        if (display == NULL)
        {
            throw std::runtime_error("Cannot open display\n");
        }

        screen = DefaultScreen(display);
        // Window XCreateSimpleWindow(display, parent, x, y, width, height, border_width,   border, background)
        window = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, BlackPixel(display, screen), 0x363d4d);

        puts("hi");
        XSelectInput(display, window, KeyPressMask | ExposureMask);
        XMapWindow(display, window);
    }
    Display *GameDisplay::getDisplay()
    {
        return display;
    }
    void GameDisplay::drawRect(unsigned long long colour, int x, int y, int width, int height)
    {
        // unsigned long long red = 0xff0000;
        XSetForeground(display, DefaultGC(display, screen), colour);
        XFillRectangle(display, window, DefaultGC(display, screen), x, y, width, height);
    }
    void GameDisplay::displayIntroText(int x, int y, std::string text, int eaten)
    {
        int length = 0;
        std::string s = std::__cxx11::to_string(eaten);
        char displaying[1000];
        // printf("%d\n", length);
        text = text + s;

        while (text[length] != '\0')
        {
            displaying[length] = text[length];
            length++;
        }
        XDrawString(display, window, DefaultGC(display, screen), x, y, displaying, length);
    }
    void GameDisplay::displayIntroText(int x, int y, std::string text)
    {
        int length = 0;
        char displaying[1000];
        while (text[length] != '\0')
        {
            displaying[length] = text[length];
            length++;
        }
        printf("%d\n", length);
        XDrawString(display, window, DefaultGC(display, screen), x, y, displaying, length);
    }
    void GameDisplay::redraw()
    {
        XClearWindow(display, window);
        Window root_wind;
        int x, y;
        unsigned int width, height, border_width, depth;
        XGetGeometry(display, window, &root_wind, &x, &y, &width, &height, &border_width, &depth);
        XEvent ev;
        ev.xexpose.type = Expose;
        ev.xexpose.display = display;
        ev.xexpose.window = window;
        ev.xexpose.x = x;
        ev.xexpose.y = y;
        ev.xexpose.height = height;
        ev.xexpose.width = width;
        ev.xexpose.count = 0;
        XSendEvent(display, window, false, ExposureMask, &ev);
    }
    GameDisplay::~GameDisplay()
    {
        XCloseDisplay(display);
    }
    Rect GameDisplay::getGeometry()
    {
        Window root_wind;
        int x, y;
        unsigned int width, height, border_width, depth;
        XGetGeometry(display, window, &root_wind, &x, &y, &width, &height, &border_width, &depth);

        Rect r;
        r.x = x;
        r.y = y;
        r.width = width;
        r.height = height;
        return r;
    }
    struct Character
    {
        unsigned long colour = 0x6091ab;
        struct Point position = {10, 10};
        struct Size size = {10, 10};

        Character(unsigned long new_colour, struct Point new_pos, struct Size new_size)
            : colour(new_colour), position(new_pos), size(new_size) {}
        Rect Position() const
        {
            return {position.x, position.y, size.width, size.height};
        }
    };
    struct Player : public Character
    {
        int Food_Eaten = 0;
        Player() : Character(0x6091ab, {10, 10}, {10, 10}){};
    };
    struct Food : public Character
    {
        Food() : Character(0xe0f731, {100, 100}, {10, 10}){};
    };
    struct Ghost : public Character
    {
        Ghost() : Character(0xff0000, {100, 100}, {10, 10})
        {
            time_at_last_move = cur_time.elapsed();
        };
        unsigned long time_at_last_move;
        unsigned long move_time = {250'000'000}; // nano seconds
        Time cur_time;
        void move()
        {
            int direction = std::rand() % 4;
            const int MOVE_DIST = 10;

            switch (direction)
            {
            case 0:
                position.y -= MOVE_DIST;
                break;
            case 1:
                position.y += MOVE_DIST;
                break;
            case 2:
                position.x -= MOVE_DIST;
                break;
            case 3:
                position.x += MOVE_DIST;
                break;
            }
            time_at_last_move = cur_time.elapsed();
        }
        bool isTimeToMove()
        {
            return (cur_time.elapsed() - time_at_last_move >= move_time);
        }
    };
    struct Follower :  public Character
    {
        Follower() : Character(0x00ff00, {100, 100}, {10, 10})
        {
             time_at_last_move = cur_time.elapsed();
        };
        unsigned long time_at_last_move;
        unsigned long move_time = {250'000'000}; // nano seconds
        Time cur_time;
        void strategicMove(Player & player)
        {
            const int MOVE_DIST = 5;
            if (player.position.x > position.x)
            {
                position.x += MOVE_DIST;
            }
            else if (player.position.x < position.x)
            {
                position.x -= MOVE_DIST;
            }
            if (player.position.y > position.y)
            {
                position.y += MOVE_DIST;
            }
            else if (player.position.y < position.y)
            {
                position.y -= MOVE_DIST;
            }
            time_at_last_move = cur_time.elapsed();
        }
          bool isTimeToMove()
        {
            return (cur_time.elapsed() - time_at_last_move >= move_time);
        }
    };
    class Game
    {
    public:
        Game();
        void run();

    private:
        GameDisplay gd;
        bool is_running = true;
        XEvent e;
        Player player;
        std::vector<Ghost> ghost;
        std::vector<Food> food;
        bool game_over = false;
        bool game_won = false;
        std::vector<Follower> following_ghost;
        // int x = 10, y = 10;
        bool getEvent();
        void updateGhosts();
        void followingGhost();
        void update();
        void handleEvent();
        void drawPlayer();
        void draw();
        bool boundaryCheck();
        void createGhost();
        void createFood();
        void createFollower();
        void drawSingleGhost(const Ghost &g);
        void drawSingleFood(const Food &f);
        void singleFollower(const Follower &fg);
        void drawAllFollower();
        void drawAllFood();
        void drawAllGhost();
        void writeMessage();
        void resetGame();
    };
    Game::Game()
    {
        srand(time(NULL));
        createFood();
        createGhost();
        createFollower();
    }
    void Game::drawPlayer()
    {

        gd.drawRect(player.colour,
                    player.position.x,
                    player.position.y,
                    player.size.width,
                    player.size.height);
    }
    void Game::draw()
    {

        drawAllFood();
        drawPlayer();
        drawAllGhost();
        drawAllFollower();
        writeMessage();
    }
    void Game::createFood()
    {
        food.clear();
        food.resize(10);
        Rect r = gd.getGeometry();
        for (auto &f : food)
        {
            f.position.x = (std::rand() % r.width) / 10 * 10;
            f.position.y = (std::rand() % r.height) / 10 * 10;
        }
    }
    void Game::createGhost()
    {
        ghost.clear();
        ghost.resize(10);
        Rect r = gd.getGeometry();
        for (auto &g : ghost)
        {
            g.position.x = (std::rand() % r.width) / 10 * 10;
            g.position.y = (std::rand() % r.height) / 10 * 10;
        }
    }
    void Game::createFollower()
    {
        following_ghost.clear();
        following_ghost.resize(2);
        Rect r = gd.getGeometry();
        for (auto &fg : following_ghost)
        {
            fg.position.x = (std::rand() % r.width) / 10 * 10;
            fg.position.y = (std::rand() % r.height) / 10 * 10;
        }
    }
    void Game::drawSingleFood(const Food &f)
    {
        gd.drawRect(f.colour,
                    f.position.x,
                    f.position.y,
                    f.size.width,
                    f.size.height);
    }
    void Game ::drawSingleGhost(const Ghost &g)
    {
        gd.drawRect(g.colour,
                    g.position.x,
                    g.position.y,
                    g.size.width,
                    g.size.height);
    }
    void Game::singleFollower(const Follower &fg)
    {
        gd.drawRect(fg.colour,
                    fg.position.x,
                    fg.position.y,
                    fg.size.width,
                    fg.size.height);
    }
    void Game::drawAllFood()
    {
        for (auto &f : food)
        {
            drawSingleFood(f);
        }
    }
    void Game::drawAllGhost()
    {
        for (auto &g : ghost)
        {
            drawSingleGhost(g);
        }
    }
    void Game::drawAllFollower()
    {
        for (auto &fg : following_ghost)
        {
            singleFollower(fg);
        }
    }
    void Game::writeMessage()
    {
        if (!game_over)
            return;
        if (game_won)
        {
            gd.displayIntroText(100, 100, "YOU WIN!! Press SPACEBAR To Play Again");
        }
        else
        {
            gd.displayIntroText(100, 100, "YOU LOSE!! Press SPACEBAR To Restart");
        }
    }
    void Game::updateGhosts()
    {
        bool ghost_moved = false;
        for (auto &g : ghost)
        {
            if (g.isTimeToMove())
            {
                g.move();
                ghost_moved = true;
            }
        }
        if (ghost_moved)
        {
            gd.redraw();
        }
    }
    void Game::followingGhost()
    {
        bool follow_ghost = false;
        for (auto &fg : following_ghost)
        {
            if (fg.isTimeToMove())
            {
                fg.strategicMove(player);
                follow_ghost = true;
            }
        }
        if (follow_ghost)
        {
            gd.redraw();
        }
    }

    void Game::resetGame()
    {
        player.position = {10, 10};
        createFood();
        createGhost();
        player.Food_Eaten = 0;
        game_over = false;
        game_won = false;
    }
    void Game::run()
    {

        while (is_running)
        {
            std::string text;
            if (!game_over)
            {
                updateGhosts();
                followingGhost();
                text = "Food Eaten : ";
                gd.displayIntroText(20, 20, text, player.Food_Eaten);
            }
            // if (player.Food_Eaten == 10)
            // {
            //     text = "YOU WON !! \n  Press SPACEBAR To Play Again ";
            //     gd.displayIntroText(text);
            //     player.Food_Eaten = 0;
            // }

            if (getEvent())
            {
                handleEvent();
                if (!game_over && !boundaryCheck())
                {
                    // char text[10] = "You Lose";
                    // gd.displayIntroText(text);
                    puts("Out of bounds , You Lose");
                    game_over = true;
                    game_won = false;
                    // is_running = false;
                    // gd.gameEnd();
                }
            }
        }
    }
    bool Game::getEvent()
    {

        if (XPending(gd.getDisplay()))
        {
            XNextEvent(gd.getDisplay(), &e);
            printf("Event type is %d\n", e.type);
            return 1;
        }
        return 0;
    }
    void Game::update()
    {

        auto iter = std::find_if(food.begin(), food.end(), [&](const Food &f)
                                 { return Intersecting(player.Position(), f.Position()); });
        if (iter != food.end())
        {
            player.Food_Eaten++;
            food.erase(iter);
        }

        if (food.empty())
        {
            game_over = true;
            game_won = true;
        }

        auto iter2 = std::find_if(ghost.begin(), ghost.end(), [&](const Ghost &g)
                                  { return Intersecting(player.Position(), g.Position()); });
        if (iter2 != ghost.end())
        {
            std::cout << "You Lost" << std::endl;
            game_over = true;
            game_won = false;
        }

        auto iter3 = std::find_if(following_ghost.begin(), following_ghost.end(), [&](const Follower &fg)
                                  { return Intersecting(player.Position(), fg.Position()); });
        if (iter3 != following_ghost.end())
        {
            std::cout << "You Lost" << std::endl;
            game_over = true;
            game_won = false;
        }
        // for (int i = 0 ; i < food.size() ; i++)
        // {
        //     Food &f = food[i];
        //     if (Intersecting( (player.Position()), f.Position()))
        //     {
        //         food.erase(food.begin() + i);
        //         // createFood();
        //     }
        // }
    }
    void Game::handleEvent()
    {
        // int x = 10 , y = 30 , height = 50 , width = 50;

        if (e.type == KeyPress)
        {
            printf("KeyCode is %d\n", e.xkey.keycode);
            switch (e.xkey.keycode)
            {
            case KEY_UP:
                printf("Up\n");
                if (!game_over)
                {
                    player.position.y -= 10;

                    gd.redraw();
                }
                break;
            case KEY_DOWN:
                printf("Down\n");
                if (!game_over)
                {
                    player.position.y += 10;

                    gd.redraw();
                }
                break;
            case KEY_LEFT:
                printf("left\n");
                if (!game_over)
                {
                    player.position.x -= 10;

                    gd.redraw();
                }
                break;
            case KEY_RIGHT:
                printf("right\n");
                if (!game_over)
                {
                    player.position.x += 10;

                    gd.redraw();
                }
                break;
            case KEY_SPACE:
                if (game_over)
                {
                    printf("space\n");
                    resetGame();
                }
                break;

            case KEY_QUIT:
                printf("quit\n");
                is_running = 0;
                break;
            }
            update();
        }
        if (e.type == Expose)
        {
            draw();
            // gd.drawRect(0x0000ff, x, y,20,20);
            // char text[12] = "Hello World";
            // gd.displayIntroText(text);
        }
    }
    bool Game::boundaryCheck()
    {
        Rect r = gd.getGeometry();
        if (player.position.x < 0 || player.position.y < 0 || player.position.x >= r.width || player.position.y >= r.height)
        {

            // is_running = false;
            return false;
        }
        return true;
    }

}
int main()
{
    my_game::Game g;
    g.run();
    printf("Exiting\n");

    return 0;
}