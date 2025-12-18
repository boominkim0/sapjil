# raylib 폴더 사용법 & API 명세(요약) — 한국어

> 이 문서는 현재 워크스페이스에 포함된 `raylib/` 소스 트리(클론본)를 기준으로, **어디에 무엇이 있는지**와 **`raylib.h`의 공개 API를 모듈별로** 빠르게 찾아볼 수 있게 정리한 “API 명세서 스타일 요약”입니다.
>
> - 기준 헤더: `raylib/src/raylib.h` (v5.6-dev, 헤더 상단 표기)
> - 파생 모듈: `raylib/src/raymath.h`, `raylib/src/rlgl.h`, `raylib/src/rcamera.h`, `raylib/src/rgestures.h`

---

## 1) raylib 폴더 구조 빠른 안내

### 최상위(`raylib/`)

- `src/`
  - **코어 라이브러리 소스/헤더**가 모여 있는 핵심 폴더
  - `raylib.h`가 “공개 API(사용자가 include해서 쓰는 API)”의 중심
- `examples/`
  - 기능별 예제가 대량으로 있음(학습/레퍼런스 최강)
  - 예제는 `src`에서 raylib을 빌드한 뒤 빌드하는 구조
- `projects/`
  - 여러 IDE용 템플릿/프로젝트 파일
- `cmake/`, `CMakeLists.txt`
  - CMake 기반 빌드 구성
- `build.zig`, `build.zig.zon`
  - Zig 빌드 지원

### `src/`에서 자주 보는 파일

- `raylib.h`
  - **공개 API 선언(함수/타입/상수)**
- `rcore.c`
  - 창(Window), 입력(Input), 프레임/루프, 기본 렌더 파이프라인 등 코어 구현
- `rshapes.c`
  - 2D 기본 도형 그리기(라인/원/사각형 등)
- `rtextures.c`
  - 이미지/텍스처 로딩·처리·그리기
- `rtext.c`
  - 폰트/텍스트
- `rmodels.c`
  - 3D 모델/메시/머티리얼
- `raudio.c`
  - 사운드/뮤직/오디오 스트림
- `external/`
  - stb 계열, miniaudio 등 **내장 의존성 소스**

---

## 2) “Hello raylib” 최소 사용 흐름(공식 루프 패턴)

### 기본 루프(2D 기준)

1. `InitWindow(width, height, title)`
2. `SetTargetFPS(fps)` (선택)
3. 매 프레임:
   - `while (!WindowShouldClose())` 루프
   - `BeginDrawing()`
   - `ClearBackground(color)`
   - Draw 호출들(`DrawText`, `DrawCircleV`, ...)
   - `EndDrawing()`
4. `CloseWindow()`

---

## 3) 빌드/실행 가이드 (이 워크스페이스 기준)

### macOS 네이티브 빌드(이미 사용 중인 방식)

`/Users/bm/workspace/cpp-test/README.md`에 정리된 커맨드를 그대로 사용하면 됩니다.

핵심 포인트:
- Homebrew로 설치한 raylib은 macOS용으로 빌드된 라이브러리(예: `libraylib.a`)입니다.
- C++ 코드에서 `#include "raylib.h"`를 쓰면 컴파일러가 헤더를 찾아야 하므로 `-I/opt/homebrew/include`가 필요할 수 있습니다.

### 웹(HTML5/WebAssembly) 빌드할 때 왜 Homebrew raylib로는 안 되나?

당신이 본 에러의 핵심:
- `wasm-ld: ... is neither Wasm object file nor LLVM bitcode`
- `undefined symbol: InitWindow ...`

의미:
- `/opt/homebrew/lib/libraylib.a`는 **macOS(네이티브)용 오브젝트**로 만들어져서
- Emscripten(웹용 링크러)이 **WASM/LLVM 비트코드**로 링크할 수 없습니다.

