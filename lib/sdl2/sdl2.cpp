/*
** EPITECH PROJECT, 2022
** arcade-Ashley
** File description:
** sdl2
*/

#include "sdl2/SDL2Window.hpp"
#include <math.h>

constexpr int PIXEL_SIZE = 21;

arcade::SDL2Window::SDL2Window()
{
    SDL_Init(SDL_INIT_EVENTS);
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_CreateWindowAndRenderer(1, 1, 0, &win, &renderer);
    SDL_SetWindowPosition(win, 10, 10);
    font = TTF_OpenFont("assets/font.ttf", 25);
}

arcade::SDL2Window::~SDL2Window()
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

void arcade::SDL2Window::setSize(const vec2int &size)
{
    SDL_SetWindowSize(win, size.x * PIXEL_SIZE, size.y * PIXEL_SIZE);
}

void arcade::SDL2Window::setTitle(const std::string &title)
{
    SDL_SetWindowTitle(win, title.c_str());
}

void arcade::SDL2Window::setFramerate(int) noexcept {};

constexpr SDL_Keycode sdl_key[arcade::KeyCount] = {SDLK_a, SDLK_b, SDLK_c,
    SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j, SDLK_k, SDLK_l,
    SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_u,
    SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z, SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_ESCAPE, SDLK_LCTRL,
    SDLK_LSHIFT, SDLK_LALT, -1, SDLK_RCTRL, SDLK_RSHIFT, SDLK_RALT, -1,
    SDLK_MENU, SDLK_LEFTBRACKET, SDLK_RIGHTBRACKET, SDLK_SEMICOLON, SDLK_COMMA,
    SDLK_PERIOD, -1, SDLK_SLASH, SDLK_BACKSLASH, '~', SDLK_EQUALS, -1,
    SDLK_SPACE, SDLK_RETURN, SDLK_BACKSPACE, SDLK_TAB, SDLK_PAGEUP,
    SDLK_PAGEDOWN, SDLK_END, SDLK_HOME, SDLK_INSERT, SDLK_DELETE,
    SDLK_KP_MEMADD, SDLK_KP_MEMSUBTRACT, SDLK_KP_MULTIPLY, SDLK_KP_DIVIDE,
    SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_0, SDLK_1, SDLK_2, SDLK_3,
    SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9, SDLK_F1, SDLK_F2, SDLK_F3,
    SDLK_F4, SDLK_F5, SDLK_F6, SDLK_F7, SDLK_F8, SDLK_F9, SDLK_F10, SDLK_F11,
    SDLK_F12, SDLK_F13, SDLK_F14, SDLK_F15, SDLK_PAUSE};

bool arcade::SDL2Window::pollEvent(Events &events_arcade)
{
    SDL_Event event_sdl;

    if (SDL_PollEvent(&event_sdl) == 0)
        return false;
    if (event_sdl.type == SDL_KEYDOWN) {
        if (event_sdl.button.button == 1)
            events_arcade.mouse.left = true;
        if (event_sdl.button.button == 2)
            events_arcade.mouse.right = true;
        if (event_sdl.button.button == 3)
            events_arcade.mouse.middle = true;
        for (size_t i = 0; i < arcade::KeyCount; i++) {
            if (event_sdl.key.keysym.sym == sdl_key[i]) {
                events_arcade.key_pressed.push_back((arcade::Key) i);
            }
        }
    }
    status = events_arcade.getStatus();
    if (event_sdl.window.event == SDL_WINDOWEVENT_CLOSE ||
        event_sdl.type == SDL_QUIT) {
        SDL_HideWindow(win);
        status = Exit;
    }
    return true;
}

void arcade::SDL2Window::display() { SDL_RenderPresent(renderer); }

