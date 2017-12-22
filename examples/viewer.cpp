#include "viewer.h"
#include <cstdlib>


Viewer::Viewer() : shader_folder("src/shader/"), 
<<<<<<< HEAD
                   win_width(960),
                   win_height(540)
=======
                   win_width(600),
                   win_height(400)
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
{
}

static void glfwErrorCallback(int error, const char* description)
{
  std::cerr << "GLFW error " << error << " " << description << std::endl;
}

<<<<<<< HEAD
void Viewer::key_callbackstatic(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Viewer* viewer = reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->key_callback(window, key, scancode, action, mods);
}


void Viewer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        shouldStop = true;
}


void Viewer::winsize_callbackstatic(GLFWwindow* window, int w, int h)
{
    Viewer* viewer = reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->winsize_callback(window, w, h);
}


void Viewer::winsize_callback(GLFWwindow* window, int w, int h)
{
    win_width = w/2;
    win_height = h/2;
}


void Viewer::initialize()
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
	}

=======
void Viewer::initialize()
{
    // init glfw - if already initialized nothing happens
    glfwInit();
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150

    GLFWerrorfun prev_func = glfwSetErrorCallback(glfwErrorCallback);
    if (prev_func)
      glfwSetErrorCallback(prev_func);

    // setup context
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
<<<<<<< HEAD
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    //glfwWindowHint(GLFW_VISIBLE, debug ? GL_TRUE : GL_FALSE);

    window = glfwCreateWindow(win_width*2, win_height, "Press ESC to exit", 0, NULL);

=======
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#endif
    //glfwWindowHint(GLFW_VISIBLE, debug ? GL_TRUE : GL_FALSE);

    window = glfwCreateWindow(win_width*2, win_height*2, "Viewer (press ESC to exit)", 0, NULL);
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
    if (window == NULL)
    {
        std::cerr << "Failed to create opengl window." << std::endl;
        exit(-1);
    }
<<<<<<< HEAD
/*
	pcwin = glfwCreateWindow(win_width, win_height, "Cloud Viewer", 0, NULL);

	if (pcwin == NULL)
    {
        std::cerr << "Failed to create cloud viewer window." << std::endl;
        exit(-1);
    }
*/
    glfwMakeContextCurrent(window);
	
=======

    glfwMakeContextCurrent(window);
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
    OpenGLBindings *b = new OpenGLBindings();
    flextInit(b);
    gl(b);

    std::string vertexshadersrc = ""
        "#version 330\n"
                                                
<<<<<<< HEAD
        "layout(location=0) in vec2 Position;"
        "layout(location=1) in vec2 TexCoord;"
        "out vec2 UV;"

        "void main(void)"
        "{"
        "    gl_Position = vec4(Position, 0.0, 1.0);"
        "    UV = TexCoord;"
=======
        "in vec2 Position;"
        "in vec2 TexCoord;"
                    
        "out VertexData{"
        "vec2 TexCoord;" 
        "} VertexOut;"  
                    
        "void main(void)"
        "{"
        "    gl_Position = vec4(Position, 0.0, 1.0);"
        "    VertexOut.TexCoord = TexCoord;"
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
        "}";
    std::string grayfragmentshader = ""
        "#version 330\n"
        
<<<<<<< HEAD
        "vec4 tempColor;"
        "in vec2 UV;"

        "layout(location = 0) out vec4 Color;"
        "uniform sampler2DRect Data;"
        
        "void main(void)"
        "{"
            "ivec2 uv = ivec2(UV.x, UV.y);"
=======
        "uniform sampler2DRect Data;"
        
        "vec4 tempColor;"
        "in VertexData{"
        "    vec2 TexCoord;"
        "} FragmentIn;"
        
        "layout(location = 0) out vec4 Color;"
        
        "void main(void)"
        "{"
            "ivec2 uv = ivec2(FragmentIn.TexCoord.x, FragmentIn.TexCoord.y);"
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
            "tempColor = texelFetch(Data, uv);"
            "Color = vec4(tempColor.x/4500, tempColor.x/4500, tempColor.x/4500, 1);"
        "}";
    std::string fragmentshader = ""
        "#version 330\n"
        
<<<<<<< HEAD
        "layout(location = 0) out vec4 Color;"
        "uniform sampler2DRect Data;"
        "in vec2 UV;"
        
        "void main(void)"
        "{"
        "    ivec2 uv = ivec2(UV.x, UV.y);"
=======
        "uniform sampler2DRect Data;"
        
        "in VertexData{"
        "    vec2 TexCoord;"
        "} FragmentIn;"
       
        "layout(location = 0) out vec4 Color;"
        
        "void main(void)"
        "{"
        "    ivec2 uv = ivec2(FragmentIn.TexCoord.x, FragmentIn.TexCoord.y);"

>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
        "    Color = texelFetch(Data, uv);"
        "}";

    renderShader.setVertexShader(vertexshadersrc);
    renderShader.setFragmentShader(fragmentshader);
    renderShader.build();

    renderGrayShader.setVertexShader(vertexshadersrc);
    renderGrayShader.setFragmentShader(grayfragmentshader);
    renderGrayShader.build();


    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Viewer::key_callbackstatic);
    glfwSetWindowSizeCallback(window, Viewer::winsize_callbackstatic);

    shouldStop = false;
}