해결:
- **raylib을 emscripten용(PLATFORM=Web)으로 다시 빌드한 정적 라이브러리**를 만든 뒤,
- 그 라이브러리를 링크해서 `index.html`을 생성해야 합니다.

### 웹(HTML5) 빌드 전체 흐름(정리)

1) raylib 웹용 라이브러리 빌드
- 이미 실행한 것처럼(예시):
  - `cd raylib && mkdir -p build && cd build`
  - `emcmake cmake .. -DPLATFORM=Web -DBUILD_SHARED_LIBS=OFF`
  - `emmake make`

2) 내 게임 소스(`main.cpp`)를 웹으로 컴파일
- 예시(현재 워크스페이스에서 성공 시도한 플래그 형태):
  - `emcc main.cpp -o index.html -Iraylib/src -Lraylib/build/raylib -lraylib -s USE_GLFW=3 -s ASYNCIFY`

3) 실행(중요)
- 브라우저는 보통 `file://`로 열린 wasm을 막는 경우가 많아서 **로컬 서버로 띄워야** 합니다.
- Emscripten에는 `emrun`이(설치/환경에 따라) 포함되기도 합니다.

---

## 4) raylib 공개 API 명세(요약)

> 전체 함수는 `raylib/src/raylib.h`를 보면 됩니다.
> 여기서는 “게임 만들 때 자주 쓰는 것” 위주로 모듈별로 정리합니다.

### 4.1 Core (Window/Graphics Device)

#### 윈도우
- `void InitWindow(int width, int height, const char *title)`
- `void CloseWindow(void)`
- `bool WindowShouldClose(void)`
- `bool IsWindowReady(void)`
- `void SetWindowTitle(const char *title)`
- `int GetScreenWidth(void)`, `int GetScreenHeight(void)`

#### 드로잉 프레임
- `void BeginDrawing(void)`
- `void EndDrawing(void)`
- `void ClearBackground(Color color)`

#### 2D/3D 모드
- `void BeginMode2D(Camera2D camera)` / `void EndMode2D(void)`
- `void BeginMode3D(Camera3D camera)` / `void EndMode3D(void)`

#### 시간/FPS
- `void SetTargetFPS(int fps)`
- `float GetFrameTime(void)`
- `double GetTime(void)`
- `int GetFPS(void)`

#### 난수
- `void SetRandomSeed(unsigned int seed)`
- `int GetRandomValue(int min, int max)`

---

### 4.2 Input (Keyboard/Mouse/Gamepad/Touch)

#### 키보드
- `bool IsKeyPressed(int key)`
- `bool IsKeyDown(int key)`
- `int GetKeyPressed(void)`
- `void SetExitKey(int key)`

자주 쓰는 키 상수 예:
- `KEY_ESCAPE`, `KEY_SPACE`, `KEY_LEFT`, `KEY_RIGHT`, `KEY_UP`, `KEY_DOWN`

#### 마우스
- `bool IsMouseButtonPressed(int button)`
- `Vector2 GetMousePosition(void)`

마우스 버튼 상수:
- `MOUSE_BUTTON_LEFT`, `MOUSE_BUTTON_RIGHT`, `MOUSE_BUTTON_MIDDLE`

#### 터치/제스처
- `Vector2 GetTouchPosition(int index)`
- `int GetTouchPointCount(void)`
- `void SetGesturesEnabled(unsigned int flags)`
- `bool IsGestureDetected(unsigned int gesture)`

---

### 4.3 Shapes (2D 기본 도형)

- `void DrawPixel(int x, int y, Color c)`
- `void DrawLine(int x1, int y1, int x2, int y2, Color c)`
- `void DrawCircleV(Vector2 center, float radius, Color c)`
- `void DrawRectangle(int x, int y, int w, int h, Color c)`
- 충돌 검사:
  - `bool CheckCollisionRecs(Rectangle a, Rectangle b)`
  - `bool CheckCollisionCircles(Vector2 c1, float r1, Vector2 c2, float r2)`

