/*********************************************************************
 * \file   kmtptabletdetect.h
 * \brief  检测电脑上是否已连接平板或者手机
 * \author 蒋珂
 * \date   2025.10.18
 *********************************************************************/
#pragma once

// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// #define _KTMW32_
// #include <windows.h>
// #include <atlbase.h>

// #ifdef ACCESS_MASK
// #undef ACCESS_MASK
// #endif

// #include <portabledeviceapi.h>
// #include <portabledevicetypes.h>
// #include <setupapi.h>
// #include <cfgmgr32.h>
// #include <devguid.h>

// #define _KTMW32_   // 阻止 <windows.h> 自动包含 <ktmw32.h>
// #include <windows.h>


// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// #include <windows.h>
// #include <atlbase.h>

// // 🔥 关键行：避免 WPD 与 Windows SDK 的 ACCESS_MASK 冲突
// #ifdef ACCESS_MASK
// #undef ACCESS_MASK
// #endif

// #include <portabledeviceapi.h>
// #include <portabledevicetypes.h>
// #include <setupapi.h>
// #include <cfgmgr32.h>
// #include <devguid.h>


// // MtpTabletDetect.cpp
// // 编译：/std:c++17 ；链接：Ole32.lib、PortableDeviceGuids.lib、Setupapi.lib、Hid.lib(不必须)
// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// #include <windows.h>
// #include <atlbase.h>

// #ifdef ACCESS_MASK
// #undef ACCESS_MASK
// #endif

// #include <portabledeviceapi.h>
// #include <portabledevicetypes.h>
// #include <setupapi.h>
// #include <cfgmgr32.h>
// #include <devguid.h>        // ★ 这里提供 GUID_DEVCLASS_WPD
// // #include <initguid.h>    // 只有在你需要在此处定义 GUID 实体时才包含（通常不需要）
// #include <string>
// #include <vector>
// #include <iostream>
// #define CM_MAX_ID_LEN  256


// #pragma comment(lib, "Ole32.lib")
// #pragma comment(lib, "PortableDeviceGuids.lib")
// #pragma comment(lib, "Setupapi.lib")

// ---- 预处理与头文件顺序（防冲突）----
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// 如果不使用事务 API，可启用此项，彻底避免 <ktmw32.h> 被包含
#define _KTMW32_

#include <windows.h>
#include <atlbase.h>

// 关键：避免 WPD 与 Windows SDK 的 ACCESS_MASK 冲突
#ifdef ACCESS_MASK
#undef ACCESS_MASK
#endif

#include <portabledeviceapi.h>
#include <portabledevicetypes.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <devguid.h>            // GUID_DEVCLASS_WPD
#include <initguid.h>           // 仅用于确保某些 GUID 可用（通常安全包含）

#include <string>
#include <vector>
#include <iostream>

// 链接库
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "PortableDeviceGuids.lib")
#pragma comment(lib, "Setupapi.lib")

#define CM_MAX_ID_LEN  256


inline struct MtpDeviceInfo {
    std::wstring deviceId;       // PnP 设备实例 ID（可用于 SetupAPI）
    std::wstring friendlyName;   // 友好名
    std::wstring manufacturer;   // 厂商
    std::wstring description;    // 描述
    std::wstring vid;            // 形如 "VID_05AC"（可为空）
    std::wstring pid;            // 形如 "PID_12A8"（可为空）
    bool isLikelyTablet = false; // 启发式判断结果
};

static inline bool LooksLikeTabletName(const std::wstring& name) {
    // 简单启发式：常见“平板”关键词
    static const wchar_t* keys[] = { L"ipad", L"pad", L"tablet", L"tab", L"galaxy tab", L"mi pad", L"lenovo tab", L"cx" };
    std::wstring low = name;
    for (auto& ch : low) ch = towlower(ch);
    for (auto k : keys) {
        if (low.find(k) != std::wstring::npos) return true;
    }
    return false;
}

