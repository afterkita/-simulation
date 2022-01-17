#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define width 1000
#define heigh 650
using namespace sf;

class Balloon
{
public:
    Balloon()
    {


        m_speed = rand() % 10 - 3;
        m_speedy = rand() % 10 - 3;;
        m_r = 20;
        m_circle = new sf::CircleShape(m_r);
        m_circle->setFillColor(sf::Color(130 - 20 * (m_speed + m_speed), 0, 0));
        m_circle->setOrigin(0 + m_r, 0 + m_r);
        m_circle->setPosition(rand() % (3 * m_r + (width - (4 * m_r))), rand() % (3 * m_r + (heigh - (4 * m_r))));

        Vector2f m_position = m_circle->getPosition();
        m_x = m_position.x;
        m_y = m_position.y;
    }
    ~Balloon()
    {

    }
    sf::CircleShape* Get()
    {
        return m_circle;
    }

    void SetSpeed(int speed)
    {
        m_speed = speed;
    }
    int GetR()
    {

        return m_r;
    }
    int GetX()
    {
        return m_x;
    }
    int GetY()
    {
        return m_y;
    }
    void SetX(int x)
    {
        m_position.x = x;
    }
    void SetY(int y)
    {
        m_position.y = y;
    }
    void SetColor(int r, int g, int b)
    {
        m_circle->setFillColor(sf::Color(r, g, b));
    }

    void Move()
    {
        m_position = m_circle->getPosition();
        if ((m_speed > 0 && m_position.x + m_r > width) ||
            (m_speed < 0 && m_position.x - m_r < 0))
        {
            m_speed = -m_speed;
            m_circle->rotate(180.0f);
        }
        m_position.x += m_speed;
        m_circle->setPosition(m_position);
        if ((m_speedy > 0 && m_position.y + m_r > heigh) ||
            (m_speedy < 0 && m_position.y - m_r < 0))
        {
            m_speedy = -m_speedy;
            m_circle->rotate(180.0f);
        }
        m_position.y += m_speedy;
        m_circle->setPosition(m_position);
        m_x += m_speed;
        m_y += m_speedy;
    }

private:
    int m_x, m_y, m_r, m_type, m_speed, m_speedy;
    Vector2f m_position;
    sf::CircleShape* m_circle = nullptr;
};
/*
int kos(int s, std::vector<Balloon*> ballons)
{
    int r = ballons[s]->GetR();
    int l = ballons.size();
    
    
    
    int v1, v2, v3;
    for (int i = 0;i < l;i++)
    {
        if (i == s)
        {
            return -1;
        }
        else
        {
            sf::CircleShape circle2 = *ballons[s]->Get();

            Vector2f position2 = circle2.getPosition();
            sf::CircleShape circle1 = *ballons[i]->Get();
            Vector2f position1 = circle1.getPosition();
            int xs = position2.x;
            int ys = position2.y;
            int x = position1.x;
            int y = position1.y;
            v1 = abs(xs - x);
            v2 = abs(ys - y);
            v3 = sqrt(v1 * v1 + v2 * v2);
            if (v3 <= (r * 2))
            {
                return i;
            }
            else
            {

            }
            {
                return -1;
            }
        }


    }

}
*/
int kos(Balloon b1,Balloon b2)
{
    int r1, r2, x1, x2, y1, y2, v3;
    r1 = b1.GetR();
    r2 = b2.GetR();
    x1 = b1.GetX();
    y1 = b1.GetY();
    x2 = b2.GetX();
    y2 = b2.GetY();
    v3 = sqrt((abs(x1 - x2) * abs(x1 - x2))) + ((abs(y1 - y2) * abs(y1 - y2)));
    if (v3 > 1)
    {
        if (v3 <= (r1+r2))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}
int main()
{
    int N = 20; // Количество шаров
    srand(time(0));
    std::vector<Balloon*> ballons; // Инициализация вектора с шарами для игры и создание первых фигур
    for (int i = 0;i < N;i++) // 20 Шаров с начала
    {
        ballons.push_back(new Balloon());
        
    }
    int uy = 0;
    for (const auto& circle : ballons)
    {
        circle->SetColor(100, uy*20,100);
        uy++;
    }

    sf::CircleShape circle2 = *ballons[0]->Get();
    int position1;
    Vector2f position2;
    position1 = circle2.getPointCount();
    std::cout << position1;
    sf::RenderWindow window(sf::VideoMode(width, heigh), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(Color(100, 100, 100, 0));

        int yi = 0;
        for (const auto& circle1 : ballons)
        {
            for (const auto& circle2 : ballons)
            {
                if (circle1 != circle2)
                {
                    if (kos(*circle1, *circle2) == 1)
                    {
                        circle2->SetColor(0, 0, 100);
                    }
                }
                
            }
        }
        for (const auto& circle : ballons)
        {
            circle->Move();
            window.draw(*circle->Get());
            yi++;
        }

        window.display();
    }

    return 0;
}