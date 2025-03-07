//stdlate.h�����ݿ�ͷ�ļ�

#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Late_List.h"
using namespace std;
class Video; class User; class Interface;

class Video {
public:
    string video_name;
    string video_size;
    string video_time;
    string video_uploader;
    bool is_public;
public:
    Video() {}
    Video(string name, string size, string time, string uploader, bool access)
        : video_name(name), video_size(size), video_time(time), video_uploader(uploader), is_public(access) {}
    Video(const Video& rhs) : video_name(rhs.video_name), video_size(rhs.video_size), video_time(rhs.video_time),
        video_uploader(rhs.video_uploader), is_public(rhs.is_public) {}
    ~Video() = default;
    void showInformation();
    string showName() { return video_name; }
    bool isPublic() { return is_public; }
    friend class User;
    friend class Interface;
    friend class Iterator<Video>;
};
class User {
public:
    string name, gender, password;
    List<Video>* video_list;
public:
    User()
        : video_list(new List<Video>) {}
    User(const User& rhs)
        : name(rhs.name), gender(rhs.gender), password(rhs.password), video_list(new List<Video>) {
        *video_list = *(rhs.video_list);
    }
    User(string u_name, string u_gender, string u_password)
        : name(u_name), gender(u_gender), password(u_password), video_list(new List<Video>) {}
    ~User()
    {
        delete video_list; video_list = nullptr;
    }
    User& operator=(const User& rhs)
    {
        name = rhs.name; gender = rhs.gender; password = rhs.password; *video_list = *(rhs.video_list); return *this;
    }
    List <Video>* returnVideoList() { return video_list; }
    string showName() { return name; }
    const string showPassword() { return password; }
    /*
    *  functions
    */
    void MyVideo(string u_name);
    bool deleteVideo(string v_name);
    void uploadVideo(string v_name, string v_size, string v_time, bool v_access);     // �ϴ���Ƶ��Ҫ���֣���С��ʱ��
    bool searchUser(Interface& inter_face, string u_name);
    bool searchVideo(Interface& inter_face, string v_name);

    friend class Interface;
    friend class Iterator<User>;
};

class Interface {
public:
    Iterator<User> online;
    List<User>* user_list;
public:
    Interface()
        : user_list(new List<User>) {}
    Interface(const Interface& rhs) : user_list(new List<User>)
    {
        *user_list = *rhs.user_list;

        if (rhs.online != Iterator<User>()) {
            Iterator<User> ol = rhs.online;
            signIn(ol->name, ol->password);
        }
    }
    Interface& operator=(const Interface& rhs)
    {
        if (user_list) { delete user_list; user_list = nullptr; }
        user_list = new List<User> ;

        *user_list = *rhs.user_list;
        if (rhs.online != Iterator<User>()) {
            Iterator<User> ol = rhs.online;
            signIn(ol->name, ol->password);
        }
        return *this;
    }
    ~Interface()
    {
        delete user_list;
    }
    void signUp();
    // ע�ắ��
    void signIn();
    // ��¼����
    void InitialInterface();
    // ��ʼ�����棬������¼��ע����˳�
    void OnlineInterface();
    // ��¼�����user����ִ�еĲ��������е����������л���user�ġ�
    void initialize();
    // �ڳ�ʼ����������ǰ��ʼ�������������ݴ�ŵ��ڴ���
    void save();
    // �������˳�֮ǰ�������е���Ϣ��
    List<User>& returnUserList() { return *user_list; }
    /*
    * new functions
    */
    bool signUp(string, string, int);
    // �Ա����ַ�����ֻ�����������int����ʱ��ӿ�ת��һ�¾ͺ�
    bool signIn(string, string);
    // �µ�¼�ӿ�

    template<typename T> friend class Iterator;
};