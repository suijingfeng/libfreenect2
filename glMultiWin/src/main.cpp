// Note the the following Includes do not need to be defined in order:
#include <cstdio>
#include <cstdlib>
#include <map>
#include <list>
#include <unistd.h>
#include <signal.h>

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>


// Note that the following includes must be defined in order:
#define GLEW_STATIC
#define GLEW_MX
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// loading image
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
 

/// freenect2 /////////////////////
  libfreenect2::Freenect2 freenect2;
  libfreenect2::Freenect2Device *dev = 0;
  libfreenect2::PacketPipeline *pipeline = 0;
/// [context]

  std::string serial = "";
  bool enable_rgb = true;
  bool enable_depth = true;

  //int deviceId = -1;
  //size_t framemax = -1;

libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color | libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);


enum ExitCodes
{
	EC_NO_ERROR = 0,
	EC_GLFW_INIT_FAIL = 1,
	EC_GLFW_FIRST_WINDOW_CREATION_FAIL = 2,
};


const char *c_szVertexShader =""
    "#version 410\n"

	"layout(location=0) in vec4 Position;"
	"layout(location=1) in vec2 UV;"
	"out vec2 vUV;"
    "/*;"
	"uniform mat4 Projection;"
	"uniform mat4 View;"
	"uniform mat4 Model;"
    "*/;"
	"void main()"
	"{" 
		"vUV = UV;"
		"gl_Position = Position;"
	"}";

const char *c_szRgbPixelShader =""
    "#version 410\n"

	"in vec2 vUV;"
	"layout(location = 0) out vec4 outColour;"
	"uniform sampler2D diffuseTexture;"
	
    "void main()"
	"{"
		"outColour = texture(diffuseTexture, vUV) ;"
	"}";

const char *c_szDepthPixelShader = ""
    "#version 410\n"
        
    "in vec2 vUV;"
    "layout(location = 0) out vec4 outColour;"

    "uniform sampler2D Data;"
    "vec4 tempColor;"

    "void main()"
    "{"
        "tempColor = texture(Data, vUV);"
        "outColour = vec4(tempColor.x/4500, tempColor.x/4500, tempColor.x/4500, 1);"
    "}";

struct Window
{
	GLFWwindow*		m_pWindow;
	GLEWContext*	m_pGLEWContext;
	unsigned int	m_uiWidth;
	unsigned int	m_uiHeight;
	glm::mat4		m_m4Projection;
	glm::mat4		m_m4ViewMatrix;

	unsigned int	m_uiID;
};

struct ShaderProgram
{
    GLuint program, vertex_shader, fragment_shader;
    GLuint texture;
    unsigned char texture_buffer[1920*1080*4];
    char error_buffer[256];
    
    ShaderProgram() :
        program(0),
        vertex_shader(0),
        fragment_shader(0)
    {
        glGenTextures(1, &texture);
    }

    ~ShaderProgram() 
    {
       glDeleteTextures(1, &texture); 
    }
    void setShader(const char* vertexSrc, const char* fragmentSrc)
    {
        int vslen = strlen(vertexSrc);
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertexSrc, &vslen);

        int fslen = strlen(fragmentSrc);
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragmentSrc, &fslen);
    }

    void build()
    {
        GLint status;

        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);

        if (status != GL_TRUE)
        {
            glGetShaderInfoLog(vertex_shader, sizeof(error_buffer),	NULL, error_buffer);
            printf("failed to compile vertex shader!\n%s\n", error_buffer);
        }

        glCompileShader(fragment_shader);
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE)
        {
            glGetShaderInfoLog(fragment_shader, sizeof(error_buffer), NULL, error_buffer);
            printf("failed to compile fragment shader!\n%s\n", error_buffer);
        }

        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status != GL_TRUE)
        {
            glGetProgramInfoLog(program, sizeof(error_buffer), NULL, error_buffer);
			printf("failed to link shader program!\n%s\n", error_buffer);
        }
    }

    void use()
    {
        glUseProgram(program);
    }

    // load a texture:
    //printf("GL_RGBA: %d, GL_BGRA: %d, GL_UNSIGNED_BYTE: %d\n", GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE);

    void setTexture(int width, int height, GLenum internalFormat, GLenum format, GLenum type)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // specify default filtering and wrapping
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
                
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, texture_buffer);
    }

 
    void loadTexture(size_t new_width, size_t new_height)
    {
        /*
        width = new_width;
        height = new_height;
        size = height * width * bytes_per_pixel;
        data = new unsigned char[size];
         */
    }

    GLint getAttributeLocation(const char* name)
    {
        return glGetAttribLocation(program, name);
    }

    void setUniform(const char* name, GLint value)
    {
        GLint idx = glGetUniformLocation(program, name);
        if (idx == -1)
            return;
        glUniform1i(idx, value);
    }

    void setUniform(const char* name, GLfloat value)
    {
        GLint idx = glGetUniformLocation(program, name);
        if (idx == -1)
            return;
        glUniform1f(idx, value);
    }

    void setUniformMatrix4(const char* name, glm::mat4 Matrix)
    {
        GLint idx = glGetUniformLocation(program, name);
        if (idx == -1)
            return;

        glUniformMatrix4fv(idx, 1, false, glm::value_ptr(Matrix) );
        //glUniformMatrix4fv(ViewID, 1, false, glm::value_ptr(window->m_m4ViewMatrix) );
		//glUniformMatrix4fv(ModelID, 1, false, glm::value_ptr(g_ModelMatrix) );
    }
};


