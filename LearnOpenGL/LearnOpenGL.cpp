#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include "../GameMath/Vector3.h"
#include <GLFW/glfw3.h>

// This project uses GLFW directly, so we load modern OpenGL functions ourselves.
// Think of these "using" lines like C# delegate type declarations.
using GLsizeiptr = ptrdiff_t;
using GLchar = char;

#ifndef GL_ARRAY_BUFFER
#define GL_ARRAY_BUFFER 0x8892
#endif
#ifndef GL_ELEMENT_ARRAY_BUFFER
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#endif
#ifndef GL_STATIC_DRAW
#define GL_STATIC_DRAW 0x88E4
#endif
#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif
#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif
#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif
#ifndef GL_INFO_LOG_LENGTH
#define GL_INFO_LOG_LENGTH 0x8B84
#endif
#ifndef GL_DEPTH_TEST
#define GL_DEPTH_TEST 0x0B71
#endif
#ifndef GL_DEPTH_BUFFER_BIT
#define GL_DEPTH_BUFFER_BIT 0x00000100
#endif
#ifndef GL_FALSE
#define GL_FALSE 0
#endif

constexpr int WindowWidth = 1920;
constexpr int WindowHeight = 1080;
constexpr float Pi = 3.1415926535f;

using GlCreateShader = GLuint(APIENTRY*)(GLenum);
using GlShaderSource = void(APIENTRY*)(GLuint, GLsizei, const GLchar* const*, const GLint*);
using GlCompileShader = void(APIENTRY*)(GLuint);
using GlGetShaderiv = void(APIENTRY*)(GLuint, GLenum, GLint*);
using GlGetShaderInfoLog = void(APIENTRY*)(GLuint, GLsizei, GLsizei*, GLchar*);
using GlDeleteShader = void(APIENTRY*)(GLuint);
using GlCreateProgram = GLuint(APIENTRY*)();
using GlAttachShader = void(APIENTRY*)(GLuint, GLuint);
using GlLinkProgram = void(APIENTRY*)(GLuint);
using GlGetProgramiv = void(APIENTRY*)(GLuint, GLenum, GLint*);
using GlGetProgramInfoLog = void(APIENTRY*)(GLuint, GLsizei, GLsizei*, GLchar*);
using GlDeleteProgram = void(APIENTRY*)(GLuint);
using GlUseProgram = void(APIENTRY*)(GLuint);
using GlGenVertexArrays = void(APIENTRY*)(GLsizei, GLuint*);
using GlBindVertexArray = void(APIENTRY*)(GLuint);
using GlDeleteVertexArrays = void(APIENTRY*)(GLsizei, const GLuint*);
using GlGenBuffers = void(APIENTRY*)(GLsizei, GLuint*);
using GlBindBuffer = void(APIENTRY*)(GLenum, GLuint);
using GlBufferData = void(APIENTRY*)(GLenum, GLsizeiptr, const void*, GLenum);
using GlDeleteBuffers = void(APIENTRY*)(GLsizei, const GLuint*);
using GlVertexAttribPointer = void(APIENTRY*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
using GlEnableVertexAttribArray = void(APIENTRY*)(GLuint);
using GlGetUniformLocation = GLint(APIENTRY*)(GLuint, const GLchar*);
using GlUniformMatrix4fv = void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat*);

GlCreateShader glCreateShader = nullptr;
GlShaderSource glShaderSource = nullptr;
GlCompileShader glCompileShader = nullptr;
GlGetShaderiv glGetShaderiv = nullptr;
GlGetShaderInfoLog glGetShaderInfoLog = nullptr;
GlDeleteShader glDeleteShader = nullptr;
GlCreateProgram glCreateProgram = nullptr;
GlAttachShader glAttachShader = nullptr;
GlLinkProgram glLinkProgram = nullptr;
GlGetProgramiv glGetProgramiv = nullptr;
GlGetProgramInfoLog glGetProgramInfoLog = nullptr;
GlDeleteProgram glDeleteProgram = nullptr;
GlUseProgram glUseProgram = nullptr;
GlGenVertexArrays glGenVertexArrays = nullptr;
GlBindVertexArray glBindVertexArray = nullptr;
GlDeleteVertexArrays glDeleteVertexArrays = nullptr;
GlGenBuffers glGenBuffers = nullptr;
GlBindBuffer glBindBuffer = nullptr;
GlBufferData glBufferData = nullptr;
GlDeleteBuffers glDeleteBuffers = nullptr;
GlVertexAttribPointer glVertexAttribPointer = nullptr;
GlEnableVertexAttribArray glEnableVertexAttribArray = nullptr;
GlGetUniformLocation glGetUniformLocation = nullptr;
GlUniformMatrix4fv glUniformMatrix4fv = nullptr;


