// アクターID
enum ACTOR_ID
{
	BEGIN_ACTOR,
	/* ステージ関係 */
	STAGE_ACTOR,			// ステージ
	PORTAL_ACTOR,			// ポータル
	WARP_ACTOR,				// ワープ
	EVENTAREA_ACTOR,		// イベントエリア
							/* キャラクター関係 */
							DUMMY_ACTOR,			// ダミー
							ENEMY_ACTOR,			// エネミー
							ENEMY_SYMBOL_ACTOR,		// シンボル
							NPC_ACTOR,				// NPC
							PLAYER_ACTOR,			// プレイヤー
													/* カメラ */
													CAMERA_ACTOR,			// カメラ
																			/* UI関係 */
																			MESSAGE_WINDOW_ACTOR,	// メッセージウィンドウ
																			UI_ACTOR,				// UI

																			END_ACTOR,
};
// 衝突判定ID
enum COL_ID
{
	BEGIN_COL,

	/* ステージ用衝突判定 */
	// アクター vs 壁
	ACTOR_WALL_COL,
	// アクター vs 床
	ACTOR_STAGE_COL,

	/* プレイヤー用衝突判定 */
	// プレイヤー vs エネミーシンボル
	PLAYER_ENEMYSYMBOL_COL,
	// プレイヤー vs ポータル
	PLAYER_PORTAL_COL,

	/* カメラ用衝突判定 */
	CAMERA_WALL_COL,

	END_COL,
};
