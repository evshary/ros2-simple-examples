#include <chrono>
#include <thread>

#include "rclcpp/rclcpp.hpp"

class TimerToggleNode : public rclcpp::Node
{
public:
    TimerToggleNode()
        : Node("timer_toggle_node"), timer_ab_enabled_(true)
    {
        timer_a_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        timer_b_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        timer_c_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        timer_a_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&TimerToggleNode::on_timer_a, this),
            timer_a_group_);
        timer_a_->reset();

        timer_b_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&TimerToggleNode::on_timer_b, this),
            timer_b_group_);
        timer_b_->reset();

        timer_c_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),
            std::bind(&TimerToggleNode::on_timer_c, this),
            timer_c_group_);
    }

private:
    void on_timer_a()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        RCLCPP_INFO(this->get_logger(), "Timer a: Data received");
    }

    void on_timer_b()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        RCLCPP_INFO(this->get_logger(), "Timer b: Data received");
    }

    void on_timer_c()
    {
        if (timer_ab_enabled_)
        {
            timer_a_->cancel();  // Stop timer_a
            timer_b_->cancel();  // Stop timer_b
            RCLCPP_INFO(this->get_logger(), "Timer A disabled");
            RCLCPP_INFO(this->get_logger(), "Timer B disabled");
        }
        else
        {
            timer_a_->reset();  // Restart timer_a
            timer_b_->reset();  // Restart timer_b
            RCLCPP_INFO(this->get_logger(), "Timer A enabled");
            RCLCPP_INFO(this->get_logger(), "Timer B enabled");
        }
        timer_ab_enabled_ = !timer_ab_enabled_;
    }

    rclcpp::TimerBase::SharedPtr timer_a_;
    rclcpp::TimerBase::SharedPtr timer_b_;
    rclcpp::TimerBase::SharedPtr timer_c_;
    bool timer_ab_enabled_;

    rclcpp::CallbackGroup::SharedPtr timer_a_group_;
    rclcpp::CallbackGroup::SharedPtr timer_b_group_;
    rclcpp::CallbackGroup::SharedPtr timer_c_group_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TimerToggleNode>();

    rclcpp::ExecutorOptions options;
    rclcpp::executors::MultiThreadedExecutor executor(options, 10);
    executor.add_node(node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
