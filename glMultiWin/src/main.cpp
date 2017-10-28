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

// a light image loading/saving lib 
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
 
////////////////// freenect2 /////////////////////
#define ENABLE_CLOUD    true
#define ENABLE_RGB      true
#define ENABLE_IR       true
#define ENABLE_DEPTH    true

libfreenect2::Freenect2 freenect2;
libfreenect2::Freenect2Device *dev = 0;
libfreenect2::PacketPipeline *pipeline = 0;
libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color | libfreenect2::Frame::Ir | libfreenect2::Frame::Depth);

#if ENABLE_CLOUD
libfreenect2::Registration* registration;
libfreenect2::Frame undistorted(512, 424, 4), cloud(512, 424, 4);
#endif

const char *c_szVertexShader =""
    "#version 330\n"

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
    "#version 330\n"

	"in vec2 vUV;"
	"layout(location = 0) out vec4 outColour;"
	"uniform sampler2D diffuseTexture;"
	
    "void main()"
	"{"
		"outColour = texture(diffuseTexture, vUV) ;"
	"}";

const char *c_szDepthPixelShader =""
    "#version 330\n"
        
    "in vec2 vUV;"
    "layout(location = 0) out vec4 outColour;"

    "uniform sampler2D Data;"
    "vec4 tempColor;"

    "void main()"
    "{"
        "tempColor = texture(Data, vUV);"
        "outColour = vec4(tempColor.x/4500, tempColor.x/4500, tempColor.x/4500, 1);"
    "}";

struct Vertex
{
	glm::vec4 m_v4Position;
	glm::vec2 m_v2UV;
};


struct ShaderProgram
{
    GLuint program, vertex_shader, fragment_shader;
    GLuint texture;
    GLuint VAO, VBO, IBO;

    unsigned int bytes_per_pixel, height, width, size;
    GLenum internalFormat, format, type;

    Vertex aoVertices[4];
    unsigned int auiIndex[6];

    char error_buffer[256];
    unsigned char* texture_buffer;

    ShaderProgram(unsigned int w, unsigned int h, unsigned int bpp, GLenum iFm, GLenum fm, GLenum t)
    {
        program = 0;
        vertex_shader = 0;
        fragment_shader = 0;

        width = w;
        height = h;
        bytes_per_pixel = bpp;

        size = width * height * bytes_per_pixel;
        texture_buffer = new unsigned char[size];

        internalFormat = iFm;
        format = fm;
        type = t;
        
        aoVertices[0].m_v4Position = glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
        aoVertices[0].m_v2UV = glm::vec2(0.0f, 0.0f);
        aoVertices[1].m_v4Position = glm::vec4(1.0f, -1.0f, 0.0f, 1.0f);
        aoVertices[1].m_v2UV = glm::vec2(1.0f, 0.0f);
        aoVertices[2].m_v4Position = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        aoVertices[2].m_v2UV = glm::vec2(1.0f, 1.0f);
        aoVertices[3].m_v4Position = glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
        aoVertices[3].m_v2UV = glm::vec2(0.0f, 1.0f);

        auiIndex[0] = 0;
        auiIndex[1] = 1;
        auiIndex[2] = 3;
        auiIndex[3] = 1;
        auiIndex[4] = 2;
        auiIndex[5] = 3;
        
        glGenTextures(1, &texture);
    }


    ~ShaderProgram() 
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &IBO);
        glDeleteTextures(1, &texture);
        delete[] texture_buffer;
    }


    void setShaderSrc(const char* vertexSrc, const char* fragmentSrc)
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

    void render()
    {
        glUseProgram(program);

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, width, height, format, type, texture_buffer); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray( VAO );
    }

    void setupVaoVbo()
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), auiIndex, GL_STATIC_DRAW);
 
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((char*)0) + 16);
        glEnableVertexAttribArray(1);
    }


    void setTexture(unsigned int i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture);

        // specify default filtering and wrapping
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
                
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, texture_buffer);
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

    
    void textureFlipY()
    {
        unsigned int linestep = width * bytes_per_pixel;

        unsigned char *first_line = texture_buffer;
        unsigned char *last_line = first_line + (height - 1) * linestep;
        unsigned char *tmp_line = new unsigned char[linestep];

        for (size_t y = 0; y < height/2; ++y)
        {      
            std::copy(first_line, first_line + linestep, tmp_line);
            std::copy(last_line, last_line + linestep ,first_line);
            std::copy(tmp_line, tmp_line + linestep ,last_line);
            first_line += linestep;
            last_line -= linestep;
        }
        delete[] tmp_line;
    }
};


