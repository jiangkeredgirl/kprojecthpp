/*********************************************************************
 * \file   kprojectio.h
 * \brief  工程输入输出接口，包括配置文件的读写
 *
 * \author jiang
 * \date   2024.07.09
 *********************************************************************/
#pragma once


#include "../kcommonhpp/kcommon.h"
#include "nlohmann/json.hpp"
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
    string puncture_com_port;             //< 穿刺串口号
    string armrest_com_port;              //< 压脉串口号
    string physicalkey_com_port;          //< 物理按键串口号
    string qr_scan_com_port;              //< 二维码扫码枪串口号，没指定则使用PID和VID自动匹配
    string laserdistance_com_port = "CH340";   //< 激光测距串口号，没指定则使用PID和VID自动匹配
    string language = "zh_CN";            //< 语言 中文 "zh_CN", 英文 "en"
    int tighten_strength = 400;           //< 压脉力度
    int fixture_strength = 400;           //< 固定力度
    int blood_center = 250;               //< 血管中心
    float contact_score = 1.0;            //< 贴合系数
    float coupling_thickness = 6.0;       //< 耦合卡扣厚度
    int  exposure = 4000;                 //< 奥比中光摄像头曝光度
    int  gain = 2000;                     //< 奥比中光摄像头增益
    int  laser_energy = 1;                //< 激光能级
    double min_blood_depth = 8.0;         //< 血管深度小于该值，入针角度太小，不适合穿刺
    float  min_blood_radius = 0.6;        //< 血管半径小于该值，不适合穿刺, 超声用
    double white_area_min = 80;           //< 穿刺模块标定针尖白点面积最小值
    double white_area_max = 500;          //< 穿刺模块标定针尖白点面积最大值
    double puncture_precision = 15;       //< 穿刺精度，期望点和实际点的距离
    int  adjust_deg = 25;                 //< 需要调整探头的穿刺角度
    double AdjustAngle =  2.0;            //< 当左右评分相差超过0.25时，机械绕工具坐标旋转的角度，默认值为2.0；
    double coefficient_z = 5.0;           //< 当机械臂旋转角度修正左右评分时，机械臂向下步进距离的比例系数，默认值为5.0
    double deflection_deg = 5;            //< 贴合前，探头的偏转角度，防止穿刺机构碰撞前臂
    double deflection_deg_2 = 6;          //< 贴花前，防止穿刺机构碰撞上臂
    double fit_blank_move_z = 0.4;        //< 贴到皮肤前机械臂下移步长,单位毫米
    double fit_skin_move_z = 0.2;         //< 贴到皮肤后机械臂下移步长,单位毫米
    double x_offset     = 4;              //< 血管偏移4毫米 放弃穿刺
    bool ir_is_real = false;              //< 红外识别血管，显示图像是否实时，默认不用实时
    bool is_draw_blood_circle = false;    //< 是否绘画血管的红色圆圈和绿色的针的x坐标
    double robotic_arm_speed = 0.1;       //< 机械臂速度
    bool   is_puncture_x_homing = false;  //< 穿刺模块第一个电机到0位是否找零
    string ultra_host_wifi_name = "H3L221101";  //< 超声主机的wifi热点名字，只写全名的前面几个字符
    string ultra_app_name = "凯瑞医疗";          //< 超声app的名字
    string his_ip = "";                         //< 服务器ip
    bool punc_ui  = false;                //< 穿刺模块测试
    bool rest_ui  = false;                //< 臂托模块测试
    bool band_ui  = false;                //< 压脉模块测试
    bool key_ui   = false;                //< 按键模块测试
    bool nir_ui   = false;                //< 红外模块测试
    bool ultra_ui = false;                //< 超声模块测试
    bool arm_ui   = false;                //< 机械臂模块测试
    bool sys_ui   = false;                //< 系统模块测试
    bool needleposdetect_ui = false;      //< 针尖检测模块测试
    bool laserdistance_ui = false;        //< 激光测距模块测试
    bool daheng_ui = false;               //< 大恒相机模块测试
    //bool login_ui = false;              //< 用户登录
    std::vector<int> break_time;          //< 加速寿命试验
    int hemostasis_time = 30;             //< 止血时间
    bool check_couplinggel = false;       //< 是否检测超声耦合剂卡膜，默认false
    bool record_clinical = false;         //< 是否是否符合临床要求的采血记录，默认false
    std::string image_save_root = "";     //< 算法图片保存的根目录
    bool  fit_plumb    = false;           //< 垂直贴合，不选择 pith和yaw的关节姿态
    int ultra_algo_option = 0;            //< 超声算法选择 0-大模型，1-传统opencv，2-大模型+传统opencv
    int ir_bright = 50;                   //< 压脉带上红外补光灯的亮度0-100
    bool fit_multi_blood = false;         //< 贴合多根血管，默认是false，只贴合一根血管

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
        , qr_scan_com_port
        , laserdistance_com_port
        , language
        , tighten_strength
        , fixture_strength
        , blood_center
        , contact_score
        , coupling_thickness
        , exposure
        , gain
        , laser_energy
        , min_blood_depth
        , min_blood_radius
        , white_area_min
        , white_area_max
        , puncture_precision
        , adjust_deg
        , AdjustAngle
        , coefficient_z
        , deflection_deg
        , deflection_deg_2
        , fit_blank_move_z
        , fit_skin_move_z
        , x_offset
        , ir_is_real
        , is_draw_blood_circle
        , robotic_arm_speed
        , is_puncture_x_homing
        , ultra_host_wifi_name
        , ultra_app_name
        , his_ip
        , punc_ui
        , rest_ui
        , band_ui
        , key_ui
        , nir_ui
        , ultra_ui
        , arm_ui
        , sys_ui
        , needleposdetect_ui
        , laserdistance_ui
        , daheng_ui
        , break_time
        , hemostasis_time
        , check_couplinggel
        , record_clinical
        , image_save_root
        , fit_plumb
        , ultra_algo_option
        , ir_bright
        , fit_multi_blood
        )
};

