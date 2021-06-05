#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

int main(int ac, char* argc[]) {
    const float pi = 3.1415926535;
    const float length1 = 150;
    const float length2 = 150;
    const float mass1 = 10;
    const float mass2 = 10;
    srand(time(0));
    float angle1 = pi/2;
    float angle2 = 0;
    // float angle1 = (rand()%180-90) * pi / 180;
    // float angle2 = (rand()%180-90) * pi / 180;
    float aVel1 = 0;
    float aVel2 = 0;
    float aAcc1 = 0;
    float aAcc2 = 0;
    float g = 1;
    float c = 0.00f;
    sf::Color hsvTorgb(float, float, float);

    sf::RenderWindow win(sf::VideoMode(600, 600), "HELLO WINDOW");
    win.setFramerateLimit(60);
    sf::RenderTexture background;
    background.create(600,600);
    sf::Vector2f offset(win.getSize().x / 2 - mass1, win.getSize().y / 5 - mass1);

    sf::CircleShape circle1(mass1);
    sf::CircleShape circle2(mass2);
    sf::CircleShape trace(2);

    circle1.setOrigin(sf::Vector2f(mass1, mass1));
    circle2.setOrigin(sf::Vector2f(mass2, mass2));

    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        float num1 = -g * (2*mass1 + mass2) * sin(angle1);
        float num2 = mass2 * g * sin(angle1 - 2 * angle2);
        float num3 = 2 * sin(angle1 - angle2) * mass2 * (aVel2 * aVel2 * length2 + aVel1 * aVel1 * length1 * cos(angle1 - angle2));
        float den = 2 * mass1 + mass2 - mass2 * cos(2 * angle1 - 2 * angle2);
        aAcc1 = (num1 - num2 - num3) / (length1 * den);
        
        num1 = 2 * sin(angle1 - angle2);
        num2 = (aVel1 * aVel1 * length1 * (mass1 + mass2) + g * (mass1 + mass2) * cos(angle1) + aVel2 * aVel2 * length2 * mass2 * cos(angle1 - angle2));
        aAcc2 = (num1 * num2) / (length2 * den);
        aVel1 += aAcc1;
        aVel2 += aAcc2;
        angle1 += aVel1;
        angle2 += aVel2;
        if (angle2 >= (2 * pi)) angle2 -= 2*pi;
        if (angle2 <= (0)) angle2 += 2*pi;

        sf::Vector2f pos1(length1 * sin(angle1), length1 * cos(angle1));
        sf::Vector2f pos2(length2 * sin(angle2), length2 * cos(angle2));
        pos2 += pos1;

        circle1.setPosition(offset + pos1);
        circle2.setPosition(offset + pos2);
        trace.setPosition(circle2.getPosition());
        trace.setFillColor(hsvTorgb(angle2,1,0.5));
        
        sf::Vertex line1[] = {
            sf::Vertex(offset+sf::Vector2f(mass1,mass1)), sf::Vertex(circle1.getPosition()) };
        sf::Vertex line2[] = {
            line1[1], sf::Vertex(circle2.getPosition()) };

        background.draw(trace);
        background.display();

        win.clear();
        win.draw(sf::Sprite(background.getTexture()));
        win.draw(line1, 2, sf::Lines);
        win.draw(circle1);
        win.draw(line2, 2, sf::Lines);
        win.draw(circle2);
        win.display();
    }

    return 0;
}


sf::Color hsvTorgb(float h, float s, float v){
    sf::Color output;
    h *= (180/3.1415926535);
    std::cout << h << '\n';
    int x = floor(h/60);
    float C = s * v;
    float X = C * (1 - abs(x%2-1));
    float m = v - C;
    if (0 <= h && h < 60){
        output.r = (C+m)*255;
        output.g = (X+m)*255;
        output.b = (0+m)*255;
    }else if (60 <= h && h < 120){
        output.r = (X+m)*255;
        output.g = (C+m)*255;
        output.b = (0+m)*255;
    }else if (120 <= h && h < 180){
        output.r = (0+m)*255;
        output.g = (C+m)*255;
        output.b = (X+m)*255;
    }else if (180 <= h && h < 240){
        output.r = (0+m)*255;
        output.g = (X+m)*255;
        output.b = (C+m)*255;
    }else if (240 <= h && h < 300){
        output.r = (X+m)*255;
        output.g = (0+m)*255;
        output.b = (C+m)*255;
    }else if (300 <= h && h < 360){
        output.r = (C+m)*255;
        output.g = (0+m)*255;
        output.b = (X+m)*255;
    }

    return output;
}