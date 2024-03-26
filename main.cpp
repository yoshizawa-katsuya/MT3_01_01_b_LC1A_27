#include <Novice.h>
#include "Vector.h"
#include "Matrix.h"
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1A_27_ヨシザワ_カツヤ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1{ 1.2f, -3.9f, 2.5f };
	Vector3 v2{ 2.8f, 0.4f, -1.3f };
	Vector3 cross = Cross(v1, v2);

	float frame = 0;
	Vector3 rotate{0};
	Vector3 translate{ float(kWindowWidth / 2), float(kWindowHeight / 2) , 0.0f};

	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4 viewportMatrix;
	Vector3 screenVertices[3];
	Vector3 nbcVertex;

	Vector3 cameraPosition = { float(kWindowWidth / 2), float(kWindowHeight / 2), -2000.0f };

	Vector3 kLocalVertices[3] = {0};
	Vector3 a, b, ab;

	kLocalVertices[0] = { 0.0f, 300.0f, 0.0f };
	kLocalVertices[1] = { 300.0f, -300.0f, 0.0f };
	kLocalVertices[2] = { -300.0f, -300.0f, 0.0f };


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_A]) {
			translate.x -= 10;
		}
		if (keys[DIK_D]) {
			translate.x += 10;
		}

		if (keys[DIK_W]) {
			translate.z += 50;
		}
		if (keys[DIK_S]) {
			translate.z -= 50;
		}

		frame++;
		if (frame > 64.0f) {
			frame = 0;
		}
		rotate.y = frame / 32.0f * float(M_PI);

		worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
		cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		
		for (uint32_t i = 0; i < 3; ++i) {
			nbcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(nbcVertex, viewportMatrix);
		}

		a = Subtract(screenVertices[1], screenVertices[0]);
		b = Subtract(screenVertices[2], screenVertices[1]);
		ab = Cross(a, b);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, cross, "Cross");

		if (Dot({ 0.0f, 0.0f, -1.0f }, ab) <= 0) {
			Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid);
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