// 从 SPDRP_HARDWAREID / SPDRP_COMPATIBLEIDS 中提取 VID/PID
static inline void TryParseVidPid(HDEVINFO hDevInfo, SP_DEVINFO_DATA& devInfoData,
                           std::wstring& outVID, std::wstring& outPID) {
    auto grabRegProp = [&](DWORD prop)->std::vector<wchar_t> {
        DWORD req = 0;
        SetupDiGetDeviceRegistryPropertyW(hDevInfo, &devInfoData, prop, nullptr, nullptr, 0, &req);
        if (req == 0) return {};
        std::vector<wchar_t> buf(req / sizeof(wchar_t));
        if (!SetupDiGetDeviceRegistryPropertyW(hDevInfo, &devInfoData, prop, nullptr,
                                               reinterpret_cast<PBYTE>(buf.data()), req, nullptr)) {
            return {};
        }
        return buf;
    };

    auto parseArr = [&](const wchar_t* multi)->bool {
        // REG_MULTI_SZ，末尾双\0
        if (!multi) return false;
        const wchar_t* p = multi;
        while (*p) {
            std::wstring s = p;
            std::wstring low = s;
            for (auto& c : low) c = towlower(c);
            size_t vpos = low.find(L"vid_");
            size_t ppos = low.find(L"pid_");
            if (vpos != std::wstring::npos && outVID.empty()) {
                outVID = std::wstring(s.begin() + static_cast<long>(vpos), s.begin() + static_cast<long>(vpos) + 8); // VID_XXXX
            }
            if (ppos != std::wstring::npos && outPID.empty()) {
                outPID = std::wstring(s.begin() + static_cast<long>(ppos), s.begin() + static_cast<long>(ppos) + 8); // PID_XXXX
            }
            if (!outVID.empty() && !outPID.empty()) return true;
            p += s.size() + 1;
        }
        return false;
    };

    auto hw = grabRegProp(SPDRP_HARDWAREID);
    if (!hw.empty() && parseArr(hw.data())) return;

    auto comp = grabRegProp(SPDRP_COMPATIBLEIDS);
    if (!comp.empty()) parseArr(comp.data());
}

// 通过 PnP 设备实例 ID 打开到 SetupAPI 的设备节点
static inline void FillVidPidFromDeviceId(const std::wstring& deviceId,
                                   std::wstring& vid, std::wstring& pid) {
    //GUID guid = GUID_DEVCLASS_PORTABLE; // 便携式设备类；也可不限制，用空 GUID 遍历
    GUID guid = GUID_DEVCLASS_WPD;   // 正确：WPD 设备类

    HDEVINFO hDevInfo = SetupDiGetClassDevsW(&guid, nullptr, nullptr, DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE) return;

    for (DWORD i = 0;; ++i) {
        SP_DEVINFO_DATA devInfoData{};
        devInfoData.cbSize = sizeof(devInfoData);
        if (!SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData)) {
            if (GetLastError() == ERROR_NO_MORE_ITEMS) break;
            continue;
        }
        wchar_t idBuf[CM_MAX_ID_LEN] = { 0 };
        if (CM_Get_Device_IDW(devInfoData.DevInst, idBuf, CM_MAX_ID_LEN, 0) == CR_SUCCESS) {
            if (_wcsicmp(idBuf, deviceId.c_str()) == 0) {
                TryParseVidPid(hDevInfo, devInfoData, vid, pid);
                break;
            }
        }
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
}

// 枚举所有 WPD (MTP/PTP) 设备，并标出可能的“平板”
static inline std::vector<MtpDeviceInfo> EnumerateMtpDevices() {
    std::vector<MtpDeviceInfo> result;

    CComPtr<IPortableDeviceManager> mgr;
    if (FAILED(CoCreateInstance(CLSID_PortableDeviceManager, nullptr, CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&mgr)))) {
        return result;
    }

    DWORD count = 0;
    if (FAILED(mgr->GetDevices(nullptr, &count)) || count == 0) {
        return result;
    }

    std::vector<LPWSTR> ids(count, nullptr);
    if (FAILED(mgr->GetDevices(ids.data(), &count))) {
        return result;
    }

    result.reserve(count);
    for (DWORD i = 0; i < count; ++i) {
        MtpDeviceInfo info;

        // 设备实例 ID
        if (ids[i]) {
            info.deviceId = ids[i];
        }

        // 友好名
        DWORD cch = 0;
        mgr->GetDeviceFriendlyName(ids[i], nullptr, &cch);
        if (cch) {
            std::wstring name(cch, L'\0');
            if (SUCCEEDED(mgr->GetDeviceFriendlyName(ids[i], &name[0], &cch))) {
                if (!name.empty() && name.back() == L'\0') name.pop_back();
                info.friendlyName = name;
            }
        }

        // 厂商
        cch = 0; mgr->GetDeviceManufacturer(ids[i], nullptr, &cch);
        if (cch) {
            std::wstring m(cch, L'\0');
            if (SUCCEEDED(mgr->GetDeviceManufacturer(ids[i], &m[0], &cch))) {
                if (!m.empty() && m.back() == L'\0') m.pop_back();
                info.manufacturer = m;
            }
        }

        // 描述
        cch = 0; mgr->GetDeviceDescription(ids[i], nullptr, &cch);
        if (cch) {
            std::wstring d(cch, L'\0');
            if (SUCCEEDED(mgr->GetDeviceDescription(ids[i], &d[0], &cch))) {
                if (!d.empty() && d.back() == L'\0') d.pop_back();
                info.description = d;
            }
        }

        // VID/PID（可选）
        FillVidPidFromDeviceId(info.deviceId, info.vid, info.pid);

        // 启发式判断“是不是平板”
        info.isLikelyTablet =
            LooksLikeTabletName(info.friendlyName) ||
            LooksLikeTabletName(info.description);

        result.push_back(std::move(info));
        CoTaskMemFree(ids[i]);
    }

    return result;
}

