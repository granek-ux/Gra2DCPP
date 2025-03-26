#pragma once
#include "Entity.h"
#include <cmath>
#include "FileHandling.h"


auto IsObjectTouched(Obstacle const &obstacle, Person &p, int const &comback) -> bool {
    if (obstacle.shape.getGlobalBounds().intersects(p.imagine.getGlobalBounds())) {
        if (obstacle.top.getGlobalBounds().intersects(p.imagine.getGlobalBounds()))
            p.position.y -= comback;
        if (obstacle.down.getGlobalBounds().intersects(p.imagine.getGlobalBounds()))
            p.position.y += comback;
        if (obstacle.left.getGlobalBounds().intersects(p.imagine.getGlobalBounds()))
            p.position.x -= comback;
        if (obstacle.right.getGlobalBounds().intersects(p.imagine.getGlobalBounds()))
            p.position.x += comback;
        return true;
    }
    return false;
}

auto Check(Person &person, const sf::RenderWindow &window, std::vector<Obstacle> const &osbstacles) -> bool {
    float comeback = 3;
    if (person.position.x < 0) {
        person.position.x += person.velocity.x;
        return false;
    }
    if (person.position.x + person.texture.getSize().x > window.getSize().x) {
        person.position.x -= person.velocity.x;
        return false;
    }
    if (person.position.y < 0) {
        person.position.y += person.velocity.y;
        return false;
    }
    if (person.position.y + person.texture.getSize().y > window.getSize().y) {
        person.position.y -= person.velocity.y;
        return false;
    }
    bool czy = true;
    for (Obstacle o: osbstacles) {
        if (IsObjectTouched(o, person, comeback))
            czy = false;
    }
    return czy;
}

auto Movment(Person &person, const sf::RenderWindow &window, std::vector<Obstacle> const &osbstacles) -> void {
    auto movment = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movment.y = -person.velocity.y;
        person.currntRotation = up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movment.x = -person.velocity.x;
        person.currntRotation = left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movment.y = person.velocity.y;
        person.currntRotation = down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movment.x = person.velocity.x;
        person.currntRotation = right;
    }
    if (movment.x != 0 || movment.y != 0) {
        if (Check(person, window, osbstacles)) {
            person.position = person.position + movment;
        }
    }
}

auto operator+(sf::Vector2f vec1, sf::Vector2f vec2) {
    vec1.x = vec1.x + vec2.x;
    vec1.y = vec1.y + vec2.y;
    return vec1;
}

auto IsInBound(Bullet &bullet, const sf::RenderWindow &window) -> bool {
    if (bullet.position.x < 0) {
        return false;
    }
    if (bullet.position.x + bullet.shape.getRadius() > window.getSize().x) {
        return false;
    }
    if (bullet.position.y < 0) {
        return false;
    }
    if (bullet.position.y + bullet.shape.getRadius() > window.getSize().y) {
        return false;
    }
    return true;
}

auto ShootByEnemy(Person const &person, Enemy &enemy, std::vector<Bullet> &bullets) -> void {
    if (!enemy.czyIstnieje) return;
    enemy.strzał.GetTime();
    if ((int) (enemy.strzał.time.asSeconds()) % enemy.coIleStrzal != enemy.coIleStrzal - 1) return;

    float radius = 10;

    auto vec = sf::Vector2f(person.position.x + person.texture.getSize().x / 2 - enemy.position.x,
                            person.position.y + person.texture.getSize().y / 2 - enemy.position.y);

    double length = sqrt(vec.x * vec.x + vec.y * vec.y);

    if (length != 0) {
        vec.x /= length;
        vec.y /= length;
    }
    enemy.strzał.clock.restart();
    bullets.push_back({sf::CircleShape(radius), vec, enemy.position, byEnemy});

}


auto IsHIT(Bullet const &bullet, Person &person, std::vector<Enemy> &enemys,
           std::vector<Obstacle> const &obstacles) -> bool {
    switch (bullet.whoShoot) {
        case byEnemy:
            if (person.imagine.getGlobalBounds().intersects(bullet.shape.getGlobalBounds())) {
                if (person.armor >= 2) person.armor -= 2;
                else person.Helth--;
                return true;
            }
            break;
        case byPlayer:
            for (int i = 0; i < enemys.size(); i++) {
                if (enemys[i].shape.getGlobalBounds().intersects(bullet.shape.getGlobalBounds()) &&
                    enemys[i].czyIstnieje) {
                    enemys[i].Helth--;
                    return true;
                }
            }
            break;
    }
    for (Obstacle const &o: obstacles) {
        if (o.shape.getGlobalBounds().intersects(bullet.shape.getGlobalBounds()))
            return true;
    }
    return false;
}

