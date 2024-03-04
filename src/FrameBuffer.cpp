#include "FrameBuffer.h"

#include "Renderer.h"

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec)
	: m_Specification(spec)
{
	// Resize(spec.Width, spec.Height);

	// glCreateFramebuffers(1, &m_RendererID);
	// glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);


	Invalidate();
}

FrameBuffer::~FrameBuffer()
{
	if (m_RendererID)
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}
}

void FrameBuffer::Invalidate()
{
	if (m_RendererID)
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	GLCall(glCreateFramebuffers(1, &m_RendererID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0));

	// depth buffer
	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
	//? texstorage???
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0));

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer is incomplete!" << std::endl;


	GLCall(glViewport(0, 0, m_Specification.Width, m_Specification.Height));
	

	

	// unbind
	// GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	Unbind();
}

// rename 
void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glViewport(0, 0, m_Specification.Width, m_Specification.Height);
}

void FrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::Resize(uint32_t width, uint32_t height)
{
	if (m_Specification.Width == width && m_Specification.Height == height)
		return;
	m_Specification.Width = width;
	m_Specification.Height = height;
	Invalidate();
}

void FrameBuffer::Delete()
{
	glDeleteFramebuffers(1, &m_RendererID);
	glDeleteTextures(1, &m_ColorAttachment);
	glDeleteTextures(1, &m_DepthAttachment);
}