struct Window
{
	GLFWwindow*		m_pWindow;
	GLEWContext*	m_pGLEWContext;
	unsigned int	m_uiWidth;
	unsigned int	m_uiHeight;
	glm::mat4		m_m4Projection;
	glm::mat4		m_m4ViewMatrix;
    static unsigned int	g_uiWindowCounter;
	unsigned int	m_uiID;
};

Window*	g_hCurrentContext = nullptr;
Window* rgbWin;
Window* depthWin;
Window* irWin;

#if ENABLE_CLOUD
Window* cloudWin;
#endif

unsigned int Window::g_uiWindowCounter = 0;

void GLFWErrorCallback(int a_iError, const char* a_szDiscription)
{
	printf("GLFW Error occured, Error ID: %i, Description: %s\n", a_iError, a_szDiscription);
}


void GLFWWindowSizeCallback(GLFWwindow* a_pWindow, int a_iWidth, int a_iHeight)
{
    if(a_pWindow == rgbWin->m_pWindow)
    {
        rgbWin->m_uiWidth = a_iWidth;
		rgbWin->m_uiHeight = a_iHeight;
        glfwMakeContextCurrent(rgbWin->m_pWindow);
        glViewport(0, 0, a_iWidth, a_iHeight);
        g_hCurrentContext = rgbWin;
    }
    else if(a_pWindow == depthWin->m_pWindow)
    {
        depthWin->m_uiWidth = a_iWidth;
        depthWin->m_uiHeight = a_iHeight;
        glfwMakeContextCurrent(depthWin->m_pWindow);
        glViewport(0, 0, a_iWidth, a_iHeight);
        g_hCurrentContext = depthWin;
    }
    else if(a_pWindow == irWin->m_pWindow)
    {
        irWin->m_uiWidth = a_iWidth;
        irWin->m_uiHeight = a_iHeight;
        glfwMakeContextCurrent(irWin->m_pWindow);
        glViewport(0, 0, a_iWidth, a_iHeight);
        g_hCurrentContext = irWin;
    }
    #if ENABLE_CLOUD
        else if(a_pWindow == cloudWin->m_pWindow)
        {
            cloudWin->m_uiWidth = a_iWidth;
            cloudWin->m_uiHeight = a_iHeight;
            glfwMakeContextCurrent(irWin->m_pWindow);
            glViewport(0, 0, a_iWidth, a_iHeight);
            g_hCurrentContext = cloudWin;
        }
    #endif
}


GLEWContext* glewGetContext()
{
	return g_hCurrentContext->m_pGLEWContext;
}

// This needs to be defined for GLEW MX to work, 
// along with the GLEW_MX define in the perprocessor!
// The MakeContextCurrent() function is a wrapper for the glfw3 
// function glfwMakeContextCurrent(), it takes in our Window* type and
// makes sure to set g_hCurrentContext to the correct window when
// it changes the context. This is how we track which context is active.

void MakeContextCurrent(Window* a_hWindowPointer)
{
	if (a_hWindowPointer != nullptr)
	{
		glfwMakeContextCurrent(a_hWindowPointer->m_pWindow);
		g_hCurrentContext = a_hWindowPointer;
	}
}


void CheckForGLErrors(std::string a_szMessage)
{
	GLenum error = glGetError();
	while (error != GL_NO_ERROR)
	{
		printf("Error: %s, ErrorID: %i: %s\n", a_szMessage.c_str(), error, gluErrorString(error));
		error = glGetError(); // get next error if any.
	}
}


Window* CreateWindow(int a_iWidth, int a_iHeight, const std::string& a_szTitle, GLFWmonitor* a_pMonitor, Window* a_hShare)
{
	// save current active context info so we can restore it later!
	Window* hPreviousContext = g_hCurrentContext;

	// create new window data:
	Window* newWindow = new Window();
	if (newWindow == nullptr)
		return nullptr;

	newWindow->m_pGLEWContext = nullptr;
	newWindow->m_pWindow = nullptr;

    // set ID and Increment Counter!
	newWindow->m_uiID = Window::g_uiWindowCounter++;
	newWindow->m_uiWidth = a_iWidth;
	newWindow->m_uiHeight = a_iHeight;

	// Create Window:
    // Check that the Window Handle passed in is valid.
	if (a_hShare != nullptr)
    {
		newWindow->m_pWindow = glfwCreateWindow(a_iWidth, a_iHeight, a_szTitle.c_str(), a_pMonitor, a_hShare->m_pWindow);  
        // Window handle is valid, Share its GL Context Data!
	}
	else
	{
		newWindow->m_pWindow = glfwCreateWindow(a_iWidth, a_iHeight, a_szTitle.c_str(), a_pMonitor, nullptr); 
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

	// now restore previous context:
	MakeContextCurrent(hPreviousContext);
	return newWindow;
}


int libfreenectInfo()
{
    bool enable_rgb = true;
    bool enable_depth = true;

    printf("Version: %s\n", LIBFREENECT2_VERSION );

    /// [discovery]
    if(freenect2.enumerateDevices() == 0)
    {
        printf("no device connected!\n");
        return -1;
    }
    
    std::string serial = freenect2.getDefaultDeviceSerialNumber();

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

        #if ENABLE_CLOUD
            registration = new libfreenect2::Registration(dev->getIrCameraParams(), dev->getColorCameraParams());
        #endif 
    }
    else
    {
        if (!dev->startStreams(enable_rgb, enable_depth))
           return -1;
    }

  return 1;
}


