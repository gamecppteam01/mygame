#pragma once

#include <Dxlib.h>

namespace BLEND_MODE
{
	//�u�����h�Ȃ�
	const int NoBlend	= DX_BLENDMODE_NOBLEND;
	//�A���t�@�u�����h
	const int Alpha		= DX_BLENDMODE_ALPHA;
	//���Z����
	const int Add		= DX_BLENDMODE_ADD;
	//���Z����
	const int Sub		= DX_BLENDMODE_SUB;
	//��Z����
	const int Mul		= DX_BLENDMODE_MULA;
	//���]
	const int Inverse	= DX_BLENDMODE_INVSRC;
	//��Z�ς݃A���t�@�p
	const int PMA_Alpha = DX_BLENDMODE_PMA_ALPHA;
	//��Z�ς݃A���t�@�p
	const int PMA_Add	= DX_BLENDMODE_PMA_ADD;
	//��Z�ς݃A���t�@�p
	const int PMA_Sub	= DX_BLENDMODE_PMA_SUB;
	//��Z�ς݃A���t�@�p
	const int PMA_Inverse = DX_BLENDMODE_PMA_INVSRC;
}