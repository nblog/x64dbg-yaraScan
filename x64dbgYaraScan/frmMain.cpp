#include "pch.h"


#include "x64dbgYaraScan.h"



namespace x64dbgYaraScan {

	value struct moduleinfo {
		String^ path;
		Int64 base;
		Int64 size;
		Int64 entry;

		virtual String^ ToString() override {
			return String::Format("{0,8:X8}  {1}", base, path);
		}
	};
	
	array<moduleinfo>^ enumerateModules() {

		BridgeList<Script::Module::ModuleInfo> list;

		if (!Script::Module::GetList(&list))
			return nullptr;

		auto res = gcnew array<moduleinfo>(list.Count());
		for (int i = 0; i < list.Count(); i++)
		{
			res[i].path = marshal_as<String^>(list[i].path);
			res[i].base = list[i].base;
			res[i].size = list[i].size;
			res[i].entry = list[i].entry;
		}

		return res;
	}


	inline System::Void frmMain::frmMain_Load(System::Object^ sender, System::EventArgs^ e) {

		auto root = gcnew DirectoryInfo(marshal_as<String^>(
			x64dbgYaraScan::ruledir().wstring()));

		for each (auto file in root->GetFiles()) {
			CHKBOXRules->Items->Add(file);
		}

		for each (auto m in enumerateModules()) {
			CBBOXMod->Items->Add(m);
		}

		if (CBBOXMod->Items->Count > 0) {
			CBBOXMod->SelectedIndex = 0; CHKAll->Checked = true;
		}

		return;
	}

	inline System::Void frmMain::btnScan_Click(System::Object^ sender, System::EventArgs^ e) {

		if (!DbgIsDebugging()) {
			x64dbgYaraScan::rtcmsgbox("Please start a debug session first");
			return;
		}

		std::vector<fs::path> rules = {};
		for (int i = 0; i < CHKBOXRules->Items->Count; i++) {
			if (!CHKBOXRules->GetItemChecked(i)) continue;
			rules.push_back(marshal_as<std::wstring>(
				((FileInfo^)(CHKBOXRules->Items[i]))->FullName));
		}

		if (!rules.size()) return;

		ptr_t base = Convert::ToInt64(TXTBase->Text, 16); 
		size_t length = Convert::ToInt64(TXTSize->Text, 16);

		std::vector<retdec::yaracpp::YaraRule> result;
		bool isOk = x64dbgYaraScan::cls_yarahelper().yara_scan_rules(
			base, length, rules, result);

		if (!isOk) return;


		TREEResult->Nodes->Clear();

		for each (auto r in result) {
			auto node = TREEResult->Nodes->Add(marshal_as<String^>(r.getName()));

			if (r.getMeta("description"))
				node->Nodes->Add(marshal_as<String^>(r.getMeta("description")->getStringValue()));

			for each (auto m in r.getMatches()) {
				auto addr = base + m.getOffset();
				auto n = node->Nodes->Add(String::Format("{0,8:X8}", addr)); n->Tag = addr;
			}
		}

		return;
	}

	inline System::Void frmMain::CHKAll_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

		for (int i = 0; i < CHKBOXRules->Items->Count; i++) {
			CHKBOXRules->SetItemChecked(i, CHKAll->Checked);
		}
	}

	inline System::Void frmMain::CBBOXMod_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (CBBOXMod->SelectedItem) {
			auto m = (moduleinfo^)CBBOXMod->SelectedItem;
			TXTBase->Text = String::Format("{0,8:X8}", m->base);
			TXTSize->Text = String::Format("{0,8:X8}", m->size);
		}
	}

	inline System::Void frmMain::TREEResult_NodeMouseDoubleClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e) {
		if (TREEResult->SelectedNode && TREEResult->SelectedNode->Tag) {
			Int64 addr = Convert::ToInt64(TREEResult->SelectedNode->Tag);

			DbgCmdExecDirect(marshal_as<std::string>(String::Format("dump {0,8:X8}", addr)).c_str());
		}
	}

}

