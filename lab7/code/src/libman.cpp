#include "libman.h"

namespace {
    /**
     * @brief 将字符串格式的时间转换为time_t
     * @param str 时间，例：20221201194830
     * @return time_t 
     */
    time_t string_to_time_t(const std::string &str)
    {
        tm tm_;                                    // 定义tm结构体。
        int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
        year = atoi((str.substr(0, 4)).c_str());
        month = atoi((str.substr(4, 2)).c_str());
        day = atoi((str.substr(6, 2)).c_str());
        hour = atoi((str.substr(8, 2)).c_str());
        minute = atoi((str.substr(10, 2)).c_str());
        second = atoi((str.substr(12, 2)).c_str());

        tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。      
        tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
        tm_.tm_mday = day;                         // 日。
        tm_.tm_hour = hour;                        // 时。
        tm_.tm_min = minute;                       // 分。
        tm_.tm_sec = second;                       // 秒。
        tm_.tm_isdst = 0;                          // 非夏令时。
        time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
        return t_;                                 // 返回值。
    }
}


libman_system::libman_system()
{

}

libman_system::~libman_system()
{

}

void libman_system::warehouse(std::string isbn, int count)
{
        
}

void libman_system::borrow(std::string borrower, std::string isbn, std::string deadline)
{

}

void libman_system::Rentrn(std::string isbn)
{

}

void libman_system::Delete(std::string isbn)
{

}