typedef Window*	WindowHandle;

unsigned int			g_uiWindowCounter = 0;
std::list<WindowHandle>	g_lWindows;
WindowHandle			g_hCurrentContext = nullptr;

Window*            rgbWin;
ShaderProgram      rgbShader;

Window*            depthWin;
ShaderProgram      depthShader;

Window*            irWin;
Window*            cloudWin;


std::map<unsigned int, unsigned int> g_mVAOs;
unsigned int g_VBO = 0;
unsigned int g_IBO = 0;
//unsigned int g_Shader = 0;
//glm::mat4	 g_ModelMatrix;

struct Vertex
{
	glm::vec4 m_v4Position;
	glm::vec2 m_v2UV;
};



int Init();
int MainLoop();
int ShutDown();

void GLFWErrorCallback(int a_iError, const char* a_szDiscription);
void GLFWWindowSizeCallback(GLFWwindow* a_pWindow, int a_iWidth, int a_iHeight);
GLEWContext* glewGetContext();

// This needs to be defined for GLEW MX to work, 
// along with the GLEW_MX define in the perprocessor!
void MakeContextCurrent(WindowHandle a_hWindowHandle);

WindowHandle CreateWindow(int a_iWidth, int a_iHeight, 
                          const std::string& a_szTitle, 
                          GLFWmonitor* a_pMonitor, WindowHandle a_hShare);

bool ShouldClose();
void CheckForGLErrors(std::string a_szMessage);


int libfreenectInfo()
{
    //std::string program_path(argv[0]);
    printf( "Version: %s\n", LIBFREENECT2_VERSION );

    /// [discovery]
    if(freenect2.enumerateDevices() == 0)
    {
        printf("no device connected!\n");
        return -1;
    }

    if (serial == "")
    {
        serial = freenect2.getDefaultDeviceSerialNumber();
        printf("device serial: %s\n", serial.c_str());
    }

    if(!pipeline)
    {
        // pipeline = new libfreenect2::CpuPacketPipeline();
        pipeline = new libfreenect2::OpenGLPacketPipeline();
        // pipeline = new libfreenect2::CudaPacketPipeline(0);
    }
    if(pipeline)
    {
        dev = freenect2.openDevice(serial, pipeline);
    } 
    else
    {
        dev = freenect2.openDevice(serial);
    }
    if(dev == 0)
    {
        printf("failure opening device\n");
        return -1;
    }
 
    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);

    if (enable_rgb && enable_depth)
    {
        if (!dev->start())
            return -1;
    }
    else
    {
        if (!dev->startStreams(enable_rgb, enable_depth))
           return -1;
    }

  return 1;
}


int main()
{
    int iReturnCode = EC_NO_ERROR;

	iReturnCode = Init();
	if (iReturnCode != EC_NO_ERROR)
		return iReturnCode;

    libfreenectInfo();

	iReturnCode = MainLoop();
	if (iReturnCode != EC_NO_ERROR)
		return iReturnCode;

	iReturnCode = ShutDown();
	if (iReturnCode != EC_NO_ERROR)
		return iReturnCode;

	return iReturnCode;
}


