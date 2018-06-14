//
// Created by jorda on 5/30/2018.
//

#include "helper.hpp"

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(this->info.selected) {
        states.blendMode = sf::BlendMode(sf::BlendMode::SrcColor, sf::BlendMode::SrcAlpha, sf::BlendMode::ReverseSubtract);
        if(this->moving)
            target.draw(destination_point);
    }
    states.texture = info.texture;
    target.draw(info.vao, states);
}

void Entity::moveCommand(sf::Vector2f point) {
    this->x_destination = point.x;
    this->y_destination = point.y;
    this->moving = true;

    this->destination_point[0].position = sf::Vector2f(this->x_destination, this->y_destination);

    this->x_destination += this->width * 1.25;
    this->y_destination -= this->height/2;

    double diff_x = fabs(static_cast<double>(this->x_destination - this->x_position));
    double diff_y = fabs(static_cast<double>(this->y_destination - this->y_position));

    this->travel_direction = (diff_x == 0) ? 0 : atan(diff_y / diff_x);

    if(this->x_position > this->x_destination && this->y_position < this->y_destination)
        this->travel_direction = M_PI - this->travel_direction;
    else if(this->x_position > this->x_destination && this->y_position > this->y_destination)
        this->travel_direction += M_PI;
    else if(this->x_position < this->x_destination && this->y_position > this->y_destination)
        this->travel_direction = 2 * M_PI - this->travel_direction;
}

void Entity::rightClickAction(sf::Vector2f point) {
    moveCommand(point);
}

void Entity::update(World * world) {
    // TODO: Fix bug where unit can't move after colliding with an entity, adjust position of unit so that rotation doesn't need to be done on every update
    if(this->moving) {
        printf("move\n");
        bool moved_x = true;
        bool moved_y = true;
        float old_x = this->x_position;
        float old_y = this->y_position;

        if(this->travel_direction == M_PI_2 || this->travel_direction == 3 * M_PI_2)
            moved_x = false;
        else if(this->travel_direction < M_PI_2 || this->travel_direction > 3 * M_PI_2)
            this->x_position = static_cast<float>(std::fmin(this->x_destination, this->x_position + this->speed * cos(this->travel_direction)));
        else
            this->x_position = static_cast<float>(std::fmax(this->x_destination, this->x_position + this->speed * cos(this->travel_direction)));

        if(this->travel_direction == 0 || this->travel_direction == M_PI || this->travel_direction == 2 * M_PI)
            moved_y = false;
        else if(this->travel_direction < M_PI)
            this->y_position = static_cast<float>(std::fmin(this->y_destination, this->y_position + this->speed * sin(this->travel_direction)));
        else
            this->y_position = static_cast<float>(std::fmax(this->y_destination, this->y_position + this->speed * sin(this->travel_direction)));

        float diff_x = this->x_position - old_x;
        float diff_y = this->y_position - old_y;
        if(!moved_x && !moved_y)
            this->moving = false;
        else {
            sf::VertexArray next_position(sf::Quads, 4);
            next_position[0].position = sf::Vector2f(this->info.vao[0].position.x + diff_x, this->info.vao[0].position.y + diff_y);
            next_position[1].position = sf::Vector2f(this->info.vao[1].position.x + diff_x, this->info.vao[1].position.y + diff_y);
            next_position[2].position = sf::Vector2f(this->info.vao[2].position.x + diff_x, this->info.vao[2].position.y + diff_y);
            next_position[3].position = sf::Vector2f(this->info.vao[3].position.x + diff_x, this->info.vao[3].position.y + diff_y);
            bool collision = false;
            for(auto &unit : world->units) {
                if (intersectRectRect(&unit->info.vao, &next_position) && unit != this) {
                    collision = true;
                    break;
                }
            }
            if(!collision) {
                for(auto &structure : world->structures) {
                    if (intersectRectRect(&structure->info.vao, &next_position)) {
                        collision = true;
                        break;
                    }
                }
            }
            if(!collision) {
                for(auto &resource : world->resources) {
                    if (intersectRectRect(&resource->info.vao, &next_position)) {
                        collision = true;
                        break;
                    }
                }
            }
            if(!collision) {
                this->info.vao[0].position = next_position[0].position;
                this->info.vao[1].position = next_position[1].position;
                this->info.vao[2].position = next_position[2].position;
                this->info.vao[3].position = next_position[3].position;
            }
            else {
                this->x_position = old_x;
                this->y_position = old_y;
                this->moving = false;
            }
        }

    }
}
