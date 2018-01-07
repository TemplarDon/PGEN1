//#include "PlayerMeleeHitboxEntity.h"
//
//PlayerMeleeHitboxEntity::PlayerMeleeHitboxEntity(Mesh* _modelMesh) :
//ProjectileBase(_modelMesh)
//{
//}
//
//PlayerMeleeHitboxEntity::~PlayerMeleeHitboxEntity()
//{
//}
//
//void PlayerMeleeHitboxEntity::Update(double dt)
//{
//	ProjectileBase::Update(dt);
//	CollidedEntityHandler();
//
//	if (animationPlayer.m_pause)
//		SetShouldRender(false);
//
//	if (this->b_IsDone)
//		HandleIsDead();
//
//	UpdateLifeSpan(dt);
//}
//
//void PlayerMeleeHitboxEntity::UpdateAnimation(double dt)
//{
//	animationPlayer.Update(dt);
//}
//
//void PlayerMeleeHitboxEntity::SetAnimationDirection(Vector3 dir)
//{
//	if (abs(dir.x) > abs(dir.y))//horizontal direction
//	{
//		if (dir.x > 0)
//			animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("right");
//		else
//			animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("left");
//	}
//	else if (abs(dir.y) > abs(dir.x)) //vertical direction
//	{
//		if (dir.y > 0)
//			animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("up");
//		else
//			animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("down");
//	}
//	else//diagonal direction
//	{
//		if (dir.y > 0)//top-diagonal
//		{
//			if (dir.x > 0)
//				animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("up_right");
//			else
//				animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("up_left");
//		}
//		else
//		{
//			if (dir.x > 0)
//				animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("down_right");
//			else
//				animationPlayer.m_anim = AnimationManager::GetInstance("player_shield_melee")->GetAnimation("down_left");
//		}
//	}
//}
//
//void PlayerMeleeHitboxEntity::Render()
//{
//	if (!b_DoRender)
//		return;
//
//	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
//
//	//float angle = Math::RadianToDegree(atan2(front.y, front.x));
//	//modelStack.PushMatrix();
//	//modelStack.Translate(position.x, position.y, position.z);
//	//modelStack.Translate(colliderOffset.x, colliderOffset.y, colliderOffset.z);
//	//modelStack.Rotate(angle, 0, 0, 1);
//	//modelStack.Scale(colliderSize.x, colliderSize.x, colliderSize.z);
//	//RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("quad2"));
//	//modelStack.PopMatrix();
//
//	//float angle = Math::RadianToDegree(atan2(front.y, front.x));
//	modelStack.PushMatrix();
//	modelStack.Translate(position.x, position.y, position.z);
//	//modelStack.Rotate(angle, 0, 0, 1);
//	modelStack.Scale(scale.x * 0.5f, scale.y * 0.5f, scale.z);
//	RenderHelper::RenderSprite(modelMesh, animationPlayer);
//	modelStack.PopMatrix();
//}
//
//void PlayerMeleeHitboxEntity::CollisionResponse(EntityBase* other, double dt)
//{
//	EnemyBase* temp = dynamic_cast<EnemyBase*>(other);
//
//	if (!temp)
//		return;
//
//	for (auto it : v_CollidedEntities)
//	{
//		if (it == other)
//			return;
//	}
//
//    ParticleBase* particle = Create::particleScale(EntityManager::GetInstance(), "player_shield_block_effect", other->GetPosition() + Vector3(0.f, 0.f, 0.1f), other->GetScale() + Vector3(9, 3, 1), 0.2f, 0.0f, 0.2f);
//	Vector3 dir = other->GetPosition() - this->position;
//	particle->SetRotate(Math::RadianToDegree(atan2(dir.y, dir.x)) - 90);
//
//
//	v_CollidedEntities.push_back(temp);
//}
//
//void PlayerMeleeHitboxEntity::HandleIsDead()
//{
//	vector<EnemyBase*>::iterator it = v_CollidedEntities.begin();
//	vector<EnemyBase*>::iterator end = v_CollidedEntities.end();
//	
//	for (it; it != end;)
//	{
//		(*it)->TakeDamage(this->projectile_Damage, this);
//		it++;
//	}
//
//	v_CollidedEntities.clear();
//}
//
//void PlayerMeleeHitboxEntity::CollidedEntityHandler()
//{
//	vector<EnemyBase*>::iterator it;
//	for (it = v_CollidedEntities.begin(); it != v_CollidedEntities.end();)
//	{
//		EntityBase* temp = (*it);
//
//		if (temp->GetIsDead() || temp->GetIsDone())
//		{
//			it = v_CollidedEntities.erase(it);
//		}
//		else
//		{
//			++it;
//		}
//	}
//}
//
//PlayerMeleeHitboxEntity* Create::playerMeleeHitboxEntity(EntityManager* em,
//    const std::string& _meshName,
//    const Vector3& _position,
//	const Vector3& _front,
//    const Vector3& _scale,
//	const float& _lifespan,
//    const float& _damage
//    )
//{
//    if (em == NULL)
//        return NULL;
//
//    Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
//
//    if (modelMesh == nullptr)
//        return nullptr;
//
//    PlayerMeleeHitboxEntity* result = new PlayerMeleeHitboxEntity(modelMesh);
//
//    result->SetPosition(_position);
//	result->SetFront(_front);
//	result->SetAnimationDirection(_front);
//    result->SetScale(_scale);
//    result->SetProjectileDamage(_damage);
//	result->SetLifespan(_lifespan);
//
//    result->SetColliderType(Collider::COLLIDER_BOX);
//	result->SetColliderSize(_scale);
//
//    em->AddEntity(result, true);
//    return result;
//}
//
//PlayerMeleeHitboxEntity* Create::playerMeleeHitboxAsset(const std::string& _meshName,
//    const Vector3& _position,
//	const Vector3& _front,
//    const Vector3& _scale,
//	const float& _lifespan,
//    const float& _damage
//    )
//{
//    Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
//    if (modelMesh == nullptr)
//        return nullptr;
//
//    PlayerMeleeHitboxEntity* result = new PlayerMeleeHitboxEntity(modelMesh);
//
//    result->SetPosition(_position);
//	result->SetFront(_front);
//	result->SetAnimationDirection(_front);
//    result->SetScale(_scale);
//    result->SetProjectileDamage(_damage);
//	result->SetLifespan(_lifespan);
//
//	result->SetColliderType(Collider::COLLIDER_BOX);
//	result->SetColliderSize(_scale);
//
//    return result;
//}
