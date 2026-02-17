#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(450, 700), "Count Master PC v1.0");
    window.setFramerateLimit(60);

    int crowdCount = 1;
    
    // Leader Player
    CircleShape leader(12.f);
    leader.setFillColor(Color(0, 200, 255));
    leader.setOutlineThickness(2);
    leader.setPosition(215, 600);

    // Crowd Visuals (Followers)
    std::vector<CircleShape> followers;

    // Gates
    RectangleShape gate(180.f, 50.f);
    gate.setFillColor(Color(0, 0, 255, 180));
    gate.setPosition(20, 150);
    bool gateActive = true;

    Font font;
    font.loadFromFile("arial.ttf"); 
    Text txt;
    txt.setFont(font);
    txt.setCharacterSize(22);
    txt.setPosition(20, 20);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        // Movement
        if (Keyboard::isKeyPressed(Keyboard::Left) && leader.getPosition().x > 10) leader.move(-6.f, 0.f);
        if (Keyboard::isKeyPressed(Keyboard::Right) && leader.getPosition().x < 420) leader.move(6.f, 0.f);

        // Gate Logic
        if (gateActive && leader.getGlobalBounds().intersects(gate.getGlobalBounds())) {
            crowdCount += 15; // +15 people
            gateActive = false;
            
            // Add followers visually
            for(int i=0; i<15; i++) {
                CircleShape f(8.f);
                f.setFillColor(Color(0, 150, 255, 150));
                followers.push_back(f);
            }
        }

        window.clear(Color(40, 40, 40));

        // Draw Followers (Offsetting them behind leader)
        for(size_t i=0; i<followers.size(); i++) {
            float ox = (i % 5) * 15 - 30; // 5 columns
            float oy = (i / 5) * 15 + 30; // rows behind
            followers[i].setPosition(leader.getPosition().x + ox, leader.getPosition().y + oy);
            window.draw(followers[i]);
        }

        if(gateActive) {
            window.draw(gate);
            Text gt("+15", font, 20);
            gt.setPosition(gate.getPosition().x + 70, gate.getPosition().y + 10);
            window.draw(gt);
        }

        txt.setString("CROWD: " + std::to_string(crowdCount));
        window.draw(leader);
        window.draw(txt);
        window.display();
    }
    return 0;
}

