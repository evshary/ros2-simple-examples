#include <chrono>
#include <thread>

#include "rclcpp/rclcpp.hpp"

class TimerToggleNode : public rclcpp::Node
{
public:
    TimerToggleNode()
        : Node("timer_toggle_node"), timer_enabled_(false)
    {
        timer_toggle_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        timer_toggle_ = this->create_wall_timer(
            std::chrono::milliseconds(1000),
            std::bind(&TimerToggleNode::timer_toggle_callback, this),
            timer_toggle_group_);
    }

private:
    void timer_node_callback()
    {
        // Make the callback run most of the time
        std::this_thread::sleep_for(std::chrono::milliseconds(190));
        std::cout << "Timer Callback is triggered at thread " << std::this_thread::get_id() << std::endl;
    }

    void timer_toggle_callback()
    {
        std::cout << "Timer Toggle is set to " << timer_enabled_ << " at thread " << std::this_thread::get_id() << std::endl;
        if (timer_enabled_)
        {
            // Stop the timer
            timer_node_->cancel();
            // Release the timer
            timer_node_ = nullptr;
            timer_node_group_ = nullptr;

            RCLCPP_INFO(this->get_logger(), "Timer Node disabled");
        }
        else
        {
            timer_node_group_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            timer_node_ = this->create_wall_timer(
                std::chrono::milliseconds(200),
                std::bind(&TimerToggleNode::timer_node_callback, this),
                timer_node_group_);
            timer_node_->reset();

            RCLCPP_INFO(this->get_logger(), "Timer Node enabled");
        }
        timer_enabled_ = !timer_enabled_;
    }

    rclcpp::TimerBase::SharedPtr timer_node_;
    rclcpp::TimerBase::SharedPtr timer_toggle_;
    bool timer_enabled_;

    rclcpp::CallbackGroup::SharedPtr timer_node_group_;
    rclcpp::CallbackGroup::SharedPtr timer_toggle_group_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TimerToggleNode>();

    rclcpp::ExecutorOptions options;
    // Run with 2 threads
    rclcpp::executors::MultiThreadedExecutor executor(options, 2);
    //rclcpp::executors::SingleThreadedExecutor executor(options);
    executor.add_node(node);
    executor.spin();

    rclcpp::shutdown();
    return 0;
}
