#include "Material.h"
#include "stb_image.h"

Material::Material(const std::string& file)
{

	int width, height, channels;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	if (!data)
	{
		std::cerr << "Failed to load texture: " << file << std::endl;
		exit(EXIT_FAILURE);
	}
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// uv = st
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

Material::~Material()
{
	glDeleteTextures(1, &m_Texture);

}

void Material::use(int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}