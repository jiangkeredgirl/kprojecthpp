/*********************************************************************
 * \file   kprojectio.h
 * \brief  工程输入输出接口，包括配置文件的读写
 *
 * \author jiang
 * \date   2024.07.09
 *********************************************************************/
#pragma once


#include "kcommonhpp/kcommon.h"
#include "./nlohmann/json.hpp"
#include <iostream>

using namespace nlohmann;
using json = nlohmann::json;
// A workaround to give to use fifo_map as map, we are just ignoring the 'less' compare
template<class K, class V, class dummy_compare, class A>
using my_workaround_fifo_map = ordered_map<K, V>;
using my_json = basic_json<my_workaround_fifo_map>;


#define NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT_ORDERED(Type, ...)  \
friend void to_json(nlohmann::ordered_json& nlohmann_json_j, const Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
    friend void from_json(const nlohmann::ordered_json& nlohmann_json_j, Type& nlohmann_json_t) { const Type nlohmann_json_default_obj{}; NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM_WITH_DEFAULT, __VA_ARGS__)) }


/**
 * config file field.
 */
struct ConfigFile
{
    /// data member
    string puncture_com_port;        //< 穿刺串口号
    string armrest_com_port;         //< 压脉串口号
    string physicalkey_com_port;     //< 物理按键串口号
    int tighten_strength = 400;      //< 压脉力度
    int blood_center = 250;          //< 血管中心
    float contact_score = 1.0;       //< 贴合系数
    float coupling_thickness = 2.0;  //< 耦合卡扣厚度
    bool punc_ui  = false; //< 模块测试
    bool rest_ui  = false; //< 模块测试
    bool key_ui   = false; //< 模块测试
    bool nir_ui   = false; //< 模块测试
    bool ultra_ui = false; //< 模块测试
    bool arm_ui   = false; //< 模块测试
    bool sys_ui   = false; //< 模块测试
    bool login_ui = false; //< 用户登录

    // 三个固定点位
    std::array<float, 6>  camera_point = {0};   //< 拍照点
    std::array<float, 6>  lose_point   = {0};   //< 丢针点
    std::array<float, 6>  change_point = {0};   //< 换针点

#if 0
public:
    const ConfigFile& operator = (const ConfigFile& config_file)
	{
        set_config_file(config_file);
		return *this;
	}
public:
    const ConfigFile& get_config_file() const
	{
		return *this;
	}
    const ConfigFile& set_config_file(const ConfigFile& config_file)
    {
        set_puncture_com_port(config_file.get_puncture_com_port());
        set_armrest_com_port(config_file.get_armrest_com_port());
        set_physicalkey_com_port(config_file.get_physicalkey_com_port());
        return *this;
    }
    string get_puncture_com_port() const
	{
        return puncture_com_port;
	}
    string set_puncture_com_port(const string text)
    {
        puncture_com_port = text;
        return puncture_com_port;
	}
    string get_armrest_com_port() const
    {
        return armrest_com_port;
    }
    string set_armrest_com_port(const string text)
    {
        armrest_com_port = text;
        return armrest_com_port;
    }
    string get_physicalkey_com_port() const
    {
        return physicalkey_com_port;
    }
    string set_physicalkey_com_port(const string text)
    {
        physicalkey_com_port = text;
        return physicalkey_com_port;
    }
    std::array<float, 6> get_change_point() const
    {
        return change_point;
    }
    std::array<float, 6> set_change_point(std::array<float, 6> arr)
    {
        change_point = arr;
        return change_point;
    }
    std::array<float, 6> get_camera_point() const
    {
        return camera_point;
    }
    std::array<float, 6> set_camera_point(std::array<float, 6> arr)
    {
        camera_point = arr;
        return camera_point;
    }
    std::array<float, 6> get_lose_point() const
    {
        return lose_point;
    }
    std::array<float, 6> set_lose_point(std::array<float, 6> arr)
    {
        lose_point = arr;
        return lose_point;
    }
#endif
public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT_ORDERED(
        ConfigFile
        , puncture_com_port
        , armrest_com_port
        , physicalkey_com_port
        , tighten_strength
        , blood_center
        , contact_score
        , coupling_thickness
        , punc_ui
        , rest_ui
        , key_ui
        , nir_ui
        , ultra_ui
        , arm_ui
        , sys_ui
        , login_ui
        , camera_point
        , lose_point
        , change_point
        )
};

