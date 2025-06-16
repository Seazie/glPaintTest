#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class Shader
{
    public:
    //this is the program ID
        unsigned int ID;
    
    // this constructor will read and build the shader
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // retrieve vertex/fragment source code from filePath
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions
        vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
         fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
         try
         {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            stringstream vShaderStream, fShaderStream;
            // readn file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

         }
         catch (ifstream::failure& e)
         {
            cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << endl;
         }
         const char* vShaderCode = vertexCode.c_str();
         const char* fShaderCode = fragmentCode.c_str();
         // 2. compile shaders
         unsigned int vertex, fragment;
          
         vertex = glCreateShader(GL_VERTEX_SHADER);
         glShaderSource(vertex, 1, &vShaderCode, NULL);
         glCompileShader(vertex);
         checkCompileErrors(vertex, "VERTEX");
    }
    // use/activate the shader
    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform function
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    
    private:
        void checkCompileErrors(unsigned int shader, string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS,  &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << endl;
            }
        }
        else{
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                cout << "error::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << endl;
            }
        }
    }
};
    

#endif