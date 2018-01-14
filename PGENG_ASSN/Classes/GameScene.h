#ifndef __GAMESCENE_TEST_H__
#define __GAMESCENE_TEST_H__

#include "cocos2d.h"
#include "Animation\AnimationController.h"
#include "Player\Player.h"
#include "Interactables\interactable.h"


using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

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

    // Puzzle Init
    void InitPuzzle();

    //Key Press
    void OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event);
    void OnMouseEvent(Event* _event);
    bool onContactBegin(PhysicsContact& contact);
	void onContactSeperate(PhysicsContact& contact);

    virtual void update(float _dt);

    void InputMouseTestFunction();
    void InputKeyboardTestFunction();
    void SwitchSceneTestFunction();
    void AddSceneTestFunction();
    void PopSceneTestFunction();

    void SwitchSceneTest(cocos2d::Ref* pSender);

	void SpawnNPC();
	void SpawnHeart(Vec2 pos);

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
    Vec2 spawnPos;
    Player* player;

	Vec2 cameraOrthoScale;

	MenuItemFont* menu_play;
	bool m_over;
};

#endif // __TEST_SCENE_H__
