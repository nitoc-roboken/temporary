#include <stdio.h>
#include <math.h>

#define NOW_TIME (0)

class Motor
{
private:
public:
    Motor(int a)
    {
    }

    void angle_reset(void)
    {
    }

    float get_angle(void)
    {
        return 0;
    }

    void set_power(float pw)
    {
    }
};

void wait(float sec)
{

}

float get_gyro_accel(void)
{
    return 0;
}

Motor mot_a(1);
Motor mot_d(2);

float fall_check_start_time;
float motor_position_sum;
float wheel_angle;
float change_in_motor_position;
float change_in_motor_position1;
float change_in_motor_position2;
float change_in_motor_position3;
float drive_speed;
int control_loop_count;
bool ok;
float robot_body_angle;

float gyro_minimum_rate;
float gyro_maximum_rate;
float gyro_sensor_value;
float gyro_sum;
float gyro_offset;

float steering;
float output_power;
float left_output_power;
float right_output_power;

int control_loop_period;
int control_loop_start_time;


void reset_sensors_and_variables(void)
{
    mot_a.reset();
    mot_d.reset();

    fall_check_start_time = NOW_TIME;
    motor_position_sum = 0;
    wheel_angle = 0;
    change_in_motor_position = 0;
    change_in_motor_position1 = 0;
    change_in_motor_position2 = 0;
    change_in_motor_position3 = 0;
    drive_speed = 0;
    control_loop_count = 0;
    ok = true;
    robot_body_angle = -0.25;
}


void calibrate_gyro_offset(void)
{
    gyro_minimum_rate = 0;
    gyro_maximum_rate = 2;

    while((gyro_maximum_rate - gyro_minimum_rate) < 2)
    {
        gyro_minimum_rate = 440;
        gyro_maximum_rate = -440;
        for(size_t i = 0; i < 200; i++)
        {
            gyro_sensor_value = get_gyro_accel();
            gyro_sum += gyro_sensor_value;
            if(gyro_maximum_rate < gyro_sensor_value)
            {
                gyro_maximum_rate = gyro_sensor_value;
            }
            if(gyro_sensor_value < gyro_minimum_rate)
            {
                gyro_minimum_rate = gyro_sensor_value;
            }
            wait(0.004);
        }
    }

    gyro_offset = gyro_sum / 200;
}


void drive_motors(void)
{
    left_output_power = output_power - (0.1 * steering);
    right_output_power = output_power + (0.1 * steering);
    mot_d.set_power(left_output_power);
    mot_a.set_power(right_output_power);
}

void check_if_robot_fell_down(void)
{
    if(absf(output_power) < 100)
    {
        fall_check_start_time = NOW_TIME;
    }

    if(1 < (NOW_TIME - fall_check_start_time)
    {
        ok = false;
    }
}

void calculate_control_loop_period(void)
{
    if(control_loop_count == 0)
    {
        control_loop_period = 0.014;
        control_loop_start_time = NOW_TIME;
    }else{
        control_loop_period = (NOW_TIME - control_loop_start_time) / control_loop_count;
    }
    control_loop_count = 1;
}

void calculate_robot_body_angle_and_speed(void)
{
    
}


int main(void)
{

}