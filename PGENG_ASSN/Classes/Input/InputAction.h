#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include <string>
#include <functional>
#include "cocos2d.h"

using namespace cocos2d;

using std::function;
using std::string;

class InputAction
{
public:
    InputAction(string _inputKey, function<void()> _action, bool _doOnPress = false, bool _doOnHeld = false, bool _doOnRelease = false)
        :
        inputKey(_inputKey),
        action(_action),
        doOnPress(_doOnPress),
        //doOnHeld(_doOnHeld),
        doOnRelease(_doOnRelease)
    {
    }

    ~InputAction()
    {

    }

#pragma region Getters and Setters  

    void SetAction(function<void()> _newAction)
    {
        this->action = _newAction;
    }

    void SetInputKey(string _newInputKey)
    {
        this->inputKey = _newInputKey;
    }

    string GetInputKey()
    {
        return inputKey;
    }

#pragma endregion

    // variables to check on what key command to do action
    bool doOnPress = false;
    //bool doOnHeld = false;
    bool doOnRelease = false;

    void DoAction()
    {
        if (action)
            action();
    }

protected: 
    
    // What is the key assigned to this action
    string inputKey;

    // The function of the action
    function<void()> action;
};

#endif INPUT_ACTION_H