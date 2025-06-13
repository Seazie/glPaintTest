#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *green = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.5f, 1.0f, 0.5f, 1.0f);\n"
"}\0";
const char *white = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //now we create a window object

    GLFWwindow* window = glfwCreateWindow(2545, 1550, "LearnOpenGL", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //the address of where the "window" is located is sent to the gladGLLoader
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    
    //initialization of Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //attach shader source code to shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //compile shader
    glCompileShader(vertexShader);
    //check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<infoLog << std::endl;
    }
    
    //initialization of green Fragment Shader
    unsigned int greenFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //attach shader source code to shader object
    glShaderSource(greenFragShader, 1, &green, NULL);
    //compile shader
    glCompileShader(greenFragShader);
    //check for shader compile errors
    glGetShaderiv(greenFragShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(greenFragShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //initialization of white Fragment Shader
    unsigned int whiteFragShader = glCreateShader(GL_FRAGMENT_SHADER);
    //attach shader source code to shader object
    glShaderSource(whiteFragShader, 1, &white, NULL);
    //compile shader
    glCompileShader(whiteFragShader);
    //check for shader compile errors
    glGetShaderiv(whiteFragShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(whiteFragShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //link shaders by initializing our Shader Program for green shader
    unsigned int greenShaderProgram = glCreateProgram();
    //attach our shaders to the shader program
    glAttachShader(greenShaderProgram, vertexShader);
    glAttachShader(greenShaderProgram, greenFragShader);
    //link our attached shaders within the shader program
    glLinkProgram(greenShaderProgram);
    //check for linking errors
    glGetProgramiv(greenShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(greenShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

        //link shaders by initializing our Shader Program for green shader
    unsigned int whiteShaderProgram = glCreateProgram();
    //attach our shaders to the shader program
    glAttachShader(whiteShaderProgram, vertexShader);
    glAttachShader(whiteShaderProgram, whiteFragShader);
    //link our attached shaders within the shader program
    glLinkProgram(whiteShaderProgram);
    //check for linking errors
    glGetProgramiv(whiteShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(whiteShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    //remember to delete shader objects after linking them
    //According to learnOpenGL example, we don't need to delete our shaders
    glDeleteShader(vertexShader);
    glDeleteShader(greenFragShader);
    glDeleteShader(whiteFragShader);
    

    /*float twoTriangles[] = {
        0.75f, 0.75f, 0.0f,
        0.75f, -0.75f, 0.0f,
        0.0f, -0.75f, 0.0f,
        0.0f, -0.75f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        -0.75f, 0.75f, 0.0f
    };*/

    float triangle1[] = {
        0.75f, 0.75f, 0.0f,
        0.75f, -0.75f, 0.0f,
        0.0f, -0.75f, 0.0f
    };
    float triangle2[] = {
        0.0f, -0.75f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        -0.75f, 0.75f, 0.0f
    };

    //initialization of Vertex Buffer Object and Vertex Array Object
    unsigned int VBOs[2], VAOs[2];
    //generate our VAO
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    //bind first VAO and VBO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //bind second VAO and VBO
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //we can unbind the VBOs buffer because it is now registered with glVertexAttribPointer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //This section not necessary but displays the width and height of the window in the output
    /*
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    std::cout << "Framebuffer size: " << width << "x" << height << std::endl;
    */

    

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        //rendering here
        glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
        //glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw triangle
        glUseProgram(greenShaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //here we add our white Shader to use that color for our new triangle
        glUseProgram(whiteShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //OPTIONAL: De-allocate all resources
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(greenShaderProgram);
    glDeleteProgram(whiteShaderProgram);

    glfwTerminate();
    return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,  GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


