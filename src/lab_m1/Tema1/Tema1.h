#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        float dirX, dirY;
        float rectangleWidth, rectangleHeight;
        int random;

        float centerX, centerY;
        float radianRandom;
        float initialRandom;
        float angularStep2;

        int flag, flag2, flagInit, flagTime, firstBird, theBirdIsHit;
        glm::mat3 tmpModelMatrix;
        glm::mat3 grassModelMatrix;
        glm::mat3 auxModelMatrix;

        float pozX, pozY;

        int speed;
        float timeSinceSpawn;
        int reachedHeaven;

        int trueMouseX, trueMouseY;
        int auxMouseX, auxMouseY;

    };
}   // namespace m1