int main(int argc, char *argv[])
{
    bool rgbWinClosed = false;
    bool depthWinClosed = false;
    bool irWinClosed = false;

    ShaderProgram rgbShader(1920, 1080, 4, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE);
    ShaderProgram depthShader(512, 424, 4, GL_R32F, GL_RED, GL_FLOAT);
    ShaderProgram irShader(512, 424, 4, GL_R32F, GL_RED, GL_FLOAT);
    
    #if ENABLE_CLOUD
        bool cloudWinClosed = false;
        ShaderProgram cloudShader(512, 424, 4, GL_RGBA, GL_BGRA, GL_UNSIGNED_BYTE);
    #endif 

    /////////////////////// INIT ///////////////////////////////
	// Setup Our GLFW error callback, we do this before glfwInit so we know what goes wrong with init if it fails:
	glfwSetErrorCallback(GLFWErrorCallback);

	// Init GLFW:
	if (!glfwInit())
		return -1;

	// create our first window:
	rgbWin = CreateWindow(960, 540, "rgb", nullptr, nullptr);
	if (rgbWin == nullptr)
	{
		glfwTerminate();
		return -1;
	}

	// Print out GLFW, OpenGL version and GLEW Version:
    printf("Status: Using GLFW Version %s\n", glfwGetVersionString() );
	printf("Status: Using OpenGL Version: %i.%i, Revision: %i\n", 
            glfwGetWindowAttrib(rgbWin->m_pWindow, GLFW_CONTEXT_VERSION_MAJOR), 
            glfwGetWindowAttrib(rgbWin->m_pWindow, GLFW_CONTEXT_VERSION_MINOR),
            glfwGetWindowAttrib(rgbWin->m_pWindow, GLFW_CONTEXT_REVISION));
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION) );

    // create our second window:
	depthWin = CreateWindow(512, 424, "Depth", nullptr, nullptr);
	if (depthWin == nullptr)
	{
		glfwTerminate();
		return -1;
	}

    // create our third window:
	irWin = CreateWindow(512, 424, "Ir", nullptr, nullptr);
    if (irWin == nullptr)
    {
        glfwTerminate();
		return -1;
    }

    #if ENABLE_CLOUD
	cloudWin = CreateWindow(512, 424, "Cloud", nullptr, nullptr);
    if (cloudWin == nullptr)
    {
        glfwTerminate();
		return -1;
    }
    #endif

    /////////////////////////// rgbWin ////////////////////////////
	MakeContextCurrent(rgbWin);
    rgbShader.setShaderSrc(c_szVertexShader, c_szRgbPixelShader);
    rgbShader.build();
    rgbShader.use();
    rgbShader.setUniform("diffuseTexture", 0);
    rgbShader.setupVaoVbo();
    CheckForGLErrors("Check creating VAO, VBO, texture loading Error");
   
    /////////////////////////// depthWin ////////////////////////////
	MakeContextCurrent(depthWin);
    depthShader.setShaderSrc(c_szVertexShader, c_szDepthPixelShader);
    depthShader.build();
    depthShader.use();
    depthShader.setUniform("Data", 0);   
    depthShader.setupVaoVbo();
    CheckForGLErrors("Check creating VAO, VBO, texture loading Error");

    /////////////////////////// irWin ////////////////////////////
	MakeContextCurrent(irWin);
    irShader.setShaderSrc(c_szVertexShader, c_szDepthPixelShader);
    irShader.build();
    irShader.use();
    irShader.setUniform("Data", 0);   
    irShader.setupVaoVbo();
    CheckForGLErrors("Check creating VAO, VBO, texture loading Error");

    #if ENABLE_CLOUD
        MakeContextCurrent(cloudWin);
        cloudShader.setShaderSrc(c_szVertexShader, c_szRgbPixelShader);
        cloudShader.build();
        cloudShader.use();
        cloudShader.setUniform("diffuseTexture", 0);
        cloudShader.setupVaoVbo();
        CheckForGLErrors("Check creating VAO, VBO, texture loading Error");
    #endif

    // set OpenGL Options:
    // glClearColor(0.25f, 0.25f, 0.25f, 1);
    // glEnable(GL_DEPTH_TEST); glEnable(GL_CULL_FACE);

    libfreenectInfo();    

	while ( !rgbWinClosed || !depthWinClosed || !irWinClosed || !cloudWinClosed )
	{
        libfreenect2::FrameMap frames;
        if (!listener.waitForNewFrame(frames, 5*1000)) // 10 sconds
        {
            printf("timeout!\n");
            return -1;
        }

        libfreenect2::Frame *depth =  frames[libfreenect2::Frame::Depth];
        libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
        libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];

         // draw each window in sequence:
		if (!glfwWindowShouldClose(rgbWin->m_pWindow))
		{
			MakeContextCurrent(rgbWin);
            // clear the backbuffer to our clear colour and clear the depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            std::copy(rgb->data, rgb->data + rgb->width * rgb->height * rgb->bytes_per_pixel, rgbShader.texture_buffer);
            rgbShader.textureFlipY();
            rgbShader.setTexture(0);
            rgbShader.render();

            glfwSwapBuffers(rgbWin->m_pWindow);
            CheckForGLErrors("Render Error");
            
            glfwPollEvents(); // process events!
		}
        else
        {
            if(!rgbWinClosed)
            {
                delete rgbWin->m_pGLEWContext;
			    glfwDestroyWindow(rgbWin->m_pWindow);
                rgbWinClosed = true;
            }
        }

		if (!glfwWindowShouldClose(depthWin->m_pWindow))
        {
            MakeContextCurrent(depthWin);
        
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            std::copy(depth->data, depth->data + depth->width * depth->height * depth->bytes_per_pixel, depthShader.texture_buffer);

            depthShader.textureFlipY(); 
	    	depthShader.setTexture(0);
            depthShader.render();
            
            glfwSwapBuffers(depthWin->m_pWindow);
            CheckForGLErrors("Render Error");
            glfwPollEvents(); // process events!
        }
        else
        {
            if(!depthWinClosed)
            {
                delete depthWin->m_pGLEWContext;
			    glfwDestroyWindow(depthWin->m_pWindow);
                depthWinClosed = true;
            }
        }
     

        if (!glfwWindowShouldClose(irWin->m_pWindow))
        {
            MakeContextCurrent(irWin);
        
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            std::copy(ir->data, ir->data + ir->width * ir->height * ir->bytes_per_pixel, irShader.texture_buffer);

            irShader.textureFlipY();
	    	irShader.setTexture(0);
            irShader.render();
            
            glfwSwapBuffers(irWin->m_pWindow);
            CheckForGLErrors("Render Error");
            glfwPollEvents(); // process events!
        }
        else
        {
            if(!irWinClosed)
            {
                delete irWin->m_pGLEWContext;
			    glfwDestroyWindow(irWin->m_pWindow);
                irWinClosed = true;
            }
        }

#if ENABLE_CLOUD
        if (!glfwWindowShouldClose(cloudWin->m_pWindow))
        {
            MakeContextCurrent(cloudWin);
            
            registration->apply(rgb, depth, &undistorted, &cloud);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            std::copy(cloud.data, cloud.data + cloud.width * cloud.height * cloud.bytes_per_pixel, cloudShader.texture_buffer);

            cloudShader.textureFlipY();
            cloudShader.setTexture(0);
            cloudShader.render();
            
            glfwSwapBuffers(cloudWin->m_pWindow);
            CheckForGLErrors("Cloud Render Error");
            glfwPollEvents(); // process events!
        }
        else
        {
            if(!cloudWinClosed)
            {
                delete cloudWin->m_pGLEWContext;
                glfwDestroyWindow(cloudWin->m_pWindow);
                cloudWinClosed = true;
            }
        }
#endif

        // IMPORTANT£¡
        listener.release(frames);
	}
   
    dev->stop();
    dev->close();

    delete rgbWin;
    delete depthWin;
    delete irWin;

#if ENABLE_CLOUD
    delete cloudWin;
#endif
    return 0;
}

