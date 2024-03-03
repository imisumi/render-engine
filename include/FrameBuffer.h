#pragma once

#include <cstdint>


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

	void Invalidate();

	void Resize(uint32_t width, uint32_t height);

	uint32_t GetColorAttachmentRendererID() const { return m_RendererID; }
	const FrameBufferSpecification& GetSpecification() const { return m_Specification; }

	uint32_t GetWidth() const { return m_Specification.Width; }
	uint32_t GetHeight() const { return m_Specification.Height; }

	// static void UnbindFrameBuffer();

	void Delete();
	

private:
	uint32_t m_RendererID = 0;
	uint32_t m_ColorAttachment;
	uint32_t m_DepthAttachment;
	FrameBufferSpecification m_Specification;

};