---

### 4.4 Textures (Image/Texture)

#### 이미지(주로 CPU 메모리)
- `Image LoadImage(const char *fileName)`
- `void UnloadImage(Image image)`

#### 텍스처(주로 GPU 메모리)
- `Texture2D LoadTexture(const char *fileName)`
- `void UnloadTexture(Texture2D texture)`
- `void DrawTexture(Texture2D texture, int x, int y, Color tint)`

---

### 4.5 Text (Font/Text)

- `Font GetFontDefault(void)`
- `Font LoadFont(const char *fileName)`
- `void UnloadFont(Font font)`

- `void DrawText(const char *text, int x, int y, int fontSize, Color color)`
- `int MeasureText(const char *text, int fontSize)`

---

### 4.6 Models (3D)

- 3D 기본 도형
  - `void DrawCube(Vector3 pos, float w, float h, float l, Color tint)`
  - `void DrawSphere(Vector3 center, float radius, Color tint)`
  - `void DrawGrid(int slices, float spacing)`

- 모델 로딩/렌더
  - `Model LoadModel(const char *fileName)`
  - `void UnloadModel(Model model)`
  - `void DrawModel(Model model, Vector3 position, float scale, Color tint)`

---

### 4.7 Audio

- 디바이스
  - `void InitAudioDevice(void)`
  - `void CloseAudioDevice(void)`
  - `bool IsAudioDeviceReady(void)`

- 사운드
  - `Sound LoadSound(const char *fileName)`
  - `void PlaySound(Sound sound)`
  - `void UnloadSound(Sound sound)`

- 뮤직(스트리밍)
  - `Music LoadMusicStream(const char *fileName)`
  - `void PlayMusicStream(Music music)`
  - `void UpdateMusicStream(Music music)`
  - `void UnloadMusicStream(Music music)`

---

## 5) 타입/구조체(자주 쓰는 것)

- `Vector2 { float x, y; }`
- `Vector3 { float x, y, z; }`
- `Rectangle { float x, y, width, height; }`
- `Color { unsigned char r, g, b, a; }`
- `Camera2D`, `Camera3D`
- `Image`, `Texture2D`, `RenderTexture2D`

---

## 6) 색상 상수(팔레트)

`raylib.h`에는 기본 팔레트가 macro로 정의돼 있습니다.

예)
- `RAYWHITE`, `WHITE`, `BLACK`
- `RED`, `GREEN`, `BLUE`
- `DARKGRAY`, `LIGHTGRAY`

---

## 7) 참고: 이 워크스페이스에서 쓰는 함수들 매핑

현재 `main.cpp`에서 직접 쓰는 함수(핵심):
- 윈도우/루프: `InitWindow`, `SetTargetFPS`, `WindowShouldClose`, `CloseWindow`
- 입력: `IsMouseButtonPressed`
- 유틸: `GetRandomValue`
- 렌더: `BeginDrawing`, `ClearBackground`, `DrawText`, `DrawCircleV`, `EndDrawing`

---

## 8) 다음 단계(선택)

원하면 이 문서를 더 “진짜 API 명세서” 느낌으로 확장할 수 있어요:
- 모듈별로 전체 함수 목록(전부) + 파라미터 설명(한글)
- 예제 링크(예: `examples/core/core_basic_window.c`)를 각 API 섹션에 연결
- C++에서 안전하게 쓰는 팁(리소스 언로드 순서, main loop 패턴, delta time 이동 등)

---

## 9) 메모리 관리(리소스 수명) 가이드 🎯

raylib은 “C 라이브러리 + 핸들(struct)” 스타일이라서, **로드/생성한 리소스를 직접 Unload 해줘야** 합니다.

### 9.1 기본 원칙

