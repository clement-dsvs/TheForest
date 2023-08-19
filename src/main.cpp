#include <raylib.h>
#include <valarray>

int main() {
    InitWindow(1920, 1080, "3D Model");
    DisableCursor();

    Model model = LoadModel("C:\\Users\\cleme\\Downloads\\Companion-bot\\Package\\Companion-bot.obj");
    Texture2D texture = LoadTexture("C:\\Users\\cleme\\Downloads\\Companion-bot\\Package\\Companion-bot.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    Camera3D cam = { 0 };
    cam.position = Vector3{ 50.0f, 50.0f, 50.0f };
    cam.target = Vector3{ 0, 0, 0 };
    cam.up = Vector3{ 0, 1, 0 };
    cam.fovy = 90.f;
    cam.projection = CAMERA_PERSPECTIVE;

    Vector3 pos = { 0, 0, 0 };
    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

    SetTargetFPS(144);
    float rotation = 0.f;
    while (!WindowShouldClose())
    {
        float left_X = GetGamepadAxisMovement(0, 0);
        float left_Y = GetGamepadAxisMovement(0, 1);

        if (!(left_X == 0 && left_Y == 0))
        {
            rotation = std::atan2(left_X, left_Y) * RAD2DEG + 180;
        }

        UpdateCamera(&cam, CAMERA_THIRD_PERSON);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(cam);
        DrawModelEx(model, pos, Vector3{0, 1, 0}, rotation, Vector3{1, 1, 1}, WHITE);

        DrawCube(Vector3{10, 0, 0}, 2, 2, 2, BLUE);
        DrawCube(Vector3{0, 0, 10}, 2, 2, 2, RED);


        DrawGrid(20, 10.f);
        DrawBoundingBox(bounds, GREEN);
        EndMode3D();
        DrawText("Loading obj file", 10, GetScreenHeight() - 25, 25, DARKGRAY);
        for (int i = 0; i < GetGamepadAxisCount(0); i++)
        {
            DrawText(TextFormat("AXIS %i: %.02f", i, GetGamepadAxisMovement(0, i)), 20, 70 + 20*i, 10, DARKGRAY);
        }
        DrawText(TextFormat("Rotation: %.02f", rotation), 20, 200, 10, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadModel(model);
    CloseWindow();

    return 0;
}

