#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transf2D.h"
#include "lab_m1/Tema1/obj2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + squareSide / 2.0f;
    cy = corner.y + squareSide / 2.0f;
    dirX = 1;
    dirY = 1;

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    /* Mesh* square1 = obj2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = obj2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = obj2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3); */

    /* Mesh* circle1 = obj2D::CreateCircle("circle1", corner + glm::vec3(525, 300, 0), 100, 64, glm::vec3(0.19f, 0.34f, 0.22f), true);
    AddMeshToList(circle1);

    Mesh* triangle1 = obj2D::CreateTriangle("triangle1", corner + glm::vec3(0, 175, 0), corner + glm::vec3(0, 400, 0), corner + glm::vec3(525, 288, 0), glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(triangle1);

    Mesh* triangle2 = obj2D::CreateTriangle("triangle2", corner + glm::vec3(175, 325, 0), corner + glm::vec3(325, 325, 0), corner + glm::vec3(250, 575, 0), glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(triangle2);

    Mesh* triangle3 = obj2D::CreateTriangle("triangle3", corner + glm::vec3(175, 250, 0), corner + glm::vec3(325, 250, 0), corner + glm::vec3(250, 0, 0), glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(triangle3);

    Mesh* triangle4 = obj2D::CreateTriangle("triangle4", corner + glm::vec3(590, 230, 0), corner + glm::vec3(590, 275, 0), corner + glm::vec3(700, 245, 0), glm::vec3(0.91f, 0.8f, 0.23f), true);
    AddMeshToList(triangle4); */

    Mesh* head = obj2D::CreateCircle("head", corner + glm::vec3(210, 120, 0), 40, 32, glm::vec3(0.19f, 0.34f, 0.22f), true);
    AddMeshToList(head);

    Mesh* body = obj2D::CreateTriangle("body", corner + glm::vec3(0, 70, 0), corner + glm::vec3(0, 160, 0), corner + glm::vec3(210, 115.2f, 0), glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(body);

    Mesh* leftArm = obj2D::CreateTriangle("leftArm", corner + glm::vec3(70, 130, 0), corner + glm::vec3(130, 130, 0), corner + glm::vec3(100, 230, 0), glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(leftArm);

    Mesh* rightArm = obj2D::CreateTriangle("rightArm", corner + glm::vec3(70, 100, 0), corner + glm::vec3(130, 100, 0), corner + glm::vec3(100, 0, 0), glm::vec3(0.35f, 0.23f, 0.15f), true);
    AddMeshToList(rightArm);

    Mesh* beak = obj2D::CreateTriangle("beak", corner + glm::vec3(236, 98, 0), corner + glm::vec3(236, 116, 0), corner + glm::vec3(280, 104, 0), glm::vec3(0.91f, 0.8f, 0.23f), true);
    AddMeshToList(beak);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    /* // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    modelMatrix = glm::mat3(1);
    modelMatrix *= transf2D::Translate(150, 250);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented.
    // Remember, the last matrix in the chain will take effect first!
    if (translateX > 200) {
        dirX = -1;
        dirY = -1;
    }
    if (translateX < 0) {
        dirX = 1;
        dirY = 1;
    }
    translateX += deltaTimeSeconds * 100 * dirX;
    translateY += deltaTimeSeconds * 100 * dirY;
    modelMatrix *= transf2D::Translate(translateX, translateY);


    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transf2D::Translate(400, 250);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!
    angularStep += deltaTimeSeconds * 2.5;

    modelMatrix *= transf2D::Translate(cx, cy);
    modelMatrix *= transf2D::Rotate(angularStep);
    modelMatrix *= transf2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transf2D::Translate(650, 250);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!
    scaleX += deltaTimeSeconds * 0.5;
    scaleY += deltaTimeSeconds * 0.5;
    modelMatrix *= transf2D::Scale(scaleX, scaleY);

    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix); */

    modelMatrix = glm::mat3(1);
    modelMatrix *= transf2D::Translate(150, 250);
    if (translateX > 200) {
        dirX = -1;
        dirY = -1;
    }
    if (translateX < 0) {
        dirX = 1;
        dirY = 1;
    }
    translateX += deltaTimeSeconds * 100 * dirX;
    translateY += deltaTimeSeconds * 100 * dirY;
    modelMatrix *= transf2D::Translate(translateX, translateY);
    if (dirX == 1)
    {
        modelMatrix *= transf2D::Translate(cx, cy);
        modelMatrix *= transf2D::Rotate(45.0f * (float)M_PI / 180.0f);
        modelMatrix *= transf2D::Translate(-cx, -cy);
    }
    if (dirX == -1)
    {
        modelMatrix *= transf2D::Translate(cx, cy);
        modelMatrix *= transf2D::Rotate(225.0f * (float)M_PI / 180.0f);
        modelMatrix *= transf2D::Translate(-cx, -cy);
    }
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["leftArm"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["rightArm"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
