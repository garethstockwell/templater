//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// gles1cube.cpp
//

#include "gles1cube.h"
#include <e32debug.h>

_LIT(KGLES1CubeName, "gles1cube");

CRendererEgl* CRendererGLES1Cube::NewL(RWindow& aWindow)
    {
    CRendererGLES1Cube* self = new (ELeave) CRendererGLES1Cube(aWindow);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

const TDesC& CRendererGLES1Cube::Name()
	{
	return KGLES1CubeName;
	}

CRendererGLES1Cube::CRendererGLES1Cube(RWindow& aWindow)
    :   CRendererEgl(aWindow, EGL_OPENGL_ES_API)
    {

    }

CRendererGLES1Cube::~CRendererGLES1Cube()
	{
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::~CRendererGLES1Cube");
	glDeleteBuffers(1, &iCoordinateColorBuffer);
	glDeleteBuffers(1, &iIndexBuffer);
	}

/*
    v6----- v4
   /|      /|
  v0------v2|
  | |     | |
  | |v7---|-|v5
  |/      |/
  v1------v3

v0: -1.0, +1.0, +1.0,
v1: -1.0, -1.0, +1.0,
v2: +1.0, +1.0, +1.0,
v3: +1.0, -1.0, +1.0,
v4: +1.0, +1.0, -1.0,
v5: +1.0, -1.0, -1.0,
v6: -1.0, +1.0, -1.0,
v7: -1.0, -1.0, -1.0,
*/

static GLfloat CoordinateData[] =
	{
	-1.0, +1.0, +1.0,	// v0
	-1.0, -1.0, +1.0,	// v1
	+1.0, +1.0, +1.0,	// v2
	+1.0, -1.0, +1.0,	// v3
	+1.0, +1.0, -1.0,	// v4
	+1.0, -1.0, -1.0,	// v5
	-1.0, +1.0, -1.0,	// v6
	-1.0, -1.0, -1.0	// v7
	};

static const TInt CoordinateElementCount = 3; // XYZ

static GLfloat ColorData[] =
	{
	 0.0,  1.0,  1.0,  1.0,	// v0
	 0.0,  0.0,  1.0,  1.0,	// v1
	 1.0,  1.0,  1.0,  1.0,	// v2
	 1.0,  0.0,  1.0,  1.0,	// v3
	 1.0,  1.0,  0.0,  1.0,	// v4
	 1.0,  0.0,  0.0,  1.0,	// v5
	 0.0,  1.0,  0.0,  1.0,	// v6
	 0.0,  0.0,  0.0,  1.0	// v7
	};

static const TInt ColorElementCount = 4; // RGBA

static GLubyte FaceData[] =
	{
	0, 1, 3, 2, // front
	2, 3, 5, 4, // right
	4, 5, 7, 6, // left
	6, 7, 1, 0, // back
	6, 0, 2, 4, // top
	1, 7, 5, 3
	};

static const TInt VerticesPerFace = 4;
static const TInt VertexCount = sizeof(FaceData) / sizeof(GLubyte);
static const TInt FaceCount = VertexCount / VerticesPerFace;

static const TInt TrianglesPerFace = 2;
static const TInt VerticesPerTriangle = 3;

static const TInt IndexCount = FaceCount * TrianglesPerFace * VerticesPerTriangle;

static GLubyte FaceIndexData[] =
	{
	0, 2, 1,
	0, 3, 2
	};

void CRendererGLES1Cube::KhrSetup()
    {
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup");

	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup vertexCount %d", VertexCount);
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup faceCount %d", FaceCount);
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup indexCount %d", IndexCount);

	const GLsizeiptr coordinateSize = CoordinateElementCount * sizeof(GLfloat);
	const GLsizeiptr coordinateDataSize = VertexCount * coordinateSize;
	const GLsizeiptr colorSize = ColorElementCount * sizeof(GLfloat);
	const GLsizeiptr colorDataSize = VertexCount * colorSize;

	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glViewport %d x %d", WindowSize().iWidth, WindowSize().iHeight);
	glViewport(0, 0, WindowSize().iWidth, WindowSize().iHeight);
	GLCheckError();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

	// Create coordinate/color buffer
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glGenBuffers vertex/color");
	glGenBuffers(1, &iCoordinateColorBuffer);
	GLCheckError();
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glBindBuffer vertex/color");
	glBindBuffer(GL_ARRAY_BUFFER, iCoordinateColorBuffer);
	GLCheckError();

	// Allocate memory for coordinate/color buffer
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glBufferData coordinate/color");
	glBufferData(GL_ARRAY_BUFFER, coordinateDataSize + colorDataSize, 0, GL_STATIC_DRAW);
	GLCheckError();

	// Upload coordinate/color data
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup supply coordinate/color data");
	GLubyte indexData[IndexCount];
	for (TInt i=0; i<FaceCount; ++i)
		{
		RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup face %d", i);
		// Upload coordinate/color data for this face
		for (TInt j=0; j<VerticesPerFace; ++j)
			{
			const TInt vertexIndex = FaceData[i * VerticesPerFace + j];
			const TInt destIndex = (i * VerticesPerFace) + j;
			const GLfloat *coordSrc = CoordinateData + vertexIndex * CoordinateElementCount;
			const TInt coordDest = destIndex * coordinateSize;
			const GLfloat *colorSrc = ColorData + vertexIndex * ColorElementCount;
			const TInt colorDest = coordinateDataSize + destIndex * colorSize;
			RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup vertex %d (%d) destIndex %d coordDest %d colorDest %d",
					       j, vertexIndex, destIndex, coordDest, colorDest);
			RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup coord %3.1f %3.1f %3.1f",
						   *(coordSrc), *(coordSrc + 1), *(coordSrc + 2));
			RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup color %3.1f %3.1f %3.1f",
						   *(colorSrc), *(colorSrc + 1), *(colorSrc + 2));
			glBufferSubData(GL_ARRAY_BUFFER, coordDest, coordinateSize, coordSrc);
			GLCheckError();
			glBufferSubData(GL_ARRAY_BUFFER, colorDest, colorSize, colorSrc);
			GLCheckError();
			}

		// Store vertex indices for this face
		TInt indexDataOffset = i * TrianglesPerFace * VerticesPerTriangle;
		TInt indexBase = i * VerticesPerFace;
		for (TInt j=0; j<TrianglesPerFace * VerticesPerTriangle; ++j)
			{
			RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup index %d offset %d value %d",
						   j, indexDataOffset, indexBase + FaceIndexData[j]);
			indexData[indexDataOffset++] = indexBase + FaceIndexData[j];
			}
		}

	// Tell GL engine how to unpack coordinate/color buffer
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glVertexPointer");
	glVertexPointer(CoordinateElementCount, GL_FLOAT, 0, 0);
	GLCheckError();
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glColorPointer");
	glColorPointer(ColorElementCount, GL_FLOAT, 0, reinterpret_cast<GLvoid*>(coordinateDataSize));
	GLCheckError();

	// Create index buffer
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glGenBuffers index");
	glGenBuffers(1, &iIndexBuffer);
	GLCheckError();
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glBindBuffer index");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIndexBuffer);
	GLCheckError();

	// Allocate memory for index buffer and upload index data
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrSetup glBufferData index");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount, indexData, GL_STATIC_DRAW);
	GLCheckError();

	glEnableClientState(GL_VERTEX_ARRAY);
	GLCheckError();
	glEnableClientState(GL_COLOR_ARRAY);
	GLCheckError();

	StartRedrawTimer();
    }

void CRendererGLES1Cube::KhrPaint()
	{
	RDebug::Printf("[{{PROJECT}}] CRendererGLES1Cube::KhrPaint");

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(-1.5f, 1.5f, -2.5f, 2.5f, -10.5f, 10.5f);

	glMatrixMode(GL_MODELVIEW);
	iAngle = (iAngle + 1.0f);
	if (iAngle > 360.0f)
		{
		iAngle -= 360.0f;
		}
	glRotatef(iAngle, 0.0f, 1.0f, 0.5f);

	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_BYTE, 0);
    }

