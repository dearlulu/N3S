// Obviously thanks to http://www.directxtutorial.com/ for a bunch of this
// As well as http://www.braynzarsoft.net/viewtutorial/q16390-4-begin-drawing

#pragma once
#include <vector>
#include "Camera.hpp"
#include "N3sPalette.hpp"
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <wrl/client.h>
#include "N3sD3DContext.h"

static float pixelSizeW = (2.0f / 256.0f);
static float pixelSizeH = (2.0f / 240.0f);

using namespace DirectX;
using namespace std;

enum ShaderType { color, overlay };

struct ColorVertex {
	XMFLOAT4 Pos;
	XMFLOAT4 Col;
};

struct OverlayVertex {
	XMFLOAT4 Pos;
};

struct VoxelMesh {
	ID3D11Buffer *buffer;
	ShaderType type;
	int size;
};

struct MatrixBuffer
{
	XMMATRIX matrix;
};

struct ShaderSet
{
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;
};

struct Crop
{
	bool zeroed();
	int top;
	int left;
	int bottom;
	int right;
};

struct MirrorState
{
	int x;
	int y;
};

class N3S3d {
public:
	static void initPipeline(N3sD3dContext context);
	static ID3D11Buffer* createBufferFromColorVertices(ColorVertex vertices[], int arraySize);
	static ID3D11Buffer* createBufferFromColorVerticesV(std::vector<ColorVertex> * vertices, int arraySize);
	static void updateMatricesWithCamera(Camera * camera);
	static void updateViewMatrices(XMFLOAT4X4 view, XMFLOAT4X4 perspective);
	static void updateWorldMatrix(float, float, float);
	static void updateMirroring(bool horizontal, bool vertical);
	static void updatePalette(float palette[72]);
	static void selectPalette(int palette);
	static XMMATRIX getProjectionMatrix(const float near_plane, const float far_plane, const float fov_horiz, const float fov_vert);
	static void setShader(ShaderType type);
	static void renderMesh(VoxelMesh *voxelMesh);
	static PPUHueStandardCollection ppuHueStandardCollection;
	static void setIndexBuffer();
	static void enabledDepthBuffer();
	static void disableDepthBuffer();
private:
	static Microsoft::WRL::ComPtr<ID3D11Device>            device;
	static Microsoft::WRL::ComPtr<ID3D11Device1>           device1;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     context;
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    context1;
	static void initShaders();
	static void initSampleState();
	static void createIndexBuffer();
	static bool initDepthStencils();
	static ShaderSet shaderSets[2];
	static ID3D11InputLayout *inputLayouts[2];
	static ID3D11Buffer *worldMatrixBuffer;
	static ID3D11Buffer *viewMatrixBuffer;
	static ID3D11Buffer *projectionMatrixBuffer;
	static ID3D11Buffer *mirrorBuffer;
	static ID3D11Buffer *paletteBuffer;
	static ID3D11Buffer *paletteSelectionBuffer;
	static ID3D11Buffer *indexBuffer;
	static MatrixBuffer *worldMatrixPtr;
	static MatrixBuffer *viewMatrixPtr;
	static MatrixBuffer *projectionMatrixPtr;
	static ID3D11SamplerState* sampleState;
	static ID3D11Texture2D* texture2d;
	static ID3D11ShaderResourceView* textureView;
	static ShaderType activeShader;
	static D3D11_SUBRESOURCE_DATA subData;
	static MirrorState mirrorState;
	static D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	static D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	static ID3D11DepthStencilState* m_depthDisabledStencilState;
	static ID3D11DepthStencilState* m_depthStencilState;

	static ID3D11DepthStencilView* m_depthStencilView;
	static int selectedPalette;
	static int mirrorBufferNumber;
	static int paletteBufferNumber;
	static int paletteSelectionBufferNumber;
};

bool toggleBool(bool b);
string replaceExt(string input, string newExt);