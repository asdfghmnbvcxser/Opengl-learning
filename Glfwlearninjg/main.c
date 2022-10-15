
#include<glad.h>
#include<GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

//the data of this char is a language called GLSL which writes shaders it is stored in this string for later compiling use
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";



//the code for my fragment shader The fragment shader is all about calculating the color output of your pixels. To keep things simple the fragment shader will always output an orange-ish color.
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
    "FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";
int main()
{
    glfwInit();

    if(!glfwInit()){
        printf("INITIALIZATION FAILED!");
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "HI", NULL,NULL);
    //if window failed to be made terminate the program and tell the user
    if(!window ){
        printf("WINDOW DID NOT GET MADE!\n");
        glfwTerminate();
        return -1;
    }
    //tell GLFW to make the context of our window the main context on the current thread.
    glfwMakeContextCurrent(window);
    //GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function:
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }



    //the moment a user resizes the window the viewport should be adjusted as well. We can register a callback function on the window that gets called each time the window is resized.
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0,0, width, height);
    }

    //tell GLFW we want to call this function on every window resize by registering it:
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //using GLFW's glfwGetKey function that takes the window as input together with a key. The function returns whether this key is currently being pressed. We're creating a processInput function to keep all input code organized
    void processInput(GLFWwindow *window)
    {
        //when escape key is clicked we close the program
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
    }

    //vertices of a triangle
    float vertices[] = {
      -0.9f, -0.5f, 0.0f,  // left
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top
        // second triangle
    };
    float vertices2[] = {//start from 0
          0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };
    ;


    //make a call to the glBufferData function that copies the previously defined vertex data into the buffer's memory:
    //. Its first argument is the type of the buffer we want to copy data into: the vertex buffer object currently bound to the GL_ARRAY_BUFFER target
    //The second argument specifies the size of the data (in bytes) we want to pass to the buffer; a simple sizeof of the vertex data suffices. The third parameter is the actual data we want to send

    //In order for OpenGL to use the shader it has to dynamically compile it at run-time from its source code.
    //The first thing we need to do is create a shader object, again referenced by an ID. So we store the vertex shader as an unsigned int and create the shader with glCreateShader:
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);



    //we attach the shader source code to the shader object and compile the shader:
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    //define int to indicate success and a storage container for the error messages then check if compiling was succesful with glgetshaderiv
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", infoLog);
    }
    //making fragment shaders in a simillar way as vertex shader instead with GL_FRAGMENT_SHADER as the type
    unsigned int fragmentShader, fragmentShader2;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED: %s\n", infoLog);
    }
    //shader program creation: final linked version of multiple shaders combined.
    unsigned int shaderProgram;
    unsigned int shaderProgrambruh;
    shaderProgram = glCreateProgram();
    shaderProgrambruh = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgrambruh, vertexShader);

    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgrambruh, fragmentShader2);
    glLinkProgram(shaderProgram);
    glLinkProgram(shaderProgrambruh);

    //error tests
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", infoLog);
    }
glGetProgramiv(shaderProgrambruh, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderProgrambruh, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", infoLog);
    }


     //initalizing a VAO (VERTEX ARRAY OBJECT) any vertex attribute calls will be stores inside the VAO


unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteShader(fragmentShader2);


    //loops the window until the user closes it
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        //render commands here
        //change color to a dark green blue color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES,0,3);
        glGetError();
        //call the triangle program

        glUseProgram(shaderProgrambruh);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES,0,3);
        glGetError();




        //swap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
        glfwSwapBuffers(window);
        // checks if any events are triggered (like keyboard input or mouse movement events), updates the window state, and calls the corresponding functions (which we can register via callback methods
        glfwPollEvents();
    }

    //terminate the program once the user closes the window.
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgrambruh);
    glfwTerminate();
    return 0;
}
