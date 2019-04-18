////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include "textureclass.h"
#include "d3dclass.h"
#include "Structs.h"

#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class GameObject
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR3 binormal;
	};


	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

public:
	GameObject(ID3D11Device*, ModelInfo*, TextureClass*, TextureClass*, bool = true);
	GameObject(const GameObject&);
	~GameObject();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	
	void GetWorldMatrix(D3DXMATRIX& worldMatrix);

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void SetScale(float, float, float);

	void Rotate(float x, float y, float z);
	void Translate(float x, float y, float z);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	ID3D11ShaderResourceView* GetDiffuseTexture();
	ID3D11ShaderResourceView* GetNormalTexture();


protected:

	

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:

	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void CalculateNormal(VectorType, VectorType, VectorType&);

protected:

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

private:

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	D3DXMATRIX m_worldMatrix, m_projectionMatrix;

private:
	ModelType* m_model;
	ModelInfo* m_ModelInfo;
	TextureClass* m_DiffuseTexture, *m_NormalTexture;


};

#endif