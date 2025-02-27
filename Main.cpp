#include <SFML/Graphics.hpp>
#include <iostream>

void random();
void windowAndEvents();
void textEvents();
void square();
void keyboardInput();
void mouseInput();
void textures();
void button();
void drag();
bool mouseInPolygon(sf::Vector2f, sf::Vector2f, sf::Vector2f);

int main()
{
    //random();
    //windowAndEvents();
    //textEvents();
    //square();
    //keyboardInput();
    //mouseInput();
    //textures();
    //button();
    drag();

    return 0;
}

// Handles the check if the mouse is currently in a polygon
bool mouseInPolygon(sf::Vector2f mousePosition, sf::Vector2f polygonPosition, sf::Vector2f polygonSize) {
    bool inside = false;

    if (mousePosition.x >= polygonPosition.x - (polygonSize.x / 2) &&
        mousePosition.x <= polygonPosition.x + (polygonSize.x / 2) &&
        mousePosition.y >= polygonPosition.y - (polygonSize.y / 2) &&
        mousePosition.y <= polygonPosition.y + (polygonSize.y / 2))
        inside = true;

    return inside;
}

// drag a square around if holding it down
void drag() {
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Button!");

    sf::RectangleShape button1(sf::Vector2f(100, 100));
    button1.setPosition(sf::Vector2f(400, 250));
    button1.setFillColor(sf::Color::Red);
    sf::Vector2f buttonSize1 = button1.getSize();
    button1.setOrigin(sf::Vector2f(buttonSize1.x / 2, buttonSize1.y / 2)); // Origin is middle of the square

    sf::RectangleShape button2(sf::Vector2f(100, 100));
    button2.setPosition(sf::Vector2f(200, 150));
    button2.setFillColor(sf::Color::Cyan);
    sf::Vector2f buttonSize2 = button2.getSize();
    button2.setOrigin(sf::Vector2f(buttonSize2.x / 2, buttonSize2.y / 2)); // Origin is middle of the square

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                sf::Vector2f buttonPosition1 = button1.getPosition();
                sf::Vector2f buttonPosition2 = button2.getPosition();

                // If the mouse is inside the button and held, it is dragged
                if (mouseInPolygon(mousePosition, buttonPosition1, buttonSize1)) button1.setPosition(mousePosition);
                if (mouseInPolygon(mousePosition, buttonPosition2, buttonSize2)) button2.setPosition(mousePosition);
                
            }
        }

        window.clear();
        window.draw(button1);
        window.draw(button2);
        window.display();

    }
}

// mouse presses square, and something happens
void button() {
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Button!");

    sf::RectangleShape button(sf::Vector2f(100, 100));
    button.setPosition(sf::Vector2f(400, 250));
    button.setFillColor(sf::Color::Red);
    sf::Vector2f buttonPosition = button.getPosition();
    sf::Vector2f buttonSize = button.getSize();
    button.setOrigin(sf::Vector2f(buttonSize.x / 2, buttonSize.y / 2)); // Origin is middle of the square
    bool buttonClicked = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !buttonClicked) {
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                buttonClicked = true;

                // If the mouse is inside the button, button is pressed 
                if (mousePosition.x >= buttonPosition.x - (buttonSize.x / 2) &&
                    mousePosition.x <= buttonPosition.x + (buttonSize.x / 2) &&
                    mousePosition.y >= buttonPosition.y - (buttonSize.y / 2) &&
                    mousePosition.y <= buttonPosition.y + (buttonSize.y / 2)) {
                    /*std::cout << "Mouse Position: " << mousePosition.x << "," << mousePosition.y << std::endl;
                    std::cout << "left x border: " << buttonPosition.x - (buttonSize.x / 2) << std::endl;
                    std::cout << "right x border: " << buttonPosition.x + (buttonSize.x / 2) << std::endl;
                    std::cout << "up y border: " << buttonPosition.y - (buttonSize.y / 2) << std::endl;
                    std::cout << "down x border: " << buttonPosition.y + (buttonSize.y / 2) << std::endl << std::endl;*/

                    // Everytime the button is clicked, it changes color
                    if (button.getFillColor() == sf::Color::Red) button.setFillColor(sf::Color::Cyan);
                    else if (button.getFillColor() == sf::Color::Cyan) button.setFillColor(sf::Color::Yellow);
                    else if (button.getFillColor() == sf::Color::Yellow) button.setFillColor(sf::Color::Red);

                }

            }
            // Button cannot be clicked again until the LEFT mouse button is released
            if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
                    buttonClicked = false;
                }
            }
        }

        window.clear();
        window.draw(button);
        window.display();

    }
}

