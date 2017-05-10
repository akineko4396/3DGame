//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 勉強用の単純なシェーダ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define MAX_BONE 400	// ボーン最大数

//===========================================================
// コンスタント(定数)バッファの作成
// 定数バッファとはグローバル定数をグループ化した物。VC側からデータを渡せる場所。
// Direct3D11ではグローバル定数は、この定数バッファにする必要がある。
//
// register(b0)のb0が定数バッファのグループ番号
// 最大14個(b0〜b13)作れる
// VC側からはこの番号を使って定数バッファをセットする
//
// 定数バッファにはパッキング規則というものがあり、きちんと意識していないと
// VC側から正常に値を持っていけないので注意
// [定数変数のパッキング規則 (DirectX HLSL)]
// https://msdn.microsoft.com/ja-jp/library/bb509632(v=vs.85).aspx
//===========================================================

//===========================================================
// [定数バッファ]フレーム単位データ
// 毎フレームに一度だけ更新されるようなデータはココ！
//===========================================================
cbuffer cbPerFrame : register(b0) {
	row_major float4x4	g_mV;	// ビュー行列
	row_major float4x4	g_mP;	// 射影行列

	float3	g_LightDir;			// 平行光源の方向

	// カメラ
	float3	g_CamPos;			// カメラ座標
};

//===========================================================
// [定数バッファ]オブジェクト単位データ
// オブジェクト(モデル)単位で更新されるデータはココ！
//===========================================================
cbuffer cbPerObject : register(b1)
{
	row_major float4x4	g_mW;	// ワールド行列

	int		g_LightEnable;		// ライティング有効?
};

//===========================================================
// [定数バッファ]マテリアル単位データ
// マテリアル単位で更新されるデータはココ！
//===========================================================
cbuffer cbPerMaterial : register(b2)
{
	float4	g_Diffuse;			// 拡散色(基本色)
	float4	g_Ambient;			// 環境色
	float4	g_Specular;			// スペキュラ(反射)
	float	g_SpePower;			// スペキュラの鋭さ
	float4	g_Emissive;			// エミッシブ(自己発光)
};

//===========================================================
// [定数バッファ]オブジェクト単位データ(スキンメッシュ用)
// スキンメッシュのボーン行列の配列です。
// ここに全ボーンの行列を持ってきます。更新頻度はオブジェクト(モデル)単位です。
// cbPerObjectと切り離した理由は、スキンメッシュ以外のモデルにMAX_BONEの数もの行列を
// 更新するのは無駄が多いからです。
//===========================================================
cbuffer cbPerSkinObject : register(b3)
{
	row_major float4x4	g_mWArray[MAX_BONE];	// ボーン用行列配列
};

//====================================================
// テクスチャ
//  VC側からセットするときに指定する番号は、t0〜t127の位置に対応している
//  最大128(t0〜t127)
//====================================================
Texture2D MeshTex	: register(t0);				// メッシュの通常テクスチャ

//====================================================
// サンプラ
//  VC側からセットするときに指定する番号は、s0〜s15の位置に対応している
//  最大16(s0〜s15)
//====================================================
SamplerState WrapSmp : register(s0);	// Wrap用のサンプラ

//===============================================
// 頂点シェーダー
//===============================================

// 頂点シェーダ出力データ
struct VS_OUT {
	float4 Pos		: SV_Position;		// 2D座標(射影座標系)
	float2 UV		: TEXCOORD0;		// UV
	float3 wN		: TEXCOORD1;		// 法線
};

// スタティックメッシュ用頂点シェーダー
VS_OUT VS(	float4 pos : POSITION,		// 頂点座標(ローカル)
			float3 normal : NORMAL,		// 法線
			float2 uv : TEXCOORD0		// テクスチャUV
){
	VS_OUT Out;	// 出力用構造体

	// 2D変換(射影座標系へ変換)
	Out.Pos = mul(pos, g_mW);
	Out.Pos = mul(Out.Pos, g_mV);
	Out.Pos = mul(Out.Pos, g_mP);

	// UVはそのまま入れる
	Out.UV = uv;

	// 法線をワールド変換
	Out.wN = normalize(mul(normal, (float3x3)g_mW));

	return Out;
}

// スキンメッシュ用頂点シェーダー
VS_OUT SkinVS(	float4 pos : POSITION,				// 頂点座標(ローカル)
				float3 normal : NORMAL,				// 法線
				float2 uv : TEXCOORD0,				// テクスチャUV
				float4 blendWeight : BLENDWEIGHT,	// ボーンウェイトx4　ここに、この頂点に影響しているボーンの影響度が入ってくる　最大４つ(x,y,z,w)
				uint4 blendIndex : BLENDINDICES		// ボーン番号x4　ここに、この頂点に影響しているボーン番号が入ってくる　最大４つ(x,y,z,w)
){
	VS_OUT Out;	// 出力用構造体

    //----------------------------------------------------------------------	
	// 4つのボーン行列で頂点座標や法線をブレンドし、3Dワールド座標・法線を求める
	float3      Pos = 0.0f;		// 3Dワールド座標用
	float3      Normal = 0.0f;	// 3Dワールド法線用

	for(int i = 0; i<4; i++){
        // 座標
		Pos += mul(pos, g_mWArray[blendIndex[i]]).xyz * blendWeight[i]; 
        // 法線
		Normal += mul(normal, (float3x3)g_mWArray[blendIndex[i]]) * blendWeight[i];
	}
    //----------------------------------------------------------------------	

	// 2D変換(射影座標系へ変換)
	Out.Pos = mul(float4(Pos, 1), g_mV);    // ワールド座標 から ビュー座標系へ変換(まだ3D  カメラが動いていないときの座標系)
	Out.Pos = mul(Out.Pos, g_mP);           // ビュー座標系 から 射影座標系へ変換(ここで2Dになる)

	// UV
	Out.UV = uv;

	// 法線
	Out.wN = Normal;

	return Out;
}

//===============================================
// ピクセルシェーダ
//===============================================

//ピクセルシェーダ出力データ
struct PS_Out {
	float4 Color : SV_Target0;
};

// ピクセルシェーダ
PS_Out PS(VS_OUT In)
{
	float4 Col = 1;	// 最終的な色を入れる変数

	// 法線を正規化
	float3 w_normal = normalize(In.wN);

	//====================================
	// ライティング計算
	//====================================
	// ランバート照明
	float LPow = 1;
	if(g_LightEnable){	// ライティング有効時のみ
		LPow = dot(-g_LightDir, w_normal);	// ライト方向と法線との角度の差を内積で求める(-1〜1)
		LPow = max(0, LPow);				// 0未満は0とする(0〜1)
	}


	//============================================================
	// テクスチャの色を取得
	//============================================================
	float4 texCol = MeshTex.Sample(WrapSmp, In.UV);		// MeshTexのIn.UVの位置の色を取得。詳細な取得方法はWrapSmpを使用。

	Col = texCol;

	//============================================================
	// ライティング適用　環境光も適用
	//============================================================
	Col.rgb *= g_Diffuse.rgb*LPow + g_Ambient.rgb;	// 材質の色*光の強さ + 環境光
	Col.a *= g_Diffuse.a;

	//============================================================
	// 出力色
	//============================================================
	PS_Out Out;	// 出力用構造体

	Out.Color = Col;

	return Out;
}

