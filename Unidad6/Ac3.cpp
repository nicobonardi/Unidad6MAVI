#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Dimensiones de la ventana
    const int wnd_width = 800;
    const int wnd_height = 600;

    // Configuración de la ventana
    sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Rebote de Esfera");
    window.setFramerateLimit(60);

    // Esfera
    sf::CircleShape ball(20.0f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(wnd_width / 2.0f, 0.0f);

    // Variables físicas
    const float gravity = 0.5f; // Gravedad (pixeles/seg^2)
    float velocityY = 0.0f;
    const float bounceFactor = 0.8f;
    const float constantBounceSpeed = 10.0f;
    bool usePercentageBounce = true;

    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Actualizar la física
        velocityY += gravity;
        sf::Vector2f position = ball.getPosition();
        position.y += velocityY;

        // Si la esfera toca el suelo
        if (position.y > wnd_height - ball.getRadius() * 2) {
            position.y = wnd_height - ball.getRadius() * 2;

            // Rebote
            if (usePercentageBounce) {
                velocityY = -velocityY * bounceFactor;
            }
            else {
                velocityY = -constantBounceSpeed;
            }

            if (std::abs(velocityY) < 1.0f) {
                velocityY = 0.0f;
            }
        }
        ball.setPosition(position);

        // Dibujar en la ventana
        window.clear(sf::Color::Black); // Fondo negro
        window.draw(ball);              // Dibujar la esfera
        window.display();
    }

    return 0;
}
