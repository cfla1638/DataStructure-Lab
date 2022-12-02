#include "libman.h"

namespace {
    /**
     * @brief ���ַ�����ʽ��ʱ��ת��Ϊtime_t
     * @param str ʱ�䣬����20221201194830
     * @return time_t 
     */
    time_t string_to_time_t(const std::string &str)
    {
        tm tm_;                                    // ����tm�ṹ�塣
        int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
        year = atoi((str.substr(0, 4)).c_str());
        month = atoi((str.substr(4, 2)).c_str());
        day = atoi((str.substr(6, 2)).c_str());
        hour = atoi((str.substr(8, 2)).c_str());
        minute = atoi((str.substr(10, 2)).c_str());
        second = atoi((str.substr(12, 2)).c_str());

        tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��      
        tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
        tm_.tm_mday = day;                         // �ա�
        tm_.tm_hour = hour;                        // ʱ��
        tm_.tm_min = minute;                       // �֡�
        tm_.tm_sec = second;                       // �롣
        tm_.tm_isdst = 0;                          // ������ʱ��
        time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
        return t_;                                 // ����ֵ��
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
