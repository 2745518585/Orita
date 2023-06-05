#pragma once
#ifndef _FILE_FILES
#define _FILE_FILES _FILE_FILES
#include"init.hpp"
#define _run_ans 1
#define _run_chk 2
#define _check_in 11
#define _check_out 12
#define _check_ans 13
#define _check_chk 14
#define _custom_start 100
#define _custom_tot 100
namespace Files
{
    #define number_len 3
    json files_json;
    void begin()
    {
        (std::ifstream)(appdata_path+sPS+"file.json")>>files_json;
    }
    void end()
    {
        (std::ofstream)(appdata_path+sPS+"file.json")<<std::setw(4)<<files_json;
    }
    int find_filestr(int num)
    {
        return (int)files_json["file"+to_string_len(num,number_len)].type()!=3;
    }
    void add_filestr(int num,const std::string file)
    {
        files_json["file"+to_string_len(num,number_len)]=systoUTF8(file);
        orita_log.print(_LOG_INFO,"name add filestr","num: "+to_string_len(num,number_len),"file: "+add_quotation(file));
    }
    std::string get_filestr(int num)
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
    std::string get_filename(int num)
    {
        return get_filename(get_filestr(num));
    }
    std::string get_filepath(const std::string file)
    {
        int pos=file.find_last_of(PS);
        if(pos==std::string::npos) return "";
        return file.substr(0,pos);
    }
    std::string get_filepath(int num)
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
    std::string get_filenamepre(int num)
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
    std::string get_filenamesuf(int num)
    {
        return get_filenamesuf(get_filestr(num));
    }
    std::string get_path(const std::string file)
    {
        #ifdef _WIN32
        if((file[0]==0||(file[0]!='%'||file[1]=='%'))&&!(file.size()>1&&file[1]==':')) return running_path+sPS+file;
        #endif
        #ifdef __linux__
        if((file[0]==0||(file[0]!='%'||file[1]=='%'))&&!(file.size()>0&&file[0]=='/')) return running_path+sPS+file;
        #endif
        return file;
    }
    void add_file(int num,const std::string file)
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
            file_result=get_file(get_filestr(std::stoi(file_result.substr(1,file_result.size()-1))+_custom_start));
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
    std::string get_file(int num)
    {
        return get_file(get_filestr(num));
    }
    std::string add_namesuf(const std::string file,const std::string namesuf)
    {
        if(get_filenamesuf(file)!=namesuf) return file+namesuf;
        return file;
    }
    std::string get_exefile(const std::string file)
    {
        return get_filepath(file)+sPS+get_filenamepre(file)+exe_suf;
    }
    std::string get_exefilename(const std::string file)
    {
        return get_filenamepre(file)+exe_suf;
    }
}
int find_filestr(int num) {return Files::find_filestr(num);}
void add_filestr(int num,const std::string file) {return Files::add_filestr(num,file);}
std::string get_filestr(int num) {return Files::get_filestr(num);}
std::string get_filename(const std::string file) {return Files::get_filename(file);}
std::string get_filename(int num) {return Files::get_filename(num);}
std::string get_filepath(const std::string file) {return Files::get_filepath(file);}
std::string get_filepath(int num) {return Files::get_filepath(num);}
std::string get_filenamepre(const std::string file) {return Files::get_filenamepre(file);}
std::string get_filenamepre(int num) {return Files::get_filenamepre(num);}
std::string get_filenamesuf(const std::string file) {return Files::get_filenamesuf(file);}
std::string get_filenamesuf(int num) {return Files::get_filenamesuf(num);}
void add_file(int num,const std::string file) {return Files::add_file(num,file);}
std::string get_file(const std::string file) {return Files::get_file(file);}
std::string get_file(int num) {return Files::get_file(num);}
std::string add_namesuf(const std::string file,const std::string namesuf) {return Files::add_namesuf(file,namesuf);}
std::string get_exefile(const std::string file) {return Files::get_exefile(file);}
std::string get_exefilename(std::string file) {return Files::get_exefilename(file);}
#endif