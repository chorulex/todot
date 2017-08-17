#ifndef _TASK_CACHE_H_
#define _TASK_CACHE_H_

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "task.h"

class task_cache
{
public:
    bool load();

    std::size_t task_count() const
    {
        return _task_map_list.size();
    }

    std::shared_ptr<task> query_by_id(const std::string& task_id)
    {
        if( exist_task(task_id) )
            return std::make_shared<task>(_task_map_list[task_id]);

        return nullptr;
    }

    std::vector<task> query_by_subject(const std::string& subject)
    {
        std::vector<task> result;

        for(auto pair : _task_map_list){
            if( pair.second.subject() == subject ){
                result.push_back(pair.second);
            }
        }

        return result;
    }

    bool exist_task(const std::string& task_id) const
    {
        return _task_map_list.find(task_id) != _task_map_list.end();
    }

    bool update_task(const task& obj)
    {
        _task_map_list[obj.id()] = obj;
    }

    bool create_task(const task& obj)
    {
        _task_map_list[obj.id()] = obj;
    }

    bool remove_task(const const std::string& task_id)
    {
        _task_map_list.erase(task_id);
    }

private:
    std::map<std::string,task> _task_map_list;
};

#endif
