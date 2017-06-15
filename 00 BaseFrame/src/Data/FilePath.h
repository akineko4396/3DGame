#pragma once

//プレイヤーパス
#define PLAYER_PATH "data/model/Player/Player2.xed"

//ステージパス
#define GROUND_PATH "data/model/map/map.x"

//アームパス
#define ARM_PATH "data/model/Arm/Arm.x"

//ベルトコンベアパス
#define BELT_PATH "data/model/Belt/belt.x"

//ブリッジパス
#define BRIDGE_PATH "data/model/Bridge/Bridge.x"

//テキスト簡略化
#define TXT_DATA_SAVE "\t" << "Pos(" << Pos.x << "," << Pos.y << "," << Pos.z << ")" << "\t" << "Scale(" << Scale.x << "," << Scale.y << "," << Scale.z << ")" << "\t" << "Angle(" << Angle.x << "," << Angle.y << "," << Angle.z << ")" 

//CSV簡略化
#define CSV_DATA_SAVE modelName << "," << Pos.x << "," << Pos.y << "," << Pos.z << "," << size << "," << Angle.x << "," << Angle.y << "," << Angle.z << ","