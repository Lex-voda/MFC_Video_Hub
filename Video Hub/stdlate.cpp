//stdlate.cpp：数据库实现文件
#include "stdafx.h"
#include"stdlate.h"
void Interface::initialize()
{
    ifstream file;
    file.open("data.txt", ios::in);
    string c_type, u_name, u_gender, u_password, v_name, v_uploader;
    string v_size, v_time;
    bool v_public;
    while (file >> c_type) {
        if (c_type == "User:") {
            file >> u_name >> u_gender >> u_password;
            User u_temp;
            u_temp.name = u_name;
            u_temp.gender = u_gender;
            u_temp.password = u_password;
            user_list->push_back(u_temp);
        }
        else {
            file >> v_name >> v_size >> v_time >> v_uploader >> v_public;
            Video v_temp(v_name, v_size, v_time, v_uploader, v_public);
            (user_list->back()).video_list->push_back(v_temp);
        }
    }
    file.close();
}

void Interface::save()
{
    ofstream file;
    file.open("data.txt", ios::out);
    file.clear();
    for (Iterator<User> it = returnUserList().begin(); it != returnUserList().end(); it++) {
        file << "User: " << it->name << " " << it->gender << " " << it->password << endl;
        for (Iterator<Video> it2 = it->returnVideoList()->begin(); it2 != it->returnVideoList()->end(); it2++) {
            file << "Video: " << it2->video_name << " " << it2->video_size << " "
                << it2->video_time << " " << it2->video_uploader << " " << it2->is_public << endl;
        }
    }
    file.close();
}

bool Interface::signUp(string u_name, string u_password, int gender)
{
    string u_gender;
    for (auto it = returnUserList().begin(); it != returnUserList().end(); it++)
        if (u_name == it->showName())
            return false;
    if (gender == 0)
        u_gender = "male";
    else if (gender == 1)
        u_gender = "female";
    else
        u_gender = "secret";
    User temp(u_name, u_gender, u_password);
    user_list->push_back(temp);
    return true;
}

bool Interface::signIn(string u_name, string u_password)
{
    for (online = returnUserList().begin(); online != returnUserList().end(); online++) {
        if (online->name == u_name && online->password == u_password) {
            return true;
        }
    }
    return false;
}

void User::MyVideo(string u_name)
{
    for (Iterator<Video> it = returnVideoList()->begin(); it != returnVideoList()->end(); it++) {
        // it可以当作指向视频的指针，在{}内遍历该User的所有视频
        // 读取信息可以直接使用 it->(information)
        //前端程序员留言：已在前端实现文件中模拟实现
    }
}

void User::uploadVideo(string v_name, string v_size, string v_time, bool v_access)
{
    Video temp(v_name, v_size, v_time, this->name, v_access);
    video_list->push_back(temp);
}
bool User::deleteVideo(string v_name)
{
    for (auto it = video_list->begin(); it != video_list->end(); it++) {
        if (it->video_name == v_name) {
            video_list->remove(it);
            return true;
        }
    }
    return false;
}
bool User::searchUser(Interface& inter_face, string u_name)
{
    for (Iterator<User> it = inter_face.returnUserList().begin(); it != inter_face.returnUserList().end(); it++) {
        if (it->showName() == u_name) {
            // 找到了之后的事情,可以将it看作是指向user的指针
            return true;
        }
    }
    return false;
}

bool User::searchVideo(Interface& inter_face, string v_name)
{
    bool flag = 0;
    for (Iterator<User> it = inter_face.returnUserList().begin(); it != inter_face.returnUserList().end(); it++) {
        for (Iterator<Video> it2 = it->returnVideoList()->begin(); it2 != it->returnVideoList()->end(); it2++) {
            if (it2->showName() == v_name) {
                return true;
                // it2可以看作是指向找到video的指针
                // warning： video will not be found if it is private.
            }
        }
    }
    return false;
}