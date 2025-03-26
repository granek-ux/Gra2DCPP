#pragma once
#include "SFML/Graphics.hpp"

enum WhoShoot {
    byPlayer, byEnemy
};


enum RotationOfPerson {
    up, down, left, right
};

enum RotationOfObstacle {
    vertical, horizontal
};

enum TypeOfEnemy {
    normal, leviathan, lightning
};

struct Czas {
    sf::Clock clock;
    sf::Time time;

    auto GetTime() {
        time = clock.getElapsedTime();
    }
};

struct Point {
    int x, y;
};


struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f position;
    WhoShoot whoShoot;

    Bullet(const sf::CircleShape &shape, const sf::Vector2f &velocity, const sf::Vector2f &position,
           const WhoShoot &whoShoot)
            : shape(shape), velocity(velocity), position(position), whoShoot(whoShoot) {
        this->shape.setFillColor(sf::Color::Cyan);
    }
};

struct Person {
    sf::Vector2f position, velocity = sf::Vector2f(1, 1);
    int Helth;
    sf::Texture texture;
    sf::Sprite imagine;
    int numberOfBombs, numberOfFreeze, currentLevel, numberofMpasPassed = 0, armor = 0, money = 0;
    float coIlestrzal;
    Czas cooldown;
    Czas regen;
    int regenerationHelth;
    Point currentPoint;
    RotationOfPerson currntRotation;
    bool regeneration = false;
    int counterhowfast;


    Person(sf::Vector2f pos, int helth) {
        position = pos;
        Helth = helth;
        numberOfBombs = 0;
        numberOfFreeze = 0;
        coIlestrzal = 1;
        currentPoint = {0, 0};
        currentLevel = 0;
        regenerationHelth = 15;
        counterhowfast = 0;
    }

    Person(int level, int Health, int bombs, int freeze, int armor, int money, bool regen, int couter) {
        position = sf::Vector2f(100, 100);
        currentLevel = level;
        Helth = Health;
        numberOfBombs = bombs;
        numberOfFreeze = freeze;
        this->armor = armor;
        this->money = money;
        regeneration = regen;
        currentPoint = {0, 0};
        regenerationHelth = 15;
        coIlestrzal = 1;
        counterhowfast = couter;
    }

    auto SetPosition() {
        imagine.setPosition(position);
    }

    auto CanShoot() {
        cooldown.GetTime();
        if (cooldown.time.asSeconds() > coIlestrzal) {
            cooldown.clock.restart();
            return true;
        }
        return false;
    }

    auto Shot() -> Bullet {
        int radius = 10;
        sf::Vector2f velocity;
        sf::Vector2f pos;
        switch (currntRotation) {
            case up:
                velocity = sf::Vector2f(0, -4.f);
                pos = sf::Vector2f(position.x + (texture.getSize().x - radius) / 2, position.y);
                break;
            case down:
                velocity = sf::Vector2f(0, 4.f);
                pos = sf::Vector2f(position.x + (texture.getSize().x - radius) / 2, position.y + texture.getSize().y);
                break;

            case left:
                velocity = sf::Vector2f(-4.f, 0);
                pos = sf::Vector2f(position.x, position.y + texture.getSize().y / 2);
                break;

            case right:
                velocity = sf::Vector2f(4.f, 0);
                pos = sf::Vector2f(position.x + texture.getSize().x, position.y + texture.getSize().y / 2);
                break;

        }
        return {sf::CircleShape(radius), velocity, pos, byPlayer};
    }

    auto Regeneratiom() {
        if (regeneration) {
            regen.GetTime();
            if (regen.time.asSeconds() > regenerationHelth) {
                if (Helth < 5) {
                    Helth++;
                    regen.clock.restart();
                }
            }
        }
    }
};

struct Obstacle {
    sf::RectangleShape top, down, left, right;
    sf::RectangleShape shape;
    sf::Color color = sf::Color::Red;
    bool czyIstnieje;

    Obstacle(sf::Vector2f p) {
        shape = sf::RectangleShape(sf::Vector2f(75.f, 75.f));
        shape.setPosition(p);
        shape.setFillColor(color);
        czyIstnieje = false;

        top = sf::RectangleShape(sf::Vector2f(shape.getSize().x, shape.getSize().y / 10));
        top.setPosition(p);

        down = sf::RectangleShape(sf::Vector2f(shape.getSize().x, shape.getSize().y / 10));
        down.setPosition(p.x, p.y + shape.getSize().y / 10 * 9);

        left = sf::RectangleShape(sf::Vector2f(shape.getSize().x / 10, shape.getSize().y));
        left.setPosition(p);

        right = sf::RectangleShape(sf::Vector2f(shape.getSize().x / 10, shape.getSize().y));
        right.setPosition(p.x + shape.getSize().x / 10 * 9, p.y);
    }
};