- **CPU 메모리(주로 `Image`, `Wave` 등)** 는 `UnloadImage()`, `UnloadWave()`처럼 *UnloadXxx*로 해제합니다.
- **GPU 메모리(주로 `Texture2D`, `RenderTexture2D`, `Font`, `Model`, `Shader` 등)** 는 대응되는 *UnloadXxx*로 해제합니다.
- 리소스는 보통 “값 타입(struct)”으로 반환되지만 내부에 **GPU/힙 자원 핸들(id/포인터)** 을 들고 있습니다.
  - 그래서 C++에서 그냥 스코프를 벗어난다고 자동 해제되지 않습니다.
- “누가 소유(owner)인가?”를 정하고, **owner가 반드시 Unload** 하는 규칙을 세우면 실수가 확 줄어듭니다.

자주 쓰는 로드/언로드 페어(대표):

- `Texture2D LoadTexture(const char*)`  →  `UnloadTexture(Texture2D)`
- `Font LoadFont(const char*)`          →  `UnloadFont(Font)`
- `Sound LoadSound(const char*)`        →  `UnloadSound(Sound)`
- `Music LoadMusicStream(const char*)`  →  `UnloadMusicStream(Music)`
- `Model LoadModel(const char*)`        →  `UnloadModel(Model)`
- `Shader LoadShader(...)`              →  `UnloadShader(Shader)`
- `RenderTexture2D LoadRenderTexture(...)` → `UnloadRenderTexture(RenderTexture2D)`

### 9.2 “언제” 해제해야 하나?

- **게임 종료 시**: `CloseWindow()` 전에 전부 해제하는 게 가장 안전합니다.
- **Scene(화면) 전환 시**:
  - “해당 씬에서만 쓰는 리소스”는 씬이 사라질 때 같이 해제
  - “전체 게임 공용 리소스(예: UI 폰트, 공용 사운드)”는 App 레벨에서 한 번만 로드하고 마지막에 해제

### 9.3 C++에서 RAII로 감싸기(권장)

실수를 줄이려면 C++에서는 소유 리소스를 래퍼 클래스로 감싸서 **소멸자에서 Unload** 하게 만드는 게 좋아요.

예: `Texture2D` RAII 래퍼(간단 버전)

```cpp
// 헤더/유틸 파일로 분리해두면 편해요.
struct Texture2DOwner {
  Texture2D tex{};

  Texture2DOwner() = default;
  explicit Texture2DOwner(const char* path) { tex = LoadTexture(path); }

  // 복사 금지(이중 해제 방지)
  Texture2DOwner(const Texture2DOwner&) = delete;
  Texture2DOwner& operator=(const Texture2DOwner&) = delete;

  // 이동 허용
  Texture2DOwner(Texture2DOwner&& other) noexcept { tex = other.tex; other.tex = {}; }
  Texture2DOwner& operator=(Texture2DOwner&& other) noexcept {
    if (this != &other) {
      reset();
      tex = other.tex;
      other.tex = {};
    }
    return *this;
  }

  ~Texture2DOwner() { reset(); }

  void reset() {
    if (tex.id != 0) UnloadTexture(tex);
    tex = {};
  }
};
```

핵심 포인트:
- **복사 금지**(copy) + **이동만 허용**(move) ⇒ double-free 방지
- `tex.id != 0` 체크 후 `UnloadTexture()`

> 같은 패턴으로 `Font`, `Sound`, `Model` 등도 만들 수 있습니다.

---

## 10) Scene(화면) 전환 패턴 🧩

raylib은 엔진이 아니라 “함수 라이브러리”라서, Scene은 보통 **상태 머신(state machine)** 으로 직접 만듭니다.

### 10.1 가장 쉬운 방식: enum + switch