<<<<<<< HEAD
=======
void Viewer::winsize_callbackstatic(GLFWwindow* window, int w, int h)
{
    Viewer* viewer = reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->winsize_callback(window, w, h);
}

void Viewer::winsize_callback(GLFWwindow* window, int w, int h)
{
    win_width = w/2;
    win_height = h/2;
}

void Viewer::key_callbackstatic(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Viewer* viewer = reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->key_callback(window, key, scancode, action, mods);
}

void Viewer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        shouldStop = true;
}
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150

void Viewer::onOpenGLBindingsChanged(OpenGLBindings *b)
{
    renderShader.gl(b);
    renderGrayShader.gl(b);
    rgb.gl(b);
    ir.gl(b);
}

<<<<<<< HEAD

=======
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
bool Viewer::render()
{
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint x = 0, y = 0;
<<<<<<< HEAD
    int fb_width, fb_width_half, fb_height;
=======
    int fb_width, fb_width_half, fb_height, fb_height_half;
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150

    std::map<std::string, libfreenect2::Frame*>::iterator iter;

    for (iter = frames.begin(); iter != frames.end(); ++iter)
    {
        libfreenect2::Frame* frame = iter->second;

<<<<<<< HEAD
        // Using the frame buffer size to account for screens
		// where window.size != framebuffer.size, e.g. retina displays
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
		// std::cout << "fb_width: " << fb_width <<", "<< "fb_height: " << fb_height << std::endl;
        fb_width_half = (fb_width + 1) / 2;

        glViewport(x, y, fb_width_half, fb_height);

		x += fb_width_half;
/*
=======
        // Using the frame buffer size to account for screens where window.size != framebuffer.size, e.g. retina displays
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
        fb_width_half = (fb_width + 1) / 2;
        fb_height_half = (fb_height + 1) / 2;

        glViewport(x, y, fb_width_half, fb_height_half);
        x += fb_width_half;
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
        if (x >= (fb_width - 1))
        {
            x = 0;
            y += fb_height_half;
        }
<<<<<<< HEAD
*/
        float w = static_cast<float>(frame->width);
        float h = static_cast<float>(frame->height);
		
		//std::cout << "width: " << w <<", "<< "height: " << h << std::endl;
=======

        float w = static_cast<float>(frame->width);
        float h = static_cast<float>(frame->height);

>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
        Vertex bl = { -1.0f, -1.0f, 0.0f, 0.0f };
        Vertex br = { 1.0f, -1.0f, w, 0.0f }; 
        Vertex tl = { -1.0f, 1.0f, 0.0f, h };
        Vertex tr = { 1.0f, 1.0f, w, h };
        Vertex vertices[] = {
            bl, tl, tr, 
            tr, br, bl
        };

        gl()->glGenBuffers(1, &triangle_vbo);
        gl()->glGenVertexArrays(1, &triangle_vao);

        gl()->glBindVertexArray(triangle_vao);
        gl()->glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);
        gl()->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

<<<<<<< HEAD
        // GLint position_attr = renderShader.getAttributeLocation("Position"); // =0
        gl()->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0 );
        gl()->glEnableVertexAttribArray(0);

        // GLint texcoord_attr = renderShader.getAttributeLocation("TexCoord"); // =1
        gl()->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(2 * sizeof(float)) );
        gl()->glEnableVertexAttribArray(1);
=======
        GLint position_attr = renderShader.getAttributeLocation("Position");
        gl()->glVertexAttribPointer(position_attr, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        gl()->glEnableVertexAttribArray(position_attr);

        GLint texcoord_attr = renderShader.getAttributeLocation("TexCoord");
        gl()->glVertexAttribPointer(texcoord_attr, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(2 * sizeof(float)));
        gl()->glEnableVertexAttribArray(texcoord_attr);
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150


        if (iter->first == "RGB" || iter->first == "registered")
        {
            renderShader.use();

            rgb.allocate(frame->width, frame->height);
<<<<<<< HEAD
            std::copy(frame->data, frame->data + 
				 	frame->width * frame->height * frame->bytes_per_pixel, rgb.data);
=======
            std::copy(frame->data, frame->data + frame->width * frame->height * frame->bytes_per_pixel, rgb.data);
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
            rgb.flipY();
            rgb.upload();
            glDrawArrays(GL_TRIANGLES, 0, 6);

            rgb.deallocate();
<<<<<<< HEAD
=======

>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
        }
        else
        {
            renderGrayShader.use();

            ir.allocate(frame->width, frame->height);
            std::copy(frame->data, frame->data + frame->width * frame->height * frame->bytes_per_pixel, ir.data);
            ir.flipY();
            ir.upload();
            glDrawArrays(GL_TRIANGLES, 0, 6);
            ir.deallocate();
        }

        gl()->glDeleteBuffers(1, &triangle_vbo);
        gl()->glDeleteVertexArrays(1, &triangle_vao);
    }

    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
    // update other events like input handling 
    glfwPollEvents();

    return shouldStop || glfwWindowShouldClose(window);
}

<<<<<<< HEAD

=======
>>>>>>> d322e53a4bec867ef7e36b74f85828c8fc38b150
void Viewer::addFrame(std::string id, libfreenect2::Frame* frame)
{
    frames[id] = frame;
}
