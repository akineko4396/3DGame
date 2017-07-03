#pragma once

//プレイヤーパス
#define PLAYER_PATH "data/model/Player/Player2.xed"

//ボス
#define BOSS_PATH ""

//スケルトン
#define SKELETON_PATH ""

//デーモン
#define DEMON_PATH "data/model/Demon/demon.xed"

//ステージパス
#define GROUND_PATH "data/model/map/map.x"

//拠点パス
#define STRONGHOLD_PATH ""

//壁パス
#define WALL_PATH ""

//投石器
#define SLING_PATH ""

//大砲
#define CANNON_PATH ""

//火炎放射器
#define FLAMETHROWER_PATH ""

//プレス機
#define PRESS_PATH ""

//アームパス
#define ARM_PATH "data/model/Arm/Arm.x"

//ベルトコンベアパス
#define BELTCONVEYOR_PATH "data/model/Belt/belt.xed"

//ブリッジパス
#define BRIDGE_PATH "data/model/Bridge/Bridge.x"

//テキスト簡略化
#define TXT_DATA_SAVE "\t" << "Pos(" << Pos.x << "," << Pos.y << "," << Pos.z << ")" << "\t" << "Scale(" << Scale.x << "," << Scale.y << "," << Scale.z << ")" << "\t" << "Angle(" << Angle.x << "," << Angle.y << "," << Angle.z << ")" 

//CSV簡略化
#define CSV_DATA_SAVE Pos.x << "," << Pos.y << "," << Pos.z << "," << size << "," << Angle.x << "," << Angle.y << "," << Angle.z << ","