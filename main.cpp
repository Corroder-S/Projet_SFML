#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

float delay;
int vitesse;
int vies = 3;
bool meteor1b = false;
bool meteor2b = false;
bool meteor3b = false;
bool meteor4b = false;
bool canShoot = true;
bool shooting = false;
bool gameover = false;
bool startscreen = true;

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Fenêtre SFML");
    Clock global;
    Clock clock;
    Clock shoot;
    int scorecount;
    float temps = 0;
    float cd = 0;
    srand(time(0));

    Font font;
    if (!font.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\scifie.ttf")) {
        return -1;
    }

    Text aff_gameover("GAME OVER", font, 100);
    aff_gameover.setPosition(560, 350);

    Text aff_score("Score : 0", font, 50);
    aff_score.setPosition(800, 90);

    Text aff_can_shoot("FIRE", font, 20);
    aff_can_shoot.setPosition(1522, 112);
    aff_can_shoot.setFillColor(Color::Black);

    Texture life;
    if (!life.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\coeur.png")){
        return -1;}

    Texture meteor;
    if (!meteor.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\meteor.png")) {
        return -1;
    }

    Texture spacecraft;
    if (!spacecraft.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\spacecraft.png")) {
        return -1;
    }

    Texture background;
    if (!background.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\space.jpg")) {
        return -1;
    }

    Sprite backgroundimage(background);

    CircleShape coeur(50);
    coeur.setPosition(100, 75);
    coeur.setTexture(&life);

    CircleShape meteor1(70);
    meteor1.setPosition(2000, 100);
    meteor1.setTexture(&meteor);

    CircleShape meteor2(70);
    meteor2.setPosition(2000, 300);
    meteor2.setTexture(&meteor);

    CircleShape meteor3(70);
    meteor3.setPosition(2000, 500);
    meteor3.setTexture(&meteor);

    CircleShape meteor4(70);
    meteor4.setPosition(2000, 700);
    meteor4.setTexture(&meteor);

    RectangleShape vaisseau(Vector2f(200, 50));
    vaisseau.setPosition(200, 500);
    vaisseau.setTexture(&spacecraft);
    
    RectangleShape missile(Vector2f(2000, 20));
    missile.setFillColor(Color::Blue);

    RectangleShape can_shoot_indicator(Vector2f(100, 100));
    can_shoot_indicator.setPosition(1500, 75);
    can_shoot_indicator.setFillColor(Color::Green);

    RectangleShape easy(Vector2f(200, 100));
    easy.setPosition(700, 400);
    easy.setFillColor(Color::Black);

    RectangleShape medium(Vector2f(200, 100));
    medium.setPosition(700, 550);
    medium.setFillColor(Color::Black);

    RectangleShape hard(Vector2f(200, 100));
    hard.setPosition(700, 700);
    hard.setFillColor(Color::Black);
    
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        if (!gameover) scorecount = global.getElapsedTime().asSeconds() * 100;
        String score = to_string(scorecount);
        aff_score.setString("Score : " + score);
        int x = vaisseau.getPosition().x;
        int y = vaisseau.getPosition().y + 15;
        missile.setPosition(Vector2f(x, y));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed && startscreen) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (easy.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y )){
                        startscreen = false;
                        vitesse = 20;
                        delay = 2.0f;
                    }
                    if (medium.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y)) {
                        startscreen = false;
                        vitesse = 30;
                        delay = 1.5f;
                    }
                    if (hard.getGlobalBounds().contains(Mouse::getPosition().x, Mouse::getPosition().y)) {
                        startscreen = false;
                        vitesse = 40;
                        delay = 1.0f;
                    }
                    
                }
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space && canShoot) {
                    if (missile.getGlobalBounds().intersects(meteor1.getGlobalBounds()) && meteor1b)
                        meteor1b = false;
                    if (missile.getGlobalBounds().intersects(meteor2.getGlobalBounds()) && meteor2b)
                        meteor2b = false;
                    if (missile.getGlobalBounds().intersects(meteor3.getGlobalBounds()) && meteor3b)
                        meteor3b = false;
                    if (missile.getGlobalBounds().intersects(meteor4.getGlobalBounds()) && meteor4b)
                        meteor4b = false;
                    shooting = true;
                    canShoot = false;
                    shoot.restart();
                }
            }
        }
            
    if (meteor1b) {
        meteor1.move(-vitesse, 0);
        if (meteor1.getPosition().x < -100) {
            meteor1b = false;
        }
    }
    if (meteor2b) {
        meteor2.move(-vitesse, 0);
        if (meteor2.getPosition().x < -100) {
            meteor2b = false;
        }
    }
    if (meteor3b) {
        meteor3.move(-vitesse, 0);
        if (meteor3.getPosition().x < -100) {
            meteor3b = false;
        }
    }
    if (meteor4b) {
        meteor4.move(-vitesse, 0);
        if (meteor4.getPosition().x < -100) {
            meteor4b = false;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        vaisseau.move(0, -vitesse/2);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        vaisseau.move(0, +vitesse/2);
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

    cd = shoot.getElapsedTime().asSeconds();

    if (cd >= 3 and canShoot == false){
        canShoot = true;
    }

    temps = clock.getElapsedTime().asSeconds();
    


    if (temps >= delay)
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
    if (startscreen) {
        window.clear();
        window.draw(backgroundimage);
        window.draw(easy);
        window.draw(medium);
        window.draw(hard);
        window.display();
    }
    else if (!gameover){
        if (vies == 0) {
            gameover = true;
            aff_score.setPosition(610, 550);
            aff_score.setString("Score final : " + score);
            }
            window.clear();
            window.draw(backgroundimage);
            window.draw(aff_score);
            window.draw(coeur);
              if (vies >= 2) {
                  coeur.setPosition(200, 75);
                  window.draw(coeur);
                  if (vies == 3) {
                      coeur.setPosition(300, 75);
                      window.draw(coeur);
                    }
                }
            coeur.setPosition(100, 75);
            if (canShoot) {
                window.draw(can_shoot_indicator);
            }
            else {
                can_shoot_indicator.setFillColor(Color::Red);
                window.draw(can_shoot_indicator);
                can_shoot_indicator.setFillColor(Color::Green);
            }
            window.draw(aff_can_shoot);
            if (meteor1b)
                window.draw(meteor1);
            if (meteor2b)
                window.draw(meteor2);
            if (meteor3b)
                window.draw(meteor3);
            if (meteor4b)
                window.draw(meteor4);
            if (shooting){
                window.draw(missile);
                shooting = false;}
            window.draw(vaisseau);
            window.display();
            temps++;
        }
    else {
        
        window.clear();
        window.draw(backgroundimage);
        window.draw(aff_gameover);
        window.draw(aff_score);
        window.display();
    }
    }
    return 0;
}