```cpp
enum class SceneId { Title, Game, Pause };

SceneId scene = SceneId::Title;

while (!WindowShouldClose()) {
  float dt = GetFrameTime();

  // Update
  switch (scene) {
    case SceneId::Title:
      if (IsKeyPressed(KEY_ENTER)) scene = SceneId::Game;
      break;
    case SceneId::Game:
      if (IsKeyPressed(KEY_P)) scene = SceneId::Pause;
      break;
    case SceneId::Pause:
      if (IsKeyPressed(KEY_P)) scene = SceneId::Game;
      break;
  }

  // Draw
  BeginDrawing();
  ClearBackground(RAYWHITE);
  switch (scene) {
    case SceneId::Title: DrawText("TITLE", 20, 20, 50, DARKGRAY); break;
    case SceneId::Game:  DrawText("GAME",  20, 20, 50, DARKGRAY); break;
    case SceneId::Pause: DrawText("PAUSE", 20, 20, 50, DARKGRAY); break;
  }
  EndDrawing();
}
```

장점: 가장 단순하고 빠름

단점: 씬이 커지면 파일/함수가 비대해짐

### 10.2 확장형: Scene 인터페이스(가벼운 OOP)

형태(개념):

- `OnEnter()` : 씬 진입 시 리소스 로드/초기화
- `Update(dt)` : 로직
- `Draw()` : 렌더
- `OnExit()` : 진출 시 리소스 해제

이렇게 하면 씬 단위로 리소스 수명이 딱 정리됩니다.

---

## 11) Tween(트윈) 애니메이션 적용 방법 ✨

Tween의 핵심은 “시간 기반 보간”입니다.

### 11.1 프레임 의존이 아니라 dt(델타 타임) 기반으로

현재 `main.cpp`는 `ballPosition += ballSpeed` 처럼 프레임당 픽셀로 움직입니다.
이 방식은 FPS가 바뀌면 속도가 달라질 수 있어요.

권장 패턴:
- `float dt = GetFrameTime();`
- `pos += velocity * dt;`  (velocity는 초당 단위)

### 11.2 최소 Tween 유틸(선형 보간)

```cpp
inline float Lerp(float a, float b, float t) {
  if (t < 0.0f) t = 0.0f;
  if (t > 1.0f) t = 1.0f;
  return a + (b - a) * t;
}

struct Tween1f {
  float from = 0.0f;
  float to = 0.0f;
  float duration = 1.0f;

  float elapsed = 0.0f;
  bool active = false;

  void Start(float f, float t, float d) {
    from = f;
    to = t;
    duration = (d <= 0.0f) ? 0.0001f : d;
    elapsed = 0.0f;
    active = true;
  }

  float Update(float dt) {
    if (!active) return to;
    elapsed += dt;
    float u = elapsed / duration;
    if (u >= 1.0f) { u = 1.0f; active = false; }
    return Lerp(from, to, u);
  }
};
```

사용 예(클릭하면 공 크기가 0.2초 동안 커졌다가 작아지게):

```cpp
Tween1f radiusTween;
float ballRadius = 20.0f;

// 클릭 시
radiusTween.Start(ballRadius, 40.0f, 0.2f);

// 매 프레임
ballRadius = radiusTween.Update(dt);
```

### 11.3 easing(가속/감속) 넣기

Linear는 기계적으로 보일 수 있습니다. 보통은 easing 함수를 t에 한 번 더 적용합니다.

```cpp
inline float EaseOutCubic(float t) {
  if (t < 0.0f) t = 0.0f;
  if (t > 1.0f) t = 1.0f;
  float inv = 1.0f - t;
  return 1.0f - inv*inv*inv;
}
```

그리고 `Lerp(from, to, EaseOutCubic(u))` 처럼 쓰면 됩니다.

---

## 12) (추천) 이 프로젝트에 바로 적용하면 좋은 개선점

현재 `main.cpp`의 공 이동을 “dt 기반”으로 바꾸면 네이티브/웹에서 체감이 더 일관됩니다.

- `ballSpeed`를 “초당 픽셀(px/s)”로 정의
- 업데이트는 `ballPosition += ballSpeed * dt` 형태

원하면 `main.cpp`를 Scene + tween 구조로 리팩터링한 버전도 바로 만들어줄게요.
