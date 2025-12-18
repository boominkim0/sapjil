# 삽질 (Sapjil) 🚧

> **엄청난 삽질**을 각오하고 시작하는 2D 게임 엔진 프로젝트

## 📖 프로젝트 소개

**삽질**은 C++로 제작되는 2D 게임 엔진입니다. [Phaser](https://phaser.io/) 게임 엔진을 참고하여 설계되며, [raylib](https://www.raylib.com/) 라이브러리를 활용하여 GUI와 빌드 산출물을 생성합니다.

## 🎯 프로젝트 목표

- **극한의 최적화**: 저사양 디바이스에서도 원활하게 작동하는 경량 게임 엔진
- **크로스 플랫폼**: 다양한 플랫폼(Windows, macOS, Linux, Web 등)에서 실행 가능
- **간편한 개발 환경**: raylib 기반의 직관적인 GUI와 개발 도구 제공

## 🛠️ 기술 스택

- **언어**: C++
- **그래픽 라이브러리**: [raylib](https://github.com/raysan5/raylib)
- **참고 엔진**: Phaser

## 🚀 빌드 방법

### macOS (네이티브 빌드)

```bash
clang++ main.cpp -o game -I/opt/homebrew/include -L/opt/homebrew/lib \
-framework CoreVideo -framework IOKit -framework Cocoa \
-framework GLUT -framework OpenGL -lraylib
```

### 웹 빌드 (Emscripten)

```bash
emcc main.cpp -o index.html -Iraylib/src -Lraylib/build/raylib \
-lraylib -s USE_GLFW=3 -s ASYNCIFY
```

### 실행

```bash
./game
```

## 📋 현재 상태

🚧 **개발 초기 단계** - 활발한 삽질 진행 중

## 📝 라이선스

TBD

## 🤝 기여

현재는 개인 프로젝트로 진행 중입니다.

---

*"삽질 없이는 아무것도 이룰 수 없다" - 프로젝트 모토*