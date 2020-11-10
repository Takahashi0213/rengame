#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>
//Audio
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>

#include <EffekseerSupporter.h>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//DirectXTKのインクルードファイル。
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

static const int MAX_BONE = 512;					//!<ボーンの最大数。
static const int MAX_DIRECTION_LIGHT = 5;			//!<ディレクションライトの最大数。
static const int MAX_POINT_LIGHT = 16;				//!<ポイントライトの最大数。

const float FRAME_BUFFER_W = 1280.0f;				//!<フレームバッファの幅。
const float FRAME_BUFFER_H = 720.0f;				//!<フレームバッファの高さ。
const int MAX_OBJ_PRIORITY = 11;					//!<オブジェクト最大優先度。
const int MAX_LEVEL_OBJ = 100;						//!<レベルに設定できる最大オブジェクト数。
const int MAX_EVENT_OBJ = 100;						//!<イベントの数。
const int MAX_STAGE_NOM = 5;						//!<ステージの最大数。
const int MAX_ITEM_NOM = 10;						//!<アイテムの種類数。

#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "physics/Physics.h"

#include "graphics/GraphicsEngine.h"

#include "graphics/skinModel/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/camera/Camera.h"
#include "graphics/camera/CCamera2D.h"

#include "Hash.h"
#include "Debug/DebugLog.h"
#include "GameTime.h"
#include "graphics/light/LightMaker.h"
#include "graphics/camera/CameraSupporter.h"
#include "GameSystem/Mouse/MouseSupporter.h"

#include "graphics/sprite/SpriteStandby.h"
#include "graphics/sprite/SpriteRender.h"

#include "graphics/skinModel/SkinModelRender.h"
#include "ShadowMap.h"

#include "graphics/font/FontRender.h"

#include "GameData.h"
#include "GameSystem/GameUI/GameEffect.h"

#include "graphics/Transition/TransitionGenerator.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include "GameObject/ObjectClass.h"

#include "GameScene/SceneManager.h"

extern SpriteRender spRen;
