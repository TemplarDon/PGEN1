#ifndef __PATHFINDER_TEST_H__
#define __PATHFINDER_TEST_H__

#include "cocos2d.h"
#include "Animation\AnimationController.h"

using namespace cocos2d;

class PathfinderTest : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PathfinderTest);

    // Callback functions
    void SetListeners();

    // Init animations4
    void InitAnimationActions();

    // Shader Init
    void InitShader();

    // Tilemap Init
    void InitTilemap();

    // FSM Init
    void InitFSM();

    //Key Press
    void OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event);
    void OnMouseEvent(Event* _event);
    bool onContactBegin(PhysicsContact& contact);

    virtual void update(float _dt);

    void InputMouseTestFunction();
    void InputKeyboardTestFunction();
    void SwitchSceneTestFunction();
    void AddSceneTestFunction();
    void PopSceneTestFunction();

    void SwitchSceneTest(cocos2d::Ref* pSender);

    void UpdatePlayer();

    void MovePlayer();
    void MovePlayerUp();
    void MovePlayerDown();
    void MovePlayerLeft();
    void MovePlayerRight();

    void StopPlayerUp();
    void StopPlayerDown();
    void StopPlayerLeft();
    void StopPlayerRight();

    void StopAnimation();
    void PlayWalkingSoundEffect();

    bool shouldMoveUp = false;
    bool shouldMoveDown = false;
    bool shouldMoveLeft = false;
    bool shouldMoveRight = false;

    void UpdateFSM();

private:
    enum ANIMLIST
    {
        FRONT = 0,
        LEFT,
        RIGHT,
        BACK,
        NUM_ANIM,
    };

    Animate* v_mainCharAnimation[NUM_ANIM];

    AnimationController* animController;

    GLProgram* proPostProcess;
    RenderTexture* rendtex;
    Sprite* rendtexSprite;

};

#endif // __TEST_SCENE_H__
