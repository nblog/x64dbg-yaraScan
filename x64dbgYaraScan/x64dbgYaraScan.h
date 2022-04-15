#pragma once

#include <string>
#include <vector>
#include <variant>
#include <functional>
#include <unordered_map>


//#include <filesystem>
//namespace fs {
//	using namespace std::filesystem;
//	using ifstream = std::ifstream;
//	using ofstream = std::ofstream;
//	using fstream = std::fstream;
//}



#include <msclr/marshal_cppstd.h>

using namespace System;


//
#include "../yaracpp/yaracpp.h"


//
#include "pluginmain.h"



//
#define FMT_HEADER_ONLY
#include "../third_party/fmt-8.1.1/include/fmt/format.h"

#include "../third_party/glob-0.0.1/single_include/glob/glob.hpp"





namespace x64dbgYaraScan {

	using namespace msclr::interop;


	typedef uint64_t ptr_t;



	EXTERN_C CONST IMAGE_DOS_HEADER __ImageBase;

	static fs::path current_dir() {
		std::wstring fileName(MAX_PATH, L'\00');
		fileName.resize(
			::GetModuleFileNameW(HINSTANCE(&__ImageBase), PWSTR(fileName.data()), DWORD(fileName.length()))
		);
		return fs::path(fileName).parent_path();
	}


	static void show_msg(std::string s) {
		Script::Gui::Message(s.c_str());
	}

	static void infos_msg(std::string info) {
		_plugin_logprintf(info.c_str());
	}




	typedef std::vector<std::variant<ptr_t, std::string>> var_nargs;
	typedef std::vector<fs::path> var_rules;

	class cls_yarascan
	{
	public:

		void mem_unmmap_all() {
			for (auto& item : mmaps()) {
				mem_unmmap(item.first);
			}
		}

		bool mem_unmmap(ptr_t addr) {
			if (mmaps().end() != mmaps().find(addr))
				mmaps().erase(addr);
			return mmaps().end() == mmaps().find(addr);
		}


		bool mem_mmap(ptr_t addr, size_t length) {
			std::vector<uint8_t> codes(length);
			
			duint retByts = 0;
			if (!Script::Memory::Read(addr, codes.data(), length, &retByts)
				|| length != retByts) {
				return false;
			}

			mmaps()[addr] = { codes };

			return mmaps().end() != mmaps().find(addr);
		}

		bool begin(
			const std::string mode,
			const var_nargs args, const var_rules rules
		) {
			return \
				matching().end() != matching().find(mode) ? \
				matching()[mode](args, rules) : false;
		}


	private:

		ptr_t dbg_module_base_fromName(std::string name) {
			return ptr_t("" == name ? \
				Script::Module::GetMainModuleBase() : Script::Module::BaseFromName(name.c_str())
			);
		}

		ptr_t dbg_module_base(ptr_t addr = 0) {
			return ptr_t(0 == addr ? \
				Script::Module::GetMainModuleBase() : Script::Module::BaseFromAddr(addr)
			);
		}

		ptr_t dbg_module_size(ptr_t addr = 0) {
			return ptr_t(0 == addr ? \
				Script::Module::GetMainModuleSize() : Script::Module::SizeFromAddr(addr)
			);
		}

		ptr_t dbg_mem_virual_base(ptr_t addr) {
			return ptr_t(Script::Memory::GetBase(duint(addr)));
		}

		ptr_t dbg_mem_virual_size(ptr_t addr) {
			return ptr_t(Script::Memory::GetSize(duint(addr)));
		}


		bool yara_scan_rules(
			ptr_t baseAddr, size_t length,
			const var_rules& rules
		)
		{
			bool isOk = false;
			retdec::yaracpp::YaraDetector detector;


			if (!mem_mmap(baseAddr, length)) {
				return false;
			}

			for (auto& r : rules) {
				fs::path rs = r;

				if (!rs.has_parent_path())
					rs = x64dbgYaraScan::current_dir() / "rules" / r;

				if (fs::exists(rs)) detector.addRuleFile(rs.string());
			}

			isOk = detector.analyze(mmaps()[baseAddr].codes);

			mem_unmmap(baseAddr);


			for (auto& r : detector.getDetectedRules()) {

				auto m_description = r.getMeta("description");

				//
				infos_msg(
					fmt::format("\nrule name: {} ({})\n", r.getName(), m_description ? m_description->getStringValue() : "")
				);

				//
				for (auto& m : r.getMatches()) {
					infos_msg(
#ifndef _WIN64
						fmt::format("    {:" "08" "X}\n", baseAddr + m.getOffset())
#else
						fmt::format("    {:" "016" "X}\n", baseAddr + m.getOffset())
#endif
					);
				}
			}

			return isOk;
		};


		//
		std::unordered_map<std::string, std::function<bool(const var_nargs&, const var_rules&)>> _matching = {

			// 内存范围
			{
				"memory",
				[this](const var_nargs& args, const var_rules& rules)
				{
					if (1 > rules.size() || 2 > args.size())
						return false;

					ptr_t baseAddr = std::get<ptr_t>(args[0]);

					size_t length = std::get<ptr_t>(args[1]);

					return yara_scan_rules(baseAddr, length, rules);
				}
			},
			// 内存区域
			{
				"range",
				[this](const var_nargs& args, const var_rules& rules)
				{
					if (1 > rules.size() || 1 > args.size())
						return false;

					ptr_t baseAddr = dbg_mem_virual_base(\
						std::get<ptr_t>(args[0])
					);
					size_t length = dbg_mem_virual_size(baseAddr);

					return yara_scan_rules(baseAddr, length, rules);
				}
			},
			// 指定模块
			{
				"module",
				[this](const var_nargs& args, const var_rules& rules)
				{
					if (1 > rules.size() || 1 > args.size())
						return false;

					ptr_t baseAddr = dbg_module_base_fromName(\
						std::get<std::string>(args[0])
					);
					size_t length = dbg_module_size(baseAddr);

					return yara_scan_rules(baseAddr, length, rules);
				}
			}
		};
		std::unordered_map<std::string, std::function<bool(const var_nargs&, const var_rules&)>>& matching() { return _matching; };



		struct mmapinfo {
			std::vector<uint8_t> codes;
		};
		std::unordered_map<ptr_t, mmapinfo> _mmaps;
		std::unordered_map<ptr_t, mmapinfo>& mmaps() { return _mmaps; };
	};



}