/**
 * robotic arm algo config file field.
 */
struct RobotAlgoConfigFile
{
    /// data member
    double safeangle      = 15;
    double init_dianji2   = 2.15;      //< 电机1的初始角度(编码器为0时的电机2的测量角度)；
    double add_dianj1     = -2.5;      //< 电机0到超声截面的补偿量
    double add_dianji3    = 4.1;       //< 电机2到超声目标深度的补偿量；
    double add_dianj1_15  = 0;
    double add_dianji3_15 = 0;
    //皮下1.5mm到超声10.89
    double add_dianj1_89  = 0;
    double add_dianji3_89 = 0;
    //超声10.89到14.7
    double add_dianj1_47  = 0;
    double add_dianji3_47 = 0;
    //14.7到16
    double add_dianj1_16  = 0;
    double add_dianji3_16 = 0;

    // 5个固定点位
    std::array<float, 6>  lose_point   = {0};   //< 丢针点
    std::array<float, 6>  load_point   = {0};   //< 上针点 等于丢针点
    std::array<float, 6>  photo_point  = {0};   //< 针尖拍照点
    std::array<float, 6>  way_point    = {0};   //< 经过点
    std::array<float, 6>  camera_point = {0};   //< 血管拍照点
    std::array<float, 16> t_uc         = { -1,    0,    0,     35.82,
                                            0,   -1,    0,    -61.70,
                                            0,    0,    1,    -47.19,
                                            0,    0,    0,     1};   //< 手眼坐标
    std::array<double, 16> t_uc_tiehe  = { -1.0,  0.0,  0.0,   35.81999969482422,
                                            0.0, -1.0,  0.0,  -61.70000076293945,
                                            0.0,  0.0,  1.0,  -47.189998626708984,
                                            0.0,  0.0,  0.0,   1.0};  //< 手眼坐标
    std::vector<double>   Add_Dianj1_2 = std::vector<double>(40, 0);  //< 自动标定后进针电机0的补偿
    std::vector<double>   Add_Dianj3_2 = std::vector<double>(40, 0);  //< 自动标定后进针电机2的补偿
    std::vector<double>   Add_Cent     = std::vector<double>(40, 0);  //< 自动标定中间线的补偿

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
        RobotAlgoConfigFile
        , safeangle
        , init_dianji2
        , add_dianj1
        , add_dianji3
        , add_dianj1_15
        , add_dianji3_15
        , add_dianj1_89
        , add_dianji3_89
        , add_dianj1_47
        , add_dianji3_47
        , add_dianj1_16
        , add_dianji3_16
        , lose_point
        , load_point
        , photo_point
        , way_point
        , camera_point
        , t_uc
        , t_uc_tiehe
        , Add_Dianj1_2
        , Add_Dianj3_2
        , Add_Cent
        )
};

/**
 * image algo config file field.
 */
