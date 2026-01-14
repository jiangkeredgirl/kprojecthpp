/*********************************************************************
 * \file   CameraLister.h
 * \brief  列举连接到电脑上的所有usb摄像头。
 * \author 蒋珂
 * \date   2024.10.14
 *********************************************************************/



#include <windows.h>
#include <dshow.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

class CameraLister {
private:
    struct CameraDetails {
        int opencv_index;
        std::wstring device_name;
        std::string device_name_utf8;
        std::vector<cv::Size> supported_resolutions;
        std::vector<double> supported_fps;
    };

    std::vector<CameraDetails> cameras_;

    std::string wstringToString(const std::wstring& wstr) {
        if (wstr.empty()) return "";
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                                              NULL, 0, NULL, NULL);
        std::string strTo(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(),
                            &strTo[0], size_needed, NULL, NULL);
        return strTo;
    }

public:
    bool enumerate() {
        cameras_.clear();

        // 步骤1: 使用DirectShow获取设备名称
        std::vector<std::wstring> device_names = getDeviceNamesDirectShow();
        if (device_names.empty()) {
            std::cerr << "未找到任何摄像头设备" << std::endl;
            return false;
        }

        // 步骤2: 为每个设备找到对应的OpenCV索引
        for (size_t i = 0; i < device_names.size(); i++) {
            int opencv_index = findOpencvIndexForDevice(i);

            if (opencv_index >= 0) {
                CameraDetails details;
                details.opencv_index = opencv_index;
                details.device_name = device_names[i];
                details.device_name_utf8 = wstringToString(device_names[i]);

                // 获取支持的格式
                getSupportedFormats(opencv_index, details.supported_resolutions, details.supported_fps);

                cameras_.push_back(details);
            }
        }

        return !cameras_.empty();
    }

private:
    std::vector<std::wstring> getDeviceNamesDirectShow() {
        std::vector<std::wstring> names;

        CoInitializeEx(NULL, COINIT_MULTITHREADED);

        ICreateDevEnum* pDevEnum = NULL;
        IEnumMoniker* pEnum = NULL;

        HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
                                      CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDevEnum));

        if (SUCCEEDED(hr)) {
            hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);

            if (hr == S_OK) {
                IMoniker* pMoniker = NULL;
                while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
                    IPropertyBag* pPropBag = NULL;
                    hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));

                    if (SUCCEEDED(hr)) {
                        VARIANT varName;
                        VariantInit(&varName);
                        hr = pPropBag->Read(L"FriendlyName", &varName, 0);

                        if (SUCCEEDED(hr)) {
                            names.push_back(varName.bstrVal);
                        }

                        VariantClear(&varName);
                        pPropBag->Release();
                    }
                    pMoniker->Release();
                }
                pEnum->Release();
            }
            pDevEnum->Release();
        }

        CoUninitialize();
        return names;
    }

    int findOpencvIndexForDevice(int device_index) {
        // 尝试多个后端
        std::vector<int> backends = {cv::CAP_DSHOW, cv::CAP_MSMF, cv::CAP_VFW};

        for (int backend : backends) {
            cv::VideoCapture cap(device_index, backend);
            if (cap.isOpened()) {
                cv::Mat test_frame;
                if (cap.read(test_frame) && !test_frame.empty()) {
                    cap.release();
                    return device_index;
                }
                cap.release();
            }
        }

        return -1;
    }

    void getSupportedFormats(int index,
                             std::vector<cv::Size>& resolutions,
                             std::vector<double>& fps_values) {
        resolutions.clear();
        fps_values.clear();

        // 测试常见分辨率
        std::vector<cv::Size> common_resolutions = {
            {640, 480}, {800, 600}, {1024, 768},
            {1280, 720}, {1920, 1080}, {3840, 2160}
        };

        cv::VideoCapture cap(index, cv::CAP_DSHOW);
        if (!cap.isOpened()) {
            return;
        }

        for (const auto& res : common_resolutions) {
            cap.set(cv::CAP_PROP_FRAME_WIDTH, res.width);
            cap.set(cv::CAP_PROP_FRAME_HEIGHT, res.height);

            int actual_width = (int)cap.get(cv::CAP_PROP_FRAME_WIDTH);
            int actual_height = (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT);

            if (actual_width == res.width && actual_height == res.height) {
                resolutions.push_back(res);

                // 测试常见帧率
                std::vector<double> test_fps = {15.0, 30.0, 60.0};
                for (double fps : test_fps) {
                    cap.set(cv::CAP_PROP_FPS, fps);
                    double actual_fps = cap.get(cv::CAP_PROP_FPS);
                    if (actual_fps >= fps * 0.9) { // 允许10%误差
                        fps_values.push_back(actual_fps);
                    }
                }
            }
        }

        cap.release();

        // 去重
        std::sort(resolutions.begin(), resolutions.end(),
                  [](const cv::Size& a, const cv::Size& b) {
                      return a.width * a.height < b.width * b.height;
                  });
        resolutions.erase(std::unique(resolutions.begin(), resolutions.end()),
                          resolutions.end());

        std::sort(fps_values.begin(), fps_values.end());
        fps_values.erase(std::unique(fps_values.begin(), fps_values.end()),
                         fps_values.end());
    }

public:
    void printDetailedInfo() {
        std::cout << "\n========== 摄像头详细信息 ==========\n" << std::endl;

        for (const auto& cam : cameras_) {
            std::wcout << L"设备 [" << cam.opencv_index << L"]: " << cam.device_name << std::endl;
            std::cout << "OpenCV索引: " << cam.opencv_index << std::endl;
            std::cout << "设备名称: " << cam.device_name_utf8 << std::endl;

            if (!cam.supported_resolutions.empty()) {
                std::cout << "支持的分辨率: ";
                for (size_t i = 0; i < cam.supported_resolutions.size(); i++) {
                    std::cout << cam.supported_resolutions[i].width
                              << "x" << cam.supported_resolutions[i].height;
                    if (i < cam.supported_resolutions.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }

            if (!cam.supported_fps.empty()) {
                std::cout << "支持的帧率: ";
                for (size_t i = 0; i < cam.supported_fps.size(); i++) {
                    std::cout << cam.supported_fps[i] << " fps";
                    if (i < cam.supported_fps.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
            }

            std::cout << std::string(50, '-') << std::endl;
        }

        std::cout << "\n共找到 " << cameras_.size() << " 个可用摄像头" << std::endl;
    }
};

// int main() {
//     CompleteCameraLister lister;

//     if (lister.enumerate()) {
//         lister.printDetailedInfo();
//     } else {
//         std::cout << "摄像头枚举失败" << std::endl;
//     }

//     return 0;
// }
