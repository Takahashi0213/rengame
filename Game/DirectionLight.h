#pragma once

//ディレクションライト

struct SDirectionLight {
	CVector4 direction[MAX_DIRECTION_LIGHT];		//ライトの方向
	CVector4 color[MAX_DIRECTION_LIGHT];			//ライトのカラー
};

