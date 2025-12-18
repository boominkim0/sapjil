#include "Container.h"

Container::Container() : GameObject() {
}

void Container::AddChild(std::unique_ptr<GameObject> child) {
    if (child) {
        children.push_back(std::move(child));
    }
}

void Container::RemoveChild(GameObject* child) {
    auto it = std::find_if(children.begin(), children.end(),
        [child](const std::unique_ptr<GameObject>& ptr) {
            return ptr.get() == child;
        });

    if (it != children.end()) {
        children.erase(it);
    }
}

void Container::ClearChildren() {
    children.clear();
}

GameObject* Container::GetChild(size_t index) const {
    if (index < children.size()) {
        return children[index].get();
    }
    return nullptr;
}

void Container::Update(float deltaTime) {
    if (!visible) return;

    // 자신의 업데이트
    GameObject::Update(deltaTime);

    // 자식들 업데이트
    for (auto& child : children) {
        child->Update(deltaTime);
    }
}

void Container::Render() const {
    if (!visible) return;

    // 자식들 렌더링 (부모 변환 적용)
    for (const auto& child : children) {
        if (child->IsVisible()) {
            // 부모 변환을 적용하기 위해 rlgl을 사용
            rlPushMatrix();
            rlMultMatrixf(MatrixToFloat(GetTransformMatrix()));
            child->Render();
            rlPopMatrix();
        }
    }
}

Rectangle Container::GetBounds() const {
    if (children.empty()) {
        return {position.x, position.y, 0, 0};
    }

    Rectangle bounds = children[0]->GetBounds();
    for (size_t i = 1; i < children.size(); ++i) {
        Rectangle childBounds = children[i]->GetBounds();
        bounds = {
            std::min(bounds.x, childBounds.x),
            std::min(bounds.y, childBounds.y),
            std::max(bounds.x + bounds.width, childBounds.x + childBounds.width) - std::min(bounds.x, childBounds.x),
            std::max(bounds.y + bounds.height, childBounds.y + childBounds.height) - std::min(bounds.y, childBounds.y)
        };
    }

    return bounds;
}

void Container::SetPosition(float x, float y) {
    Vector2 oldPos = position;
    GameObject::SetPosition(x, y);

    // 자식들의 상대 위치 유지
    Vector2 delta = {x - oldPos.x, y - oldPos.y};
    for (auto& child : children) {
        Vector2 childPos = child->GetPosition();
        child->SetPosition(childPos.x + delta.x, childPos.y + delta.y);
    }
}

void Container::SetPosition(const Vector2& pos) {
    SetPosition(pos.x, pos.y);
}

void Container::SetRotation(float rot) {
    // 회전은 자식들에게도 적용되므로 별도 처리
    GameObject::SetRotation(rot);
}

void Container::SetScale(float x, float y) {
    // 스케일도 자식들에게 적용
    GameObject::SetScale(x, y);
}

void Container::SetScale(const Vector2& s) {
    SetScale(s.x, s.y);
}