int Init()
{
	// Setup Our GLFW error callback, 
    // we do this before Init so we know what goes wrong with init if it fails:
	glfwSetErrorCallback(GLFWErrorCallback);

	// Init GLFW:
	if (!glfwInit())
		return EC_GLFW_INIT_FAIL;

	// create our first window:
	rgbWin = CreateWindow(960, 540, "rgb", nullptr, nullptr);
	
	if (rgbWin == nullptr)
	{
		glfwTerminate();
		return EC_GLFW_FIRST_WINDOW_CREATION_FAIL;
	}

	// Print out GLFW, OpenGL version and GLEW Version:
	int iOpenGLMajor = glfwGetWindowAttrib(rgbWin->m_pWindow, GLFW_CONTEXT_VERSION_MAJOR);
	int iOpenGLMinor = glfwGetWindowAttrib(rgbWin->m_pWindow, GLFW_CONTEXT_VERSION_MINOR);
	int iOpenGLRevision = glfwGetWindowAttrib(rgbWin->m_pWindow, GLFW_CONTEXT_REVISION);
	
    printf("Status: Using GLFW Version %s\n", glfwGetVersionString() );
	printf("Status: Using OpenGL Version: %i.%i, Revision: %i\n", iOpenGLMajor, iOpenGLMinor, iOpenGLRevision);
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION) );

	// create our second window:
	depthWin = CreateWindow(512, 414, "depth", nullptr, nullptr);


    /////////////////////////// rgbWin ////////////////////////////
	MakeContextCurrent(rgbWin);
    
    rgbShader.setShader(c_szVertexShader, c_szRgbPixelShader);
    rgbShader.build();
    rgbShader.use();
    // set the texture to use slot 0 in the shader
    rgbShader.setUniform("diffuseTexture", 0);
    CheckForGLErrors("Texture Loading Error"); 
   

    /////////////////////////// depthWin ////////////////////////////
	MakeContextCurrent(depthWin);
    depthShader.setShader(c_szVertexShader, c_szDepthPixelShader);
    depthShader.build();
    depthShader.use();
    
    // set the texture to use slot 0 in the shader
    depthShader.setUniform("Data", 0);   
    CheckForGLErrors("Texture Loading Error");

    return EC_NO_ERROR;
}


void flipY(size_t width, size_t height, size_t bytes_per_pixel, unsigned char * data)
{
    size_t linestep = width * bytes_per_pixel;

    unsigned char *first_line = data; 
    unsigned char *last_line = first_line + (height - 1) * linestep;
    
    unsigned char *tmp_line = new unsigned char[linestep];

    for (size_t y = 0; y < height / 2; ++y)
    {      
        std::copy(first_line, first_line + linestep, tmp_line);
        std::copy(last_line, last_line + linestep ,first_line);
        std::copy(tmp_line, tmp_line + linestep ,last_line);
        first_line += linestep;
        last_line -= linestep;
    }
    delete[] tmp_line;
}


