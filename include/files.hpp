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
    void add_filestr(int num,std::string file)
    {
        files_json["file"+to_string_len(num,number_len)]=systoUTF8(file);
    }
    std::string get_filestr(int num)
    {
        return UTF8tosys(files_json["file"+to_string_len(num,number_len)]);
    }
    std::string get_filename(std::string file)
    {
        int pos=file.find_last_of(PS);
        if(pos==std::string::npos) return file;
        return file.substr(pos+1,file.size()-pos-1);
    }
    std::string get_filename(int num)
    {
        return get_filename(get_filestr(num));
    }
    std::string get_filepath(std::string file)
    {
        int pos=file.find_last_of(PS);
        if(pos==std::string::npos) return "";
        return file.substr(0,pos);
    }
    std::string get_filepath(int num)
    {
        return get_filepath(get_filestr(num));
    }
    std::string get_filenamepre(std::string file)
    {
        std::string name=get_filename(file);
        int pos=name.find_last_of(".");
        if(pos==std::string::npos) return name;
        return name.substr(0,pos);
    }
    std::string get_filenamepre(int num)
    {
        return get_filenamepre(get_filestr(num));
    }
    std::string get_filenamesuf(std::string file)
    {
        std::string name=get_filename(file);
        int pos=name.find_last_of(".");
        if(pos==std::string::npos) return "";
        return name.substr(pos,name.size()-pos);
    }
    std::string get_filenamesuf(int num)
    {
        return get_filenamesuf(get_filestr(num));
    }
    void add_file(int num,std::string file)
    {
        #ifdef _WIN32
        if((file[0]==0||(file[0]!='%'||file[1]=='%'))&&!(file.size()>1&&file[1]==':')) file=running_path+sPS+file;
        #endif
        #ifdef __linux__
        if((file[0]==0||(file[0]!='%'||file[1]=='%'))&&!(file.size()>0&&file[0]=='/')) file=running_path+sPS+file;
        #endif
        add_filestr(num,file);
    }
    std::string get_file(std::string file)
    {
        #ifdef _WIN32
        if((file[0]==0||(file[0]!='%'||file[1]=='%'))&&!(file.size()>1&&file[1]==':')) file=running_path+sPS+file;
        #endif
        #ifdef __linux__
        if((file[0]==0||(file[0]!='%'||file[1]=='%'))&&!(file.size()>0&&file[0]=='/')) file=running_path+sPS+file;
        #endif
        if(file.size()>0&&file[0]=='%'&&file.find('%',1)==std::string::npos)
        {
            return get_file(get_filestr(std::stoi(file.substr(1,file.size()-1))+_custom_start));
        }
        int pos=0;
        while(file.find('%',pos)!=std::string::npos)
        {
            int pos1=file.find('%',pos),pos2=file.find('%',pos1+1);
            if(pos2-pos1==1)
            {
                file=file.substr(0,pos1)+"%"+file.substr(pos2+1,file.size()-pos2-1);
                pos=pos1+1;
                continue;
            }
            file=file.substr(0,pos1)+getenv(file.substr(pos1+1,pos2-pos1-1).c_str())+file.substr(pos2+1,file.size()-pos2-1);
        }
        return file;
    }
    std::string get_file(int num)
    {
        return get_file(get_filestr(num));
    }
    std::string add_namesuf(std::string file,std::string namesuf)
    {
        if(get_filenamesuf(file)!=namesuf) file+=namesuf;
        return file;
    }
    std::string get_exefile(std::string file)
    {
        return get_filepath(file)+sPS+get_filenamepre(file)+exe_suf;
    }
    std::string get_exefilename(std::string file)
    {
        return get_filenamepre(file)+exe_suf;
    }
    int find_file(std::string file)
    {
        return ssystem("dir \""+file+"\""+system_to_nul);
    }
    int copy_source(std::string file,std::string copy)
    {
        #ifdef _WIN32
        return ssystem("copy \""+file+"\" \""+appdata_path+sPS+copy+"\""+system_to_nul);
        #endif
        #ifdef __linux__
        return ssystem("cp \""+file+"\" \""+appdata_path+sPS+copy+"\""+system_to_nul);
        #endif
    }
    int copy_result(std::string file,std::string copy)
    {
        #ifdef _WIN32
        return ssystem("copy \""+appdata_path+sPS+file+"\" \""+copy+"\""+system_to_nul);
        #endif
        #ifdef __linux__
        return ssystem("cp \""+appdata_path+sPS+file+"\" \""+copy+"\""+system_to_nul);
        #endif
    }
}
int find_filestr(int num) {return Files::find_filestr(num);}
void add_filestr(int num,std::string file) {return Files::add_filestr(num,file);}
std::string get_filestr(int num) {return Files::get_filestr(num);}
std::string get_filename(std::string file) {return Files::get_filename(file);}
std::string get_filename(int num) {return Files::get_filename(num);}
std::string get_filepath(std::string file) {return Files::get_filepath(file);}
std::string get_filepath(int num) {return Files::get_filepath(num);}
std::string get_filenamepre(std::string file) {return Files::get_filenamepre(file);}
std::string get_filenamepre(int num) {return Files::get_filenamepre(num);}
std::string get_filenamesuf(std::string file) {return Files::get_filenamesuf(file);}
std::string get_filenamesuf(int num) {return Files::get_filenamesuf(num);}
void add_file(int num,std::string file) {return Files::add_file(num,file);}
std::string get_file(std::string file) {return Files::get_file(file);}
std::string get_file(int num) {return Files::get_file(num);}
std::string add_namesuf(std::string file,std::string namesuf) {return Files::add_namesuf(file,namesuf);}
std::string get_exefile(std::string file) {return Files::get_exefile(file);}
std::string get_exefilename(std::string file) {return Files::get_exefilename(file);}
int find_file(std::string file) {return Files::find_file(file);}
int copy_source(std::string file,std::string copy) {return Files::copy_source(file,copy);}
int copy_result(std::string file,std::string copy) {return Files::copy_result(file,copy);}
#endif