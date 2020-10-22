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

//DirectXTK�̃C���N���[�h�t�@�C���B
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

static const int MAX_BONE = 512;					//!<�{�[���̍ő吔�B
static const int MAX_DIRECTION_LIGHT = 5;			//!<�f�B���N�V�������C�g�̍ő吔�B
static const int MAX_POINT_LIGHT = 16;				//!<�|�C���g���C�g�̍ő吔�B

const float FRAME_BUFFER_W = 1280.0f;				//�t���[���o�b�t�@�̕��B
const float FRAME_BUFFER_H = 720.0f;				//�t���[���o�b�t�@�̍����B
const int MAX_OBJ_PRIORITY = 11;					//�I�u�W�F�N�g�ő�D��x
const int MAX_LEVEL_OBJ = 100;						//���x���ɐݒ�ł���ő�I�u�W�F�N�g��

#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "physics/Physics.h"

#include "graphics/GraphicsEngine.h"

#include "graphics/skinModel/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"
#include "CCamera2D.h"

#include "Hash.h"
#include "DebugLog.h"
#include "GameTime.h"
#include "LightMaker.h"
#include "CameraSupporter.h"
#include "MouseSupporter.h"

#include "SpriteStandby.h"
#include "SpriteRender.h"

#include "graphics/skinModel/SkinModelRender.h"
#include "ShadowMap.h"

#include "FontRender.h"

#include "GameData.h"
#include "GameEffect.h"

#include "TransitionGenerator.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include "ObjectClass.h"

#include "SceneManager.h"

extern SpriteRender spRen;
