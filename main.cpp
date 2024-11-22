#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

int vies = 3;
bool meteor1b = false;
bool meteor2b = false;
bool meteor3b = false;
bool meteor4b = false;


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fenêtre SFML");
    Clock clock;
    float temps = 0;
    srand(time(0));
    CircleShape meteor1(70);
    meteor1.setPosition(2000, 100);

    CircleShape meteor2(70);
    meteor2.setPosition(2000, 300);

    CircleShape meteor3(70);
    meteor3.setPosition(2000, 500);

    CircleShape meteor4(70);
    meteor4.setPosition(2000, 700);

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
        meteor1.move(-20, 0);
        if (meteor1.getPosition().x < -100) {
            meteor1b = false;
        }
    }
    if (meteor2b) {
        meteor2.move(-20, 0);
        if (meteor2.getPosition().x < -100) {
            meteor2b = false;
        }
    }
    if (meteor3b) {
        meteor3.move(-20, 0);
        if (meteor3.getPosition().x < -100) {
            meteor3b = false;
        }
    }
    if (meteor4b) {
        meteor4.move(-20, 0);
        if (meteor4.getPosition().x < -100) {
            meteor4b = false;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        vaisseau.move(0, -10);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        vaisseau.move(0, +10);
    }
    if (vaisseau.getGlobalBounds().intersects(meteor1.getGlobalBounds()) && meteor1b) {
        meteor1b = false;
        vies--;
    }
    if (vaisseau.getGlobalBounds().intersects(meteor2.getGlobalBounds()) && meteor2b) {
        meteor2b = false;
        vies--;
    }
    if (vaisseau.getGlobalBounds().intersects(meteor3.getGlobalBounds()) && meteor3b) {
        meteor3b = false;
        vies--;
    }
    if (vaisseau.getGlobalBounds().intersects(meteor4.getGlobalBounds()) && meteor4b) {
        meteor4b = false;
        vies--;
    }

    temps = clock.getElapsedTime().asSeconds();

    if (temps >= 2.0f)
    {
        for (int i = 0; i < 3; i++){
        int x = rand() % 4;
        switch (x) {
        case 0:meteor1.setPosition(2000, 100); meteor1b = true; break;
        case 1:meteor2.setPosition(2000, 300); meteor2b = true; break;
        case 2:meteor3.setPosition(2000, 500); meteor3b = true; break;
        case 3:meteor4.setPosition(2000, 700); meteor4b = true; break;
        }
        }
        clock.restart();
    
    }
    if (vies == 0) {
        window.close();
        }
        window.clear();
        if (meteor1b)
            window.draw(meteor1);
        if (meteor2b)
            window.draw(meteor2);
        if (meteor3b)
            window.draw(meteor3);
        if (meteor4b)
            window.draw(meteor4);
        window.draw(vaisseau);
        window.display();
        temps++;
        
    }

    return 0;
}