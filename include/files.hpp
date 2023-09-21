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
    json files_json,default_files_json;
    class Init
    {
      public:
        Init()
        {
            (sifstream(file_path/"files"/"file.json",false))>>default_files_json;
            try {(sifstream(appdata_path/"file.json",false))>>files_json;} catch(...) {}
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
        explicit file_number(const std::string &str):num([&]
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
    void add_filestr(const file_number &num,const std::string &file)
    {
        files_json[num.str()]=file;
        INFO("add filestr","num: "+add_squo(num.str()),"file: "+add_squo(file));
    }
    std::string get_filestr(const file_number &num)
    {
        if(files_json[num.str()].type()!=json::value_t::string)
        {
            ERROR("get filestr - empty filename","num: "+add_squo(num.str()));
            class empty_filename {}error;
            throw error;
        }
        const std::string file=(std::string)files_json[num.str()];
        INFO("get filestr","num: "+add_squo(num.str()),"file: "+add_squo(file));
        return file;
    }
    std::string get_default_filestr(const file_number &num)
    {
        if(default_files_json[num.str()].type()!=json::value_t::string)
        {
            ERROR("get default filestr - empty filename","num: "+add_squo(num.str()));
            class empty_filename {}error;
            throw error;
        }
        const std::string file=(std::string)default_files_json[num.str()];
        INFO("get default filestr","num: "+add_squo(num.str()),"file: "+add_squo(file));
        return file;
    }
    pat get_path(const pat &file)
    {
        if(file==pat()||std::regex_match(file.toString(),std::regex("^%([^%]|$).*"))) return file;
        else return file.absolute();
    }
    void add_file(const file_number &num,const pat &file)
    {
        pat file_result=get_path(file);
        INFO("add file","name: "+add_squo(file),"file: "+add_squo(file_result));
        add_filestr(num,file_result.toString());
    }
    fil get_file(const file_number &num);
    fil get_file(const pat &file)
    {
        pat tmp=get_path(file),final_path=pat("/");
        final_path.setDevice(tmp.getDevice());
        final_path.setNode(tmp.getNode());
        for(int i=0;i<=tmp.depth();++i)
        {
            const pat dir=tmp[i];
            if(std::regex_match(dir.toString(),std::regex("^%[^%]*")))
            {
                pat path=get_file((file_number)dir.toString()).path();
                final_path/=path;
                if(path.getDevice()!="") final_path.setDevice(path.getDevice());
            }
            else if(std::regex_match(dir.toString(),std::regex("^%[^%]+%$")))
            {
                pat path=sgetenv(dir.toString().substr(1,dir.toString().length()-2));
                final_path/=path;
                if(path.getDevice()!="") final_path.setDevice(path.getDevice());
            }
            else
            {
                if(std::regex_match(dir.toString(),std::regex(".*(^|[^%])(%%)*%($|[^%]).*")))
                {
                    ERROR("get file - invaild path",add_squo(tmp.toString()));
                    class invaild_path {}error;
                    throw error;
                }
                final_path/=std::regex_replace(dir.toString(),std::regex("%%"),"%");
            }
        }
        INFO("get file","name: "+add_squo(file),"file: "+add_squo(final_path));
        return final_path;
    }
    fil get_file(const file_number &num)
    {
        return get_file(get_filestr(num));
    }
    template<typename Type> fil get_file(const Type &str,bool err)
    {
        try {return get_file(str);}
        catch(...) {return fil();}
    }
    pat check_file() {return pat();}
    template<typename Type> pat check_file(const Type &str)
    {
        if constexpr(std::is_convertible<Type,file_number>::value)
        {
            if(find_filestr(str)) return get_filestr(str);
            return pat();
        }
        else if constexpr(std::is_convertible<Type,pat>::value)
        {
            if(pat(str)!=pat()) return str;
            return pat();
        }
        else if constexpr(std::is_convertible<Type,fil>::value)
        {
            if(pat(fil(str).path())!=pat()) return str;
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
    pat add_namesuf(const pat &file,const std::string &namesuf)
    {
        if(file==pat()) return pat();
        if(file.getExtension()!=namesuf) return file.toString()+"."+namesuf;
        return file;
    }
    fil add_namesuf(const fil &file,const std::string &namesuf)
    {
        const pat path=file.path();
        if(path==pat()) return pat();
        if(path.getExtension()!=namesuf) return path.toString()+"."+namesuf;
        return (fil)path;
    }
    #undef number_len
}
using Files::find_filestr;
using Files::add_filestr;
using Files::get_filestr;
using Files::get_default_filestr;
using Files::add_file;
using Files::get_file;
using Files::check_file;
using Files::add_namesuf;
#endif