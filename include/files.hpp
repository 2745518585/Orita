#pragma once
#ifndef _FILE_FILES
#define _FILE_FILES _FILE_FILES
#include"init.hpp"
#include"log.hpp"
#define _run_ans 101
#define _run_chk 102
#define _check_in 111
#define _check_out 112
#define _check_ans 113
#define _check_chk 114
#define _max_file_num 999
namespace Files
{
    #define number_len 3
    json files_json;
    class Init
    {
      public:
        Init()
        {
            (sifstream(appdata_path/"file.json",false))>>files_json;
        }
        ~Init()
        {
            (sofstream(appdata_path/"file.json",false))<<std::setw(4)<<files_json;
        }
    }_Init_files;
    class file_number
    {
      public:
        const unsigned num;
        std::string str()const {return "file"+to_string_len(num,number_len);}
        file_number(const unsigned _num):num(_num)
        {
            if(num<0||num>_max_file_num)
            {
                ERROR("file_number - invalid file_number","num: "+add_squo(this->str()));
                class invalid_file_number {}error;
                throw error;
            }
        }
        file_number(const std::string &str):num([&]
        {
            if(str[0]!='%')
            {
                ERROR("file_number - invalid file_number","str: "+add_squo(str));
                class invalid_file_number {}error;
                throw error;
            }
            try {return std::stoul(str.substr(1));}
            catch(...)
            {
                ERROR("file_number - invalid file_number","str: "+add_squo(str));
                class invalid_file_number {}error;
                throw error;
            }
        }())
        {
            if(num<0||num>_max_file_num)
            {
                ERROR("file_number - invalid file_number","num: "+add_squo(this->str()));
                class invalid_file_number {}error;
                throw error;
            }
        }
    };
    bool find_filestr(const file_number &num)
    {
        return files_json[num.str()].type()==json::value_t::string;
    }
    void add_filestr(const file_number &num,const pat &file)
    {
        files_json[num.str()]=file.string();
        INFO("add filestr","num: "+add_squo(num.str()),"file: "+add_squo(file));
    }
    pat get_filestr(const file_number &num)
    {
        if(files_json[num.str()].type()!=json::value_t::string)
        {
            ERROR("get filestr - empty filename","num: "+add_squo(num.str()));
            class empty_filename {}error;
            throw error;
        }
        const pat file=files_json[num.str()];
        INFO("get filestr","num: "+add_squo(num.str()),"file: "+add_squo(file));
        return file;
    }
    pat get_path(const pat &file)
    {
        if(file==pat()||std::regex_match(file.string(),std::regex("^%([^%]|$).*"))) return file;
        else return std::filesystem::absolute(file);
    }
    void add_file(const file_number &num,const pat &file)
    {
        pat file_result=get_path(file);
        INFO("add file","name: "+add_squo(file),"file: "+add_squo(file_result));
        add_filestr(num,file_result.string());
    }
    pat get_file(const file_number &num);
    pat get_file(const pat &file)
    {
        pat tmp=get_path(file),final_path;
        for(const auto &dir:tmp)
        {
            if(std::regex_match(dir.string(),std::regex("^%[^%]*")))
            {
                final_path/=get_file((file_number)dir.string());
            }
            else if(std::regex_match(dir.string(),std::regex("^%[^%]+%$"))) final_path/=sgetenv(dir.string().substr(1,dir.string().length()-2).c_str());
            else
            {
                if(std::regex_match(dir.string(),std::regex(".*(^|[^%])(%%)*%($|[^%]).*")))
                {
                    ERROR("get file - invaild path",tmp.string());
                    class invaild_path {}error;
                    throw error;
                }
                final_path/=std::regex_replace(dir.string(),std::regex("%%"),"%");
            }
        }
        INFO("get file","name: "+add_squo(file),"file: "+add_squo(final_path));
        return final_path;
    }
    pat get_file(const file_number &num)
    {
        return get_file(get_filestr(num));
    }
    pat check_file() {return pat();}
    template<typename Type> pat check_file(const Type &str)
    {
        if constexpr(std::is_convertible<Type,pat>::value) return str;
        else if constexpr(std::is_convertible<Type,file_number>::value)
        {
            if(find_filestr(str)) return get_filestr(str);
            return pat();
        }
        else return pat();
    }
    template<typename Type,typename ...others_type> pat check_file(const Type &str,const others_type ...others)
    {
        pat result=check_file(str);
        if(result==pat()) return check_file(others...);
        else return result;
    }
    pat add_namesuf(const pat &file,const pat &namesuf)
    {
        if(file==pat()) return pat();
        if(file.extension()!=namesuf) return replace_extension(file,namesuf);
        return file;
    }
    #undef number_len
}
bool find_filestr(const unsigned num) {return Files::find_filestr(num);}
void add_filestr(const unsigned num,const pat &file) {return Files::add_filestr(num,file);}
pat get_filestr(const unsigned num) {return Files::get_filestr(num);}
void add_file(const unsigned num,const pat &file) {return Files::add_file(num,file);}
pat get_file(const pat &file) {return Files::get_file(file);}
pat get_file(const unsigned num) {return Files::get_file(num);}
template<typename ...others_type> pat check_file(const others_type ...others) {return Files::check_file(others...);}
pat add_namesuf(const pat &file,const pat &namesuf) {return Files::add_namesuf(file,namesuf);}
#endif