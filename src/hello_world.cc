#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main(int argc, char** argv) {
    sf::Window App(sf::VideoMode(800, 600, 32), "SFML Window");

    bool Running = true;

    while (Running) {
        App.Display();
    }

    return EXIT_SUCCESS;
}
