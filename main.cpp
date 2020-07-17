#include <windows.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;;

string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    string::size_type pos = string( buffer ).find_last_of( "\\/" );
    return string( buffer ).substr( 0, pos);
}

bool check_is_compressed(string file_name)
{
    const unsigned int len = 2;
    string name[len] = {"rar", "zip"};
    string temp = "";
    for(unsigned int i = file_name.length() - 3; i<file_name.length(); i++)
    {
        temp += file_name[i];
    }
    for(unsigned int i=0;i<len;i++)
    {
        if(temp == name[i])
            return true;
    }
    return false;
}

int main() {
    //cout << "my directory is " << ExePath() << "\n";
    ///check list file is(not) exist
    try
    {
        if(remove("files.txt")!=0)
            throw -1;
        cout<<"delete success"<<endl;
    }
    catch(int err)
    {
        if(err == -1)
            cout<<"Nothing need to delete\n";
    }

    ///get current directory
    string a = ExePath();
    system(("cd "+ ExePath()).c_str());
    system("dir /b >> files.txt");

    ///save the list of folder name
    vector<string> folder_name;
    ifstream fin("files.txt");
    string temp = "";

    ///read the directory list from files.txt
    while(getline(fin, temp))
    {
        if(temp != "autoRAR.exe" && temp != "files.txt" && temp != "autoRAR.cpp" && temp != "autoRAR.o")
        {
            folder_name.push_back(temp);
        }
    }
    ///compress all the files with counter(number)
    for(unsigned int i=0;i<folder_name.size();i++)
    {
        ///check if is compress file
        if(check_is_compressed(folder_name[i]))
        {
            temp="rename \"";
            temp+=folder_name[i];
            temp+="\" \"";
            temp+=to_string(i+1);
            temp+=". ";
            temp+=folder_name[i];
            temp+="\"";
            cout<<i+1<<". "<<folder_name[i]<<endl;
            Sleep(100);
            //cout<<temp<<endl;
            system(temp.c_str());
            continue;
        }
        temp = "";
        temp+="C:\\\"Program Files\"\\WinRAR\\WinRAR.exe A \"";
        temp+=to_string(i+1);
        temp+=". ";
        temp+=folder_name[i];
        temp+=".rar\" \"";
        temp+=folder_name[i];
        temp+="\" -r";
        cout<<i+1<<". "<<folder_name[i]<<endl;
        Sleep(100);
        system(temp.c_str());
    }
    ofstream fout("files.txt");
    for(unsigned int i=0;i<folder_name.size();i++)
    {
        fout<<i+1<<". "<<folder_name[i]<<endl;
    }

    system("pause");
}
