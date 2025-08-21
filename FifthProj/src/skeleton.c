#include <raylib/raylib.h>
#include <math.h>

Vector2 GetScreenScale(Vector2 gameRes, Vector2 screenRes)
{
	double winAspect = (double) screenRes.x / screenRes.y;
	double gameAspect = (double) gameRes.x / gameRes.y;

	if (fabs(winAspect - gameAspect) < 0.01)
	{
		return (Vector2) {screenRes.x, screenRes.y};
	} else if (winAspect < gameAspect) {
		return (Vector2) {screenRes.x, (winAspect / gameAspect) * screenRes.y};
	} else {
		return (Vector2) {screenRes.x / ( winAspect / gameAspect) , screenRes.y};
	}
}

Vector2 GetScreenResolution()
{
	return (Vector2) {GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor())};
}

int main()
{
	Vector2 gameResolution = {320, 180};
	Vector2 scaledRes = (Vector2) {0.0, 0.0};
	Vector2 screenOffset = (Vector2) {0.0, 0.0};

	//SetConfigFlags(FLAG_MSAA_4X_HINT);
	
	InitWindow(GetScreenResolution().x, GetScreenResolution().y, "Scaling");
	//InitWindow(gameResolution.x, gameResolution.y, "Scaling");

	//SetTargetFPS(15);

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	RenderTexture2D renderTexture = LoadRenderTexture(gameResolution.x, gameResolution.y);

	if (IsWindowFullscreen()) {
		SetWindowSize(GetScreenResolution().x, GetScreenResolution().y);
		scaledRes = GetScreenScale(gameResolution, GetScreenResolution());
	} else {
		SetWindowSize(gameResolution.x, gameResolution.y);
		scaledRes = gameResolution;
	}

	while (!WindowShouldClose())
	{

		if (IsKeyReleased(KEY_F11)) 
		{
			if(IsWindowFullscreen())
			{
				scaledRes = gameResolution;
				SetWindowSize(gameResolution.x, gameResolution.y);
				screenOffset = (Vector2) {0.0, 0.0};
				ToggleFullscreen();
			} else {
				scaledRes = GetScreenScale(gameResolution, GetScreenResolution());
				SetWindowSize(GetScreenResolution().x, GetScreenResolution().y);
				screenOffset = (Vector2) {(GetScreenResolution().x - scaledRes.x) / 2, (GetScreenResolution().y - scaledRes.y) / 2};
				ToggleFullscreen();
			}
		}
		
		BeginTextureMode(renderTexture);
		ClearBackground((Color) {0, 0, 192, 255});
		DrawCircle(gameResolution.x / 2,  gameResolution.y / 2, gameResolution.x / 24, (Color){255,0,0,255});
		DrawText("Raylib", gameResolution.x / 2, gameResolution.y / 2, gameResolution.x / 25, WHITE);
		EndTextureMode();
		
		// Map Render Target to Screen
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(
			renderTexture.texture, 
			(Rectangle) {0,0,(float)renderTexture.texture.width, (float) -renderTexture.texture.height},
			(Rectangle) {screenOffset.x, screenOffset.y, (float) scaledRes.x, (float) scaledRes.y},
			(Vector2) {0,0},
			0,
			WHITE
		);

		EndDrawing();
	}

	UnloadRenderTexture(renderTexture);
	CloseWindow();
	return 0;
}
