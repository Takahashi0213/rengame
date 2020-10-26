/*!
 * @brief	カプセルコライダー。
 */

#include "stdafx.h"
#include "physics/Collider/CapsuleCollider.h"



/*!
	* @brief	デストラクタ。
	*/
CapsuleCollider::~CapsuleCollider()
{
	delete shape;
}