auto IsProblemInSpawning(int x, int y, std::vector<Obstacle> const &obstacles, std::vector<Enemy> const &enemys,
                         Person const &person) -> bool {
    auto op = sf::RectangleShape(sf::Vector2f(60, 60));
    op.setPosition(sf::Vector2f(x, y));
    for (Obstacle o: obstacles) {
        if (o.shape.getGlobalBounds().intersects(op.getGlobalBounds())) {
            return false;
        }
    }
    for (Enemy e: enemys) {
        if (e.shape.getGlobalBounds().intersects(op.getGlobalBounds()))
            return false;
    }
    if (person.imagine.getGlobalBounds().intersects(op.getGlobalBounds()))
        return false;
    return true;
}

auto
RandomPosition(sf::RenderWindow const &window, std::vector<Obstacle> const &obstacles, std::vector<Enemy> const &enemys,
               Person const &person) -> sf::Vector2f {
    float x, y;
    do {
        x = 50 + rand() % (window.getSize().x - 100);
        y = 50 + rand() % (window.getSize().y - 100);
    } while (!IsProblemInSpawning(x, y, obstacles, enemys, person));
    return {x, y};
}

auto SpawningOpponents(int quantity, sf::RenderWindow const &window,
                       std::vector<Obstacle> const &obstacles, Person const &person) -> std::vector<Enemy> {
    auto vec = std::vector<Enemy>();
    while (quantity > 0) {
        int id = std::rand() % 10;

        auto position = RandomPosition(window, obstacles, vec, person);

        Enemy e = Enemy(position, id);
        vec.push_back(e);

        quantity--;
    }
    return vec;
}


auto Destruction(std::vector<Obstacle> &obst, Person const &person, sf::RenderWindow &window) -> void {
    sf::CircleShape destruction = sf::CircleShape(100);
    destruction.setPosition(person.position);
    std::vector<Obstacle>::iterator it;
    it = obst.begin();
    for (int i = 0; i < obst.size(); i++) {
        if (obst[i].shape.getGlobalBounds().intersects(destruction.getGlobalBounds())) {
            obst.erase(it);
        }
        it++;
    }
}

auto IsEnemysAlive(std::vector<Enemy> const &enemys) -> bool {
    bool alive = false;
    for (Enemy const &e: enemys) {
        if (e.Helth > 0)
            alive = true;
    }
    return alive;
}

auto CanSpawnBonus(sf::RenderWindow const &window, Person const &person, Level &levels) -> void {
    levels.TimeOFBonusSpawning.GetTime();
    if ((int) levels.TimeOFBonusSpawning.time.asSeconds() % levels.howOftenBonus == levels.howOftenBonus - 1 &&
        IsEnemysAlive(levels.maps[person.currentPoint.x][person.currentPoint.y].enemys)) {
        SpawningBonus(levels.maps[person.currentPoint.x][person.currentPoint.y].bonuses, window,
                      levels.maps[person.currentPoint.x][person.currentPoint.y].obstacles,
                      levels.maps[person.currentPoint.x][person.currentPoint.y].enemys, person);
        levels.TimeOFBonusSpawning.clock.restart();
    }
}

auto SpawningBonus(std::vector<std::unique_ptr<Bonus>> &bonuses, sf::RenderWindow const &window,
                   std::vector<Obstacle> const &obstacles, std::vector<Enemy> const &enemys,
                   Person const &person) -> void {
    int a = rand() % 4 + 1;

    auto position = RandomPosition(window, obstacles, enemys, person);

    switch (a) {
        case 1:
            bonuses.push_back(std::make_unique<FreezeShooting>(FreezeShooting(position)));
            break;

        case 2:
            bonuses.push_back(std::make_unique<Bomb>(Bomb(position)));
            break;

        case 3:
            bonuses.push_back(std::make_unique<BonusHelth>(BonusHelth(position)));
            break;
        case 4:
            bonuses.push_back(std::make_unique<FasterShooting>(FasterShooting(position)));
            break;
    }
}

auto BuildExits(sf::RenderWindow const &window) -> std::vector<Door> {
    int middlex = window.getSize().x / 2;
    int middley = window.getSize().y / 2;

    auto vec = std::vector<Door>();


    auto doorNorth = Door(sf::Vector2f(middlex - 50, 0), horizontal);

    auto doorSouth = Door(sf::Vector2f(middlex - 50, window.getSize().y - 50), horizontal);

    auto doorEast = Door(sf::Vector2f(window.getSize().x - 50, middley - 50), vertical);

    auto doorWest = Door(sf::Vector2f(0, middley - 50), vertical);

    vec.push_back(doorNorth);
    vec.push_back(doorSouth);
    vec.push_back(doorEast);
    vec.push_back(doorWest);

    return vec;
}