int MainLoop()
{
    // now create a quad:
    Vertex aoVertices[4];

    aoVertices[0].m_v4Position = glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
    aoVertices[0].m_v2UV = glm::vec2(0.0f, 0.0f);

    aoVertices[1].m_v4Position = glm::vec4(1.0f, -1.0f, 0.0f, 1.0f);
    aoVertices[1].m_v2UV = glm::vec2(1.0f, 0.0f);
    
    aoVertices[2].m_v4Position = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    aoVertices[2].m_v2UV = glm::vec2(1.0f, 1.0f);
    
    aoVertices[3].m_v4Position = glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
    aoVertices[3].m_v2UV = glm::vec2(0.0f, 1.0f);

    unsigned int auiIndex[6] = { 0,1,3,   1,2,3 };


    /////////////////////////////////////////////////////////////////////////////////
    MakeContextCurrent(rgbWin);

    // Create VBO/IBO
    glGenBuffers(1, &g_VBO);
    glGenBuffers(1, &g_IBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), auiIndex, GL_STATIC_DRAW);

    
    // Setup VAO:
    // g_mVAOs[rgbWin->m_uiID] = 0;
    glGenVertexArrays(1, &(g_mVAOs[rgbWin->m_uiID]));
    glBindVertexArray(g_mVAOs[rgbWin->m_uiID]);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((char*)0) + 16);

    CheckForGLErrors("Creating VAO Error");
    
    // set OpenGL Options:
    glViewport(0, 0, rgbWin->m_uiWidth, rgbWin->m_uiHeight);
    glClearColor(0.25f, 0.25f, 0.25f, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    CheckForGLErrors("OpenGL Options Error");


    ///////////////////////////////////////////////////////////////////////////////
    MakeContextCurrent(depthWin);
  
    // Create VBO/IBO
    glGenBuffers(1, &g_VBO);
    glGenBuffers(1, &g_IBO);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), auiIndex, GL_STATIC_DRAW);

    // Setup VAO:
    g_mVAOs[depthWin->m_uiID] = 0;
    glGenVertexArrays(1, &(g_mVAOs[depthWin->m_uiID]));
    glBindVertexArray(g_mVAOs[depthWin->m_uiID]);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_IBO);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((char*)0) + 16);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    CheckForGLErrors("Creating VAO Error");
    
    // set OpenGL Options:
    glViewport(0, 0, depthWin->m_uiWidth, depthWin->m_uiHeight);
    glClearColor(0.25f, 0.25f, 0.25f, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    CheckForGLErrors("OpenGL Options Error");



	while (!ShouldClose())
	{

        libfreenect2::FrameMap frames;
        if (!listener.waitForNewFrame(frames, 5*1000)) // 10 sconds
        {
            printf("timeout!\n");
            return -1;
        }

        libfreenect2::Frame *depth =  frames[libfreenect2::Frame::Depth];
        libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];

		// draw each window in sequence:
        MakeContextCurrent(rgbWin);
        {   
			std::copy(rgb->data, rgb->data + rgb->width * rgb->height * rgb->bytes_per_pixel, rgbShader.texture_buffer);
            flipY(rgb->width, rgb->height, rgb->bytes_per_pixel, rgbShader.texture_buffer);

			// clear the backbuffer to our clear colour and clear the depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            rgbShader.setTexture(1920, 1080, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE);
            rgbShader.use();
            glBindVertexArray( g_mVAOs[rgbWin->m_uiID] );
    
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
            glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, rgb->width, rgb->height, GL_BGRA, GL_UNSIGNED_BYTE, rgbShader.texture_buffer);
               
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(rgbWin->m_pWindow);
			CheckForGLErrors("Render Error");
        }
		glfwPollEvents(); // process events!


        MakeContextCurrent(depthWin);
        { 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            std::copy(depth->data, depth->data + depth->width * depth->height * depth->bytes_per_pixel, depthShader.texture_buffer);
            flipY(depth->width, depth->height, depth->bytes_per_pixel, depthShader.texture_buffer);

			//glActiveTexture( GL_TEXTURE0 );
	    	depthShader.setTexture(512, 414, GL_R32F, GL_RED, GL_FLOAT);
            depthShader.use();
            //libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];

            glBindVertexArray( g_mVAOs[depthWin->m_uiID] );
            glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
            glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, 512, 414, GL_RED, GL_FLOAT, depthShader.texture_buffer);
      
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(depthWin->m_pWindow);
			CheckForGLErrors("Render Error");
        }
      
		glfwPollEvents(); // process events!
         
        // IMPORTANT£¡
        listener.release(frames);
	}
   
    glDeleteBuffers(1, &g_VBO);
    glDeleteBuffers(1, &g_IBO);

    glDeleteVertexArrays(1, &g_mVAOs[depthWin->m_uiID]);
    glDeleteVertexArrays(1, &g_mVAOs[rgbWin->m_uiID]);
 
    dev->stop();
    dev->close();

	return EC_NO_ERROR;
}


int ShutDown()
{
	// cleanup any remaining windows:
	for (auto& window :g_lWindows)
	{
		delete window->m_pGLEWContext;
		glfwDestroyWindow(window->m_pWindow);

		delete window;
	}

	// terminate GLFW:
	glfwTerminate();

	return EC_NO_ERROR;
}


void GLFWErrorCallback(int a_iError, const char* a_szDiscription)
{
	printf("GLFW Error occured, Error ID: %i, Description: %s\n", a_iError, a_szDiscription);
}


void GLFWWindowSizeCallback(GLFWwindow* a_pWindow, int a_iWidth, int a_iHeight)
{
	// find the window data corrosponding to a_pWindow;
	WindowHandle window = nullptr;
	for (auto& itr : g_lWindows)
	{
		if (itr->m_pWindow == a_pWindow)
		{
			window = itr;
			window->m_uiWidth = a_iWidth;
			window->m_uiHeight = a_iHeight;
			// window->m_m4Projection = glm::perspective(45.0f, float(a_iWidth)/float(a_iHeight), 0.1f, 1000.0f);
		}
	}

	WindowHandle previousContext = g_hCurrentContext;
	MakeContextCurrent(window);
	glViewport(0, 0, a_iWidth, a_iHeight);
	MakeContextCurrent(previousContext);
}


