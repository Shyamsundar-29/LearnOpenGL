//#include <array>
//#include <cmath>
//#include <iostream>
//#include <string>
//
//#include <GLFW/glfw3.h>
//
//// This project uses GLFW directly, so we load modern OpenGL functions ourselves.
//// Think of these "using" lines like C# delegate type declarations.
//using GLsizeiptr = ptrdiff_t;
//using GLchar = char;
//
//#ifndef GL_ARRAY_BUFFER
//#define GL_ARRAY_BUFFER 0x8892
//#endif
//#ifndef GL_ELEMENT_ARRAY_BUFFER
//#define GL_ELEMENT_ARRAY_BUFFER 0x8893
//#endif
//#ifndef GL_STATIC_DRAW
//#define GL_STATIC_DRAW 0x88E4
//#endif
//#ifndef GL_VERTEX_SHADER
//#define GL_VERTEX_SHADER 0x8B31
//#endif
//#ifndef GL_FRAGMENT_SHADER
//#define GL_FRAGMENT_SHADER 0x8B30
//#endif
//#ifndef GL_COMPILE_STATUS
//#define GL_COMPILE_STATUS 0x8B81
//#endif
//#ifndef GL_LINK_STATUS
//#define GL_LINK_STATUS 0x8B82
//#endif
//#ifndef GL_INFO_LOG_LENGTH
//#define GL_INFO_LOG_LENGTH 0x8B84
//#endif
//#ifndef GL_DEPTH_TEST
//#define GL_DEPTH_TEST 0x0B71
//#endif
//#ifndef GL_DEPTH_BUFFER_BIT
//#define GL_DEPTH_BUFFER_BIT 0x00000100
//#endif
//#ifndef GL_FALSE
//#define GL_FALSE 0
//#endif
//
//constexpr int WindowWidth = 1920;
//constexpr int WindowHeight = 1080;
//constexpr float Pi = 3.1415926535f;
//
//using GlCreateShader = GLuint(APIENTRY*)(GLenum);
//using GlShaderSource = void(APIENTRY*)(GLuint, GLsizei, const GLchar* const*, const GLint*);
//using GlCompileShader = void(APIENTRY*)(GLuint);
//using GlGetShaderiv = void(APIENTRY*)(GLuint, GLenum, GLint*);
//using GlGetShaderInfoLog = void(APIENTRY*)(GLuint, GLsizei, GLsizei*, GLchar*);
//using GlDeleteShader = void(APIENTRY*)(GLuint);
//using GlCreateProgram = GLuint(APIENTRY*)();
//using GlAttachShader = void(APIENTRY*)(GLuint, GLuint);
//using GlLinkProgram = void(APIENTRY*)(GLuint);
//using GlGetProgramiv = void(APIENTRY*)(GLuint, GLenum, GLint*);
//using GlGetProgramInfoLog = void(APIENTRY*)(GLuint, GLsizei, GLsizei*, GLchar*);
//using GlDeleteProgram = void(APIENTRY*)(GLuint);
//using GlUseProgram = void(APIENTRY*)(GLuint);
//using GlGenVertexArrays = void(APIENTRY*)(GLsizei, GLuint*);
//using GlBindVertexArray = void(APIENTRY*)(GLuint);
//using GlDeleteVertexArrays = void(APIENTRY*)(GLsizei, const GLuint*);
//using GlGenBuffers = void(APIENTRY*)(GLsizei, GLuint*);
//using GlBindBuffer = void(APIENTRY*)(GLenum, GLuint);
//using GlBufferData = void(APIENTRY*)(GLenum, GLsizeiptr, const void*, GLenum);
//using GlDeleteBuffers = void(APIENTRY*)(GLsizei, const GLuint*);
//using GlVertexAttribPointer = void(APIENTRY*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
//using GlEnableVertexAttribArray = void(APIENTRY*)(GLuint);
//using GlGetUniformLocation = GLint(APIENTRY*)(GLuint, const GLchar*);
//using GlUniformMatrix4fv = void(APIENTRY*)(GLint, GLsizei, GLboolean, const GLfloat*);
//
//GlCreateShader glCreateShader = nullptr;
//GlShaderSource glShaderSource = nullptr;
//GlCompileShader glCompileShader = nullptr;
//GlGetShaderiv glGetShaderiv = nullptr;
//GlGetShaderInfoLog glGetShaderInfoLog = nullptr;
//GlDeleteShader glDeleteShader = nullptr;
//GlCreateProgram glCreateProgram = nullptr;
//GlAttachShader glAttachShader = nullptr;
//GlLinkProgram glLinkProgram = nullptr;
//GlGetProgramiv glGetProgramiv = nullptr;
//GlGetProgramInfoLog glGetProgramInfoLog = nullptr;
//GlDeleteProgram glDeleteProgram = nullptr;
//GlUseProgram glUseProgram = nullptr;
//GlGenVertexArrays glGenVertexArrays = nullptr;
//GlBindVertexArray glBindVertexArray = nullptr;
//GlDeleteVertexArrays glDeleteVertexArrays = nullptr;
//GlGenBuffers glGenBuffers = nullptr;
//GlBindBuffer glBindBuffer = nullptr;
//GlBufferData glBufferData = nullptr;
//GlDeleteBuffers glDeleteBuffers = nullptr;
//GlVertexAttribPointer glVertexAttribPointer = nullptr;
//GlEnableVertexAttribArray glEnableVertexAttribArray = nullptr;
//GlGetUniformLocation glGetUniformLocation = nullptr;
//GlUniformMatrix4fv glUniformMatrix4fv = nullptr;
//
//struct Matrix4
//{
//    std::array<float, 16> values{};
//};
//
//struct CubeGeometry
//{
//    GLuint vertexArray = 0;
//    GLuint vertexBuffer = 0;
//    GLuint indexBuffer = 0;
//    GLsizei indexCount = 0;
//};
//
//struct ShaderUniforms
//{
//    GLint model = -1;
//    GLint view = -1;
//    GLint projection = -1;
//};
//
//template <typename OpenGLFunction>
//bool loadOpenGLFunction(OpenGLFunction& destination, const char* functionName)
//{
//    destination = reinterpret_cast<OpenGLFunction>(glfwGetProcAddress(functionName));
//
//    if (destination == nullptr)
//    {
//        std::cerr << "Failed to load OpenGL function: " << functionName << '\n';
//        return false;
//    }
//
//    return true;
//}
//
//bool loadOpenGLFunctions()
//{
//    return loadOpenGLFunction(glCreateShader, "glCreateShader")
//        && loadOpenGLFunction(glShaderSource, "glShaderSource")
//        && loadOpenGLFunction(glCompileShader, "glCompileShader")
//        && loadOpenGLFunction(glGetShaderiv, "glGetShaderiv")
//        && loadOpenGLFunction(glGetShaderInfoLog, "glGetShaderInfoLog")
//        && loadOpenGLFunction(glDeleteShader, "glDeleteShader")
//        && loadOpenGLFunction(glCreateProgram, "glCreateProgram")
//        && loadOpenGLFunction(glAttachShader, "glAttachShader")
//        && loadOpenGLFunction(glLinkProgram, "glLinkProgram")
//        && loadOpenGLFunction(glGetProgramiv, "glGetProgramiv")
//        && loadOpenGLFunction(glGetProgramInfoLog, "glGetProgramInfoLog")
//        && loadOpenGLFunction(glDeleteProgram, "glDeleteProgram")
//        && loadOpenGLFunction(glUseProgram, "glUseProgram")
//        && loadOpenGLFunction(glGenVertexArrays, "glGenVertexArrays")
//        && loadOpenGLFunction(glBindVertexArray, "glBindVertexArray")
//        && loadOpenGLFunction(glDeleteVertexArrays, "glDeleteVertexArrays")
//        && loadOpenGLFunction(glGenBuffers, "glGenBuffers")
//        && loadOpenGLFunction(glBindBuffer, "glBindBuffer")
//        && loadOpenGLFunction(glBufferData, "glBufferData")
//        && loadOpenGLFunction(glDeleteBuffers, "glDeleteBuffers")
//        && loadOpenGLFunction(glVertexAttribPointer, "glVertexAttribPointer")
//        && loadOpenGLFunction(glEnableVertexAttribArray, "glEnableVertexAttribArray")
//        && loadOpenGLFunction(glGetUniformLocation, "glGetUniformLocation")
//        && loadOpenGLFunction(glUniformMatrix4fv, "glUniformMatrix4fv");
//}
//
//Matrix4 createIdentityMatrix()
//{
//    return Matrix4{
//        1.0f, 0.0f, 0.0f, 0.0f,
//        0.0f, 1.0f, 0.0f, 0.0f,
//        0.0f, 0.0f, 1.0f, 0.0f,
//        0.0f, 0.0f, 0.0f, 1.0f
//    };
//}
//
//Matrix4 createYRotationMatrix(float angleInRadians)
//{
//    const float cosine = std::cos(angleInRadians);
//    const float sine = std::sin(angleInRadians);
//
//    return Matrix4{
//         cosine, 0.0f, -sine,   0.0f,
//         0.0f,   1.0f,  0.0f,   0.0f,
//         sine,   0.0f,  cosine, 0.0f,
//         0.0f,   0.0f,  0.0f,   1.0f
//    };
//}
//
//Matrix4 createTranslationMatrix(float x, float y, float z)
//{
//    Matrix4 matrix = createIdentityMatrix();
//
//    matrix.values[12] = x;
//    matrix.values[13] = y;
//    matrix.values[14] = z;
//
//    return matrix;
//}
//
//Matrix4 createPerspectiveMatrix(float fieldOfViewDegrees, float aspectRatio, float nearPlane, float farPlane)
//{
//    const float fieldOfViewRadians = fieldOfViewDegrees * Pi / 180.0f;
//    const float scale = 1.0f / std::tan(fieldOfViewRadians / 2.0f);
//
//    return Matrix4{
//        scale / aspectRatio, 0.0f,  0.0f,                                             0.0f,
//        0.0f,                scale, 0.0f,                                             0.0f,
//        0.0f,                0.0f,  -(farPlane + nearPlane) / (farPlane - nearPlane), -1.0f,
//        0.0f,                0.0f,  -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane), 0.0f
//    };
//}
//
//GLuint compileShader(GLenum shaderType, const char* shaderSource)
//{
//    const GLuint shader = glCreateShader(shaderType);
//
//    glShaderSource(shader, 1, &shaderSource, nullptr);
//    glCompileShader(shader);
//
//    GLint didCompile = 0;
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &didCompile);
//
//    if (didCompile)
//    {
//        return shader;
//    }
//
//    GLint logLength = 0;
//    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
//
//    std::string errorLog(logLength, '\0');
//    glGetShaderInfoLog(shader, logLength, nullptr, errorLog.data());
//
//    std::cerr << "Shader compilation failed:\n" << errorLog << '\n';
//    glDeleteShader(shader);
//
//    return 0;
//}
//
//GLuint createShaderProgram()
//{
//    const char* vertexShaderSource = R"(
//        #version 330 core
//
//        layout (location = 0) in vec3 position;
//
//        uniform mat4 model;
//        uniform mat4 view;
//        uniform mat4 projection;
//
//        void main()
//        {
//            gl_Position = projection * view * model * vec4(position, 1.0);
//        }
//    )";
//
//    const char* fragmentShaderSource = R"(
//        #version 330 core
//
//        out vec4 fragmentColor;
//
//        void main()
//        {
//            fragmentColor = vec4(0.15, 0.65, 1.0, 1.0);
//        }
//    )";
//
//    const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
//    const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
//
//    if (vertexShader == 0 || fragmentShader == 0)
//    {
//        glDeleteShader(vertexShader);
//        glDeleteShader(fragmentShader);
//        return 0;
//    }
//
//    const GLuint shaderProgram = glCreateProgram();
//
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    GLint didLink = 0;
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &didLink);
//
//    if (didLink)
//    {
//        return shaderProgram;
//    }
//
//    GLint logLength = 0;
//    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
//
//    std::string errorLog(logLength, '\0');
//    glGetProgramInfoLog(shaderProgram, logLength, nullptr, errorLog.data());
//
//    std::cerr << "Shader program link failed:\n" << errorLog << '\n';
//    glDeleteProgram(shaderProgram);
//
//    return 0;
//}
//
//ShaderUniforms getShaderUniforms(GLuint shaderProgram)
//{
//    return ShaderUniforms{
//        glGetUniformLocation(shaderProgram, "model"),
//        glGetUniformLocation(shaderProgram, "view"),
//        glGetUniformLocation(shaderProgram, "projection")
//    };
//}
//
//GLFWwindow* createWindow()
//{
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "LearnOpenGL", nullptr, nullptr);
//
//    if (window == nullptr)
//    {
//        std::cerr << "Failed to create GLFW window\n";
//    }
//
//    return window;
//}
//
//void framebufferSizeCallback(GLFWwindow*, int width, int height)
//{
//    glViewport(0, 0, width / 2, height / 2);
//}
//
//CubeGeometry createCubeGeometry()
//{
//    const std::array<float, 24> vertices = {
//        -0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//        -0.5f,  0.5f, -0.5f,
//
//        -0.5f, -0.5f,  0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f
//    };
//
//    const std::array<unsigned int, 36> indices = {
//        0, 1, 2, 2, 3, 0, // back face
//        4, 5, 6, 6, 7, 4, // front face
//        0, 4, 7, 7, 3, 0, // left face
//        1, 5, 6, 6, 2, 1, // right face
//        3, 2, 6, 6, 7, 3, // top face
//        0, 1, 5, 5, 4, 0  // bottom face
//    };
//
//    CubeGeometry cube{};
//    cube.indexCount = static_cast<GLsizei>(indices.size());
//
//    glGenVertexArrays(1, &cube.vertexArray);
//    glGenBuffers(1, &cube.vertexBuffer);
//    glGenBuffers(1, &cube.indexBuffer);
//
//    glBindVertexArray(cube.vertexArray);
//
//    glBindBuffer(GL_ARRAY_BUFFER, cube.vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
//
//    // Attribute 0 is the "position" value used in the vertex shader.
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(0);
//
//    return cube;
//}
//
//void deleteCubeGeometry(const CubeGeometry& cube)
//{
//    glDeleteBuffers(1, &cube.indexBuffer);
//    glDeleteBuffers(1, &cube.vertexBuffer);
//    glDeleteVertexArrays(1, &cube.vertexArray);
//}
//
//void drawCube(GLuint shaderProgram, const ShaderUniforms& uniforms, const CubeGeometry& cube)
//{
//    const Matrix4 model = createYRotationMatrix(static_cast<float>(glfwGetTime()));
//    const Matrix4 view = createTranslationMatrix(0.0f, 0.0f, -10.0f);
//    const Matrix4 projection = createPerspectiveMatrix(45.0f, static_cast<float>(WindowWidth) / WindowHeight, 0.1f, 100.0f);
//
//    glUseProgram(shaderProgram);
//    glUniformMatrix4fv(uniforms.model, 1, GL_FALSE, model.values.data());
//    glUniformMatrix4fv(uniforms.view, 1, GL_FALSE, view.values.data());
//    glUniformMatrix4fv(uniforms.projection, 1, GL_FALSE, projection.values.data());
//
//    glBindVertexArray(cube.vertexArray);
//    glDrawElements(GL_TRIANGLES, cube.indexCount, GL_UNSIGNED_INT, nullptr);
//}
//
//void renderFrame(GLuint shaderProgram, const ShaderUniforms& uniforms, const CubeGeometry& cube)
//{
//    glClearColor(0.08f, 0.10f, 0.12f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    drawCube(shaderProgram, uniforms, cube);
//}
//
//int Runmain()
//{
//    if (!glfwInit())
//    {
//        std::cerr << "Failed to initialize GLFW\n";
//        return -1;
//    }
//
//    GLFWwindow* window = createWindow();
//    if (window == nullptr)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
//
//    if (!loadOpenGLFunctions())
//    {
//        glfwDestroyWindow(window);
//        glfwTerminate();
//        return -1;
//    }
//
//    const GLuint shaderProgram = createShaderProgram();
//    if (shaderProgram == 0)
//    {
//        glfwDestroyWindow(window);
//        glfwTerminate();
//        return -1;
//    }
//
//    const ShaderUniforms uniforms = getShaderUniforms(shaderProgram);
//    const CubeGeometry cube = createCubeGeometry();
//
//    glEnable(GL_DEPTH_TEST);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        renderFrame(shaderProgram, uniforms, cube);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // deleteCubeGeometry(cube);
//    glDeleteProgram(shaderProgram);
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}
