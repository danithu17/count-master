#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(400, 700), "Count Master Clone");
    window.setFramerateLimit(60);

    // Player (Crowd Leader)
    CircleShape player(15.f);
    player.setFillColor(Color::Cyan);
    player.setOutlineThickness(2);
    player.setOutlineColor(Color::White);
    player.setPosition(185, 600);

    int crowdCount = 1;

    // Gate 1 (Addition Gate - Blue)
    RectangleShape gateAdd(150.f, 40.f);
    gateAdd.setFillColor(Color(0, 0, 255, 150));
    gateAdd.setPosition(30, 200);

    // Gate 2 (Multiplication Gate - Red)
    RectangleShape gateMult(150.f, 40.f);
    gateMult.setFillColor(Color(255, 0, 0, 150));
    gateMult.setPosition(220, 200);

    // Font Loading (Make sure to push arial.ttf to github too)
    Font font;
    font.loadFromFile("arial.ttf"); 

    Text uiText;
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setPosition(10, 10);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        // Movement
        if (Keyboard::isKeyPressed(Keyboard::Left) && player.getPosition().x > 0) player.move(-5.f, 0.f);
        if (Keyboard::isKeyPressed(Keyboard::Right) && player.getPosition().x < 370) player.move(5.f, 0.f);

        // Simple Collision Logic
        FloatRect playerBound = player.getGlobalBounds();
        if (playerBound.intersects(gateAdd.getGlobalBounds())) {
            crowdCount += 10; 
            gateAdd.setPosition(-500, -500); // Remove gate after hit
        }
        if (playerBound.intersects(gateMult.getGlobalBounds())) {
            crowdCount *= 2;
            gateMult.setPosition(-500, -500);
        }

        uiText.setString("CROWD: " + std::to_string(crowdCount));

        window.clear(Color(30, 30, 30)); // Dark Road
        
        // Draw UI Elements
        window.draw(gateAdd);
        window.draw(gateMult);
        window.draw(player);
        window.draw(uiText);
        
        window.display();
    }
    return 0;
}

