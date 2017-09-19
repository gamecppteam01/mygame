// �A�N�^�[ID
enum ACTOR_ID
{
	BEGIN_ACTOR,
	/* �X�e�[�W�֌W */
	STAGE_ACTOR,			// �X�e�[�W
	PORTAL_ACTOR,			// �|�[�^��
	WARP_ACTOR,				// ���[�v
	EVENTAREA_ACTOR,		// �C�x���g�G���A
							/* �L�����N�^�[�֌W */
							DUMMY_ACTOR,			// �_�~�[
							ENEMY_ACTOR,			// �G�l�~�[
							ENEMY_SYMBOL_ACTOR,		// �V���{��
							NPC_ACTOR,				// NPC
							PLAYER_ACTOR,			// �v���C���[
													/* �J���� */
													CAMERA_ACTOR,			// �J����
																			/* UI�֌W */
																			MESSAGE_WINDOW_ACTOR,	// ���b�Z�[�W�E�B���h�E
																			UI_ACTOR,				// UI

																			END_ACTOR,
};
// �Փ˔���ID
enum COL_ID
{
	BEGIN_COL,

	/* �X�e�[�W�p�Փ˔��� */
	// �A�N�^�[ vs ��
	ACTOR_WALL_COL,
	// �A�N�^�[ vs ��
	ACTOR_STAGE_COL,

	/* �v���C���[�p�Փ˔��� */
	// �v���C���[ vs �G�l�~�[�V���{��
	PLAYER_ENEMYSYMBOL_COL,
	// �v���C���[ vs �|�[�^��
	PLAYER_PORTAL_COL,

	/* �J�����p�Փ˔��� */
	CAMERA_WALL_COL,

	END_COL,
};
