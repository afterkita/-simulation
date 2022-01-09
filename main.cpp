#include <SFML/Graphics.hpp>
#include <vector>


#define width 1000
#define heigh 650
using namespace sf;
class Balloon
{
public:
    Balloon()
    {
        
        
        m_speed = rand()%10-3;
        m_speedy = rand() % 10 - 3;;
        m_r = 20;
        m_circle = new sf::CircleShape(m_r);
        m_circle->setFillColor(sf::Color(130-20*(m_speed+m_speed),0, 0));
        m_circle->setOrigin(0 + m_r, 0 + m_r);
        m_circle->setPosition(rand() % (3 * m_r + (width - (4 * m_r))),rand() % (3 * m_r + (heigh - (4 * m_r))));
        Vector2f m_position = m_circle->getPosition();
       
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
    int GetY()
    {
        return m_y;
    }
    int GetX()
    {
        return m_x;
    }
    int GetR()
    {
        return m_r;
    }
    void SetX(int x)
    {
        m_position.x  = x;
    }
    void SetY(int y)
    {
        m_position.y = y;
    }
    void SetColor(int r,int g,int b)
    {
        m_circle->setFillColor(sf::Color(r,g,b));
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
        m_position.x += m_speed ;
        m_circle->setPosition(m_position);
        if ((m_speedy > 0 && m_position.y + m_r > heigh) ||
            (m_speedy < 0 && m_position.y - m_r < 0))
        {
            m_speedy = -m_speedy;
            m_circle->rotate(180.0f);
        }
        m_position.y += m_speedy;
        m_circle->setPosition(m_position);
    }


   


private:
    int m_x, m_y, m_r, m_type, m_speed,m_speedy;
    Vector2f m_position;
    sf::CircleShape* m_circle = nullptr;
};
int main()
{
    srand(time(0));
    std::vector<Balloon*> ballons; // Инициализация вектора с шарами для игры и создание первых фигур
    for (int i = 0;i < 20;i++) // 20 Шаров с начала
    {
        ballons.push_back(new Balloon());

    }
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
        
       
        for (const auto& circle : ballons)
        {
            circle->Move();
            window.draw(*circle->Get());
        }
        window.display();
    }

    return 0;
}