struct Enemy {
    sf::Vector2f position, velocity;
    int Helth;
    sf::RectangleShape shape;
    int coIleStrzal, coIleRuch;
    Czas strzał;
    Czas przemieszczanie;
    bool czyIstnieje;
    TypeOfEnemy typeOfEnemy;

    Enemy(sf::Vector2f pos, int id) {
        position = pos;
        switch (id) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                Helth = 3;
                shape = sf::RectangleShape(sf::Vector2f(50, 50));
                shape.setFillColor(sf::Color::Cyan);
                coIleStrzal = rand() % 6 + 4;
                typeOfEnemy = normal;
                break;
            case 5:
            case 6:
            case 7:
                Helth = 5;
                shape = sf::RectangleShape(sf::Vector2f(80, 80));
                shape.setFillColor(sf::Color::Blue);
                coIleStrzal = rand() % 7 + 6;
                typeOfEnemy = leviathan;
                break;
            default:
                Helth = 2;
                shape = sf::RectangleShape(sf::Vector2f(40, 40));
                shape.setFillColor(sf::Color::Yellow);
                coIleStrzal = rand() % 7 + +6;
                typeOfEnemy = lightning;
        }
        shape.setPosition(position);
        coIleStrzal = rand() % 6 + 3;
        strzał.GetTime();
        przemieszczanie.GetTime();
        czyIstnieje = true;
        RandomiseMovment();
    }

    auto RandomiseMovment() -> void {
        coIleRuch = rand() % 5 + 4;
    }

};

struct Bonus {
    sf::Vector2f position;
    bool touhced = false;
    sf::RectangleShape shape;

    Bonus() {}


    virtual auto IsTouched(Person &p) -> bool {
        if (!touhced) {
            if (p.imagine.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                touhced = true;
            }
        }
        return false;
    }
};


struct Bomb : Bonus {
    sf::CircleShape destruction;

    Bomb(const sf::Vector2f &pos) {
        shape = sf::RectangleShape(sf::Vector2f(35, 35));
        shape.setPosition(pos);
        destruction = sf::CircleShape(60);
        shape.setFillColor(sf::Color::Green);
    }


    auto IsTouched(Person &p) -> bool override {
        if (!touhced) {
            if (p.imagine.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                p.numberOfBombs++;
                touhced = true;
                return true;
            }
        }
        return false;
    }
};

struct BonusHelth : Bonus {

    BonusHelth(const sf::Vector2f &pos) {
        shape = sf::RectangleShape(sf::Vector2f(35, 35));
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Green);
    }

    auto IsTouched(Person &p) -> bool override {
        if (!touhced) {
            if (p.imagine.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                p.Helth++;
                touhced = true;
                return true;
            }
        }
        return false;
    }
};

struct FreezeShooting : Bonus {

    FreezeShooting(const sf::Vector2f &pos) {
        shape = sf::RectangleShape(sf::Vector2f(35, 35));
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Green);

    }

    auto IsTouched(Person &p) -> bool override {
        if (!touhced) {
            if (p.imagine.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                touhced = true;
                p.numberOfFreeze++;
                return true;
            }
        }
        return false;
    }
};

struct FasterShooting : Bonus {

    FasterShooting(const sf::Vector2f &pos) {
        shape = sf::RectangleShape(sf::Vector2f(35, 35));
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Green);
    }

    auto IsTouched(Person &p) -> bool override {
        if (!touhced) {
            if (p.imagine.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                if (p.coIlestrzal > 0.25) {
                    p.coIlestrzal = p.coIlestrzal / 10 * 9;
                }
                touhced = true;
                return true;
            }
        }
        return false;
    }
};


struct Door {
    sf::RectangleShape shape;

    Door(sf::Vector2f pos, RotationOfObstacle rot) {
        switch (rot) {
            case vertical:
                shape.setSize(sf::Vector2f(50, 100));
                break;
            case horizontal:
                shape.setSize(sf::Vector2f(100, 50));
                break;
        }
        shape.setPosition(pos);
        shape.setFillColor(sf::Color(93, 93, 93));
    }
};


auto operator+(sf::Vector2f vec1, sf::Vector2f vec2) {
    vec1.x = vec1.x + vec2.x;
    vec1.y = vec1.y + vec2.y;
    return vec1;
}

auto IsObjectTouched(Obstacle const &obstacle, Person &p, int const &comback) -> bool;

auto Check(Person &person, const sf::RenderWindow &window, std::vector<Obstacle> const &osbstacles) -> bool;

auto Movment(Person &person, const sf::RenderWindow &window, std::vector<Obstacle> const &osbstacles) -> void;

auto IsInBound(Bullet &Bullet, const sf::RenderWindow &window) -> bool;

