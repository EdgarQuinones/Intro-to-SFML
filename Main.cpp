#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
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


    return 0;
}