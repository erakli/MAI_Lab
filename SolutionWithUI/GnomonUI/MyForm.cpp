#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void _tmain(array<String^>^ arg) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew GnomonUI::MyForm);
}