// Learning textures & sprite sheets
void textures() {

    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Textures");
    sf::RectangleShape player(sf::Vector2f(100, 150));
    player.setPosition(sf::Vector2f(400, 250));

    //texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("sprite-sheet_person.png");
    player.setTexture(&playerTexture);

    // Texture coordinates 
    sf::Vector2u textureSize = playerTexture.getSize();

    // for sprite sheets
    textureSize.x /= 3; // 3 columns for width
    textureSize.y /= 4; // 4 rows for height
    // x * 2 means index 2(3rd item) and y * 0 means index 1(fist item)
    player.setTextureRect(sf::IntRect({ (int)textureSize.x * 2, (int)textureSize.y * 0 }, { (int)textureSize.x, (int)textureSize.y }));


    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }


        }
        window.clear();
        window.draw(player);
        window.display();

    }
}

// Mouse events and moving the box with it 
void mouseInput() {
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Keyboards!!");
    sf::RectangleShape player(sf::Vector2f(100, 100));
    player.setPosition(sf::Vector2f(400, 250));
    player.setFillColor(sf::Color::Red);
    player.setOrigin(sf::Vector2f(50, 50));

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                // Follows mouse exact position
                sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                player.setPosition(mousePosition);

                std::cout << "Player Position: " << player.getPosition().x << ", " << player.getPosition().y << std::endl;

            }
        }

        window.clear();
        window.draw(player);
        window.display();
    }
}

// Using keyboard input to move a square
void keyboardInput() {
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Keyboards!!");
    sf::RectangleShape player(sf::Vector2f(100, 100));
    player.setPosition(sf::Vector2f(400, 250));

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Reading key inputs
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << static_cast<int>(keyPressed->scancode) << std::endl;
                    std::cout << "code: " << static_cast<int>(keyPressed->code) << std::endl;
                    std::cout << "control: " << keyPressed->control << std::endl;
                    std::cout << "alt: " << keyPressed->alt << std::endl;
                    std::cout << "shift: " << keyPressed->shift << std::endl;
                    std::cout << "system: " << keyPressed->system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString() << std::endl;
                    std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed->scancode)) << std::endl;
                    std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed->code)) << std::endl;

                }

                // move square up/down/left/right
                if (keyPressed->scancode == sf::Keyboard::Scan::A) {
                    // move square to the left
                    player.move(sf::Vector2f(-10, 0));
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::S) {
                    // move square to the left
                    player.move(sf::Vector2f(0, 10));
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::W) {
                    // move square to the left
                    player.move(sf::Vector2f(0, -10));
                }
                if (keyPressed->scancode == sf::Keyboard::Scan::D) {
                    // move square to the left
                    player.move(sf::Vector2f(10, 0));
                }

            }
        }

        window.clear();
        window.draw(player);
        window.display();
    }

}

// Draw a square
void square() {

    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Squares!!!!", sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(100, 100)); // Make a rectangle
    player.setFillColor(sf::Color::Cyan); // Set the color
    player.setPosition(sf::Vector2f(400, 250)); // set the location

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // When the left mouse button is pressed, rotate the square by 15 degrees 
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                player.rotate(sf::degrees(15));
            }

        }

        window.clear(); // clear front buffer
        window.draw(player); // add player to back buffer
        window.display(); // swap buffers

    }

}

// How to take user input and print it
void textEvents() {

    // Create window
    sf::RenderWindow window(sf::VideoMode({ 800, 500 }), "Text Events!!");

    // Loop while window is open
    while (window.isOpen()) {

        // Keep track of window events
        while (const std::optional event = window.pollEvent()) {

            // If window close button is pressed, close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Prints out the character the user pressed 
            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {

                if (textEntered->unicode < 128) {
                    std::cout << static_cast<char>(textEntered->unicode);

                }
            }
        }
    }

}

// How to make a window, plus some event checking
void windowAndEvents() {

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

            // If close button pressed, close window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Window auto closes once out of focus, used for debugging purposes
            if (!window.hasFocus()) {
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
