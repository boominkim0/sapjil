# 삽질 (Sapjil) 🚧

> **엄청난 삽질**을 각오하고 시작하는 2D 게임 엔진 코어 프로젝트

---

## 📖 프로젝트 소개

**삽질(Sapjil)** 은 C++로 제작되는 **2D 게임 엔진 코어(Game Engine Core)** 입니다.  
이 프로젝트는 [Phaser](https://phaser.io/)의 **Scene / Sprite / Update-Render 구조**를 참고하되,  
모바일·데스크탑·웹 환경에서 재사용 가능한 **그래픽 표현과 게임 연산에만 집중한 엔진**을 목표로 합니다.

> ⚠️ 삽질은 **입력(Input), 네트워크(Network), 파일 IO, 플랫폼 API를 포함하지 않습니다.**  
> 이 엔진은 **게임 세계의 계산과 그리기 명령 생성**만을 담당합니다.

---

## 🧠 설계 철학 (중요)

삽질은 **"모든 걸 다 하는 엔진"** 이 아니라,

> **"게임 상태를 계산하고, 그 결과를 빠르게 그리는 엔진"**

를 지향합니다.

따라서 다음과 같은 역할 분리가 전제됩니다:

```
[플랫폼 레이어]
- 터치 / 마우스 / 키보드 입력
- 네트워크 (HTTP, preload)
- 파일 시스템, OS 기능

[삽질 엔진]
- Scene / GameObject 관리
- Sprite / Animation
- Physics / Collision
- Game Loop (update + render)
- Draw Command 생성
```

이 구조는 **iOS, Android, macOS, Windows, HTML5** 등 어떤 플랫폼과도 결합 가능한 엔진 코어를 만드는 것을 목표로 합니다.

---

## 🎮 이 프로젝트는 게임 엔진인가?

**예.**  
입력과 네트워크가 없어도 다음 조건을 만족하면 **게임 엔진**입니다:

- 시간에 따라 변하는 게임 상태를 계산하고
- 그 결과를 화면에 렌더링한다

```
state(t)
  ↓ update(dt)
state(t+1)
  ↓ render()
pixels
```

삽질은 이 **엔진의 최소 본질**에 집중합니다.

---

## 🎯 프로젝트 목표

- **엔진 코어 분리**
  - 플랫폼에 종속되지 않는 2D 게임 엔진 코어 구현

- **고성능 그래픽 표현**
  - CPU 연산과 GPU 렌더링에 집중한 구조
  - 불필요한 플랫폼 오버헤드 제거

- **Phaser 스타일 API 재해석**
  - Scene / Object / Update 흐름을 C++로 재구성

- **학습과 실험**
  - 렌더링 파이프라인, 게임 루프, 엔진 구조에 대한 깊은 이해

---

## 🛠️ 기술 스택

- **언어**: C++
- **그래픽 라이브러리**: [raylib](https://github.com/raysan5/raylib) (PC / Web 전용)
- **참고 엔진**: Phaser 3

> raylib은 플랫폼 윈도우 생성 및 기본 렌더링 백엔드로 사용되며,  
> 삽질 엔진의 구조적 개념과는 분리됩니다.

---

## 🧩 엔진이 제공하는 것 / 제공하지 않는 것

### ✅ 제공

- Scene / World 관리
- Sprite / Transform
- Animation / Tween
- Physics / Collision (예정)
- Game Loop (update / render)
- Draw Command 생성

### ❌ 제공하지 않음

- 터치 / 키보드 / 마우스 입력 처리
- 네트워크 (HTTP, preload, fetch)
- 파일 IO / Asset 다운로드
- 플랫폼 API

> 위 기능들은 **엔진 외부(iOS, Android, Web 등)** 에서 처리한 뒤  
> **데이터와 이벤트 형태로 삽질 엔진에 전달**하는 구조를 전제로 합니다.

---

## 🧩 의존성(중요)

이 프로젝트는 **raylib을 레포에 포함하지 않습니다.**  
대신 **각자 환경에 설치된 raylib 라이브러리**를 링크해서 빌드합니다.

- ✅ 레포에 `raylib/` 폴더가 없어도 빌드 가능 (시스템에 raylib이 설치되어 있다면)
- ❌ raylib “없이” 동작하는 것은 아님 (실행 파일은 raylib에 의존)

> 참고: `otool -L ./game`(macOS) / `ldd ./game`(Linux)로 raylib 링크 여부를 확인할 수 있습니다.

---

## 🚀 빌드 방법

아래 커맨드들은 **예시**이며, 환경에 따라 include/lib 경로가 다를 수 있습니다.  
가장 쉬운 방법은 **패키지 매니저로 raylib을 설치**하는 것입니다.

### 1) raylib 설치

#### macOS (Homebrew)
```bash
brew install raylib
```

#### Linux
- Arch:
```bash
sudo pacman -S raylib
```

- Ubuntu/Debian 계열: 배포판에 `raylib` 패키지가 없을 수 있어, 이 경우 raylib을 소스에서 설치하거나(vcpkg/빌드) 아래 “CMake 사용” 방식으로 전환하는 것을 권장합니다.

#### Windows
- 권장: **vcpkg**로 설치
```powershell
vcpkg install raylib
```

---

### 2) 네이티브 빌드 (clang++ 예시)

#### macOS (Homebrew 경로 기준)
```bash
clang++ main.cpp core/*.cpp examples/testGameObjects/*.cpp -o game \
-I. -I/opt/homebrew/include \
-L/opt/homebrew/lib \
-framework CoreVideo -framework IOKit -framework Cocoa \
-framework OpenGL -lraylib
```

> Intel Mac(Homebrew가 /usr/local 인 경우): `-I/usr/local/include -L/usr/local/lib` 로 바꿔야 합니다.

#### Linux (설치 경로가 표준(/usr)인 경우가 많음)
```bash
clang++ main.cpp core/*.cpp examples/testGameObjects/*.cpp -o game \
-I. \
-lraylib -lm -ldl -lpthread
```

> 배포판/설치 방식에 따라 추가 링크 옵션이 필요할 수 있습니다.

---

### 3) 웹 빌드 (Emscripten)

⚠️ 웹 빌드는 **시스템에 설치된 raylib(Homebrew 등)** 을 쓰는 게 아니라,  
**raylib 소스를 Emscripten으로 웹용(wasm)으로 직접 빌드한 정적 라이브러리(libraylib.a)** 를 링크해야 합니다.

#### 3-1) raylib 소스 준비 (submodule 권장)
```bash
git submodule add https://github.com/raysan5/raylib external/raylib
git submodule update --init --recursive
```

#### 3-2) raylib을 웹용으로 빌드 (libraylib.a 생성)
```bash
cd external/raylib/src
emmake make clean
emmake make PLATFORM=PLATFORM_WEB -B
cd ../../../
```

생성 확인:
```bash
ls -la external/raylib/src/libraylib.web.a
```

#### 3-3) 프로젝트 웹 빌드
```bash
mkdir -p build/html

emcc main.cpp core/*.cpp examples/testGameObjects/*.cpp \
  -o build/html/index.html \
  -I. -Iexternal/raylib/src \
  external/raylib/src/libraylib.web.a \
  -s USE_GLFW=3 -s ASYNCIFY \
  --preload-file logo.png
```

---

## ▶️ 실행

### 네이티브(현재 README의 `clang++ -o game` 빌드 기준)

- macOS / Linux:

```bash
./game
```

- Windows (PowerShell):

```powershell
./game.exe
```

### 웹(Emscripten)

웹 빌드 결과물은 실행 파일이 아니라 `build/html/index.html` 입니다.

```bash
python3 -m http.server --directory build/html 8000
```

그 다음 브라우저에서 `http://localhost:8000/` 를 열면 됩니다.
---

## 📋 현재 상태

🚧 **개발 초기 단계**  
- 엔진 구조 설계 및 기본 루프 구현 중  
- 활발한 삽질 진행 중

---

## 📝 라이선스

TBD

---

## 🤝 기여

현재는 개인 학습 및 연구 목적의 프로젝트로 진행 중입니다.

---

> "삽질 없이는 아무것도 이룰 수 없다"  
> — Sapjil Project Motto

## AI 사용 안내

이 프로젝트는 **AI 기반 개발을 위한 엄격한 제약 조건**을 포함하고 있습니다.

Copilot, Cursor, ChatGPT 등 어떤 AI 도구를 사용하든  
작업을 시작하기 전에 반드시 아래 문서를 읽고 그 규칙을 따라야 합니다.

👉 [AI_ENGINE_CONSTRAINTS.md](AI_ENGINE_CONSTRAINTS.md)