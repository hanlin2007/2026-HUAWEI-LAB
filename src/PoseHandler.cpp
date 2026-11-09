#include "PoseHandler.hpp"
namespace adas {
PoseHandler::PoseHandler(const Pose& pose) noexcept
    : point(pose.x, pose.y), direction(&Direction::GetDirection(pose.heading)) {}
Pose PoseHandler::Query() const noexcept { return {point.GetX(), point.GetY(), direction->GetHeading()}; }
void PoseHandler::Forward() noexcept { point += direction->Move(); }
void PoseHandler::Backward() noexcept { point -= direction->Move(); }
void PoseHandler::Move() noexcept {
    if (IsReverse()) { Backward(); }
    else { Forward(); }
}
void PoseHandler::TurnLeft() noexcept { direction = &direction->LeftOne(); }
void PoseHandler::TurnRight() noexcept { direction = &direction->RightOne(); }
void PoseHandler::Fast() noexcept { fast = !fast; }
bool PoseHandler::IsFast() const noexcept { return fast; }
void PoseHandler::Reverse() noexcept { reverse = !reverse; }
bool PoseHandler::IsReverse() const noexcept { return reverse; }
} // namespace adas
