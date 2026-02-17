#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(400, 600), "C++ Count Master");
    window.setFramerateLimit(60);

    // Player Shape (Blue Circle)
    CircleShape player(20.f);
    player.setFillColor(Color::Blue);
    player.setPosition(180, 500);

    int crowdCount = 1;

    // Font and Text
    Font font;
    if (!font.loadFromFile("arial.ttf")) return -1; // Need a font file
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        // Controls
        if (Keyboard::isKeyPressed(Keyboard::Left) && player.getPosition().x > 0)
            player.move(-5.f, 0.f);
        if (Keyboard::isKeyPressed(Keyboard::Right) && player.getPosition().x < 360)
            player.move(5.f, 0.f);

        scoreText.setString("Crowd: " + std::to_string(crowdCount));

        window.clear(Color(50, 50, 50)); // Road color
        window.draw(player);
        window.draw(scoreText);
        window.display();
    }
    return 0;
}