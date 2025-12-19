# 📌 프로젝트 지침서 (Copilot에게 그대로 읽히는 용도)

## 1. 프로젝트 목표
이 프로젝트의 목표는 **플랫폼 독립적인 C++ 게임 엔진 코어**를 만들고,
이를 **iOS, macOS, Windows, Android, HTML5 앱에서 라이브러리 형태로 사용**하는 것이다.

- 엔진은 **C++로만 작성**한다
- 각 플랫폼 앱은 **플랫폼에 맞는 기술 스택**을 사용한다 (예: iOS는 Swift + Metal/UIKit, HTML5는 WebGL 등)
- 엔진은 **렌더링, OS, 플랫폼 API를 절대 직접 호출하지 않는다**

엔진은 오직 **게임 로직, 상태 관리, 수학 계산**만 담당한다.

---

## 2. 절대 하지 말아야 할 것 (중요)

다음은 **엔진 코드에서 금지 사항**이다:

- OpenGL / OpenGL ES / Metal 호출
- raylib, SDL, UIKit, Android API 포함
- 파일 시스템, 네트워크, 스레드 직접 접근
- 플랫폼 분기 코드 (`#ifdef IOS` 같은 것)

엔진은 **순수 C++ 라이브러리**여야 한다.

---

## 3. 엔진 설계 원칙

### 3.1 엔진 역할
엔진은 다음만 책임진다:

- 게임 상태 초기화
- 프레임 단위 업데이트
- 물리 / 충돌 / 수학 계산
- 입력 이벤트 처리 (좌표 값만 받음)

### 3.2 엔진이 하지 않는 것

- 실제 화면에 그림 그리기
- 사운드 재생
- 터치 이벤트 직접 처리
- 앱 생명주기 관리

---

## 4. 외부와의 통신 규칙 (C API)

엔진은 **C API로만 외부와 통신**한다.
Swift / Flutter / Kotlin / JavaScript에서 직접 호출 가능해야 한다.

### 4.1 엔진 외부 인터페이스 예시

```cpp
#ifdef __cplusplus
extern "C" {
#endif

void engine_init(int width, int height);
void engine_update(float deltaTime);
void engine_onTouch(float x, float y);

#ifdef __cplusplus
}
#endif
```

- 모든 함수는 `extern "C"` 사용
- 클래스, 템플릿, STL 타입을 외부로 노출하지 않는다

---

## 5. Draw Command 설계 규칙

---

## 6. 플랫폼 연동 전제

### 6.1 빌드 결과물

엔진은 다음 형태로 제공된다:

- `libengine.a` (static library)
- `engine.h` (C API 헤더)

### 6.2 각 플랫폼 앱에서의 역할

각 플랫폼 앱은 다음을 담당한다:

- 입력 이벤트 수집 (터치, 키보드 등)
- 화면 크기 전달
- 프레임 루프 관리 (예: CADisplayLink, game loop 등)
- Draw Command를 플랫폼에 맞는 렌더링 기술로 렌더링

엔진은 플랫폼 존재 자체를 모른다.

---

## 7. raylib 사용 규칙

- raylib은 **엔진 코어에 포함하지 않는다**
- raylib은 **PC / Web 전용 렌더러 구현체**로만 사용 가능

구조 예시:

```
engine_core/
renderer_raylib/   (PC, Web)
renderer_metal/    (iOS)
renderer_vulkan/   (Android)
```

---

## 8. Copilot 작업 지침 (중요)

Copilot은 다음 원칙을 반드시 지켜야 한다:

- 엔진 코드는 항상 플랫폼 독립적으로 작성할 것
- 플랫폼 관련 코드는 제안하지 말 것 (예: Metal, UIKit, WebGL 등)
- 렌더링 코드를 엔진에 추가하지 말 것
- C API 외부 인터페이스를 변경할 경우 명확히 설명할 것

Copilot은 **"엔진 개발자" 역할**만 수행한다.

---

## 9. 코드 스타일

- C++17 기준
- 헤더/구현 분리
- 전역 변수 최소화
- 명확한 네이밍 사용

---

## 10. 요약

이 프로젝트는:

- C++ 엔진 코어와
- 각 플랫폼 앱을
- 완전히 분리한다

엔진은 **라이브러리**, 각 플랫폼 앱은 **껍데기**다.

Copilot은 이 구조를 절대 벗어나지 말 것.

