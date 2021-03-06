#include "input.h"
#include <iostream>

IInput::~IInput()
{ }

Input::Input()
{
    // For now we hard code this part
    this->_digitalActionHandles = std::map<std::string, DigitalActionHandle>({
                                                                                 { "start_throw", 1 },
                                                                                 { "back", 2 },
                                                                             });

    this->_analogActionHandles = std::map<std::string, AnalogActionHandle>({
                                                                               { "panning", 1 },
                                                                               { "zooming", 2 },
                                                                             });

    for (unsigned int i = 0; i < int(KeyboardKeys::Count); i++)
    {
        this->_digitalMapping_OnKeyAction[i] = MAX_DIGITAL_ACTIONS;
    }
    for (unsigned int i = 0; i < int(MouseButtons::Count); i++)
    {
        this->_digitalMapping_OnMouseAction[i] = MAX_DIGITAL_ACTIONS;
    }

    for (int i = 0; i < MAX_DIGITAL_ACTIONS; i++)
    {
        this->_digitalActionStates[i].state = 0;
    }

    // This is the keybinding part, for now hardcoded :/
    this->_digitalMapping_OnMouseAction[int(MouseButtons::Left)] = this->_digitalActionHandles["start_throw"];
    this->_digitalMapping_OnKeyAction[int(KeyboardKeys::Escape)] = this->_digitalActionHandles["back"];
    this->_analogMapping_OnMouseMove = this->_analogActionHandles["panning"];
    this->_analogMapping_OnMouseWheel = this->_analogActionHandles["zooming"];
}

Input::~Input()
{ }

void Input::OnKeyAction(KeyboardKeys key, ActionStates state)
{
    DigitalActionHandle mappedAction = this->_digitalMapping_OnKeyAction[int(key)];
    if (mappedAction != MAX_DIGITAL_ACTIONS)
    {
        this->_digitalActionStates[mappedAction].state = (state == ActionStates::Pressed);
    }
}

void Input::OnMouseAction(MouseButtons button, ActionStates state)
{
    DigitalActionHandle mappedAction = this->_digitalMapping_OnMouseAction[int(button)];
    if (mappedAction != MAX_DIGITAL_ACTIONS)
    {
        this->_digitalActionStates[mappedAction].state = (state == ActionStates::Pressed);
    }
}

void Input::OnMouseMove(double x, double y)
{
    if (this->_analogMapping_OnMouseMove != MAX_ANALOG_ACTIONS)
    {
        this->_analogActionStates[int(this->_analogMapping_OnMouseMove)].x = x;
        this->_analogActionStates[int(this->_analogMapping_OnMouseMove)].y = y;
        this->_analogActionStates[int(this->_analogMapping_OnMouseMove)].source = AnalogActionSourceTypes::Absolute;
    }
}

void Input::OnMouseWheel(double x, double y)
{
    if (this->_analogMapping_OnMouseWheel != MAX_ANALOG_ACTIONS)
    {
        this->_analogActionStates[int(this->_analogMapping_OnMouseWheel)].x = x;
        this->_analogActionStates[int(this->_analogMapping_OnMouseWheel)].y = y;
        this->_analogActionStates[int(this->_analogMapping_OnMouseWheel)].source = AnalogActionSourceTypes::Relative;
    }
}

void Input::ResetRelativeActionSources()
{
    for (int i = 0; i < MAX_ANALOG_ACTIONS; ++i)
    {
        if (this->_analogActionStates[i].source == AnalogActionSourceTypes::Relative)
        {
            this->_analogActionStates[i].x = this->_analogActionStates[i].y = 0.0;
        }
    }
}

DigitalActionHandle Input::getDigitalActionHandle(const std::string& name) const
{
    auto found = this->_digitalActionHandles.find(name);

    if (found != this->_digitalActionHandles.end()) return found->second;

    return -1;
}

DigitalActionState Input::getDigitalActionData(DigitalActionHandle action) const
{
    if (action < MAX_DIGITAL_ACTIONS) return this->_digitalActionStates[action];

    return this->_digitalActionStates[MAX_DIGITAL_ACTIONS];
}

AnalogActionHandle Input::getAnalogActionHandle(const std::string& name) const
{
    auto found = this->_analogActionHandles.find(name);

    if (found != this->_analogActionHandles.end()) return found->second;

    return -1;
}

AnalogActionState Input::getAnalogActionData(AnalogActionHandle action) const
{
    if (action < MAX_ANALOG_ACTIONS) return this->_analogActionStates[action];

    return this->_analogActionStates[MAX_ANALOG_ACTIONS];
}
