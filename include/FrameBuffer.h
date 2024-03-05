#pragma once

#include <cstdint>

#include "Renderer.h"

struct FrameBufferSpecification
{
	uint32_t Width;
	uint32_t Height;
	uint32_t Samples = 1;

	// format / type

	bool SwapChainTarget = false;
};

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(const FrameBufferSpecification& spec);
	~FrameBuffer();

	void Bind();
	void Unbind();

	// void Resize(uint32_t width, uint32_t height);

	void UpdateSpec(const FrameBufferSpecification& spec) { m_Specification = spec; }

	void Create();

	void Invalidate();

	void Resize(uint32_t width, uint32_t height);

	uint32_t GetColorAttachmentRendererID() const { return m_RendererID; }
	const FrameBufferSpecification& GetSpecification() const { return m_Specification; }

	// uint32_t GetDepthAttachmentRendererID() const { return m_DepthAttachment; }

	uint32_t GetWidth() const { return m_Specification.Width; }
	uint32_t GetHeight() const { return m_Specification.Height; }

	// static void UnbindFrameBuffer();

	void Delete();


	void RescaleFrameBuffer(uint32_t width, uint32_t height);
	

private:
	uint32_t m_RendererID = 0;
	uint32_t m_ColorAttachment = 0;
	// uint32_t m_DepthAttachment = 0;
	uint32_t m_RenderBuffer = 0;
	FrameBufferSpecification m_Specification;

};