struct CubeGeometry
{
    GLuint vertexArray = 0;
    GLuint vertexBuffer = 0;
    GLuint indexBuffer = 0;
    GLsizei indexCount = 0;
};

struct Line 
{
    GLuint vertexArray = 0;
    GLuint vertexBuffer = 0;
};

struct ShaderUniforms
{
    GLint model = -1;
    GLint view = -1;
    GLint projection = -1;
};

template <typename OpenGLFunction>
bool loadOpenGLFunction(OpenGLFunction& destination, const char* functionName)
{
    destination = reinterpret_cast<OpenGLFunction>(glfwGetProcAddress(functionName));

    if (destination == nullptr)
    {
        std::cerr << "Failed to load OpenGL function: " << functionName << '\n';
        return false;
    }

    return true;
}

bool loadOpenGLFunctions()
{
    return loadOpenGLFunction(glCreateShader, "glCreateShader")
        && loadOpenGLFunction(glShaderSource, "glShaderSource")
        && loadOpenGLFunction(glCompileShader, "glCompileShader")
        && loadOpenGLFunction(glGetShaderiv, "glGetShaderiv")
        && loadOpenGLFunction(glGetShaderInfoLog, "glGetShaderInfoLog")
        && loadOpenGLFunction(glDeleteShader, "glDeleteShader")
        && loadOpenGLFunction(glCreateProgram, "glCreateProgram")
        && loadOpenGLFunction(glAttachShader, "glAttachShader")
        && loadOpenGLFunction(glLinkProgram, "glLinkProgram")
        && loadOpenGLFunction(glGetProgramiv, "glGetProgramiv")
        && loadOpenGLFunction(glGetProgramInfoLog, "glGetProgramInfoLog")
        && loadOpenGLFunction(glDeleteProgram, "glDeleteProgram")
        && loadOpenGLFunction(glUseProgram, "glUseProgram")
        && loadOpenGLFunction(glGenVertexArrays, "glGenVertexArrays")
        && loadOpenGLFunction(glBindVertexArray, "glBindVertexArray")
        && loadOpenGLFunction(glDeleteVertexArrays, "glDeleteVertexArrays")
        && loadOpenGLFunction(glGenBuffers, "glGenBuffers")
        && loadOpenGLFunction(glBindBuffer, "glBindBuffer")
        && loadOpenGLFunction(glBufferData, "glBufferData")
        && loadOpenGLFunction(glDeleteBuffers, "glDeleteBuffers")
        && loadOpenGLFunction(glVertexAttribPointer, "glVertexAttribPointer")
        && loadOpenGLFunction(glEnableVertexAttribArray, "glEnableVertexAttribArray")
        && loadOpenGLFunction(glGetUniformLocation, "glGetUniformLocation")
        && loadOpenGLFunction(glUniformMatrix4fv, "glUniformMatrix4fv");
}


GLuint compileShader(GLenum shaderType, const char* shaderSource)
{
    const GLuint shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint didCompile = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &didCompile);

    if (didCompile)
    {
        return shader;
    }

    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    std::string errorLog(logLength, '\0');
    glGetShaderInfoLog(shader, logLength, nullptr, errorLog.data());

    std::cerr << "Shader compilation failed:\n" << errorLog << '\n';
    glDeleteShader(shader);

    return 0;
}

GLuint createShaderProgram()
{
    const char* vertexShaderSource = R"(
        #version 330 core

        layout (location = 0) in vec3 position;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(position, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core

        out vec4 fragmentColor;

        void main()
        {
            fragmentColor = vec4(0.15, 0.65, 1.0, 1.0);
        }
    )";

    const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (vertexShader == 0 || fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    const GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint didLink = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &didLink);

    if (didLink)
    {
        return shaderProgram;
    }

    GLint logLength = 0;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);

    std::string errorLog(logLength, '\0');
    glGetProgramInfoLog(shaderProgram, logLength, nullptr, errorLog.data());

    std::cerr << "Shader program link failed:\n" << errorLog << '\n';
    glDeleteProgram(shaderProgram);

    return 0;
}

ShaderUniforms getShaderUniforms(GLuint shaderProgram)
{
    return ShaderUniforms{
        glGetUniformLocation(shaderProgram, "model"),
        glGetUniformLocation(shaderProgram, "view"),
        glGetUniformLocation(shaderProgram, "projection")
    };
}

GLFWwindow* createWindow()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
    }

    return window;
}

void framebufferSizeCallback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}



void renderFrame(GLuint shaderProgram, const ShaderUniforms& uniforms)
{
    glClearColor(0.08f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = createWindow();
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!loadOpenGLFunctions())
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    const GLuint shaderProgram = createShaderProgram();
    if (shaderProgram == 0)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    const ShaderUniforms uniforms = getShaderUniforms(shaderProgram);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        renderFrame(shaderProgram, uniforms);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