//将C++对象转换成nlohmann::json对象
inline void to_json(nlohmann::json& j, const QVector3D& p)
{
    j = json{ {"x", p.x()}, {"y", p.y()}, {"z", p.z()} };
}

//将nlohmann::json对象转换成C++对象
inline void from_json(const nlohmann::json& j, QVector3D& p)
{
    j.at("x").get_to(p[0]);
    j.at("y").get_to(p[1]);
    j.at("z").get_to(p[2]);
}

//将C++对象转换成nlohmann::json对象
inline void to_json(nlohmann::ordered_json& j, const QVector3D& p)
{
    j = json{ {"x", p.x()}, {"y", p.y()}, {"z", p.z()} };
}

//将nlohmann::json对象转换成C++对象
inline void from_json(const nlohmann::ordered_json& j, QVector3D& p)
{
    j.at("x").get_to(p[0]);
    j.at("y").get_to(p[1]);
    j.at("z").get_to(p[2]);
}

class ProjectIO
{	

public:
    static ProjectIO& instance()
    {
        static ProjectIO projectio;
        return projectio;
    }

public:
    string getConfigPath() const
    {
        return m_config_path;
    }
    string setConfigPath(const string& config_file_path)
    {
        m_config_path = config_file_path;
        return m_config_path;
    }
    const ConfigFile& getConfig()const
    {
        return m_config;
    }
#if 0
	/**
	 * 遍历用户文件夹下所有文件.
	 *
	 * \return
	 */
	int FindAllFiles();
	/**
	 * 将用户文件夹绑定到tree控件.
	 *
	 * \return
	 */
	int FilesTreeFill();
#endif


#if 0
	int ReloadFiles(QTreeWidgetItem& tree_item);
#endif
#if 0
int ProjectJson::FindAllFiles()
{
    KDirectory::FindFiles(USERDIR, m_userfiles);
    return 0;
}

int ProjectJson::FilesTreeFill()
{
    for (const auto& dir_item : m_userfiles.sub_dirs)
    {
        QTreeWidgetItem* top_tree_item = new QTreeWidgetItem(ENUM_TREE_ITEM_TYPE_PROJECT);
        top_tree_item->setText(0, /*utf8*/(dir_item.file_name).c_str());
        top_tree_item->setData(0, Qt::UserRole, /*utf8*/(dir_item.relative_path).c_str());

        /// test code
        //QString k = top_tree_item->data(0, Qt::UserRole).toString();
        //string test_file_path = k.toLocal8Bit().toStdString();

        m_file_tree->addTopLevelItem(top_tree_item);
        FilesTreeFill(dir_item, *top_tree_item, ENUM_TREE_ITEM_TYPE_PROJECT);
    }
    return 0;
}
#endif

#if 0
int ProjectJson::ReloadFiles(QTreeWidgetItem& tree_item)
{
    int errorcode = 1;
    string dir_path = tree_item.data(0, Qt::UserRole).toString()/*.toLocal8Bit()*/.toStdString();
    LOG_INFO("dir_path path:{}", dir_path);
    if (!dir_path.empty())
    {
        while (tree_item.childCount() > 0)
        {
            delete tree_item.child(0);
        }
        KDirectory   m_files;
        KDirectory::FindFiles(dir_path, m_files);
        for (const auto& file_item : m_files.sub_files)
        {
            int item_type = tree_item.type();
            QTreeWidgetItem* file_tree_item = new QTreeWidgetItem(item_type + 1);
            file_tree_item->setText(0, /*utf8*/(file_item.file_name).c_str());
            file_tree_item->setData(0, Qt::UserRole, /*utf8*/(file_item.relative_path).c_str());
            tree_item.addChild(file_tree_item);
        }
        for (const auto& dir_item : m_files.sub_dirs)
        {
            LOG_INFO("dir item name:{}, dir item type:{}", /*utf8*/(dir_item.file_name), MacroToStr(m_tree_item_types[/*utf8*/(dir_item.file_name)]));
            QTreeWidgetItem* dir_tree_item = new QTreeWidgetItem(m_tree_item_types[/*utf8*/(dir_item.file_name)]);
            dir_tree_item->setText(0, /*utf8*/(dir_item.file_name).c_str());
            dir_tree_item->setData(0, Qt::UserRole, /*utf8*/(dir_item.relative_path).c_str());
            tree_item.addChild(dir_tree_item);
            FilesTreeFill(dir_item, *dir_tree_item, m_tree_item_types[/*utf8*/(dir_item.file_name)]);
        }
        //tree_item.treeWidget()->viewport()->update();
        m_selected_item = nullptr;
        m_cur_show_item = nullptr;
    }
    return 0;
}
#endif

#if 0
	/**
     * Read data from a file to an in-memory data structure of config file.
	 *
     * \param config_file
	 * \return 0 success
	 */
    int ReadConfigFile(ConfigFile& config_file)
    {
        // 读取一个json文件，nlohmann会自动解析其中数据
        std::ifstream jsonfile;
        std::filesystem::path file_path = std::filesystem::u8path(m_config_path).string();
        jsonfile.open(/*"pretty.json"*/file_path, ios::in | ios::out);
        //if (jsonfile.get() != EOF)
        {
            json j;
            jsonfile >> j;
            ConfigFile _config_file;
            _config_file.set_puncture_com_port(j.at("puncture_com_port"));
            config_file = _config_file;
        }
        return 0;
    }
	/**
     * Writes memory data of config file to a file.
	 *
     * \param config_file
	 * \return 0 success
	 */
    int WriteConfigFile(ConfigFile& config_file)
    {
        /*json*/my_json j; // 首先创建一个空的json对象
        j["puncture_com_port"]     = config_file.get_puncture_com_port();
        std::ofstream jsonfile;
        std::filesystem::path file_path = std::filesystem::u8path(m_config_path).string();
        jsonfile.open(/*"pretty.json"*/file_path, ios::in | ios::out | ios::trunc);
        jsonfile << j.dump(4) << std::endl;
        jsonfile.close();
        return 0;
    }
#endif