void arcade::SDL2Window::draw(const Line &line)
{
    float size_x = line.getLineEnd().x - line.getPosition().x;
    float size_y = line.getLineEnd().y - line.getPosition().y;
    float x = line.getPosition().x;
    float y = line.getPosition().y;

    if (line.getPosition().x == line.getLineEnd().x ||
        line.getPosition().y == line.getLineEnd().y) {
        this->drawRectangleFill(Rectangle{line.getPosition(),
            vec2int{line.getLineEnd().x - line.getPosition().x,
                line.getLineEnd().y - line.getPosition().y + 1},
            line.getColor()});
        return;
    }
    if (size_x <= size_y) {
        for (int i = 0; i <= size_y; i++) {
            this->draw(Point{
                vec2int{(int) round(x), (int) round(y)}, line.getColor()});
            y++;
            x += size_x / size_y;
        }
        return;
    }
    for (int i = 0; i <= size_x; i++) {
        this->draw(
            Point{vec2int{(int) round(x), (int) round(y)}, line.getColor()});
        x++;
        y += size_y / size_x;
    }
}

void arcade::SDL2Window::drawRectangleFill(const Rectangle &rectangle)
{
    SDL_Rect rect{rectangle.getPosition().x * PIXEL_SIZE,
        rectangle.getPosition().y * PIXEL_SIZE,
        rectangle.getSize().x * PIXEL_SIZE,
        rectangle.getSize().y * PIXEL_SIZE};

    SDL_SetRenderDrawColor(renderer, rectangle.getColor().r,
        rectangle.getColor().g, rectangle.getColor().b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void arcade::SDL2Window::drawRectangleEmpty(const Rectangle &rectangle)
{
    Rectangle rect(rectangle);

    rect.setSize(vec2int{1, rectangle.getSize().y});
    drawRectangleFill(rect);
    rect.setSize(vec2int{rectangle.getSize().x, 1});
    drawRectangleFill(rect);
    rect.setPosition(vec2int{rectangle.getPosition().x,
        rectangle.getPosition().y + rectangle.getSize().y - 1});
    drawRectangleFill(rect);
    rect.setPosition(
        vec2int{rectangle.getPosition().x + rectangle.getSize().x - 1,
            rectangle.getPosition().y});
    rect.setSize(vec2int{1, rectangle.getSize().y});
    drawRectangleFill(rect);
}

void arcade::SDL2Window::draw(const Rectangle &rectangle)
{
    switch (rectangle.getFillValue()) {
        case true:
            return drawRectangleFill(rectangle);
        case false:
            return drawRectangleEmpty(rectangle);
    }
}

void arcade::SDL2Window::draw(const Point &point)
{
    SDL_Rect rect{point.getPosition().x * PIXEL_SIZE,
        point.getPosition().y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};

    SDL_SetRenderDrawColor(renderer, point.getColor().r, point.getColor().g,
        point.getColor().b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void arcade::SDL2Window::draw(const Text &txt)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, txt.getString().c_str(),
        SDL_Color{txt.getColor().r, txt.getColor().g, txt.getColor().b, 255});
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect{txt.getPosition().x * PIXEL_SIZE,
        (txt.getPosition().y - 1) * PIXEL_SIZE,
        (int) txt.getString().size() * PIXEL_SIZE, PIXEL_SIZE * 2};

    draw(Line{txt.getPosition(),
        vec2int{
            txt.getPosition().x + (int) txt.getString().size() * PIXEL_SIZE,
            txt.getPosition().y},
        txt.getBackColor()});
    SDL_RenderCopy(renderer, text, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);
}

void arcade::SDL2Window::clear(void)
{
    int x;
    int y;

    SDL_GetWindowSize(win, &x, &y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    drawRectangleFill(Rectangle{
        vec2int{0, 0}, vec2int{x / PIXEL_SIZE, y / PIXEL_SIZE}, BLACK_COLOR});
}

extern "C"
{
    std::unique_ptr<arcade::IWindow> arcade::createLib()
    {
        return std::make_unique<SDL2Window>();
    };
}

arcade::Status arcade::SDL2Window::getStatus()
{
    Status tmp = status;
    if (tmp < Exit)
        status = Nothing;
    return tmp;
}