auto ShootByEnemy(Person const &person, Enemy &enemy, std::vector<Bullet> &bullets) -> void;

auto
IsHIT(Bullet const &bullet, Person &person, std::vector<Enemy> &enemys, std::vector<Obstacle> const &obstacles) -> bool;

auto IsProblemInSpawning(int x, int y, std::vector<Obstacle> const &obstacles, std::vector<Enemy> const &enemys,
                         Person const &person) -> bool;

auto
RandomPosition(sf::RenderWindow const &window, std::vector<Obstacle> const &obstacles, std::vector<Enemy> const &enemys,
               Person const &person) -> sf::Vector2f;

auto SpawningOpponents(int quantity, sf::RenderWindow const &window, std::vector<Obstacle> const &obstacles,
                       Person const &person) -> std::vector<Enemy>;

auto MapGeneration(sf::RenderWindow const &window) -> std::vector<Obstacle>;


auto Destruction(std::vector<Obstacle> &obst, Person const &personm, sf::RenderWindow &window) -> void;

template<typename T>
auto Drawing(sf::RenderWindow &window, std::vector<T> const &vec) -> void {
    for (T t: vec) {
        window.draw(t.shape);
    }
}

auto BuildWalls(sf::RenderWindow const &window) -> std::vector<Obstacle>;

auto BuildExits(sf::RenderWindow const &window) -> std::vector<Door>;

struct Map {
    std::vector<Obstacle> obstacles;
    std::vector<Enemy> enemys;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    std::vector<Door> exits;
    std::vector<Bullet> bullets;

    Map(sf::RenderWindow const &window, Person const &person) {
        auto enemyq = rand() % 5 + 2;
        obstacles = MapGeneration(window);
        obstacles = BuildWalls(window);
        enemys = SpawningOpponents(enemyq + person.currentLevel, window, obstacles, person);
        exits = BuildExits(window);

    }

    auto clear() -> void {
        enemys.clear();
        bonuses.clear();
        bullets.clear();
    }

};


struct Level {
    std::deque<std::deque<Map>> maps;
    int NoumberOfMaps;
    int numberOfLevel;
    Czas Bonuses, freezetime;
    int forHowLongFreeze, howOftenBonus;
    bool freeze;
    Czas TimeOFBonusSpawning;

    Level(sf::RenderWindow const &window, Person const &person) {
        maps.push_back(std::deque<Map>());
        maps[0].push_back(Map(window, person));
        NoumberOfMaps = rand() % 10 + 3;
        freeze = false;
        forHowLongFreeze = 20;
        howOftenBonus = 5;
        TimeOFBonusSpawning.GetTime();
        numberOfLevel = person.currentLevel;
    }

    auto NewLevel(sf::RenderWindow const &window, Person &person) -> void {
        maps.clear();
        maps.push_back(std::deque<Map>());
        maps[0].push_back(Map(window, person));
        person.currentPoint = Point{0, 0};
        NoumberOfMaps = rand() % 5 + 3 + ++numberOfLevel;
        person.numberofMpasPassed = 0;
        person.currentLevel++;
        person.coIlestrzal = 1;
    }

};

auto Pauza(sf::RenderWindow &window, Person &person, Level &level) -> void;

auto IsEnemysAlive(std::vector<Enemy> const &enemys) -> bool;

auto CanSpawnBonus(sf::RenderWindow const &window, Person const &person, Level &levels) -> void;

auto SpawningBonus(std::vector<std::unique_ptr<Bonus>> &bonuses, sf::RenderWindow const &window,
                   std::vector<Obstacle> const &obstacles, std::vector<Enemy> const &enemys,
                   Person const &person) -> void;

auto MoveEnemy(Enemy &enemy, sf::RenderWindow const &window, Map const &map, Person const &person) -> void;

auto Exit(Person &person, sf::RenderWindow const &window, std::deque<std::deque<Map>> &maps) -> bool;

auto AddMap(sf::RenderWindow const &window, Person &person,
            std::deque<std::deque<Map>> &maps) -> void;


auto Erasebullets(std::vector<Bullet> &bullets, std::vector<int> const &usedBullets) -> void;

auto ShowInfo(sf::RenderWindow &window, Person const &person) -> void;

auto Shop(sf::RenderWindow &window, Person &person) -> void;

auto Freeze(Level &level) -> bool;

auto pauseBetweenLevels(sf::RenderWindow &window, Person &person, Level &level) -> void;

auto endGame(sf::RenderWindow &window, Person &person, Level &level) -> void;

auto delatelast(sf::String str) -> sf::String;

auto placeToWrite() -> std::string;

auto Saving(Person const &person, Level const &level) -> void;

auto Load(sf::RenderWindow const &window, Person &person, Level &level) -> void;


auto Game(sf::RenderWindow &window, Person &person) -> void;