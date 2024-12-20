#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Objeto {
protected:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Objeto(float x, float y, float radius, sf::Color color) {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setPosition(x, y);
    }

    virtual void update(float deltaTime) = 0;
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
    bool isHit(float x, float y) const {
        return shape.getGlobalBounds().contains(x, y);
    }
};

class ObjetoMRUV : public Objeto {
private:
    float gravity;

public:
    ObjetoMRUV(float x, float y, float radius, sf::Color color, float g)
        : Objeto(x, y, radius, color), gravity(g) {
    }

    void update(float deltaTime) override {
        velocity.y += gravity * deltaTime;
        shape.move(velocity * deltaTime);
    }
};

class ObjetoMRU : public Objeto {
public:
    ObjetoMRU(float x, float y, float radius, sf::Color color, sf::Vector2f vel)
        : Objeto(x, y, radius, color) {
        velocity = vel;
    }

    void update(float deltaTime) override {
        shape.move(velocity * deltaTime);
    }
};

int main() {
    const int wnd_width = 800;
    const int wnd_height = 600;

    sf::RenderWindow window(sf::VideoMode(wnd_width, wnd_height), "Juego de Objetos Cinemáticos");
    window.setFramerateLimit(60);

    // Semilla para números aleatorios
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Lista de objetos
    std::vector<Objeto*> objetos;

    // Crear algunos objetos MRUV y MRU
    for (int i = 0; i < 5; ++i) {
        float x = static_cast<float>(std::rand() % wnd_width);
        float y = -50.0f; // Comienza fuera de la pantalla (arriba)
        objetos.push_back(new ObjetoMRUV(x, y, 20.0f, sf::Color::Green, 200.0f));
    }

    for (int i = 0; i < 5; ++i) {
        float x = -50.0f; // Comienza fuera de la pantalla (izquierda)
        float y = static_cast<float>(std::rand() % wnd_height);
        sf::Vector2f velocity(150.0f, 0.0f); // Velocidad constante horizontal
        objetos.push_back(new ObjetoMRU(x, y, 20.0f, sf::Color::Red, velocity));
    }

    // Variables de juego
    int puntaje = 0;
    sf::Font font;
    if (!font.loadFromFile("Uni6assets/Perfect DOS VGA 437.ttf")) {
        std::cerr << "Error al cargar la fuente\n";
        return -1;
    }

    sf::Text textoPuntaje;
    textoPuntaje.setFont(font);
    textoPuntaje.setCharacterSize(20);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setPosition(10.0f, 10.0f);

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                float mouseX = static_cast<float>(event.mouseButton.x);
                float mouseY = static_cast<float>(event.mouseButton.y);

                for (auto it = objetos.begin(); it != objetos.end();) {
                    if ((*it)->isHit(mouseX, mouseY)) {
                        puntaje += 10;
                        delete* it;
                        it = objetos.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
        }

        float deltaTime = 1.0f / 60.0f;
        for (auto* objeto : objetos) {
            objeto->update(deltaTime);
        }

        window.clear(sf::Color::Black);
        for (auto* objeto : objetos) {
            objeto->draw(window);
        }

        textoPuntaje.setString("Puntaje: " + std::to_string(puntaje));
        window.draw(textoPuntaje);
        window.display();
    }

    for (auto* objeto : objetos) {
        delete objeto;
    }

    return 0;
}
