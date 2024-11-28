#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

float delay;
int vitesse;
int vies = 3;
int scoremulti;
int inv_delay;
int explosion_delay;
bool meteor1b = false;
bool meteor2b = false;
bool meteor3b = false;
bool meteor4b = false;
bool canShoot = true;
bool shooting = false;
bool gameover = false;
bool startscreen = true;
bool invicibilityb = false;
bool inv_state = false;


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "A Travers la Ceinture v0.8");
    Clock scoreclock;
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

    // Textes :

    Text aff_gameover("GAME OVER", font, 100);
    aff_gameover.setPosition(560, 350);

    Text aff_score("Score : 0", font, 50);
    aff_score.setPosition(800, 90);

    Text title("A TRAVERS LA \n   CEINTURE", font, 120);
    title.setFillColor(Color::Color(0x008dd2ff));
    title.setPosition(400, 75);

    Text easyText("EASY", font, 30);
    easyText.setFillColor(Color::Black);

    Text mediumText("MEDIUM", font, 30);
    mediumText.setFillColor(Color::Black);

    Text hardText("HARD", font, 30);
    hardText.setFillColor(Color::Black);

    Text aff_can_shoot("FIRE", font, 20);
    aff_can_shoot.setPosition(1522, 112);
    aff_can_shoot.setFillColor(Color::Black);


    // Textures :

    Texture life;
    if (!life.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\coeur.png")){
        return -1;}

    Texture meteor;
    if (!meteor.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\meteor.png")) {
        return -1;
    }

    Texture explosionT;
    if (!explosionT.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\boom.png")) {
        return -1;
    }

    Texture inv_shield;
    if (!inv_shield.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\shield.png")) {
        return -1;
    }

    Texture spacecraft;
    if (!spacecraft.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\spacecraft.png")) {
        return -1;
    }

    Texture spacecraft_inv;
    if (!spacecraft_inv.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\spacecraft_inv.png")) {
        return -1;
    }

    Texture background;
    if (!background.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\space.jpg")) {
        return -1;
    }

    Texture button_on;
    if (!button_on.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\button_on.png")) {
        return -1;
    }

    Texture button_off;
    if (!button_off.loadFromFile("C:\\Users\\sbrossard\\source\\repos\\Corroder-S\\Projet_SFML\\button_off.png")) {
        return -1;
    }


    // Objets :

    Sprite backgroundimage(background);

    CircleShape explosion(70);
    explosion.setTexture(&explosionT);

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
    
    CircleShape can_shoot_indicator(50);
    can_shoot_indicator.setPosition(1500, 75);
    can_shoot_indicator.setFillColor(Color::Green);

    CircleShape invincibility(50);
    invincibility.setPosition(2000, 700);
    invincibility.setTexture(&inv_shield);

    RectangleShape vaisseau(Vector2f(200, 50));
    vaisseau.setPosition(200, 500);
    vaisseau.setTexture(&spacecraft);

    
    RectangleShape missile(Vector2f(2000, 20));
    missile.setFillColor(Color::Blue);

    RectangleShape easy(Vector2f(200, 100));
    easy.setPosition(830, 450);
    easy.setTexture(&button_off);
    easyText.setOrigin(easyText.getGlobalBounds().getSize() / 2.f + easyText.getLocalBounds().getPosition());
    easyText.setPosition(easy.getPosition() + (easy.getSize() / 2.f));

    RectangleShape medium(Vector2f(200, 100));
    medium.setPosition(830, 600);
    medium.setTexture(&button_off);
    mediumText.setOrigin(mediumText.getGlobalBounds().getSize() / 2.f + mediumText.getLocalBounds().getPosition());
    mediumText.setPosition(medium.getPosition() + (medium.getSize() / 2.f));



    RectangleShape hard(Vector2f(200, 100));
    hard.setPosition(830, 750);
    hard.setTexture(&button_off);
    hardText.setOrigin(hardText.getGlobalBounds().getSize() / 2.f + hardText.getLocalBounds().getPosition());
    hardText.setPosition(hard.getPosition() + (hard.getSize() / 2.f));

    
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        if (!gameover && !startscreen) scorecount = scoreclock.getElapsedTime().asSeconds() * scoremulti;
        String score = to_string(scorecount);
        aff_score.setString("Score : " + score);
        int x = vaisseau.getPosition().x;
        int y = vaisseau.getPosition().y + 15;
        missile.setPosition(Vector2f(x, y));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Boutons :

            if (event.type == Event::MouseButtonPressed && startscreen) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (easy.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y )){
                        startscreen = false;
                        vitesse = 20;
                        delay = 2.0f;
                        scoremulti = 100;
                    }
                    if (medium.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
                        startscreen = false;
                        vitesse = 30;
                        delay = 1.5f;
                        scoremulti = 200;
                    }
                    if (hard.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
                        startscreen = false;
                        vitesse = 40;
                        delay = 1.0f;
                        scoremulti = 400;
                    }
                    
                }
            }
            
            // Collision des météores avec le missile/laser :

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

    // Texture changeante des boutons :

        if (easy.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) easy.setTexture(&button_on);
        else easy.setTexture(&button_off);
        if (medium.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) medium.setTexture(&button_on);
        else medium.setTexture(&button_off);
        if (hard.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) hard.setTexture(&button_on);
        else hard.setTexture(&button_off);
            


    // Scrolling météores et power up:

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

    if (invicibilityb) {
        invincibility.move(-vitesse / 2, 0);
        if (invincibility.getPosition().x < -100) {
            invicibilityb = false;
            inv_delay = 600;
        }
    }

    // Movement du vaisseau :

    if (Keyboard::isKeyPressed(Keyboard::Up) && vaisseau.getPosition().y > 0) {
        vaisseau.move(0, -vitesse/2);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) && vaisseau.getPosition().y < 950) {
        vaisseau.move(0, +vitesse/2);
    }

    if (inv_delay > 600)
        vaisseau.setTexture(&spacecraft_inv);
    else
        vaisseau.setTexture(&spacecraft);

    // Collisions avec météores et power up : 

    if (vaisseau.getGlobalBounds().intersects(meteor1.getGlobalBounds()) && meteor1b && inv_delay <= 600) {
        meteor1b = false;
        vies--;
        explosion.setPosition(meteor1.getPosition());
        explosion_delay = 60;
    }
    if (vaisseau.getGlobalBounds().intersects(meteor2.getGlobalBounds()) && meteor2b && inv_delay <= 600) {
        meteor2b = false;
        vies--;
        explosion.setPosition(meteor2.getPosition());
        explosion_delay = 60;
    }
    if (vaisseau.getGlobalBounds().intersects(meteor3.getGlobalBounds()) && meteor3b && inv_delay <= 600) {
        meteor3b = false;
        vies--;
        explosion.setPosition(meteor3.getPosition());
        explosion_delay = 60;
    }
    if (vaisseau.getGlobalBounds().intersects(meteor4.getGlobalBounds()) && meteor4b && inv_delay <= 600) {
        meteor4b = false;
        vies--;
        explosion.setPosition(meteor4.getPosition());
        explosion_delay = 60;
    }

    if (vaisseau.getGlobalBounds().intersects(invincibility.getGlobalBounds()) && invicibilityb) {
        invicibilityb = false;
        inv_state = true;
        inv_delay = 900;
    }

    // Cooldown du tir :

    cd = shoot.getElapsedTime().asSeconds();

    if (cd >= 3 and canShoot == false){
        canShoot = true;
    }

    temps = clock.getElapsedTime().asSeconds();
    

    // Boucle de création des météores :

    if (temps >= delay && !startscreen && !gameover)
    {
        for (int i = 0; i < 3; i++) {
            int x = rand() % 4;
            switch (x) {
            case 0: if (meteor1b == false) meteor1.setPosition(2000, 100); meteor1b = true; break;
            case 1: if (meteor2b == false) meteor2.setPosition(2000, 300); meteor2b = true; break;
            case 2: if (meteor3b == false) meteor3.setPosition(2000, 500); meteor3b = true; break;
            case 3: if (meteor4b == false) meteor4.setPosition(2000, 700); meteor4b = true; break;
            }
        }
        clock.restart();
    }

    // Apparition du power up d'invicibilité :

    if (!invicibilityb && !startscreen && !gameover && inv_delay == 0) {
        int spawn = rand() % 100;
        if (spawn < 2) {
            int x = rand() % 700;
            invincibility.setPosition(2000, x + 100);
            invicibilityb = true;
        }
    }

    // Display de l'écran de départ :

    if (startscreen) {
        window.clear();
        window.draw(backgroundimage);
        window.draw(easy);
        window.draw(easyText);
        window.draw(medium);
        window.draw(mediumText);
        window.draw(hard);
        window.draw(hardText);
        window.draw(title);
        window.display();
        scoreclock.restart();
    }

    // Display de la phase de jeu :

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
            if (invicibilityb)
                window.draw(invincibility);
            if (shooting){
                window.draw(missile);
                shooting = false;}
            window.draw(vaisseau);
            if (explosion_delay > 0) {
                window.draw(explosion);
                explosion_delay--;
            }
            window.display();
            temps++;
            if (inv_delay > 0)
                inv_delay--;
        }

    // Display de l'écran de game over :

    else if(gameover){
        
        window.clear();
        window.draw(backgroundimage);
        window.draw(aff_gameover);
        window.draw(aff_score);
        window.display();
    }
    }
    return 0;
}

