#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	//Project1::MyMessageFilter^ NewFilter;
	//Application::AddMessageFilter(NewFilter);

	Application::Run(gcnew Project1::MyForm);
}