auto Exit(Person &person, sf::RenderWindow const &window, std::deque<std::deque<Map>> &maps) -> bool {
    bool czy = false;
    auto temporaryPoint = person.currentPoint;

    if (maps[temporaryPoint.x][temporaryPoint.y].exits[0].shape.getGlobalBounds().intersects(
            person.imagine.getGlobalBounds())) {
        person.currentPoint.y--;
        czy = true;
    }
    if (maps[temporaryPoint.x][temporaryPoint.y].exits[1].shape.getGlobalBounds().intersects(
            person.imagine.getGlobalBounds())) {
        person.currentPoint.y++;
        czy = true;
    }
    if (maps[temporaryPoint.x][temporaryPoint.y].exits[2].shape.getGlobalBounds().intersects(
            person.imagine.getGlobalBounds())) {
        person.currentPoint.x++;
        czy = true;
    }

    if (maps[temporaryPoint.x][temporaryPoint.y].exits[3].shape.getGlobalBounds().intersects(
            person.imagine.getGlobalBounds())) {
        person.currentPoint.x--;
        czy = true;
    }
    if (czy) {
        maps[temporaryPoint.x][temporaryPoint.y].clear();
        AddMap(window, person, maps);
        person.position = sf::Vector2f(100, 100);
    }
    return czy;
}

auto AddMap(sf::RenderWindow const &window, Person &person, std::deque<std::deque<Map>> &maps) -> void {
    if (person.currentPoint.x < 0) {
        person.currentPoint.x = 0;
        maps.emplace_front();
        maps[0].emplace_front(window, person);
        person.numberofMpasPassed++;
        return;
    }
    if (person.currentPoint.y < 0) {
        person.currentPoint.y = 0;
        maps[person.currentPoint.x].emplace_front(window, person);
        person.numberofMpasPassed++;
        return;
    }
    if (person.currentPoint.y == maps[person.currentPoint.x].size()) {
        maps[person.currentPoint.x].emplace_back(window, person);
        person.numberofMpasPassed++;
        return;
    }
    if (person.currentPoint.x == maps.size()) {
        maps.emplace_back();
        maps[person.currentPoint.x].emplace_back(window, person);
        person.numberofMpasPassed++;
        return;
    }
}

auto BuildWalls(sf::RenderWindow const &window) -> std::vector<Obstacle> {
    int choice = rand() % 6;
    auto obst = std::vector<Obstacle>();

    switch (choice) {
        case 0:
            obst.push_back(Obstacle(sf::Vector2f(300, 400)));
            obst.push_back(Obstacle(sf::Vector2f(600, 300)));
            obst.push_back(Obstacle(sf::Vector2f(1000, 500)));
            obst.push_back(Obstacle(sf::Vector2f(1400, 200)));
            obst.push_back(Obstacle(sf::Vector2f(1600, 800)));
            obst.push_back(Obstacle(sf::Vector2f(400, 700)));

            break;

        case 1:
            obst.push_back(Obstacle(sf::Vector2f(550, 555)));
            obst.push_back(Obstacle(sf::Vector2f(600, 300)));
            obst.push_back(Obstacle(sf::Vector2f(1760, 880)));
            obst.push_back(Obstacle(sf::Vector2f(1400, 200)));
            obst.push_back(Obstacle(sf::Vector2f(1000, 600)));
            obst.push_back(Obstacle(sf::Vector2f(400, 700)));

            break;

        case 3:

            obst.push_back(Obstacle(sf::Vector2f(200, 300)));
            obst.push_back(Obstacle(sf::Vector2f(200, 880)));
            obst.push_back(Obstacle(sf::Vector2f(1700, 880)));
            obst.push_back(Obstacle(sf::Vector2f(1700, 300)));
            obst.push_back(Obstacle(sf::Vector2f(950, 500)));
            break;

        case 4:
            obst.push_back(Obstacle(sf::Vector2f(547, 643)));
            obst.push_back(Obstacle(sf::Vector2f(849, 834)));
            obst.push_back(Obstacle(sf::Vector2f(1483, 335)));
            obst.push_back(Obstacle(sf::Vector2f(400, 367)));
            obst.push_back(Obstacle(sf::Vector2f(1389, 748)));
            break;
    }
    return obst;
}

auto MoveEnemy(Enemy &enemy, sf::RenderWindow const &window, Map const &map, Person const &person) -> void {
    if (!enemy.czyIstnieje) return;
    enemy.przemieszczanie.GetTime();
    if ((int) (enemy.przemieszczanie.time.asSeconds()) % enemy.coIleRuch != enemy.coIleRuch - 1) return;

    auto position = RandomPosition(window, map.obstacles, map.enemys, person);

    enemy.position = position;
    enemy.shape.setPosition(position);
    if (enemy.typeOfEnemy != lightning) {
        enemy.przemieszczanie.clock.restart();
        enemy.RandomiseMovment();
    }
}

auto Erasebullets(std::vector<Bullet> &bullets, std::vector<int> const &usedBullets) -> void {

    for (int i: usedBullets) {
        auto itB = bullets.begin() + i;
        bullets.erase(itB);
    }
}


auto Freeze(Level &level) -> bool {
    if (level.freeze) {
        level.freezetime.GetTime();
        if (level.freezetime.time.asSeconds() < level.forHowLongFreeze)
            return false;
        else level.freeze = false;
    }
    return true;
}