GLEWContext* glewGetContext()
{
	return g_hCurrentContext->m_pGLEWContext;
}


WindowHandle CreateWindow(int a_iWidth, int a_iHeight, 
        const std::string& a_szTitle, GLFWmonitor* a_pMonitor, WindowHandle a_hShare)
{
	// save current active context info so we can restore it later!
	WindowHandle hPreviousContext = g_hCurrentContext;

	// create new window data:
	WindowHandle newWindow = new Window();
	if (newWindow == nullptr)
		return nullptr;

	newWindow->m_pGLEWContext = nullptr;
	newWindow->m_pWindow = nullptr;

    // set ID and Increment Counter!
	newWindow->m_uiID = g_uiWindowCounter++;
	newWindow->m_uiWidth = a_iWidth;
	newWindow->m_uiHeight = a_iHeight;

	// Create Window:
    // Check that the Window Handle passed in is valid.
	if (a_hShare != nullptr)
    {
		newWindow->m_pWindow = glfwCreateWindow(a_iWidth, a_iHeight, 
                a_szTitle.c_str(), a_pMonitor, a_hShare->m_pWindow);  
        // Window handle is valid, Share its GL Context Data!
	}
	else
	{
		newWindow->m_pWindow = glfwCreateWindow(a_iWidth, a_iHeight, 
                a_szTitle.c_str(), a_pMonitor, nullptr); 
        // Window handle is invlad, do not share!
	}
	
	// Confirm window was created successfully:
	if (newWindow->m_pWindow == nullptr)
	{
		printf("Error: Could not Create GLFW Window!\n");
		delete newWindow;
		return nullptr;
	}

	// create GLEW Context:
	newWindow->m_pGLEWContext = new GLEWContext();
	if (newWindow->m_pGLEWContext == nullptr)
	{
		printf("Error: Could not create GLEW Context!\n");
		delete newWindow;
		return nullptr;
	}

	glfwMakeContextCurrent(newWindow->m_pWindow);   
    // Must be done before init of GLEW for this new windows Context!
	MakeContextCurrent(newWindow);
    // and must be made current too :)
 
    glewExperimental = true;
	// Init GLEW for this context:
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		// a problem occured when trying to init glew, report it:
		printf("GLEW Error occured, Description: %s\n", glewGetErrorString(err));
		glfwDestroyWindow(newWindow->m_pWindow);
		delete newWindow;
		return nullptr;
	}
	
	// setup callbacks:
	glfwSetWindowSizeCallback(newWindow->m_pWindow, GLFWWindowSizeCallback);

	// add new window to list:
	g_lWindows.push_back(newWindow);

	// now restore previous context:
	MakeContextCurrent(hPreviousContext);
	return newWindow;
}


// The MakeContextCurrent() function is a wrapper for the glfw3 
// function glfwMakeContextCurrent(), it takes in our WindowHandle type and
// makes sure to set g_hCurrentContext to the correct window when
// it changes the context. This is how we track which context is active.
void MakeContextCurrent(WindowHandle a_hWindowHandle)
{
	if (a_hWindowHandle != nullptr)
	{
		glfwMakeContextCurrent(a_hWindowHandle->m_pWindow);
		g_hCurrentContext = a_hWindowHandle;
	}
}

bool ShouldClose()
{
	if (g_lWindows.empty())
		return true;

	std::list<WindowHandle> lToDelete;
	for (const auto& window : g_lWindows)
	{
		if (glfwWindowShouldClose(window->m_pWindow))
		{
			lToDelete.push_back(window);
		}
	}

	if (!lToDelete.empty())
	{
		// we have windows to delete, Delete them:
		for (auto& window : lToDelete)
		{
			delete window->m_pGLEWContext;
			glfwDestroyWindow(window->m_pWindow);

			delete window;

			g_lWindows.remove(window);
		}
	}

	if (g_lWindows.empty())
		return true;

	return false;
}

void CheckForGLErrors(std::string a_szMessage)
{
	GLenum error = glGetError();
	while (error != GL_NO_ERROR)
	{
		printf("Error: %s, ErrorID: %i: %s\n", 
                a_szMessage.c_str(), error, gluErrorString(error));
		error = glGetError(); // get next error if any.
	}
}
