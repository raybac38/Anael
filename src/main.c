/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <stdio.h>
#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Pixel Art Shader - Raylib");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Shader pixelShader = LoadShader(0, "./shaders/pixelart.fs");

    int resolutionLoc = GetShaderLocation(pixelShader, "resolution");
    int pixelSizeLoc = GetShaderLocation(pixelShader, "pixelSize");

    Vector2 resolution = { screenWidth, screenHeight };
    int pixelSize = 1;

    SetShaderValue(pixelShader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(pixelShader, pixelSizeLoc, &pixelSize, SHADER_UNIFORM_INT);

    // Création d'une texture vide (obligatoire pour appliquer le shader en 3D)
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    SetTargetFPS(60);

    printf("monitor fps : %i\n", GetMonitorRefreshRate(0));


    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_ORBITAL); // Permet de bouger la caméra avec la souris
        //----------------------------------------------------------------------------------

        // Rendu dans la texture pour appliquer le shader


        BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        int size = 3;
        for (int i = -size; i < size; i++) {
            for (int k = -size; k < size; k++) {
                Vector3 cubePosition = (Vector3){ i, 0, k };
                DrawCube(cubePosition, 1.0, 1.0, 1.0, RED);
                DrawCubeWires(cubePosition, 1.0, 1.0, 1.0, BLACK);
            }
        }

        EndMode3D();
        EndTextureMode();

        // Affichage avec shader
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginShaderMode(pixelShader);
        DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)screenWidth, -(float)screenHeight }, (Vector2){ 0, 0 }, WHITE);
        EndShaderMode();

        DrawText("Pixel Art Shader with Raylib", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    // Déchargement des ressources
    UnloadShader(pixelShader);
    UnloadRenderTexture(target);
    CloseWindow();
    
    return 0;
}
