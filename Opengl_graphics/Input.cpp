#include "Input.h"
#include <iostream>
#include <SDL3/SDL.h>

Input* Input::Instance()
{
    static Input* inputObject = new Input();
    return inputObject;
}

Input::Input()
{
    m_keyUp = 0;
    m_keyDown = 0;
    m_isXClicked = false;
    m_isKeyPressed = false;
    m_isLeftButtonClicked = false;
    m_isRightButtonClicked = false;
    m_isMiddleButtonClicked = false;
    m_mouseMotionX = 0;
    m_mouseMotionY = 0;
    m_mousePositionX = 0;
    m_mousePositionY = 0;

}

void Input::Update()
{
    m_mouseMotionX = 0;
    m_mouseMotionY = 0;
    m_mousePositionX = 0;
    m_mousePositionY = 0;

    SDL_Event events;

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_EVENT_KEY_DOWN:
            m_isKeyPressed = true;
            m_keyDown = events.key.key;
            break;

        case SDL_EVENT_KEY_UP:
            m_isKeyPressed = false;
            m_keyUp = events.key.key;
            break;

        case SDL_EVENT_QUIT:
            m_isXClicked = true;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            switch (events.button.button)
            {
            case SDL_BUTTON_LEFT:
                m_isLeftButtonClicked = true;
                break;

            case SDL_BUTTON_RIGHT:
                m_isRightButtonClicked = true;
                break;

            case SDL_BUTTON_MIDDLE:
                m_isMiddleButtonClicked = true;
                break;
            }
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            switch (events.button.button)
            {
            case SDL_BUTTON_LEFT:
                m_isLeftButtonClicked = false;
                break;

            case SDL_BUTTON_RIGHT:
                m_isRightButtonClicked = false;
                break;

            case SDL_BUTTON_MIDDLE:
                m_isMiddleButtonClicked = false;
                break;
            }
            break;

        case SDL_EVENT_MOUSE_MOTION:
            m_mouseMotionX = events.motion.xrel;
            m_mouseMotionY = events.motion.yrel;
            m_mousePositionX = events.motion.x;
            m_mousePositionY = events.motion.y;

            break;
        }
    }

}

bool Input::IsXClicked()
{
    return m_isXClicked;
}

bool Input::IsKeyPressed()
{
    return m_isKeyPressed;
}

char Input::GetKeyUp()
{
    return m_keyUp;
}

char Input::GetKeyDown()
{
    return m_keyDown;
}

bool Input::IsLeftButtonClicked()
{
    return m_isLeftButtonClicked;
}

bool Input::IsRightButtonClicked()
{
    return m_isRightButtonClicked;
}

bool Input::IsMiddleButtonClicked()
{
    return m_isMiddleButtonClicked;
}

int Input::GetMousePositionX()
{
    return m_mousePositionX;
}

int Input::GetMousePositionY()
{
    return m_mousePositionY;
}

int Input::GetMouseMotionX()
{
    return m_mouseMotionX;
}

int Input::GetMouseMotionY()
{
    return m_mouseMotionY;
}
