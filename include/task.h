#ifndef _TASK_H_
#define _TASK_H_

#include <cstring>
#include <ctime>
#include <exception>
#include <stdexcept>
#include <string>

class task
{
public:
    task()
    {
        time(&_dt_create);

        _id = std::to_string(_dt_create);
    }

    task(const task& src)
    {
        this->_id = src._id;
        this->_subject = src._subject;
        this->_discription = src._discription;
        this->_dt_create = src._dt_create;
        this->_dt_finish = src._dt_finish;
        this->_finish = src._finish;
    }

    task& operator= (const task& src)
    {
        if( this != &src ){
            this->_id = src._id;
            this->_subject = src._subject;
            this->_discription = src._discription;
            this->_dt_create = src._dt_create;
            this->_dt_finish = src._dt_finish;
            this->_finish = src._finish;
        }

        return *this;
    }

public:
    void reopen()
    {
        _dt_finish = 0;
        _finish = false;
    }
    void finish() 
    {
        time(&_dt_finish);
        _finish = true;
    }
    bool had_finish() const 
    {
        return _finish;
    }
    time_t finish_time_t() const
    {
        return _dt_finish;
    }
    std::string finish_datetime() const
    {
        return dt_to_strimg(_dt_finish);
    }

    time_t create_time_t() const
    {
        return _dt_create;
    }
    std::string create_datetime() const 
    {
        return dt_to_strimg(_dt_create);
    }

    void subject(const std::string& sub)
    {
        _subject = sub;
    }

    std::string subject() const
    {
        return _subject;
    }

    void discription(const std::string& disc) throw(std::logic_error)
    {
        if( disc.empty() )
            throw std::logic_error("empty discription!");

        _discription = disc;
    }
    std::string discription() const 
    {
        return _discription;
    }

    std::string id() const
    {
        return _id;
    }

private:
    std::string dt_to_strimg(time_t time_val) const
    {
        struct tm *dt_tm = localtime(&time_val);

        char dt_buffer[64] = {0};
        strftime(dt_buffer, sizeof(dt_buffer), "%A %D %X", dt_tm);

        return dt_buffer;
    }

private:
    std::string _id;
    std::string _subject;
    std::string _discription;
    time_t _dt_create;
    time_t _dt_finish = 0;

    bool _finish = false;
};

#endif
