# Game 클래스 설계 문서

## 개요
`Game` 클래스는 게임의 전체적인 시스템을 총괄하는 역할을 담당합니다. 이 클래스는 게임 실행에 필요한 다양한 설정값을 초기화하고, 여러 시스템(Scene, Sound 등)을 관리합니다. 게임의 핵심적인 동작을 제어합니다.

---

## 주요 기능

### 1. 초기화 및 설정
- **FPS 값**: 게임의 프레임 속도를 설정합니다.
- **디바이스 사이즈**: 디바이스의 화면 크기를 설정합니다.
- **반응형 여부**: 반응형 레이아웃을 사용할지 여부를 설정합니다.
- **캔버스 사이즈**: 실제 렌더링에 사용될 캔버스의 크기를 정의합니다.
- **Sound 및 Plugin 설정**: 사용할 사운드 시스템과 플러그인을 정의합니다.

### 2. Scene 관리
- 여러 Scene을 등록하고 관리하는 기능을 제공합니다.
- Scene은 중복으로 존재할 수 있습니다.
- Scene의 위치와 크기는 조정할 수 없으며, 이는 Scene 내부의 카메라를 통해 제어됩니다.

### 3. 게임 시스템 정의
- 물리 엔진 사용 여부를 판단합니다.
- 충돌 처리와 애니메이션은 각 Scene에서 관리됩니다.

---

## 클래스 설계

### 파라미터
다음과 같은 설정값들을 전달받습니다:

- `fps`: 게임의 목표 프레임 속도
- `deviceWidth`, `deviceHeight`: 디바이스 화면 크기
- `responsive`: 반응형 여부

### 생성자

- `fps`: 게임의 목표 프레임 속도
- `responsive`: 반응형 여부
- `canvasWidth`, `canvasHeight`: 캔버스 크기
- `sceneList`: 등록된 Scene들의 리스트
- `soundConfig`: 사운드 시스템 설정
- `plugins`: 사용할 플러그인 목록

### 주요 메서드

#### 1. `initialize()`
- 게임의 초기 설정값을 기반으로 시스템을 초기화합니다.

#### 2. `openScene(sceneId)`
- 지정된 Scene을 활성화하고 실행합니다.

#### 3. `closeScene(sceneId)`
- 지정된 Scene을 비활성화하고 종료합니다.

#### 4. `pause()`
- 게임을 일시 정지합니다.

#### 5. `resume()`
- 일시 정지된 게임을 다시 시작합니다.

#### 6. `getFrame()`
- 현재 프레임 번호를 반환합니다.

---

## 예제 코드

```cpp
#include "Game.h"

int main() {
    // Game 초기화
    Game game(60, 1920, 1080, true, 1280, 720, soundConfig, plugins);

    // Scene 열기
    game.openScene("MainMenu");

    // 게임 루프
    while (true) {
        float deltaTime = calculateDeltaTime();
        // 게임 시스템 업데이트 및 렌더링은 각 Scene에서 처리

        // 현재 프레임 번호 출력
        int currentFrame = game.getFrame();
        std::cout << "Current Frame: " << currentFrame << std::endl;

        // 예제: 게임 일시 정지 및 재개
        if (shouldPause()) {
            game.pause();
        }
        if (shouldResume()) {
            game.resume();
        }
    }

    // Scene 닫기
    game.closeScene("MainMenu");

    return 0;
}
```

---

## 결론
`Game` 클래스는 게임의 핵심적인 시스템을 총괄하며, 다양한 설정값과 시스템을 관리합니다. 이 클래스는 플랫폼 독립적으로 설계되어, 다양한 환경에서 재사용 가능하도록 구현됩니다.