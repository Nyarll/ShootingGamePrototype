#pragma once

// ステージクリアの処理
void InitStage(void);		// クリアしたなら初期化
void StageClearCheck(void);	// クリアしたかどうか
void GameOverCheck(void);	// 残機がなくなったかどうか

// プレイ中の処理
void InitPlay(void);
void UpdatePlay(void);
void RenderPlay(void);
void FinalPlay(void);

// 当たり判定
void PlayerShot_EnemyCollision(void);
void EnemyShot_PlayerCollision(void);
void GrazeCollision(void);
void Player_ItemCollision(void);

void PlayerShot_BossCollision(void);
void BossShot_PlayerCollison(void);

void DrawGameObject(void);


// デバッグ用
void UseDebug(void);
void DrawDebug(void);