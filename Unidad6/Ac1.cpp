#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Dimensiones de la ventana
    const int wnd_width = 800;
    const int wnd_height = 600;

    sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Círculo en Movimiento");
    window.setFramerateLimit(60);

    // Círculo
    sf::CircleShape circle(20.0f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(0.0f, wnd_height / 2.0f - circle.getRadius());

    // Velocidades
    float V0 = 5.0f;
    float Vfinal = 20.0f;
    float velocidad = V0;

    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Actualizar posición del círculo
        sf::Vector2f pos = circle.getPosition();
        pos.x += velocidad;

        if (pos.x > wnd_width) {
            pos.x = -circle.getRadius() * 2;
            velocidad += 2.0f;
            std::cout << "Nueva velocidad: " << velocidad << " px/segundo" << std::endl;

            // Verificar si se alcanzó la velocidad final
            if (velocidad >= Vfinal) {
                std::cout << "Se alcanzó la velocidad final: " << velocidad << std::endl;
                window.close();
            }
        }
        circle.setPosition(pos);

        // Dibujar en la ventana
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
