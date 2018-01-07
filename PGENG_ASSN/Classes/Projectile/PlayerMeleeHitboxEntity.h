//#ifndef _PLAYER_MELEE_HITBOX_ENTITY_H
//#define _PLAYER_MELEE_HITBOX_ENTITY_H
//
//#include "ProjectileBase.h"
//
//#include <vector>
//using std::vector;
//
//class EnemyBase;
//
//class PlayerMeleeHitboxEntity : public ProjectileBase
//{
//public:
//    PlayerMeleeHitboxEntity(Mesh* _modelMesh);
//    virtual ~PlayerMeleeHitboxEntity();
//
//	virtual void UpdateAnimation(double dt);
//	//virtual void CollisionResponse(EntityBase* other, double dt);
//
//	//virtual void SetAnimationDirection(Vector3 dir);
//    virtual void Update(double dt);
//    virtual void Render();
//
//	virtual void HandleIsDead();
//	void CollidedEntityHandler();
//
//protected:
//	vector<EnemyBase*> v_CollidedEntities;
//};
//
//namespace Create
//{
//    PlayerMeleeHitboxEntity* playerMeleeHitboxEntity(
//        EntityManager* em,
//        const std::string& _meshName,
//        const Vector3& _position = Vector3(0, 0, 0),
//		const Vector3& _front = Vector3(0, 0, 0),
//        const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f),
//		const float& _lifespan = FLT_MAX,
//        const float& _damage = 0
//        );
//
//	PlayerMeleeHitboxEntity* playerMeleeHitboxAsset(
//        const std::string& _meshName,
//        const Vector3& _position = Vector3(0, 0, 0),
//		const Vector3& _front = Vector3(0, 0, 0),
//        const Vector3& _scale = Vector3(1.0f, 1.0f, 1.0f),
//		const float& _lifespan = FLT_MAX,
//        const float& _damage = 0
//        );
//};
//
//#endif // _PLAYER_MELEE_HITBOX_ENTITY_H