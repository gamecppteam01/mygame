#pragma once


// スプライトID
enum SPRITE_ID
{
	START_SPRITE,
	WHITE_SCREEN_SPRITE,
	BLACK_SCREEN_SPRITE,

	TITLE_START,
	TITLE_END,
	TITLE_SELECT,


	COUNT_SPRITE//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

// モデルID
enum MODEL_ID
{
	DUMMY_MODEL,
	PLAYER_MODEL,
	ENEMY_MODEL,
	SKYBOX_MODEL,
	STAGE_MODEL,
	COUNT_MODEL//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

// SE_ID
enum SE_ID
{
	CHECK_SE,

	COUNT_CHECK//全リソース数確認用キー(このキーにリソースを設定しないこと)
};

// BGM_ID
enum BGM_ID
{
	TITLE_BGM,
	
	COUNT_BGM//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

enum FONT_ID {
	JAPANESE_FONT,
	
	COUNT_FONT//全リソース数確認用キー(このキーにリソースを設定しないこと)

};