struct ImageAlgoConfigFile
{
    /// data member
    float sample_pos = 0.7;                     //< 采样位置 工装用0.5，采血用0.7
    double punc_sapce_double_mm = 50;           //< 进针空间
    float  min_blood_diameter = 0.2/*2.0*/;     //< 血管直径小于该值，不适合穿刺，筛查用
    float US_PROBE_LR_DEPTH_MM = 6.0f;          //< 探头长轴深度差最大值
    float US_PROBE_FB_DEPTH_MM = 1.0f;          //< 探头短轴深度差最大值
    int blind_flag = 0;                         //< 盲贴测试 默认0 红外识别不成功进行盲贴
    bool simulation = false;                    //< 是否用仿体
    int valid_circle_num = 10;                  //< 超声可信度预值
    float rectConfidenceThreshold = 0.65;       //< 矩形框置信度阈值
    float iouThreshold = 0.5;                   //< 矩形框IOU阈值
    int area_threshold = 2000;                  //< 最小面积阈值
    int height_threshold = 50;                  //< 最小高度阈值
    float contact_thr = 0.03f;                  //< 贴合阈值

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT_ORDERED(
        ImageAlgoConfigFile
        , sample_pos
        , punc_sapce_double_mm
        , min_blood_diameter
        , US_PROBE_LR_DEPTH_MM
        , US_PROBE_FB_DEPTH_MM
        , blind_flag
        , simulation
        , valid_circle_num
        , rectConfidenceThreshold
        , iouThreshold
        , area_threshold
        , height_threshold
        , contact_thr
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
    string getRobotAlgoConfigPath() const
    {
        return m_robot_algo_config_path;
    }
    string setRobotAlgoConfigPath(const string& algo_config_file_path)
    {
        m_robot_algo_config_path = algo_config_file_path;
        return m_robot_algo_config_path;
    }
    const RobotAlgoConfigFile& getRobotAlgoConfig()const
    {
        return m_robot_algo_config;
    }
    string getImageAlgoConfigPath() const
    {
        return m_image_algo_config_path;
    }
    string setImageAlgoConfigPath(const string& algo_config_file_path)
    {
        m_image_algo_config_path = algo_config_file_path;
        return m_image_algo_config_path;
    }
    const ImageAlgoConfigFile& getImageAlgoConfig()const
    {
        return m_image_algo_config;
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
        if (!file.is_open())
        {
            std::cerr << "file open failed: " << m_config_path << std::endl;
            return 1;
        }
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
        if (!file.is_open())
        {
            std::cerr << "file open failed: " << m_config_path << std::endl;
            return 1;
        }
        file << j.dump(4) << std::endl;
        file.close();
        return 0;
    }

    /**
     * @brief RobotAlgoConfigFileFromFile
     * @return
     */
    int RobotAlgoConfigFileFromFile()
    {
        /*json*/nlohmann::ordered_json j; // 首先创建一个空的json对象
        //string filecontent;
        std::ifstream file;
        std::filesystem::path file_path = std::filesystem::u8path(m_robot_algo_config_path).string();
        file.open(/*"pretty.json"*/file_path, ios::in | ios::out);
        if (!file.is_open())
        {
            std::cerr << "file open failed: " << m_robot_algo_config_path << std::endl;
            return 1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string filecontent(buffer.str());
        cout << filecontent << endl;
        file.close();
        j = nlohmann::json::parse(filecontent);//将字符串转换为json对象
        m_robot_algo_config = j.get<RobotAlgoConfigFile>();//将json对象转换为person对象
        return 0;
    }
    /**
     * @brief RobotAlgoConfigFileToFile
     * @param config_file
     * @return
     */
    int RobotAlgoConfigFileToFile(const RobotAlgoConfigFile& algo_config_file)
    {
        m_robot_algo_config = algo_config_file;
        /*json*/nlohmann::ordered_json j; // 首先创建一个空的json对象
        j = m_robot_algo_config;//将ConfigFile对象转换为json对象
        std::ofstream file;
        std::filesystem::path file_path = std::filesystem::u8path(m_robot_algo_config_path).string();
        file.open(/*"pretty.json"*/file_path, ios::in | ios::out | ios::trunc);
        if (!file.is_open())
        {
            std::cerr << "file open failed: " << m_robot_algo_config_path << std::endl;
            return 1;
        }
        file << j.dump(4) << std::endl;
        file.close();
        return 0;
    }

    /**
     * @brief ImageAlgoConfigFileFromFile
     * @return
     */
    int ImageAlgoConfigFileFromFile()
    {
        /*json*/nlohmann::ordered_json j; // 首先创建一个空的json对象
        //string filecontent;
        std::ifstream file;
        std::filesystem::path file_path = std::filesystem::u8path(m_image_algo_config_path).string();
        file.open(/*"pretty.json"*/file_path, ios::in | ios::out);
        if (!file.is_open())
        {
            std::cerr << "file open failed: " << m_image_algo_config_path << std::endl;
            return 1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string filecontent(buffer.str());
        cout << filecontent << endl;
        file.close();
        j = nlohmann::json::parse(filecontent);//将字符串转换为json对象
        m_image_algo_config = j.get<ImageAlgoConfigFile>();//将json对象转换为person对象
        return 0;
    }
    /**
     * @brief ImageAlgoConfigFileToFile
     * @param config_file
     * @return
     */
    int ImageAlgoConfigFileToFile(const ImageAlgoConfigFile& algo_config_file)
    {
        m_image_algo_config = algo_config_file;
        /*json*/nlohmann::ordered_json j; // 首先创建一个空的json对象
        j = m_image_algo_config;//将ConfigFile对象转换为json对象
        std::ofstream file;
        std::filesystem::path file_path = std::filesystem::u8path(m_image_algo_config_path).string();
        file.open(/*"pretty.json"*/file_path, ios::in | ios::out | ios::trunc);
        if (!file.is_open())
        {
            std::cerr << "file open failed: " << m_image_algo_config_path << std::endl;
            return 1;
        }
        file << j.dump(4) << std::endl;
        file.close();
        return 0;
    }

private:
    string m_config_path              = "./config.json";
    string m_robot_algo_config_path   = "./config_algo_robot.json";
    string m_image_algo_config_path   = "./config_algo_image.json";
    ConfigFile m_config;
    RobotAlgoConfigFile m_robot_algo_config;
    ImageAlgoConfigFile m_image_algo_config;
};

