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
    rectangleWidth = 280;
    rectangleHeight = 230;

    cx = corner.x + rectangleWidth / 2.0f;
    cy = corner.y + rectangleHeight / 2.0f;

    randomAngle = transf2D::getRandomAngle();

    timeElapsed = 0;

    speed = 175;

    coordinatesX = cx + (resolution.x - rectangleWidth) / 2.0f;
    coordinatesY = cy;

    translateX = 0;
    translateY = 0;

    /*scaleX = 1;
    scaleY = 1;*/

    leftAngularStep = 0;
    rightAngularStep = 0;

    isFirstBird = true;
    birdEscaped = false;
    reachedHeaven = false;
    isHit = false;
    reachedFloor = false;

    Mesh* grass = obj2D::CreateRectangle("grass", corner, (float)resolution.x, 172.5f, glm::vec3(0, 0.6f, 0.09f), true);
    AddMeshToList(grass);

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

    Mesh* hitbox = obj2D::CreateRectangle("hitbox", corner, 280, 230, glm::vec3(0, 0.5f, 1.0f), false);
    AddMeshToList(hitbox);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0.5f, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    timeElapsed += deltaTimeSeconds;

    grassModelMatrix = glm::mat3(1);

    RenderMesh2D(meshes["grass"], shaders["VertexColor"], grassModelMatrix);

    if (timeElapsed >= 5 && reachedHeaven == false && isHit == false)
    {
        birdEscaped = true;
        modelMatrix = glm::mat3(1);
        modelMatrix *= transf2D::Translate(translateX, translateY);

        modelMatrix *= transf2D::Translate(cx, cy);
        modelMatrix *= transf2D::Rotate((float)90.0f * (float)M_PI / 180.0f);
        modelMatrix *= transf2D::Translate(-cx, -cy);

        coordinatesX += deltaTimeSeconds * speed * cosf((float)90.0f * (float)M_PI / 180.0f);
        coordinatesY += deltaTimeSeconds * speed * sinf((float)90.0f * (float)M_PI / 180.0f);

        translateX = coordinatesX - rectangleWidth / 2.0f;
        translateY = coordinatesY - rectangleHeight / 2.0f;
        if (translateY > resolution.y * 9.0f / 8.0f)
            reachedHeaven = true;
    }
    else if (timeElapsed >= 0 && reachedHeaven == true && isHit == false)
    {
        timeElapsed = 0;
        if ((rand() % 2) == 0)
            randomAngle = rand() % 50 + 15;
        else
            randomAngle = rand() % 50 + 105;
        coordinatesX = cx + (resolution.x - rectangleWidth) / 2.0f;
        coordinatesY = cy;
        reachedHeaven = false;
        birdEscaped = false;
    }
    else if (isHit && reachedFloor == false)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transf2D::Translate(translateX, translateY);

        modelMatrix *= transf2D::Translate(cx, cy);
        modelMatrix *= transf2D::Rotate((float)270.0f * (float)M_PI / 180.0f);
        modelMatrix *= transf2D::Translate(-cx, -cy);

        coordinatesX += deltaTimeSeconds * speed * cosf((float)270.0f * (float)M_PI / 180.0f);
        coordinatesY += deltaTimeSeconds * speed * sinf((float)270.0f * (float)M_PI / 180.0f);

        translateX = coordinatesX - rectangleWidth / 2.0f;
        translateY = coordinatesY - rectangleHeight / 2.0f;
        if (translateY < -280.0f)
            reachedFloor = true;
    }
    else if (isHit && reachedFloor == true)
    {
        timeElapsed = 0;
        if ((rand() % 2) == 0)
            randomAngle = rand() % 50 + 15;
        else
            randomAngle = rand() % 50 + 105;
        coordinatesX = cx + (resolution.x - rectangleWidth) / 2.0f;
        coordinatesY = cy;
        isHit = 0;
        reachedFloor = false;
    }
    else {
        if (isFirstBird)
        {
            if (timeElapsed >= 3) {
                timeElapsed = 0;
                isFirstBird = false;
            }
        }
        else if (coordinatesX > resolution.x) {
            if (randomAngle > 0 && randomAngle < 90)
                randomAngle = 90 + (90 - randomAngle);
            else
                randomAngle = 180 + (360 - randomAngle);
            coordinatesX = (float)resolution.x;
            translateX = coordinatesX - rectangleWidth / 2.0f;
        }
        else if (coordinatesY > resolution.y) {
            if (randomAngle >= 90 && randomAngle <= 180)
                randomAngle = 180 + (180 - randomAngle);
            else
                randomAngle = 270 + (90 - randomAngle);
            coordinatesY = (float)resolution.y;
            translateY = coordinatesY - rectangleHeight / 2.0f;
        }
        else if (coordinatesX < 0) {
            if (randomAngle >= 180 && randomAngle <= 270)
                randomAngle = 270 + (270 - randomAngle);
            else
                randomAngle = 180 - randomAngle;
            coordinatesX = 0;
            translateX = coordinatesX - rectangleWidth / 2.0f;
        }
        else if (coordinatesY < 0) {
            if (randomAngle >= 270 && randomAngle <= 360)
                randomAngle = 360 - randomAngle;
            else
                randomAngle = 90 + (270 - randomAngle);
            coordinatesY = 0;
            translateX = coordinatesY - rectangleHeight / 2.0f;
        }
        else
        {
            cout << "aici\n";
            coordinatesX += deltaTimeSeconds * speed * cosf((float)(randomAngle) * (float)M_PI / 180.0f);
            coordinatesY += deltaTimeSeconds * speed * sinf((float)(randomAngle) * (float)M_PI / 180.0f);

            translateX = coordinatesX - rectangleWidth / 2.0f;
            translateY = coordinatesY - rectangleHeight / 2.0f;

            modelMatrix = glm::mat3(1);
            modelMatrix *= transf2D::Translate(translateX, translateY);

            modelMatrix *= transf2D::Translate(cx, cy);
            modelMatrix *= transf2D::Rotate((float)(randomAngle) * (float)M_PI / 180.0f);
            modelMatrix *= transf2D::Translate(-cx, -cy);
        }
    }

    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

    tmpModelMatrix = modelMatrix;

    if (leftAngularStep < ((float)(30.0f) * (float)M_PI / 180.0f))
        leftAngularStep += deltaTimeSeconds;
    else
        leftAngularStep = (float)(- 10.0f) * (float)M_PI / 180.0f;

    modelMatrix *= transf2D::Translate(cx, cy);
    modelMatrix *= transf2D::Rotate(leftAngularStep);
    modelMatrix *= transf2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["leftArm"], shaders["VertexColor"], modelMatrix);

    modelMatrix = tmpModelMatrix;

    if (rightAngularStep > ((float)(- 30.0f) * (float)M_PI / 180.0f))
        rightAngularStep -= deltaTimeSeconds;
    else
        rightAngularStep = ((float)(10.0f) * (float)M_PI / 180.0f);

    modelMatrix *= transf2D::Translate(cx, cy);
    modelMatrix *= transf2D::Rotate(rightAngularStep);
    modelMatrix *= transf2D::Translate(-cx, -cy);

    RenderMesh2D(meshes["rightArm"], shaders["VertexColor"], modelMatrix);

    modelMatrix = tmpModelMatrix;

    RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrix);
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
    glm::ivec2 resolution = window->GetResolution();

    trueMouseX = (float)mouseX;
    trueMouseY = resolution.y - (float)mouseY;

    trueMouseX -= coordinatesX;
    trueMouseY -= coordinatesY;

    auxMouseX = trueMouseX;
    auxMouseY = trueMouseY;

    trueMouseX = cosf((float)randomAngle * (float)M_PI / 180.0f) * auxMouseX + sinf((float)randomAngle * (float)M_PI / 180.0f) * auxMouseY;
    trueMouseY = -sinf((float)randomAngle * (float)M_PI / 180.0f) * auxMouseX + cosf((float)randomAngle * (float)M_PI / 180.0f) * auxMouseY;

    if (trueMouseX >= -140.0f && trueMouseX <= 140.0f && trueMouseY >= -115.0f && trueMouseY <= 115.0f && birdEscaped == false) {
        cout << "Poc\n";
        isHit = true;
    }
    else
        cout << "Ai ratat fraiere\n";
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
