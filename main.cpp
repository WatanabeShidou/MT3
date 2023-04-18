#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "GC2B_11_ワタナベシドウ";

struct Vecter3 {
	float x, y, z;
};

Vecter3 Add(const Vecter3& v1, const Vecter3& v2) {
	Vecter3 result;
	result.x = (v1.x + v2.x);
	result.y = (v1.y + v2.y);
	result.z = (v1.z + v2.z);
	return result;
}

Vecter3 Subtract(const Vecter3& v1, const Vecter3& v2) {
	Vecter3 result;
	result.x = (v1.x - v2.x);
	result.y = (v1.y - v2.y);
	result.z = (v1.z - v2.z);
	return result;
}

Vecter3 Multiply(float scalar, Vecter3& v) {
	Vecter3 result;
	result.x = (v.x * scalar);
	result.y = (v.y * scalar);
	result.z = (v.z * scalar);
	return result;
}

float Dot(const Vecter3& v1, const Vecter3& v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float Length(const Vecter3& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }

Vecter3 Normalize(const Vecter3& v) {
	Vecter3 result;
	result.x = (v.x / sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	result.y = (v.y / sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	result.z = (v.z / sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return result;
}

static const int kColumnWidth = 60;
void VecterScreenPrintf(int x, int y, const Vecter3& vecter, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vecter.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vecter.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vecter.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vecter3 v1{ 1.0f, 3.0f, -5.0f };
	Vecter3 v2{ 4.0f, -1.0f, 2.0f };
	float k = { 4.0f};

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
		Vecter3 resultAdd = Add(v1, v2);
		Vecter3 resultSubtract = Subtract(v1, v2);
		Vecter3 resultMultply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vecter3 resultNormalize = Normalize(v2);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VecterScreenPrintf(0, 0, resultAdd, " : Add");
		VecterScreenPrintf(0, 20, resultSubtract, " : Subtract");
		VecterScreenPrintf(0, 40, resultMultply, " : Multply");
		Novice::ScreenPrintf(0, 60, "%.02f  : Dot", resultDot);
		Novice::ScreenPrintf(0, 80, "%.02f  : Length", resultLength);
		VecterScreenPrintf(0, 100, resultNormalize, " : Normalize");

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
