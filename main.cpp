#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

bool meteor1b = true;
bool meteor2b = true;
bool meteor3b = true;
bool meteor4b = true;

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fenêtre SFML");

    CircleShape meteor1(70);
    meteor1.setPosition(1700, 100);

    CircleShape meteor2(70);
    meteor2.setPosition(1700, 300);

    CircleShape meteor3(70);
    meteor3.setPosition(1700, 500);

    CircleShape meteor4(70);
    meteor4.setPosition(1700, 700);

    RectangleShape vaisseau(Vector2f(200, 50));
    vaisseau.setPosition(200, 500);

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            }
            
    if (meteor1b) {
        meteor1.move(-10, 0);
        if (meteor1.getPosition().x < 0) {
            meteor1b = false;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        vaisseau.move(0, -10);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        vaisseau.move(0, +10);
    }
    
        
        window.clear();
        if (meteor1b)
            window.draw(meteor1);
        window.draw(vaisseau);
        window.display();
    }

    return 0;
}