#include "Transform.h"
#include "Core/Engine.h"
#include "Core/Common.h"

namespace Blue
{
	Transform::Transform()
	{
		// Ʈ������ ��� ���(SRT).
		transformMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);

		// ��ġ ��� ( CPU�� GPU�� ����� �ٷ�� ����� �޶� ).
		// �� ���� ����� �� ���� ��ķ� ��ȯ�ϱ� ���� ��ġ��� ó��.
		transformMatrix = Matrix4::Transpose(transformMatrix);

		// ��� ����.
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = Matrix4::Stride();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;					// GPU �� �а� CPU�� ���� ��Ȳ.
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPU�� ���� ���� ��.

		// ���ۿ� ���� ������ ����.
		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		// ���� ����.
		ID3D11Device& device = Engine::Get().Device();
		ThrowIfFailed(
			device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer),
			TEXT("Failed to create a transform buffer."));

	}

	Transform::~Transform()
	{
		// ���ҽ� ����.
		if (constantBuffer)
		{
			constantBuffer->Release();
			constantBuffer = nullptr;
		}
	}

	void Transform::Bind()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		// Ʈ������ ��� ���(SRT).
		transformMatrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);

		// ��ġ ��� ( CPU�� GPU�� ����� �ٷ�� ����� �޶� ).
		// �� ���� ����� �� ���� ��ķ� ��ȯ�ϱ� ���� ��ġ��� ó��.
		transformMatrix = Matrix4::Transpose(transformMatrix);

		// ���� ������Ʈ https://learn.microsoft.com/ko-kr/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-updatesubresource.
		// context.UpdateSubresource(constantBuffer, 0, nullptr, &transformMatrix, 0, 0);
		D3D11_MAPPED_SUBRESOURCE resource = {};
		context.Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);		// GPU�� ���ǵ帮�� ��.
		//resource.pData = &transformMatrix;
		memcpy(resource.pData, &transformMatrix, sizeof(Matrix4));					// �� ����
		context.Unmap(constantBuffer, 0);											// �� Ǯ��.

		// ���� ���ε�.
		context.VSSetConstantBuffers(0, 1, &constantBuffer);
	}
}