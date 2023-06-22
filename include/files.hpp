#pragma once
#ifndef _FILE_FILES
#define _FILE_FILES _FILE_FILES
#include"init.hpp"
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
    void begin()
    {
        (std::ifstream)(makepath(appdata_path,"file.json"))>>files_json;
    }
    void end()
    {
        (std::ofstream)(makepath(appdata_path,"file.json"))<<std::setw(4)<<files_json;
    }
    int find_filestr(const int num)
    {
        return (int)files_json["file"+to_string_len(num,number_len)].type()!=3;
    }
    void add_filestr(const int num,const std::string file)
    {
        files_json["file"+to_string_len(num,number_len)]=systoUTF8(file);
        orita_log.print(_LOG_INFO,"name add filestr","num: "+to_string_len(num,number_len),"file: "+add_quotation(file));
    }
    std::string get_filestr(const int num)
    {
        const std::string file=UTF8tosys(files_json["file"+to_string_len(num,number_len)]);
        orita_log.print(_LOG_INFO,"name get filestr","num: "+to_string_len(num,number_len),"file: "+add_quotation(file));
        return file;
    }
    std::string get_filename(const std::string file)
    {
        int pos=file.find_last_of(PS);
        if(pos==std::string::npos) return file;
        return file.substr(pos+1,file.size()-pos-1);
    }
    std::string get_filename(const int num)
    {
        return get_filename(get_filestr(num));
    }
    std::string get_filepath(const std::string file)
    {
        int pos=file.find_last_of(PS);
        if(pos==std::string::npos) return "";
        return file.substr(0,pos);
    }
    std::string get_filepath(const int num)
    {
        return get_filepath(get_filestr(num));
    }
    std::string get_filenamepre(const std::string file)
    {
        const std::string name=get_filename(file);
        int pos=name.find_last_of(".");
        if(pos==std::string::npos) return name;
        return name.substr(0,pos);
    }
    std::string get_filenamepre(const int num)
    {
        return get_filenamepre(get_filestr(num));
    }
    std::string get_filenamesuf(const std::string file)
    {
        const std::string name=get_filename(file);
        int pos=name.find_last_of(".");
        if(pos==std::string::npos) return "";
        return name.substr(pos,name.size()-pos);
    }
    std::string get_filenamesuf(const int num)
    {
        return get_filenamesuf(get_filestr(num));
    }
    std::string get_path(const std::string file)
    {
        #ifdef _WIN32
        if(std::regex_match(file,std::regex("(%([^%]|$)|([a-z]|[A-Z]):|\\\\).*"))) return file;
        #endif
        #ifdef __linux__
        if(std::regex_match(file,std::regex("(%([^%]|$)|/).*"))) return file;
        #endif
        return makepath(running_path,file);
    }
    void add_file(const int num,const std::string file)
    {
        std::string file_result=get_path(file);
        orita_log.print(_LOG_INFO,"name add file","name: "+add_quotation(file),"file: "+add_quotation(file_result));
        add_filestr(num,file_result);
    }
    std::string get_file(const std::string file)
    {
        std::string file_result=get_path(file);
        if(file_result.size()>0&&file_result[0]=='%'&&file_result.find('%',1)==std::string::npos)
        {
            file_result=get_file(get_filestr(std::stoi(file_result.substr(1,file_result.size()-1))));
        }
        else
        {
            int pos=0;
            while(file_result.find('%',pos)!=std::string::npos)
            {
                int pos1=file_result.find('%',pos),pos2=file_result.find('%',pos1+1);
                if(pos2-pos1==1)
                {
                    file_result=file_result.substr(0,pos1)+"%"+file_result.substr(pos2+1,file_result.size()-pos2-1);
                    pos=pos1+1;
                    continue;
                }
                file_result=file_result.substr(0,pos1)+getenv(file_result.substr(pos1+1,pos2-pos1-1).c_str())+file_result.substr(pos2+1,file_result.size()-pos2-1);
            }
        }
        orita_log.print(_LOG_INFO,"name get file","name: "+add_quotation(file),"file: "+add_quotation(file_result));
        return file_result;
    }
    std::string get_file(const int num)
    {
        return get_file(get_filestr(num));
    }
    std::string check_file(const int str) {if(!find_filestr(str)) return get_filestr(str);return "";}
    std::string check_file(const std::string str) {return str;}
    std::string check_file(const json str) {if((int)str.type()==3) return (std::string)str;return "";}
    template<typename ...others_type> std::string check_file(const int str,const others_type ...others) {if(!find_filestr(str)) return get_filestr(str);return check_file(others...);}
    template<typename ...others_type> std::string check_file(const std::string str,const others_type ...others) {return str;}
    template<typename ...others_type> std::string check_file(const json str,const others_type ...others) {if((int)str.type()==3) return (std::string)str;return check_file(others...);}
    std::string add_namesuf(const std::string file,const std::string namesuf)
    {
        if(get_filenamesuf(file)!=namesuf) return file+namesuf;
        return file;
    }
    std::string get_exefile(const std::string file)
    {
        return makepath(get_filepath(file),get_filenamepre(file)+(std::string)settings["exe_suf"]);
    }
    std::string get_exefilename(const std::string file)
    {
        return get_filenamepre(file)+(std::string)settings["exe_suf"];
    }
    #undef number_len
}
int find_filestr(const int num) {return Files::find_filestr(num);}
void add_filestr(const int num,const std::string file) {return Files::add_filestr(num,file);}
std::string get_filestr(const int num) {return Files::get_filestr(num);}
std::string get_filename(const std::string file) {return Files::get_filename(file);}
std::string get_filename(const int num) {return Files::get_filename(num);}
std::string get_filepath(const std::string file) {return Files::get_filepath(file);}
std::string get_filepath(const int num) {return Files::get_filepath(num);}
std::string get_filenamepre(const std::string file) {return Files::get_filenamepre(file);}
std::string get_filenamepre(const int num) {return Files::get_filenamepre(num);}
std::string get_filenamesuf(const std::string file) {return Files::get_filenamesuf(file);}
std::string get_filenamesuf(const int num) {return Files::get_filenamesuf(num);}
void add_file(const int num,const std::string file) {return Files::add_file(num,file);}
std::string get_file(const std::string file) {return Files::get_file(file);}
std::string get_file(const int num) {return Files::get_file(num);}
template<typename ...others_type> std::string check_file(const others_type ...others) {return Files::check_file(others...);}
std::string add_namesuf(const std::string file,const std::string namesuf) {return Files::add_namesuf(file,namesuf);}
std::string get_exefile(const std::string file) {return Files::get_exefile(file);}
std::string get_exefilename(std::string file) {return Files::get_exefilename(file);}
#endif