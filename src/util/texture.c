#include "../../include/texture.h"

void Texture_Load(GLuint *ID, const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType){
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0);
	if(!data)
		ERROR("Could not load texture!\n");
	
	//number of textures we want, 1, and a pointer to the reference variable
	glGenTextures(1, ID);
	glActiveTexture(slot);
	//Bind our texture onto the texType buffer
	glBindTexture(texType, *ID);
	//now that we have binded we will do the following
	
	//type of our texture, setting we want to modify, how we want to modify the setting
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//type of texture, 0, tye type of color texture, the width, the height, 0, type of color channels our image has, data type of our pixels, the image data
	glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, data);

	//mipmaps are just smaller resoulutions of the texture witch are used when the texture is for example far away
	glGenerateMipmap(GL_TEXTURE_2D);

	//free memory
	stbi_image_free(data);

	//unbind texture
	glBindTexture(texType, 0);
}

void Texture_TexUnit(const char *uniform, GLuint unit){
	GLuint texUni = glGetUniformLocation(ShaderID, uniform);
	Shader_Use();
	glUniform1i(texUni, unit);
}

void Texture_Bind(GLenum type, GLuint *ID){
	glBindTexture(type, *ID);
}

void Texture_Unbind(GLenum type, GLuint *ID){
	glBindTexture(type, 0);
}

void Texture_Delete(GLenum type, GLuint *ID){
	glDeleteTextures(1, ID);
}
