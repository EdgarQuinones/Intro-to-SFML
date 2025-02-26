#include <SFML/Graphics.hpp>
#include <iostream>

void random();
void window();

int main()
{

    //random();
    window();

    return 0;
}

// How to make a window
void window() {

    sf::RenderWindow window(sf::VideoMode({ 512, 512 }), "This is a window!", sf::Style::Default);

    while (window.isOpen()) {
        
        while (const std::optional event = window.pollEvent()) {

            // If the window is resized, print size
            if (event->is<sf::Event::Resized>()) {
                sf::Vector2u size = window.getSize();
                auto [width, height] = size;
                std::cout << "(" << width << ", " << height << ")" << std::endl;
            }

            // If left mouse button is clicked, print relative location in window
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                auto [x, y] = localPosition;
                std::cout << x << ", " << y << std::endl;
            }

            // If the window is closed
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
                

        }

    }
}

// Some random stuff I learned on the first day
void random() {
    // SFML windows are handled by the sf::Window class
        // Argument 1: Defines the size of the window with the sf::VideoMode class 
        // Argument 2: Title of the window
        // Argument 3 (Optional): Window style
        // Argument 4 (Optional): Full screen or not
        // Argument 5 (Optional): OpenGL Specific options
    //sf::Window window(sf::VideoMode({ 800, 600 }), "My Window", sf::Style::Default, sf::State::Windowed);

    // Can also make window with create function
    //sf::Window anotherWindow;
    //anotherWindow.create(sf::VideoMode({ 700, 500 }), "My other window");

    // Some windows edits
    //window.setPosition({ 10, 50 });
    //window.setSize({ 640, 480 });
    //window.setTitle("New title");
    // Check window stats
    //sf::Vector2u size = window.getSize();
    //auto [width, height] = size;
    //bool focus = window.hasFocus();

    // Mouse Settings
    sf::Vector2i globalPosition = sf::Mouse::getPosition();
    sf::Mouse::setPosition({ 10, 50 });

    // Draw using the sf::RenderWindow class (superset of sf::window)
    sf::RenderWindow window(sf::VideoMode({ 1200,600 }), "Draw Window");

    // 2D Sprite = rectange(shape) + texture(image)
    sf::Texture texture;

    // Left is start location, right is size, position (10,10) in size 100x100
    if (!texture.loadFromFile("preview.jpg", false, sf::IntRect({ 10, 10 }, { 100, 100 }))) {
        // error...
    }
    texture.setRepeated(false);
    texture.setSmooth(false);
    sf::Sprite sprite(texture);
    sprite.setColor(sf::Color(0, 255, 0, 128));
    sprite.move({ 400.f, 300.f });
    // More sprite edits
    sprite.setRotation(sf::degrees(63)); // This is absolute, use .rotate for local
    sprite.setScale({ 0.5f, 2.f });


    // Window will not work for 2 reasons 
        // No loop (Window closes right away)
        // No event handling (Window buttons wont work)

    // Run as long as the window is open
    while (window.isOpen()) {

        // Check all windows events since last iteration
        while (const std::optional event = window.pollEvent()) {

            // If "close event" event called, close the window
            if (event->is<sf::Event::Closed>())
                window.close();

            // Mouse
            //if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            //    std::cout << "Mouse pressed" << std::endl;
            //}
        }


        // Clear window with color black
        window.clear(sf::Color::Black);

        // draw stuff here...
        window.draw(sprite);
        sprite.rotate(sf::degrees(2)); // This is absolute, use .rotate for local


        // end current frame
        window.display();


    }
}