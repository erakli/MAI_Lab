#pragma once
#include "modelling.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//ref class MyNativeWindowListener;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		//static MyForm^ myMainForm;
		MyNativeWindowListener^ nwl;
		static HWND hWndMain;

		UINT counter, limit;
	private: System::Windows::Forms::Label^  label_Ready;


	public:
		MyForm(void);

		void AddPoint(TYPE xPoint, TYPE yPoint){
			currentSeries->Points->AddXY(xPoint, yPoint);
			counter++;
			if (counter >= 100)
			{
				chart1->Refresh();
				//Refresh();
				counter = 0;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: 
		System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
		DataVisualization::Charting::Series^ currentSeries;
		//DataVisualization::Charting::Series^  series1;
		//DataVisualization::Charting::ChartArea^  chartArea1;
		//DataVisualization::Charting::Legend^  legend1;

	private: System::Windows::Forms::Button^  button_Modelling;
	private: System::Windows::Forms::TextBox^  textBox_Time;
	private: System::Windows::Forms::Label^  label_Time;
	private: System::Windows::Forms::Label^  label_ProgressStatus;
	private: System::Windows::Forms::Label^  label_Greeting;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button_Modelling = (gcnew System::Windows::Forms::Button());
			this->textBox_Time = (gcnew System::Windows::Forms::TextBox());
			this->label_Time = (gcnew System::Windows::Forms::Label());
			this->label_ProgressStatus = (gcnew System::Windows::Forms::Label());
			this->label_Greeting = (gcnew System::Windows::Forms::Label());
			this->label_Ready = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisX->IsMarginVisible = false;
			chartArea1->AxisX->MajorGrid->Interval = 0;
			chartArea1->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->CursorX->Interval = 0.01;
			chartArea1->CursorX->IsUserEnabled = true;
			chartArea1->CursorX->IsUserSelectionEnabled = true;
			chartArea1->CursorY->Interval = 0.01;
			chartArea1->CursorY->IsUserEnabled = true;
			chartArea1->CursorY->IsUserSelectionEnabled = true;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 12);
			this->chart1->Name = L"chart1";
			this->chart1->Size = System::Drawing::Size(723, 499);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			// 
			// button_Modelling
			// 
			this->button_Modelling->Location = System::Drawing::Point(744, 54);
			this->button_Modelling->Name = L"button_Modelling";
			this->button_Modelling->Size = System::Drawing::Size(122, 26);
			this->button_Modelling->TabIndex = 0;
			this->button_Modelling->Text = L"Моделирование";
			this->button_Modelling->UseVisualStyleBackColor = true;
			this->button_Modelling->Click += gcnew System::EventHandler(this, &MyForm::button_Modelling_Click);
			// 
			// textBox_Time
			// 
			this->textBox_Time->Location = System::Drawing::Point(766, 28);
			this->textBox_Time->Name = L"textBox_Time";
			this->textBox_Time->Size = System::Drawing::Size(100, 20);
			this->textBox_Time->TabIndex = 2;
			this->textBox_Time->Text = L"10";
			// 
			// label_Time
			// 
			this->label_Time->AutoSize = true;
			this->label_Time->Location = System::Drawing::Point(741, 12);
			this->label_Time->Name = L"label_Time";
			this->label_Time->Size = System::Drawing::Size(125, 13);
			this->label_Time->TabIndex = 3;
			this->label_Time->Text = L"Время интегрирования";
			// 
			// label_ProgressStatus
			// 
			this->label_ProgressStatus->AutoSize = true;
			this->label_ProgressStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_ProgressStatus->Location = System::Drawing::Point(236, 239);
			this->label_ProgressStatus->Name = L"label_ProgressStatus";
			this->label_ProgressStatus->Size = System::Drawing::Size(182, 24);
			this->label_ProgressStatus->TabIndex = 4;
			this->label_ProgressStatus->Text = L"Процесс запущен...";
			this->label_ProgressStatus->Visible = false;
			// 
			// label_Greeting
			// 
			this->label_Greeting->AutoSize = true;
			this->label_Greeting->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_Greeting->Location = System::Drawing::Point(114, 242);
			this->label_Greeting->Name = L"label_Greeting";
			this->label_Greeting->Size = System::Drawing::Size(427, 20);
			this->label_Greeting->TabIndex = 5;
			this->label_Greeting->Text = L"Для запуска моделирования нажмите Моделирование\r\n";
			// 
			// label_Ready
			// 
			this->label_Ready->AutoSize = true;
			this->label_Ready->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_Ready->Location = System::Drawing::Point(827, 498);
			this->label_Ready->Name = L"label_Ready";
			this->label_Ready->Size = System::Drawing::Size(39, 13);
			this->label_Ready->TabIndex = 6;
			this->label_Ready->Text = L"Готов.";
			this->label_Ready->Visible = false;
			// 
			// MyForm
			// 
			this->ClientSize = System::Drawing::Size(878, 523);
			this->Controls->Add(this->label_Ready);
			this->Controls->Add(this->label_ProgressStatus);
			this->Controls->Add(this->label_Time);
			this->Controls->Add(this->textBox_Time);
			this->Controls->Add(this->button_Modelling);
			this->Controls->Add(this->label_Greeting);
			this->Controls->Add(this->chart1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"Моделирование САУ с ПИД-контроллером";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// создание нового графика
		private: DataVisualization::Charting::Series^ CreateSeries(DataVisualization::Charting::Chart^ chart){

			// задание случайного цвета графика
			Random r;
			Color NewColor = Color::FromArgb(r.Next(255), r.Next(255), r.Next(255));

			// создание нового графика
			System::Windows::Forms::DataVisualization::Charting::Series^  series = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());;

			//series->ChartArea = L"ChartArea1";
			series->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			//series->Legend = L"Legend1";
			//series->Name = L"Выходное\nвоздействие";
			series->Color = NewColor;
			series->BorderWidth = 2;
			chart->Series->Add(series);

			return series;
		}

		private: System::Void button_Modelling_Click(System::Object^  sender, System::EventArgs^  e) {

			TYPE Time = 0;

			if (!String::IsNullOrEmpty(textBox_Time->Text))
			{
				Time = Convert::ToDouble(textBox_Time->Text);
				if ((Time <= 0) || (Time > 40000))
				{
					MessageBox::Show(
						"Время интегрирования выбрано\nвне допустимого диапазона",
						"Неверный ввод",
						MessageBoxButtons::OK,
						MessageBoxIcon::Asterisk);
					return;
				}
			}
			else
			{
				MessageBox::Show(
					"Время интегрирования не может\nбыть оставлено пустым", 
					"Неверный ввод",
					MessageBoxButtons::OK,
					MessageBoxIcon::Asterisk);
				return;
			}

			if (label_Greeting->Visible) 
				label_Greeting->Visible = false;

			label_Ready->Visible = false;
			label_ProgressStatus->Visible = true;
			MyForm::Refresh();

			currentSeries = CreateSeries(this->chart1);
			
			limit = 10; //(UINT)(Time);

			CMatrix Result(PIDModelling(Time, hWndMain));

			label_ProgressStatus->Visible = false;
			label_Ready->Visible = true;
		}

	};

	// Creates a  message filter.
	//ref class MyMessageFilter : public System::Windows::Forms::IMessageFilter
	//{
	//public:
	//	[SecurityPermission(SecurityAction::LinkDemand, Flags = SecurityPermissionFlag::UnmanagedCode)]
	//	virtual bool PreFilterMessage(Message % m)
	//	{

	//		// Blocks all the messages relating to the left mouse button.
	//		/*if (m.Msg >= 513 && m.Msg <= 515)
	//		{
	//		Console::WriteLine("Processing the messages : {0}", m.Msg);
	//		return true;
	//		}*/

	//		if (m.Msg == WM_ADDPOINT)
	//		{
	//			TYPE
	//				x = *((double *)&(m.WParam)),
	//				y = *((double *)&(m.LParam));

	//			MyForm::myMainForm->AddPoint(x, y);
	//		}

	//		return false;
	//	}
	
	//};


	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	/* NativeWindow class to listen to operating system messages.  */
	/* Осталось нерешённой оптимизация скорости                    */
	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	//ref class MyNativeWindowListener : public NativeWindow
	//{
	//private:

	//	// Constant value was found in the S"windows.h" header file.
	//	//literal int WM_ACTIVATEAPP = 0x001C;
	//	MyForm^ parent;

	//public:
	//	MyNativeWindowListener(MyForm^ parent)
	//	{
	//		parent->HandleCreated += gcnew EventHandler(this, &MyNativeWindowListener::OnHandleCreated);
	//		parent->HandleDestroyed += gcnew EventHandler(this, &MyNativeWindowListener::OnHandleDestroyed);
	//		this->parent = parent;
	//	}

	//internal:

	//	// Listen for the control's window creation and then hook into it.
	//	void OnHandleCreated(Object^ sender, EventArgs^ /*e*/)
	//	{
	//		// Window is now created, assign handle to NativeWindow.
	//		AssignHandle((dynamic_cast<MyForm^>(sender))->Handle);
	//	}

	//	void OnHandleDestroyed(Object^ /*sender*/, EventArgs^ /*e*/)
	//	{
	//		// Window was destroyed, release hook.
	//		ReleaseHandle();
	//	}

	//protected:

	//	virtual void WndProc(Message %m) override
	//	{
	//		// Listen for operating system messages
	//		switch (m.Msg)
	//		{
	//		case WM_ADDPOINT:

	//			// Notify the form that this message was received.
	//			// Application is activated or deactivated,
	//			// based upon the WParam parameter.
	//			PosXY *pStruct = (PosXY *)m.LParam.ToPointer();
	//			parent->AddPoint(pStruct->posX, pStruct->posY);

	//			if (pStruct) delete pStruct;

	//			break;
	//		}
	//		NativeWindow::WndProc(m);
	//	}

	//};

	MyForm::MyForm(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
		//myMainForm = this;
		AcceptButton = button_Modelling;

		//nwl = gcnew MyNativeWindowListener(this);

		hWndMain = (HWND)this->Handle.ToInt32();

		counter = 0;
	}

}
