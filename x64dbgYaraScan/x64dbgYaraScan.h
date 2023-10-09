#pragma once

#include "plugintemplate/plugin.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include <variant>
#include <unordered_map>
#include <initializer_list>

#include <filesystem>
namespace fs = std::filesystem;


#include "retdec/yaracpp/yara_detector.h"


#include "msclr/marshal_cppstd.h"

#include "frmMain.h"


using namespace System;


namespace x64dbgYaraScan {
	public ref class YaraDialog
	{
	public:
		static void Show() {
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);
			Application::Run(gcnew frmMain());
		};
		static void ShowAsyn() {
			auto frmThread = gcnew Threading::Thread(gcnew Threading::ThreadStart(YaraDialog::Show));
			frmThread->SetApartmentState(Threading::ApartmentState::STA);
			frmThread->Start();
		}
	};
}


namespace x64dbgYaraScan {

	using namespace System::IO;

	using namespace System::Runtime::InteropServices;

	using namespace msclr::interop;


	static
		void rtcmsgbox(String^ msg) {
		MessageBox::Show(msg, PLUGIN_NAME, MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	static
	auto icon() {
#pragma push_macro("ExtractAssociatedIcon")
		std::vector<uint8_t> byteicon;
#undef ExtractAssociatedIcon
		auto icon = Icon::ExtractAssociatedIcon(Reflection::Assembly::GetExecutingAssembly()->Location);
#pragma pop_macro("ExtractAssociatedIcon")

		auto memoryStream = gcnew MemoryStream();
		icon->ToBitmap()->Save(memoryStream, Drawing::Imaging::ImageFormat::Png);
		auto m_icon = memoryStream->ToArray(); byteicon.resize(m_icon->Length);
		Marshal::Copy(m_icon, 0, IntPtr(byteicon.data()), m_icon->Length);
		return byteicon;
	}

	static
	auto ruledir() {
		auto program = marshal_as<std::wstring>(
			Path::GetDirectoryName(
				Reflection::Assembly::GetExecutingAssembly()->Location));
		return fs::path(program) / "rules";
	}


	typedef int64_t ptr_t;



	class cls_yarahelper
	{
	public:

		void mem_unmmap_all() {
			for (auto& item : mmaps())
				mem_unmmap(item.first);
		}

		bool mem_unmmap(ptr_t addr) {
			if (mmaps().end() != mmaps().find(addr))
				mmaps().erase(addr);
			return mmaps().end() == mmaps().find(addr);
		}

		bool mem_mmap(ptr_t addr, size_t length) {
			std::vector<uint8_t> bytearr(length);

			duint retByts = 0;
			if (!Script::Memory::IsValidPtr(addr) 
				|| !Script::Memory::Read(addr, bytearr.data(), length, &retByts)
				|| length != retByts) {
				return false;
			}

			mmaps()[addr] = { bytearr };

			return mmaps().end() != mmaps().find(addr);
		}


		bool yara_scan_rules(
			ptr_t baseAddr, size_t length,
			std::vector<fs::path>& rules,
			std::vector<retdec::yaracpp::YaraRule>& result
		) {
			bool isOk = false;
			retdec::yaracpp::YaraDetector detector;

			result.clear();

			if (!mem_mmap(baseAddr, length)) {
				return false;
			}

			for (auto& r : rules) {

				if (fs::exists(r)) detector.addRuleFile(r.string());

				isOk = detector.analyze(mmaps()[baseAddr].bytearr);

				mem_unmmap(baseAddr);

				result = detector.getDetectedRules();

				return isOk && result.size();
			}

			return true;
		};

	private:

		struct mmapinfo {
			std::vector<uint8_t> bytearr;
		};
		std::unordered_map<ptr_t, mmapinfo> _mmaps;
		std::unordered_map<ptr_t, mmapinfo>& mmaps() { return _mmaps; };
	};

}
