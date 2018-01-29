#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include "cocos2d.h"
#include "InputAction.h"
#include "../Common/SingletonNode.h"

#include <map>
#include <bitset>
#include <vector>
#include <functional>

using std::map;
using std::bind;
using std::bitset;
using std::vector;
using std::function;

using namespace cocos2d;
/*
    *Use this function to assign functions to specific key press

    // Example of how to add new actions
    InputHandler::GetInstance()->AssignKeyboardAction(EventKeyboard::KeyCode::KEY_SPACE, bind(&TestScene::InputTestFunction, this), true, true, true);

*/

class InputHandler : public SingletonNode<InputHandler>
{
    friend SingletonNode <InputHandler>;

public:
    InputHandler();
    ~InputHandler();

    void ClearActionMaps();

#pragma region Keyboard Functions

    bool GetKeyDown(EventKeyboard::KeyCode _keyPressed){ return keyboardInputButtons[(int)_keyPressed]; };

    // Note - Use bind(&Class::Function, this) to assign the action function
    void AssignKeyboardAction(EventKeyboard::KeyCode _keyPressed, function<void()> _action, bool _doOnPress = false, bool _doOnHeld = false, bool _doOnRelease = false);

#pragma endregion

#pragma region Mouse Functions

    // Note - Use bind(&Class::Function, this) to assign the action function
    void AssignMouseAction(EventMouse::MouseButton _keyPressed, function<void()> _action, bool _doOnPress = false, bool _doOnHeld = false, bool _doOnRelease = false);

    inline bool HasMouseMoved(){ return (currentMousePosition == previousMousePosition); }

    inline Vec2 GetMouseUpPosition(){ return this->mouseUpPosition; };
    inline Vec2 GetMouseDownPosition(){ return this->mouseDownPosition; };
           
    inline Vec2 GetCurrentMousePosition(){ return this->currentMousePosition; };
    inline Vec2 GetPreviousMousePosition(){ return this->previousMousePosition; };

#pragma endregion


protected:
    bool init();

private:
    static InputHandler* instance;

    // Action Maps
    map<string, vector<InputAction>> actionMap;

    // Identifyer changes the string that is stored in the map
    string keyboardIdentifyer = "KB_";
    string mouseIdentifyer = "MB_";

#pragma region Mouse

    void DoMouseOnPress(Event* _event);
    void DoMouseOnRelease(Event* _event);
    void DoMouseOnMove(Event* _event);

    Vec2 currentMousePosition;
    Vec2 previousMousePosition;

    Vec2 mouseUpPosition;
    Vec2 mouseDownPosition;

#pragma endregion

#pragma region Keyboard

public:
    void DoKeyboardOnPress(EventKeyboard::KeyCode _keyPressed, Event* _event);
    void DoKeyboardOnRelease(EventKeyboard::KeyCode _keyPressed, Event* _event);

    bitset<(int)EventKeyboard::KeyCode::KEY_PLAY> keyboardInputButtons;
    
#pragma endregion

};

#endif INPUT_HANDLER_H_
