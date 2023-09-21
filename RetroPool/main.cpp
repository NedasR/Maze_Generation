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
    sf::RenderWindow window(sf::VideoMode(400,400), "SFML works!");
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
    sf::Texture mazeTex;
    sf::Image mazeImage;
    mazeImage.create(6, 6, sf::Color::White);
    sf::RenderWindow window(sf::VideoMode(600, 600), "Maze generation!" /*sf::Style::Fullscreen*/);;
    std::cout << mazeTex.create(window.getSize().x, window.getSize().y) << std::endl;
    //window.setFramerateLimit(120);
    sf::RectangleShape cell(sf::Vector2f(window.getSize().x, window.getSize().y));
    cell.setPosition(sf::Vector2f(0.0f,0.0f));
    cell.setTexture(&mazeTex);
    sf::Clock clock;
    sf::Time time;
    bool oneTimeStamp = true;

    std::vector<std::vector<char>> type;

    int Cellsize = mazeImage.getSize().x;
    int width = window.getSize().x;
    int height = window.getSize().y;

    type.resize(height);
    for (int y = 0; y < height; y++)
    {
        type[y].resize(width);
        for (int x = 0; x < width; x++)
        {
            type[y][x] = '#';
        }
    }

    sf::Vector2i temphead(0,0);
    std::vector<int> nums;
    std::stack<sf::Vector2i> processNodes;
    processNodes.push(temphead);
    int dir = 0;
    directionAvilib dirAvilib;
    std::srand(std::time(nullptr));
    sf::Vector2i head(0, 0);
    bool start = false;
    int condition = 0;
    while (window.isOpen())
    {
        condition++;
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
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
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

            if (head.x + Cellsize * 2 >= width)
            {
            }
            else if (type[head.y][head.x + Cellsize * 2] == '#')
            {
                dirAvilib.dir[4] = true;
                nums.push_back(4);
            }

            if (head.y + Cellsize * 2 >= height)
            {
            }
            else if (type[head.y + Cellsize * 2][head.x] == '#')
            {
                dirAvilib.dir[3] = true;
                nums.push_back(3);
            }

            if (head.x - Cellsize * 2 < 0)
            {
            }
            else if (type[head.y][head.x - Cellsize * 2] == '#')
            {
                dirAvilib.dir[2] = true;
                nums.push_back(2);
            }

            if (head.y - Cellsize * 2 < 0)
            {
            }
            else if (type[head.y - Cellsize * 2][head.x] == '#')
            {
                dirAvilib.dir[1] = true;
                nums.push_back(1);
            }


            if (!dirAvilib.dir[1] &&
                !dirAvilib.dir[2] &&
                !dirAvilib.dir[3] &&
                !dirAvilib.dir[4])
            {
                dirAvilib.dir[0] = true;
                dir = 0;
            } else {
                do
                {
                    if (nums.size() == 1)
                    {
                        dir = nums[0];
                    } else
                    {
                        dir = nums[std::rand() % nums.size()];
                    }
                    nums.clear();

                } while (!dirAvilib.dir[dir]);
            }
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
                type[head.y - Cellsize][head.x] = '0';
                type[head.y - Cellsize * 2][head.x] = '0';
                processNodes.push(sf::Vector2i(head.x, head.y - Cellsize * 2));
                mazeTex.update(mazeImage, head.x, head.y - Cellsize);
                mazeTex.update(mazeImage, head.x, head.y - Cellsize * 2);
                break;
            }
            case directions::left:
            {
                type[head.y][head.x - Cellsize] = '0';
                type[head.y][head.x - Cellsize * 2] = '0';
                processNodes.push(sf::Vector2i(head.x - Cellsize * 2, head.y));
                mazeTex.update(mazeImage, head.x - Cellsize, head.y);
                mazeTex.update(mazeImage, head.x - Cellsize * 2, head.y);
                break;
            }

            case directions::down:
            {
                type[head.y + Cellsize][head.x] = '0';
                type[head.y + Cellsize * 2][head.x] = '0';
                processNodes.push(sf::Vector2i(head.x, head.y + Cellsize * 2));
                mazeTex.update(mazeImage, head.x, head.y + Cellsize);
                mazeTex.update(mazeImage, head.x, head.y + Cellsize * 2);
                break;
            }
            case directions::right:
            {
                type[head.y][head.x + Cellsize] = '0';
                type[head.y][head.x + Cellsize * 2] = '0';
                processNodes.push(sf::Vector2i(head.x + Cellsize * 2, head.y));
                mazeTex.update(mazeImage, head.x + Cellsize, head.y);
                mazeTex.update(mazeImage, head.x + Cellsize * 2, head.y );
                break;
            }
            }
        }
        else if (oneTimeStamp && start)
        {
            time = clock.getElapsedTime();
            oneTimeStamp = false;
            std::cout << time.asSeconds();
        } else {clock.restart(); }
        if(condition % 3 == 0)
        {

            window.clear();
            for (int y = 0; y < 1; y++)
            {
                for (int x = 0; x < 1; x++)
                {

                    if (type[y][x] == '#')
                    {
                        continue;
                    }
                    window.draw(cell);
                }
            }
            window.display();
        }
    }

    return 0;
}