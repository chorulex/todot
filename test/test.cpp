#include <cassert>
#include <cstdio>
#include <iostream>
#include "task.h"

static unsigned int test_count = 0;

#define SETUP();\
    std::cout << "=================================================" << std::endl;\
    std::cout << "test " << ++test_count << "\t" << __FUNCTION__ << std::endl;

#define WRAP(); std::cout << "=================================================" << std::endl;

void test_create_empty_task()
{
    SETUP();
    task new_task;
    WRAP();
}

void test_create_valid_task()
{
    SETUP();
    task new_task;
    new_task.discription("this is a test task.");
    WRAP();
}

void test_set_empty_disc_task()
{
    SETUP();
    task new_task;

    try{
        new_task.discription("");
    }
    catch(std::logic_error ex)
    {
        assert(strcmp(ex.what(),"empty discription!") == 0 );
        return;
    }

    assert(false);
    WRAP();
}

void test_get_disc_after_create_task()
{
    SETUP();
    std::string disc("this is a test task.");

    task new_task;
    new_task.discription(disc);

    const std::string& disc_got = new_task.discription();
    assert( disc_got == disc );
    WRAP();
}

void test_get_create_dt_after_create_task()
{
    SETUP();
    task new_task;
    time_t cre_dt_t = new_task.create_time_t();

    struct tm *dt_tm = localtime(&cre_dt_t);
    char dt_buffer[64] = {0};
    strftime(dt_buffer, sizeof(dt_buffer), "%A %D %X", dt_tm);

    const std::string& dt_str = new_task.create_datetime();
    assert( dt_str == dt_buffer );

    std::cout << "Create datetime:"<< dt_str << std::endl;
    WRAP();
}

void test_finish()
{
    SETUP();
    std::string disc("this is a test task.");

    task new_task;
    new_task.discription(disc);

    assert(!new_task.had_finish());
    assert(new_task.finish_time_t() == 0);

    new_task.finish();
    assert(new_task.had_finish());

    time_t cre_dt_t = new_task.finish_time_t();
    struct tm *dt_tm = localtime(&cre_dt_t);
    char dt_buffer[64] = {0};
    strftime(dt_buffer, sizeof(dt_buffer), "%A %D %X", dt_tm);

    const std::string& dt_str = new_task.finish_datetime();
    assert( dt_str == dt_buffer );

    std::cout << "Create datetime:"<< new_task.create_datetime() << std::endl;
    std::cout << "Finish datetime:"<< new_task.finish_datetime() << std::endl;

    WRAP();
}

void test_reopen()
{
    SETUP();
    std::string disc("this is a test task.");

    task new_task;
    new_task.discription(disc);

    new_task.finish();
    assert(new_task.had_finish());
    std::cout << "Finish datetime:"<< new_task.finish_datetime() << std::endl;

    std::cout << "Reopen!" << std::endl;

    new_task.reopen();
    assert(!new_task.had_finish());
    assert(new_task.finish_time_t() == 0);

    new_task.finish();
    std::cout << "Finish datetime:"<< new_task.finish_datetime() << std::endl;

    WRAP();
}

void test_subject()
{
    SETUP();
    std::string disc("this is a test task.");
    std::string subject("test");

    task new_task;
    new_task.subject(subject);

    assert( new_task.subject() == subject );

    WRAP();
}
void test_main()
{
    test_create_empty_task();
    test_create_valid_task();
    test_set_empty_disc_task();
    test_get_disc_after_create_task();
    test_get_create_dt_after_create_task();
    test_subject();

    test_finish();
    test_reopen();
}

