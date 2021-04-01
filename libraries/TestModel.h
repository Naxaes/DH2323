#ifndef TEST_MODEL_CORNEL_BOX_H
#define TEST_MODEL_CORNEL_BOX_H

// Defines a simple test model: The Cornel Box

#include <vector>

#include "glm/glm.hpp"


// Used to describe a triangular surface:
class Triangle
{
public:
	glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 normal;
	glm::vec3 color;

	Triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 color)
		: v0(v0), v1(v1), v2(v2), color(color)
	{
		ComputeNormal();
	}

	void ComputeNormal()
	{
		glm::vec3 e1 = v1-v0;
		glm::vec3 e2 = v2-v0;
		normal = glm::normalize( glm::cross( e1, e2 ) );
	}
};

// Loads the Cornell Box. It is scaled to fill the volume:
// -1 <= x <= +1
// -1 <= y <= +1
// -1 <= z <= +1
std::vector<Triangle> LoadTestModel()
{
	std::vector<Triangle> triangles;

	using glm::vec3;

	// Defines colors:
	vec3 red(    0.75f, 0.15f, 0.15f );
	vec3 yellow( 0.75f, 0.75f, 0.15f );
	vec3 green(  0.15f, 0.75f, 0.15f );
	vec3 cyan(   0.15f, 0.75f, 0.75f );
	vec3 blue(   0.15f, 0.15f, 0.75f );
	vec3 purple( 0.75f, 0.15f, 0.75f );
	vec3 white(  0.75f, 0.75f, 0.75f );

	triangles.clear();
	triangles.reserve( 5*2*3 );

	// ---------------------------------------------------------------------------
	// Room

	float L = 555;			// Length of Cornell Box side.

	vec3 A(L,0,0);
	vec3 B(0,0,0);
	vec3 C(L,0,L);
	vec3 D(0,0,L);

	vec3 E(L,L,0);
	vec3 F(0,L,0);
	vec3 G(L,L,L);
	vec3 H(0,L,L);

	// Floor:
	triangles.emplace_back( C, B, A, green );
	triangles.emplace_back( C, D, B, green );

	// Left wall
	triangles.emplace_back( A, E, C, purple );
	triangles.emplace_back( C, E, G, purple );

	// Right wall
	triangles.emplace_back( F, B, D, yellow );
	triangles.emplace_back( H, F, D, yellow );

	// Ceiling
	triangles.emplace_back( E, F, G, cyan );
	triangles.emplace_back( F, H, G, cyan );

	// Back wall
	triangles.emplace_back( G, D, C, white );
	triangles.emplace_back( G, H, D, white );

	// ---------------------------------------------------------------------------
	// Short block

	A = vec3(290,0,114);
	B = vec3(130,0, 65);
	C = vec3(240,0,272);
	D = vec3( 82,0,225);

	E = vec3(290,165,114);
	F = vec3(130,165, 65);
	G = vec3(240,165,272);
	H = vec3( 82,165,225);

	// Front
	triangles.emplace_back( E,B,A,red );
	triangles.emplace_back( E,F,B,red );

	// Front
	triangles.emplace_back( F,D,B,red );
	triangles.emplace_back( F,H,D,red );

	// BACK
	triangles.emplace_back( H,C,D,red );
	triangles.emplace_back( H,G,C,red );

	// LEFT
	triangles.emplace_back( G,E,C,red );
	triangles.emplace_back( E,A,C,red );

	// TOP
	triangles.emplace_back( G,F,E,red );
	triangles.emplace_back( G,H,F,red );

	// ---------------------------------------------------------------------------
	// Tall block

	A = vec3(423,0,247);
	B = vec3(265,0,296);
	C = vec3(472,0,406);
	D = vec3(314,0,456);

	E = vec3(423,330,247);
	F = vec3(265,330,296);
	G = vec3(472,330,406);
	H = vec3(314,330,456);

	// Front
	triangles.emplace_back( E,B,A,blue );
	triangles.emplace_back( E,F,B,blue );

	// Front
	triangles.emplace_back( F,D,B,blue );
	triangles.emplace_back( F,H,D,blue );

	// BACK
	triangles.emplace_back( H,C,D,blue );
	triangles.emplace_back( H,G,C,blue );

	// LEFT
	triangles.emplace_back( G,E,C,blue );
	triangles.emplace_back( E,A,C,blue );

	// TOP
	triangles.emplace_back( G,F,E,blue );
	triangles.emplace_back( G,H,F,blue );


	// ----------------------------------------------
	// Scale to the volume [-1,1]^3

	for (size_t i = 0; i < triangles.size(); ++i)
	{
		triangles[i].v0 *= 2/L;
		triangles[i].v1 *= 2/L;
		triangles[i].v2 *= 2/L;

		triangles[i].v0 -= vec3(1,1,1);
		triangles[i].v1 -= vec3(1,1,1);
		triangles[i].v2 -= vec3(1,1,1);

		triangles[i].v0.x *= -1;
		triangles[i].v1.x *= -1;
		triangles[i].v2.x *= -1;

		triangles[i].v0.y *= -1;
		triangles[i].v1.y *= -1;
		triangles[i].v2.y *= -1;

        triangles[i].v0.z *= -1;
        triangles[i].v1.z *= -1;
        triangles[i].v2.z *= -1;

        triangles[i].ComputeNormal();
	}

	return triangles;
}

#endif