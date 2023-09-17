#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#define PLAYER_SPEED 60
enum class directions
{
    NONE = 0,
    up = 1,
    left = 2,
    down = 3,
    right = 4,
};

struct directionAvilib
{
    bool dir[5];
};

int main2()
{
    std::vector<float> num;
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    window.setFramerateLimit(60);
    sf::RectangleShape a(sf::Vector2f(10.0f,10.0f));
    num.push_back(220);
    for (float i = 0; i < 200; i++)
    {
        num.push_back(num[i] / 1.04);
        std::cout << num[i] << std::endl;
    }
    sf::Clock clock;
    sf::Time time;
    float count = 0;
    a.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    while (window.isOpen())
    {
        count++;
        if (count > 199)
        {
            count = 0;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        a.setPosition((num[count] * num[count]) * 0.01, num[count]+180);
        window.draw(a);
        window.display();
    }

    return 0;
}

#define OFFSET_FOR_MAZE_CENTER 10

int main()
{
    sf::RenderWindow window(sf::VideoMode(610, 610), "Maze generation!");
    window.setFramerateLimit(120);
    sf::RectangleShape cell(sf::Vector2f(10.0f, 10.0f));
    sf::Clock clock;
    sf::Time time;
    float count = 0;

    cell.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    std::vector<std::vector<sf::Vector2f>> cellsPostions;
    std::vector<std::vector<char>> type;

    int width = 60;
    int height = 60;

    type.resize(height);
    for (int y = 0; y < height; y++)
    {
        type[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            type[y][x] = '#';
        }
    }
    cellsPostions.resize(height);
    for (int y = 0; y < height; y++)
    {   
        cellsPostions[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            sf::Vector2f newPos = sf::Vector2f(x * 10 + OFFSET_FOR_MAZE_CENTER, y * 10 + OFFSET_FOR_MAZE_CENTER);
            cellsPostions[y][x] = newPos;
        }
    }

    sf::Vector2i temphead(0,0);

    std::stack<sf::Vector2i> processNodes;
    processNodes.push(temphead);
    int dir = 0;
    directionAvilib dirAvilib;
    std::srand(std::time(nullptr));
    sf::Vector2i head(0, 0);
    bool start = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    if (!start)
                    {
                        start = true;
                    }
                    else
                    {
                        start = false;
                    }
                }
            }
        }
        if (!processNodes.empty() && start)
        {
            head = processNodes.top();

            dirAvilib.dir[0] = false;
            dirAvilib.dir[1] = false;
            dirAvilib.dir[2] = false;
            dirAvilib.dir[3] = false;
            dirAvilib.dir[4] = false;

            if (head.x + 2 >= width)
            {
            }
            else if (type[head.y][head.x + 2] == '#')
            {
                dirAvilib.dir[4] = true;
            }

            if (head.y + 2 >= height)
            {
            }
            else if (type[head.y + 2][head.x] == '#')
            {
                dirAvilib.dir[3] = true;
            }

            if (head.x - 2 < 0)
            {
            }
            else if (type[head.y][head.x - 2] == '#')
            {
                dirAvilib.dir[2] = true;
            }

            if (head.y - 2 < 0)
            {
            }
            else if (type[head.y - 2][head.x] == '#')
            {
                dirAvilib.dir[1] = true;
            }


            if (!dirAvilib.dir[1] &&
                !dirAvilib.dir[2] &&
                !dirAvilib.dir[3] &&
                !dirAvilib.dir[4])
            {
                dirAvilib.dir[0] = true;
            }

            do
            {
                dir = std::rand() % 5;
                if (dirAvilib.dir[0])
                {
                    dir = 0;
                    break;
                }
            } while (!dirAvilib.dir[dir]);

            type[head.y][head.x] = '0';
            switch (static_cast<directions>(dir))
            {
            case directions::NONE:
            {
                processNodes.pop();
                break;
            }
            case directions::up:
            {
                type[head.y - 1][head.x] = '0';
                type[head.y - 2][head.x] = '0';
                processNodes.push(sf::Vector2i(head.x, head.y - 2));
                break;
            }
            case directions::left:
            {
                type[head.y][head.x - 1] = '0';
                type[head.y][head.x - 2] = '0';
                processNodes.push(sf::Vector2i(head.x - 2, head.y));
                break;
            }
            case directions::down:
            {
                type[head.y + 1][head.x] = '0';
                type[head.y + 2][head.x] = '0';
                processNodes.push(sf::Vector2i(head.x, head.y + 2));
                break;
            }
            case directions::right:
            {
                type[head.y][head.x + 1] = '0';
                type[head.y][head.x + 2] = '0';
                processNodes.push(sf::Vector2i(head.x + 2, head.y));

                break;
            }
            }
        }
        
        window.clear();
        for (int y = 0; y < height;y++)
        {
            for (int x = 0; x < width; x++)
            {
                cell.setFillColor(sf::Color::White);
                if (type[y][x] == '#')
                {
                    cell.setFillColor(sf::Color::Black);
                }
                cell.setPosition(cellsPostions[y][x].x, cellsPostions[y][x].y);
                window.draw(cell);
            }
        }
        window.display();
    }

    return 0;
}