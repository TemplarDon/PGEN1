#ifndef __ENDROOM_TEST_H__
#define __ENDROOM_TEST_H__

#include "cocos2d.h"
#include "Animation/AnimationController.h"
#include "Player/Player.h"
#include "Interactables/interactable.h"

// Facebook
//#define SDKBOX_ENABLED
#include "proj.ios_mac/PluginFacebook.framework/Versions/A/Headers/PluginFacebook.h"
using namespace sdkbox;

using namespace cocos2d;

class EndRoom : public cocos2d::Scene, sdkbox::FacebookListener
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(EndRoom);

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

    // Environment Init
    void InitEnvironment();

    //Key Press
    void OnKeyPressed(EventKeyboard::KeyCode _keycode, Event* _event);
    void OnMouseEvent(Event* _event);
    bool onContactBegin(PhysicsContact& contact);
    void onContactSeperate(PhysicsContact& contact);

    virtual void update(float _dt);

    void InputMouseTestFunction();
    void InputKeyboardTestFunction();
    void SpawnNPC();
    void Pause();

    void SwitchSceneTest(cocos2d::Ref* pSender);

	void FacebookShare();

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

    //Facebook callback
    void onLogin(bool isLogin, const std::string& msg);
    void onSharedSuccess(const std::string& message);
    void onSharedFailed(const std::string& message);
    void onSharedCancel();
    void onAPI(const std::string& key, const std::string& jsonData);
    void onPermission(bool isLogin, const std::string& msg);
    void onFetchFriends(bool ok, const std::string& msg);
    void onRequestInvitableFriends(const sdkbox::FBInvitableFriendsInfo& friends);
    void onInviteFriendsWithInviteIdsResult(bool result, const std::string& msg);
    void onInviteFriendsResult(bool result, const std::string& msg);
    void onGetUserInfo(const sdkbox::FBGraphUser& userInfo);
};

#endif // __TEST_SCENE_H__