// 对外：是否存在“疑似平板”的 MTP 设备
static inline bool IsMtpTabletConnected(std::vector<MtpDeviceInfo>* outList = nullptr) {
    std::vector<MtpDeviceInfo> list = EnumerateMtpDevices();
    if (outList) *outList = list;
    for (auto& d : list) {
        if (d.isLikelyTablet) return true;
    }
    return false;
}

// int wmain() {
//     CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

//     std::vector<MtpDeviceInfo> list;
//     bool anyTablet = IsMtpTabletConnected(&list);

//     if (list.empty()) {
//         std::wcout << L"未检测到任何 WPD(MTP/PTP) 设备。\n";
//         std::cout << "未检测到任何 WPD(MTP/PTP) 设备。\n";
//     }
//     else {
//         std::wcout << L"发现 " << list.size() << L" 个 WPD 设备：\n";
//         std::cout << "发现 " << list.size() << " 个 WPD 设备：\n";
//         for (const auto& d : list) {
//             std::wcout << L"---\n";
//             std::wcout << L"DeviceID:     " << d.deviceId << L"\n";
//             std::wcout << L"Name:         " << (d.friendlyName.empty() ? L"(null)" : d.friendlyName) << L"\n";
//             std::wcout << L"Manufacturer: " << (d.manufacturer.empty() ? L"(null)" : d.manufacturer) << L"\n";
//             std::wcout << L"Description:  " << (d.description.empty() ? L"(null)" : d.description) << L"\n";
//             std::wcout << L"VID/PID:      " << (d.vid.empty() ? L"(???)" : d.vid) << L" / "
//                        << (d.pid.empty() ? L"(???)" : d.pid) << L"\n";
//             std::wcout << L"LikelyTablet: " << (d.isLikelyTablet ? L"YES" : L"NO") << L"\n";
//         }
//     }

//     std::wcout << L"\n判定：是否存在疑似“平板电脑”的 MTP 设备？ "
//                << (anyTablet ? L"是" : L"否") << L"\n";

//     CoUninitialize();
//     system("pause");
//     return 0;
// }

static inline bool IsTabletConnected()
 {
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    std::vector<MtpDeviceInfo> list;
    bool anyTablet = IsMtpTabletConnected(&list);
    if (list.empty())
    {
        std::cout << "未检测到任何 WPD(MTP/PTP) 设备。\n";
    }
    else
    {
        std::cout << "发现 " << list.size() << " 个 WPD 设备：\n";
        // for (const auto& d : list)
        // {
        //     std::wcout << L"---\n";
        //     std::wcout << L"DeviceID:     " << d.deviceId << L"\n";
        //     std::wcout << L"Name:         " << (d.friendlyName.empty() ? L"(null)" : d.friendlyName) << L"\n";
        //     std::wcout << L"Manufacturer: " << (d.manufacturer.empty() ? L"(null)" : d.manufacturer) << L"\n";
        //     std::wcout << L"Description:  " << (d.description.empty() ? L"(null)" : d.description) << L"\n";
        //     std::wcout << L"VID/PID:      " << (d.vid.empty() ? L"(???)" : d.vid) << L" / "
        //                << (d.pid.empty() ? L"(???)" : d.pid) << L"\n";
        //     std::wcout << L"LikelyTablet: " << (d.isLikelyTablet ? L"YES" : L"NO") << L"\n";
        // }
    }

    std::cout << "\n判定：是否存在疑似“平板电脑”的 MTP 设备？ "
               << (anyTablet ? "是" : "否") << "\n";

    CoUninitialize();

    return anyTablet;
}
