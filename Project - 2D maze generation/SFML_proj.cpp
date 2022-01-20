#include<iostream>
#include <SFML/Graphics.hpp>
#include <array>

//int main() {
	// create the window
	//sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	//system("pause");

//#include <SFML/Graphics.hpp>

void modulate(sf::VertexArray& points, double hue) {
    // First, Let's "sanitize" inputs a bit.
    // Don't accept negative numbers.
    if (hue < 0)
        hue = 0;
    // Lazy overflow by subtracting the integer portion of the number.
    else if (hue > 1)
        hue -= static_cast<int>(hue);

    // Now iterate over all "pixels" and upate their colors.
    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            // "Calculate" our missing HSV components with ranges from 0 to 1.
            const double s = x / 255.; // x is our saturation
            const double v = y / 255.; // y is our value

            // Pick the correct case based on our position on the color wheel.
            const int cs = hue * 6;

            // Calculate some helper values used in our cases below.
            const double f = hue * 6 - cs;
            const double p = v * (1 - s);
            const double q = v * (1 - s * f);
            const double t = v * (1 - s * (1 - f));

            switch (cs) {
            case 0:
            case 6:
                points[y * 256 + x].color = sf::Color(v * 255, t * 255, p * 255);
                break;
            case 1:
                points[y * 256 + x].color = sf::Color(q * 255, v * 255, p * 255);
                break;
            case 2:
                points[y * 256 + x].color = sf::Color(p * 255, v * 255, t * 255);
                break;
            case 3:
                points[y * 256 + x].color = sf::Color(p * 255, q * 255, v * 255);
                break;
            case 4:
                points[y * 256 + x].color = sf::Color(t * 255, p * 255, v * 255);
                break;
            case 5:
                points[y * 256 + x].color = sf::Color(v * 255, p * 255, q * 255);
                break;
            }
        }
    }
}

int main(int argc, char** argv) {
    // Setup a render window
    sf::RenderWindow window(sf::VideoMode(256, 256), "Color Picker");

    // We're using a clock to change the hue dynamically.
    sf::Clock timer;

    // This vertex array is going to be used for drawing.
    // It includes one vertex/point/pixel per color.
    sf::VertexArray colors(sf::Points, 256 * 256);
    for (unsigned int y = 0; y <= 255; ++y) {
        for (unsigned int x = 0; x <= 255; ++x) {
            sf::Vertex& vertex(colors[y * 256 + x]);

            // Note that I "flip" the displayed texture here, by subtracting
            // x/y from 255 rather than just using x/y, but that's really just
            // to get the same orientation that you have.
            vertex.position.x = 255 - x;
            vertex.position.y = 255 - y;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        // Your typical event loop
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        // Update our colors based on the time passed.
        // I want to cycle all hues in 5 seconds, so dividing the timer.
        modulate(colors, timer.getElapsedTime().asSeconds() / 5);

        // Draw and display our colors
        window.clear();
        window.draw(colors);
        window.display();
    }

    return 0;
}