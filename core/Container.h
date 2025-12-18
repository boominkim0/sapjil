#pragma once

#include "GameObject.h"
#include <vector>
#include <memory>

class Container : public GameObject {
private:
    std::vector<std::unique_ptr<GameObject>> children;

public:
    Container();
    ~Container() override = default;

    // 자식 관리
    void AddChild(std::unique_ptr<GameObject> child);
    void RemoveChild(GameObject* child);
    void ClearChildren();

    // 자식 접근
    GameObject* GetChild(size_t index) const;
    size_t GetChildCount() const { return children.size(); }

    // 재정의된 메서드들
    void Update(float deltaTime) override;
    void Render() const override;
    Rectangle GetBounds() const override;

    // 컨테이너 특성 메서드
    void SetPosition(float x, float y);
    void SetPosition(const Vector2& pos);
    void SetRotation(float rot);
    void SetScale(float x, float y);
    void SetScale(const Vector2& s);
};