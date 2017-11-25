#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "InputAction.h"
#include <map>
#include <vector>
#include <functional>
#include "../Common/SingletonNode.h"
#include "cocos2d.h"

using namespace cocos2d;
using std::map;
using std::vector;
using std::function;
using std::bind;

/*
    *Use this function to assign functions to specific key press

    // Example of how to add new actions
    InputHandler::GetInstance().AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&TestScene::InputTestFunction, this), true, true, true);

*/

class InputHandler : public SingletonNode<InputHandler>
{
    friend SingletonNode <InputHandler>;

public:
    InputHandler();
    ~InputHandler();

#pragma region Keyboard Functions

    void DoKeyboardOnPress(EventKeyboard::KeyCode _keyPressed, Event* _event);
    void DoKeyboardOnRelease(EventKeyboard::KeyCode _keyPressed, Event* _event);

    // Note - Use bind(&Class::Function, this) to assign the action function
    void AssignKeyboardAction(EventKeyboard::KeyCode _keyPressed, function<void()> _action, bool _doOnPress = false, bool _doOnHeld = false, bool _doOnRelease = false);

    // Clear all actions from the map
    bool init();
    void ClearActionMaps();

#pragma endregion

#pragma region Mouse Functions

    void DoMouseOnPress(Event* _event);
    void DoMouseOnRelease(Event* _event);

    // Note - Use bind(&Class::Function, this) to assign the action function
    void AssignMouseAction(EventMouse::MouseButton _keyPressed, function<void()> _action, bool _doOnPress = false, bool _doOnHeld = false, bool _doOnRelease = false);

#pragma endregion

private:
    static InputHandler* instance;

    // Action Maps
    map<string, vector<InputAction>> actionMap;

    // Identifyer changes the string that is stored in the map
    string keyboardIdentifyer = "KB_";
    string mouseIdentifyer = "MB_";

};

#endif INPUT_HANDLER_H
