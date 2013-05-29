#include <iostream>
#include <sstream>
#include <string>

#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

std::string FloatToString(float f) {
    std::ostringstream os;
    os << f;
    return os.str();
}

template <typename T> std::string ToStr(const T& t) {
    std::ostringstream os;
    os << t;
    return os.str();
}

int init_opengl() {
    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    return 0;
}

int main(int argc, char** argv) {
    sf::RenderWindow App(sf::VideoMode(800, 600), "Ark", sf::Style::Default, sf::ContextSettings(32));

    // Create a clock for measuring time elapsed
    sf::Clock globalClock;
    sf::Clock fpsClock;
    // float lastTime = 0.f;
    int frameCounter = 0;
    int fps = 0;

    init_opengl();

    // App.setVerticalSyncEnabled(true);
    App.setFramerateLimit(120);

    sf::Font font;

    if (!font.loadFromFile("res/fonts/Arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text Fps("0", font, 25);

    bool running = true;
    // while (App.isOpen()) {
    while (running) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::Closed:
                    // App.close();
                    running = false;
                    break;
                case sf::Event::Resized:
                    glViewport(0, 0, Event.size.width, Event.size.height);
                    break;
                default:
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            // App.close();
            running = false;
        }

        // Set the active window before using OpenGL commands
        // It's useless here because active window is always the same,
        // but don't forget it if you use multiple windows or controls
        App.setActive();

        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        glRotatef(globalClock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
        glRotatef(globalClock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
        glRotatef(globalClock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

        // Draw a cube
        glBegin(GL_QUADS);

            glColor3f(1, 0, 0); // red
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);

            glColor3f(0, 1, 0); // green
            glVertex3f(-50.f, -50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f( 50.f, -50.f, 50.f);

            glColor3f(0, 0, 1); // blue
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f, -50.f,  50.f);

            glColor3f(1, 1, 0); // ???
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

            glColor3f(1, 0, 1); // ???
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);

            glColor3f(0, 1, 1); // ???
            glVertex3f(-50.f, 50.f,  50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f,  50.f);

            // glColor3f(1, 1, 1); //white

        glEnd();

        // float currentTime = fpsClock.restart().asSeconds();
        // x frames / 1 second = 1 frame / y seconds
        // float fps = 1.f / (currentTime - lastTime);
        // float fps = (currentTime - lastTime);
        // lastTime = currentTime;

        frameCounter++;
        sf::Time elapsedTime = fpsClock.getElapsedTime();
        if (elapsedTime.asMilliseconds() > 999) {
            fps = frameCounter;
            frameCounter = 0;
            fpsClock.restart();
        }

        Fps.setString("FPS: " + ToStr(fps));

        App.pushGLStates();
        // App.clear();
        App.draw(Fps);
        App.popGLStates();

        App.display();
    }

    return EXIT_SUCCESS;
}