    /**
     * @brief ConfigFileFromFile
     * @return
     */
    int ConfigFileFromFile()
    {
        /*json*/nlohmann::ordered_json j; // 首先创建一个空的json对象
        //string filecontent;
        std::ifstream file;
        std::filesystem::path file_path = std::filesystem::u8path(m_config_path).string();
        file.open(/*"pretty.json"*/file_path, ios::in | ios::out);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string filecontent(buffer.str());
        cout << filecontent << endl;
        file.close();
        j = nlohmann::json::parse(filecontent);//将字符串转换为json对象
        m_config = j.get<ConfigFile>();//将json对象转换为person对象
        return 0;
    }
    /**
     * @brief ConfigFileToFile
     * @param config_file
     * @return
     */
    int ConfigFileToFile(const ConfigFile& config_file)
    {
        m_config = config_file;
        /*json*/nlohmann::ordered_json j; // 首先创建一个空的json对象
        j = m_config;//将ConfigFile对象转换为json对象
        std::ofstream file;
        std::filesystem::path file_path = std::filesystem::u8path(m_config_path).string();
        file.open(/*"pretty.json"*/file_path, ios::in | ios::out | ios::trunc);
        file << j.dump(4) << std::endl;
        file.close();

        return 0;
    }

private:
    string m_config_path = "./config.json";
    ConfigFile m_config;
};

