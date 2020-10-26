#pragma once

//ポイントライト

struct SPointLight {
	CVector4 position[MAX_POINT_LIGHT];				//ライトの座標
	CVector4 color[MAX_POINT_LIGHT];				//ライトのカラー(wにライトの影響範囲)
//	float range[MAX_POINT_LIGHT];					//ライトの影響範囲
};

