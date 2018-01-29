#include "InputHandler.h"

InputHandler::InputHandler() 
{
    if (Node::init())
        init();
}

InputHandler::~InputHandler()
{
}

bool InputHandler::init()
{
    if (!Node::init())
    {
        return false;
    }

    keyboardInputButtons.reset();

    // Clear Action and event listeners
    this->ClearActionMaps();
    //_eventDispatcher->removeAllEventListeners();

    // Keyboard Listener Init
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(InputHandler::DoKeyboardOnPress, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(InputHandler::DoKeyboardOnRelease, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);


    // Mouse Listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(InputHandler::DoMouseOnPress, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(InputHandler::DoMouseOnMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(InputHandler::DoMouseOnRelease, this);
    _eventDispatcher->addEventListenerWithFixedPriority(mouseListener, 1);

    return true;
}

void InputHandler::ClearActionMaps()
{
    actionMap.clear();
    keyboardInputButtons.reset();
}

void InputHandler::DoKeyboardOnPress(EventKeyboard::KeyCode _keyPressed, Event* _event)
{
    string key = keyboardIdentifyer;
    key += (int)_keyPressed;

    keyboardInputButtons.set((int)_keyPressed, true);
    
    if (!actionMap.count(key))
        return;
    
    vector<InputAction> assignedAction = actionMap[key];

	for (vector<InputAction>::iterator itr = assignedAction.begin(); itr != assignedAction.end(); ++itr)
	{
        if (itr->doOnPress)
            itr->DoAction();
    }

}

void InputHandler::DoKeyboardOnRelease(EventKeyboard::KeyCode _keyPressed, Event* _event)
{
    string key = keyboardIdentifyer;
    key += (int)_keyPressed;

    keyboardInputButtons.set((int)_keyPressed, false);

    if (!actionMap.count(key))
        return;

    vector<InputAction> assignedAction = actionMap[key];

	for (vector<InputAction>::iterator itr = assignedAction.begin(); itr != assignedAction.end(); ++itr)
	{
        if (itr->doOnRelease)
            itr->DoAction();
    }
}

void InputHandler::AssignKeyboardAction(EventKeyboard::KeyCode _keyPressed, function<void()> _action, bool _doOnPress, bool _doOnHeld, bool _doOnRelease)
{
    // input key in string
    string key = keyboardIdentifyer;
    key += (int)_keyPressed;

    if (actionMap.count(key))
    {
        actionMap[key].push_back(InputAction(key, _action, _doOnPress, _doOnHeld, _doOnRelease));
     }
    else
    {
        vector<InputAction> newActionVector;
        newActionVector.push_back(InputAction(key, _action, _doOnPress, _doOnHeld, _doOnRelease));

        actionMap.insert(std::pair<string, vector<InputAction>>(key, newActionVector));
    }

}

void InputHandler::DoMouseOnPress(Event* _event)
{
    EventMouse* mouseEvent = (EventMouse*)_event;
    
    this->mouseDownPosition = mouseEvent->getStartLocation();

    string key = mouseIdentifyer;
    key += (int)mouseEvent->getMouseButton();

    if (!actionMap.count(key))
        return;

    vector<InputAction> assignedAction = actionMap[key];

    for (auto it : assignedAction)
    {
        if (it.doOnPress)
            it.DoAction();
    }
}

void InputHandler::DoMouseOnRelease(Event* _event)
{
    EventMouse* mouseEvent = (EventMouse*)_event;

    this->mouseUpPosition = mouseEvent->getLocation();

    string key = mouseIdentifyer;
    key += (int)mouseEvent->getMouseButton();
    
    if (!actionMap.count(key))
        return;

    vector<InputAction> assignedAction = actionMap[key];

    for (auto it : assignedAction)
    {
        if (it.doOnRelease)
            it.DoAction();
    }
}

void InputHandler::DoMouseOnMove(Event* _event)
{
    EventMouse* mouseEvent = (EventMouse*)_event;

    currentMousePosition = mouseEvent->getLocation();
    previousMousePosition = mouseEvent->getPreviousLocation();
}

void InputHandler::AssignMouseAction(EventMouse::MouseButton _keyPressed, function<void()> _action, bool _doOnPress, bool _doOnHeld, bool _doOnRelease)
{
    // input key in string
    string key = mouseIdentifyer;
    key += (int)_keyPressed;

    if (actionMap.count(key))
    {
        actionMap[key].push_back(InputAction(key, _action, _doOnPress, _doOnHeld, _doOnRelease));
    }
    else
    {
        vector<InputAction> newActionVector;
        newActionVector.push_back(InputAction(key, _action, _doOnPress, _doOnHeld, _doOnRelease));

        actionMap.insert(std::pair<string, vector<InputAction>>(key, newActionVector));
    }
}
