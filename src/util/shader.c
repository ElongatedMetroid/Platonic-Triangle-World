#include "../../include/shader.h"

unsigned int ShaderID;

int Shader_ReadAndBuild(const char* vertexPath, const char *fragmentPath){
    char *vertexCode = NULL;
    char *fragmentCode = NULL;

    FILE *vShaderFile = NULL;
    FILE *fShaderFile = NULL;

    long lSize = 0l;

    if(!(vShaderFile = fopen(vertexPath, "r"))){
        printf("Error opening vertex shader file!\n");
        return -1;
    }

    fseek( vShaderFile , 0L , SEEK_END);
    lSize = ftell( vShaderFile );
    rewind( vShaderFile );

    /* allocate memory for entire content */
    vertexCode = xcalloc( 1, lSize+1 );

    /* copy the file into the buffer */
    if(!(fread( vertexCode , lSize, 1 , vShaderFile))){
        fclose(vShaderFile);
        free(vertexCode);
        fputs("entire read fails",stderr);
        return -1;
    }
    fclose(vShaderFile); 

    if(!(fShaderFile = fopen(fragmentPath, "r"))){
        printf("Error opening fragment shader file!\n");
        return -1;
    }

    fseek( fShaderFile , 0L , SEEK_END);
    lSize = ftell( fShaderFile );
    rewind( fShaderFile );

    /* allocate memory for entire content */
    fragmentCode = xcalloc( 1, lSize+1 );

    /* copy the file into the buffer */
    if(!(fread(fragmentCode , lSize, 1 , fShaderFile))){
        fclose(fShaderFile);
        free(fragmentCode);
        fputs("entire read fails",stderr);
        return -1;
    }
    fclose(fShaderFile); 

    const char *vShaderCode = vertexCode;
    const char *fShaderCode = fragmentCode;

    unsigned int vertex, fragment;
    int success; 
    char infoLog[512];

	//all openGL objects are acessed through a reference, here we are getting and setting vertex to a reference value
    vertex = glCreateShader(GL_VERTEX_SHADER);
	//reference value, 1 string for the whole shader, pointer to source code
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	//pass the reference to the vertex shader to glCompileShader so OpenGL can compile the shader to machine code
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        fprintf(stderr, "Shader vertex compilation failed!\n %s\n", infoLog);
        return -1;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        fprintf(stderr, "Shader fragment compilation failed!\n %s\n", infoLog);
        return -1;
    }

	//set the ShaderID reference value
    ShaderID = glCreateProgram();
	//attach both shaders to the shader program
    glAttachShader(ShaderID, vertex);
    glAttachShader(ShaderID, fragment);
	//link all shaders together
    glLinkProgram(ShaderID);

    glGetProgramiv(ShaderID, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        fprintf(stderr, "Shader program linking failed!\n %s\n", infoLog);
        return -1;
    }
	
	//delete the shaders since they are already in the program
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return 0;
}

void Shader_Use(){
    glUseProgram(ShaderID);
}

void Shader_SetBool(const char *name, bool value){
    glUniform1i(glGetUniformLocation(ShaderID, name), (int)value);
}
void Shader_SetInt(const char *name, int value){
    glUniform1i(glGetUniformLocation(ShaderID, name), value);
}
void Shader_SetFloat(const char *name, float value){
    glUniform1f(glGetUniformLocation(ShaderID, name), value);
}
void Shader_SetMat4(const char *name, vec4 value){
    glUniformMatrix4fv(glGetUniformLocation(ShaderID, name), 1, GL_FALSE, value);
}

