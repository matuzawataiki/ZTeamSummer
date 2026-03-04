/*!
 * @brief	シンプルなモデルシェーダー。
 */

////////////////////////////////////////////////
// ライト構造体
////////////////////////////////////////////////
//ディレクションライト構造体
struct DirectionLig
{
    float3 direction;	//方向
    float4 color;		//色
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ライト用の定数バッファ
cbuffer LightCb : register(b1)
{
    DirectionLig	m_directionLig;					//ディレクションライト
    float3          m_eyePos;                       //視点の位置
    float3          m_ambientLight;                 //環境光
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float2 uv 		: TEXCOORD0;	//UV座標。
    float3 normal	: NORMAL;		//法線ベクトル
    float3 tangent : TANGENT; //接ベクトル
    float3 biNormal : BINORMAL; //従ベクトル
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 normal		: NORMAL;		//法線ベクトル
    float3 worldPos     : TEXCOORD1; // ワールド空間でのピクセルの座標
    float3 tangent      : TANGENT; //接ベクトル
    float3 biNormal     : BINORMAL; //従ベクトル
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
Texture2D<float4> g_normalMap : register(t1);           //ノーマルマップ
Texture2D<float4> g_specularMap : register(t2);         //ノーマルマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

Texture2D<float4> g_shadowMap : register(t10);           ///シャドウマップ
////////////////////////////////////////////////
//関数宣言
////////////////////////////////////////////////
//ディレクションライトの計算
float3 CalcDirectionLight(SPSIn psIn);

//Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
//Phon鏡面反射光の計算
float3 CalcPhongSpecular(SPSIn psIn, float3 lightDirection, float3 lightColor, float3 normal, float3 worldPos);

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
/// <summary>
/// ディレクションライトの計算
/// </summary>
float3 CalcDirectionLight(SPSIn psIn)
{	
    //拡散反射
    float3 diffuseLig = CalcLambertDiffuse(m_directionLig.direction, m_directionLig.color, psIn.normal);
    //鏡面反射
    float3 specularLig = CalcPhongSpecular(psIn, m_directionLig.direction, m_directionLig.color, psIn.normal, psIn.worldPos);
    
    float3 finalLig = diffuseLig + specularLig;
	
    return finalLig;
}

/// <summary>
//Lambert拡散反射光の計算
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    //法線とディレクションライトの向きの内積を求める
    float t = dot(normal, lightDirection) * -1.0f;
    //0以下は0にする
    t = max(0.0f, t);
	//陰をつける
    float3 diffuseLig = lightColor * t;
    
    return diffuseLig;
}

/// <summary>
/// Phon鏡面反射光の計算
/// </summary>
float3 CalcPhongSpecular(SPSIn psIn, float3 lightDirection, float3 lightColor, float3 normal, float3 worldPos)
{
    float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;
    
    //ディレクションライトの向きの反射ベクトルを求める
    float3 refVec = reflect(lightDirection, normal);
    
	//サーフェイスから視点に向かうベクトルを作る
    float3 toEye = m_eyePos - worldPos;
    toEye = normalize(toEye);
    
    float t;
	//鏡面反射の強さを求める
    t = dot(refVec, toEye);
    //0以下は0にする
    t = max(0.0f, t);
    //鏡面反射の強さを絞る
    t = pow(t, 5.0f);
    
	//鏡面反射をつける
    float3 specularLig = lightColor * t;
    specularLig *= specPower * 10.0f;

	
    return specularLig;
}

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	psIn.uv = vsIn.uv;
	
	//追加
    psIn.normal = mul(mWorld, vsIn.normal);         //法線を回転させる
    psIn.tangent = mul(mWorld, vsIn.tangent); //接ベクトル
    psIn.biNormal = mul(mWorld, vsIn.biNormal); //接ベクトル
	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}

/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn) : SV_Target0
{
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    localNormal = (localNormal - 0.5) * 2.0f;
    psIn.normal = psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + psIn.normal * localNormal.z;
    
    float3 finalLig;
	//ディレクションライトの計算
    finalLig = CalcDirectionLight(psIn);
	
    //環境光の設定
    finalLig += m_ambientLight;

    //最終合成
    float4 finalColor = g_albedo.Sample(g_sampler, psIn.uv);
    
    finalColor.xyz *= finalLig;

	return finalColor;
}
