#pragma once

#include "modelling.h"

namespace GnomonUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			AcceptButton = button_Modelling_Day;

			comboBox_TimeZone->SelectedIndex = 12 + 3;

			dataPoint_Gnomon = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(1.0e-7, 1.0e-7));
			dataPoint_Gnomon->MarkerColor = System::Drawing::Color::Red;
			dataPoint_Gnomon->MarkerSize = 7;
		}

	private:
		/* 
			Добавление точек на график протяжённости светлого времени суток
		*/
		void AddPoints(DataVisualization::Charting::Series^ series, const CVector &Result)
		{
			series->Points->Clear();	// стираем предыдущий результат

			for (int i = 0; i < Result.getSize(); i++)
			{
				series->Points->AddXY(i + 1, 42370 + Result[i] / 86400.0);
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
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::GroupBox^  groupBox_Coordinates;
	private: System::Windows::Forms::Label^  label_Coordinates_lambda_minutes;
	private: System::Windows::Forms::Label^  label_Coordinates_fi_minutes;
	private: System::Windows::Forms::Label^  label_Coordinates_lambda_deg;
	private: System::Windows::Forms::Label^  label_Coordinates_fi_deg;
	private: System::Windows::Forms::Label^  label_Coordinates_lambda;
	private: System::Windows::Forms::Label^  label_Coordinates_fi;
	private: System::Windows::Forms::TextBox^  textBox_Coordinates_lambda_minutes;
	private: System::Windows::Forms::TextBox^  textBox_Coordinates_fi_minutes;
	private: System::Windows::Forms::TextBox^  textBox_Coordinates_lambda_deg;
	private: System::Windows::Forms::TextBox^  textBox_Coordinates_fi_deg;
	private: System::Windows::Forms::TextBox^  textBox_Height;
	private: System::Windows::Forms::Label^  label_Height;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox_Date;

	private: System::Windows::Forms::Label^  label_Date;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
			 System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint_Gnomon;
	private: System::Windows::Forms::Button^  button_Modelling_Day;
	private: System::Windows::Forms::Label^  label_InProgress;

	private: System::Windows::Forms::ComboBox^  comboBox_TimeZone;
	private: System::Windows::Forms::Label^  label_TimeZone;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::Button^  button_LightTime;
	private: System::Windows::Forms::Label^  label_InProgress_LightTime;
	private: System::Windows::Forms::CheckedListBox^  checkedListBox_LightTime;
	private: System::Windows::Forms::Label^  label_Info;
	private: System::Windows::Forms::Button^  button_ClearYear;



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
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint1 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::DataPoint^  dataPoint2 = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0,
				0));
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label_InProgress = (gcnew System::Windows::Forms::Label());
			this->label_Date = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox_Date = (gcnew System::Windows::Forms::MaskedTextBox());
			this->button_Modelling_Day = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->checkedListBox_LightTime = (gcnew System::Windows::Forms::CheckedListBox());
			this->label_InProgress_LightTime = (gcnew System::Windows::Forms::Label());
			this->button_LightTime = (gcnew System::Windows::Forms::Button());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox_Coordinates = (gcnew System::Windows::Forms::GroupBox());
			this->label_Coordinates_lambda_minutes = (gcnew System::Windows::Forms::Label());
			this->label_Coordinates_fi_minutes = (gcnew System::Windows::Forms::Label());
			this->label_Coordinates_lambda_deg = (gcnew System::Windows::Forms::Label());
			this->label_Coordinates_fi_deg = (gcnew System::Windows::Forms::Label());
			this->label_Coordinates_lambda = (gcnew System::Windows::Forms::Label());
			this->label_Coordinates_fi = (gcnew System::Windows::Forms::Label());
			this->textBox_Coordinates_lambda_minutes = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Coordinates_fi_minutes = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Coordinates_lambda_deg = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Coordinates_fi_deg = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Height = (gcnew System::Windows::Forms::TextBox());
			this->label_Height = (gcnew System::Windows::Forms::Label());
			this->comboBox_TimeZone = (gcnew System::Windows::Forms::ComboBox());
			this->label_TimeZone = (gcnew System::Windows::Forms::Label());
			this->label_Info = (gcnew System::Windows::Forms::Label());
			this->button_ClearYear = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->groupBox_Coordinates->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(661, 403);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label_InProgress);
			this->tabPage1->Controls->Add(this->label_Date);
			this->tabPage1->Controls->Add(this->maskedTextBox_Date);
			this->tabPage1->Controls->Add(this->button_Modelling_Day);
			this->tabPage1->Controls->Add(this->chart1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(653, 377);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Движение тени";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label_InProgress
			// 
			this->label_InProgress->AutoSize = true;
			this->label_InProgress->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label_InProgress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_InProgress->Location = System::Drawing::Point(183, 156);
			this->label_InProgress->Name = L"label_InProgress";
			this->label_InProgress->Size = System::Drawing::Size(174, 26);
			this->label_InProgress->TabIndex = 5;
			this->label_InProgress->Text = L"Моделирование...";
			this->label_InProgress->Visible = false;
			// 
			// label_Date
			// 
			this->label_Date->AutoSize = true;
			this->label_Date->Location = System::Drawing::Point(531, 281);
			this->label_Date->Name = L"label_Date";
			this->label_Date->Size = System::Drawing::Size(116, 13);
			this->label_Date->TabIndex = 4;
			this->label_Date->Text = L"Дата моделирования";
			// 
			// maskedTextBox_Date
			// 
			this->maskedTextBox_Date->Location = System::Drawing::Point(580, 297);
			this->maskedTextBox_Date->Mask = L"00/00/0000";
			this->maskedTextBox_Date->Name = L"maskedTextBox_Date";
			this->maskedTextBox_Date->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox_Date->TabIndex = 5;
			this->maskedTextBox_Date->Text = L"22062016";
			this->maskedTextBox_Date->ValidatingType = System::DateTime::typeid;
			// 
			// button_Modelling_Day
			// 
			this->button_Modelling_Day->Location = System::Drawing::Point(556, 343);
			this->button_Modelling_Day->Name = L"button_Modelling_Day";
			this->button_Modelling_Day->Size = System::Drawing::Size(91, 23);
			this->button_Modelling_Day->TabIndex = 1;
			this->button_Modelling_Day->Text = L"Моделировать";
			this->button_Modelling_Day->UseVisualStyleBackColor = true;
			this->button_Modelling_Day->Click += gcnew System::EventHandler(this, &MyForm::button_Modelling_Day_Click);
			// 
			// chart1
			// 
			chartArea1->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::DarkGray;
			chartArea1->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->Maximum = 20;
			chartArea1->AxisX->Minimum = -20;
			chartArea1->AxisX->Title = L"Z, м";
			chartArea1->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::DarkGray;
			chartArea1->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisY->Maximum = 20;
			chartArea1->AxisY->Minimum = -20;
			chartArea1->AxisY->Title = L"X, м";
			chartArea1->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Location = System::Drawing::Point(6, 6);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->MarkerSize = 3;
			series1->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series1->Name = L"Series1";
			dataPoint1->IsEmpty = true;
			series1->Points->Add(dataPoint1);
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(483, 365);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button_ClearYear);
			this->tabPage2->Controls->Add(this->checkedListBox_LightTime);
			this->tabPage2->Controls->Add(this->label_InProgress_LightTime);
			this->tabPage2->Controls->Add(this->button_LightTime);
			this->tabPage2->Controls->Add(this->chart2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(653, 377);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Эволюция продолжительности светового дня";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// checkedListBox_LightTime
			// 
			this->checkedListBox_LightTime->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->checkedListBox_LightTime->CheckOnClick = true;
			this->checkedListBox_LightTime->FormattingEnabled = true;
			this->checkedListBox_LightTime->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"Летнее время", L"Часть светового дня между 8:00 и 20:00",
					L"Переход между Летним и Зимним временем"
			});
			this->checkedListBox_LightTime->Location = System::Drawing::Point(36, 319);
			this->checkedListBox_LightTime->Name = L"checkedListBox_LightTime";
			this->checkedListBox_LightTime->Size = System::Drawing::Size(256, 47);
			this->checkedListBox_LightTime->TabIndex = 7;
			this->checkedListBox_LightTime->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &MyForm::checkedListBox_LightTime_ItemCheck);
			// 
			// label_InProgress_LightTime
			// 
			this->label_InProgress_LightTime->AutoSize = true;
			this->label_InProgress_LightTime->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label_InProgress_LightTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_InProgress_LightTime->Location = System::Drawing::Point(305, 139);
			this->label_InProgress_LightTime->Name = L"label_InProgress_LightTime";
			this->label_InProgress_LightTime->Size = System::Drawing::Size(105, 26);
			this->label_InProgress_LightTime->TabIndex = 6;
			this->label_InProgress_LightTime->Text = L"Считаем...";
			this->label_InProgress_LightTime->Visible = false;
			// 
			// button_LightTime
			// 
			this->button_LightTime->Location = System::Drawing::Point(556, 343);
			this->button_LightTime->Name = L"button_LightTime";
			this->button_LightTime->Size = System::Drawing::Size(91, 23);
			this->button_LightTime->TabIndex = 2;
			this->button_LightTime->Text = L"Рассчитать";
			this->button_LightTime->UseVisualStyleBackColor = true;
			this->button_LightTime->Click += gcnew System::EventHandler(this, &MyForm::button_LightTime_Click);
			// 
			// chart2
			// 
			chartArea2->AxisX->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea2->AxisX->IsMarginVisible = false;
			chartArea2->AxisX->IsStartedFromZero = false;
			chartArea2->AxisX->MajorGrid->Enabled = false;
			chartArea2->AxisX->MajorGrid->LineColor = System::Drawing::Color::DarkGray;
			chartArea2->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea2->AxisX->Maximum = 366;
			chartArea2->AxisX->Minimum = 1;
			chartArea2->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea2->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea2->AxisY->MajorGrid->LineColor = System::Drawing::Color::DarkGray;
			chartArea2->AxisY->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea2->AxisY->MaximumAutoSize = 90;
			chartArea2->AxisY->ScaleView->SmallScrollMinSize = 0.001;
			chartArea2->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea2->CursorX->IsUserEnabled = true;
			chartArea2->CursorX->IsUserSelectionEnabled = true;
			chartArea2->CursorY->Interval = 0.001;
			chartArea2->CursorY->IsUserEnabled = true;
			chartArea2->CursorY->IsUserSelectionEnabled = true;
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			this->chart2->Location = System::Drawing::Point(6, 6);
			this->chart2->Name = L"chart2";
			series2->BorderWidth = 2;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Area;
			series2->Color = System::Drawing::Color::LightGray;
			series2->Name = L"Series_InAll";
			dataPoint2->IsEmpty = true;
			series2->Points->Add(dataPoint2);
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt32;
			series2->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Time;
			series3->ChartArea = L"ChartArea1";
			series3->Color = System::Drawing::Color::Orange;
			series3->MarkerSize = 4;
			series3->Name = L"Series_Summer";
			series3->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt32;
			series3->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Time;
			series4->ChartArea = L"ChartArea1";
			series4->Color = System::Drawing::Color::DodgerBlue;
			series4->MarkerSize = 4;
			series4->Name = L"Series_Winter";
			series4->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt32;
			series4->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Time;
			series5->BorderWidth = 4;
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Color = System::Drawing::Color::Firebrick;
			series5->Name = L"Series_Switch";
			series5->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::UInt32;
			series5->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Time;
			this->chart2->Series->Add(series2);
			this->chart2->Series->Add(series3);
			this->chart2->Series->Add(series4);
			this->chart2->Series->Add(series5);
			this->chart2->Size = System::Drawing::Size(641, 319);
			this->chart2->TabIndex = 1;
			this->chart2->Text = L"chart2";
			// 
			// groupBox_Coordinates
			// 
			this->groupBox_Coordinates->Controls->Add(this->label_Coordinates_lambda_minutes);
			this->groupBox_Coordinates->Controls->Add(this->label_Coordinates_fi_minutes);
			this->groupBox_Coordinates->Controls->Add(this->label_Coordinates_lambda_deg);
			this->groupBox_Coordinates->Controls->Add(this->label_Coordinates_fi_deg);
			this->groupBox_Coordinates->Controls->Add(this->label_Coordinates_lambda);
			this->groupBox_Coordinates->Controls->Add(this->label_Coordinates_fi);
			this->groupBox_Coordinates->Controls->Add(this->textBox_Coordinates_lambda_minutes);
			this->groupBox_Coordinates->Controls->Add(this->textBox_Coordinates_fi_minutes);
			this->groupBox_Coordinates->Controls->Add(this->textBox_Coordinates_lambda_deg);
			this->groupBox_Coordinates->Controls->Add(this->textBox_Coordinates_fi_deg);
			this->groupBox_Coordinates->Location = System::Drawing::Point(679, 12);
			this->groupBox_Coordinates->Name = L"groupBox_Coordinates";
			this->groupBox_Coordinates->Size = System::Drawing::Size(223, 81);
			this->groupBox_Coordinates->TabIndex = 0;
			this->groupBox_Coordinates->TabStop = false;
			this->groupBox_Coordinates->Text = L"Координаты гномона";
			// 
			// label_Coordinates_lambda_minutes
			// 
			this->label_Coordinates_lambda_minutes->AutoSize = true;
			this->label_Coordinates_lambda_minutes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_Coordinates_lambda_minutes->Location = System::Drawing::Point(206, 53);
			this->label_Coordinates_lambda_minutes->Name = L"label_Coordinates_lambda_minutes";
			this->label_Coordinates_lambda_minutes->Size = System::Drawing::Size(11, 18);
			this->label_Coordinates_lambda_minutes->TabIndex = 2;
			this->label_Coordinates_lambda_minutes->Text = L"\'";
			// 
			// label_Coordinates_fi_minutes
			// 
			this->label_Coordinates_fi_minutes->AutoSize = true;
			this->label_Coordinates_fi_minutes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_Coordinates_fi_minutes->Location = System::Drawing::Point(206, 27);
			this->label_Coordinates_fi_minutes->Name = L"label_Coordinates_fi_minutes";
			this->label_Coordinates_fi_minutes->Size = System::Drawing::Size(11, 18);
			this->label_Coordinates_fi_minutes->TabIndex = 2;
			this->label_Coordinates_fi_minutes->Text = L"\'";
			// 
			// label_Coordinates_lambda_deg
			// 
			this->label_Coordinates_lambda_deg->AutoSize = true;
			this->label_Coordinates_lambda_deg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_Coordinates_lambda_deg->Location = System::Drawing::Point(137, 53);
			this->label_Coordinates_lambda_deg->Name = L"label_Coordinates_lambda_deg";
			this->label_Coordinates_lambda_deg->Size = System::Drawing::Size(14, 18);
			this->label_Coordinates_lambda_deg->TabIndex = 1;
			this->label_Coordinates_lambda_deg->Text = L"°";
			// 
			// label_Coordinates_fi_deg
			// 
			this->label_Coordinates_fi_deg->AutoSize = true;
			this->label_Coordinates_fi_deg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_Coordinates_fi_deg->Location = System::Drawing::Point(137, 27);
			this->label_Coordinates_fi_deg->Name = L"label_Coordinates_fi_deg";
			this->label_Coordinates_fi_deg->Size = System::Drawing::Size(14, 18);
			this->label_Coordinates_fi_deg->TabIndex = 1;
			this->label_Coordinates_fi_deg->Text = L"°";
			// 
			// label_Coordinates_lambda
			// 
			this->label_Coordinates_lambda->AutoSize = true;
			this->label_Coordinates_lambda->Location = System::Drawing::Point(6, 57);
			this->label_Coordinates_lambda->Name = L"label_Coordinates_lambda";
			this->label_Coordinates_lambda->Size = System::Drawing::Size(50, 13);
			this->label_Coordinates_lambda->TabIndex = 1;
			this->label_Coordinates_lambda->Text = L"Долгота";
			// 
			// label_Coordinates_fi
			// 
			this->label_Coordinates_fi->AutoSize = true;
			this->label_Coordinates_fi->Location = System::Drawing::Point(6, 31);
			this->label_Coordinates_fi->Name = L"label_Coordinates_fi";
			this->label_Coordinates_fi->Size = System::Drawing::Size(45, 13);
			this->label_Coordinates_fi->TabIndex = 1;
			this->label_Coordinates_fi->Text = L"Широта";
			// 
			// textBox_Coordinates_lambda_minutes
			// 
			this->textBox_Coordinates_lambda_minutes->Location = System::Drawing::Point(154, 54);
			this->textBox_Coordinates_lambda_minutes->Name = L"textBox_Coordinates_lambda_minutes";
			this->textBox_Coordinates_lambda_minutes->Size = System::Drawing::Size(46, 20);
			this->textBox_Coordinates_lambda_minutes->TabIndex = 3;
			this->textBox_Coordinates_lambda_minutes->Text = L"37";
			// 
			// textBox_Coordinates_fi_minutes
			// 
			this->textBox_Coordinates_fi_minutes->Location = System::Drawing::Point(154, 28);
			this->textBox_Coordinates_fi_minutes->Name = L"textBox_Coordinates_fi_minutes";
			this->textBox_Coordinates_fi_minutes->Size = System::Drawing::Size(46, 20);
			this->textBox_Coordinates_fi_minutes->TabIndex = 1;
			this->textBox_Coordinates_fi_minutes->Text = L"45";
			// 
			// textBox_Coordinates_lambda_deg
			// 
			this->textBox_Coordinates_lambda_deg->Location = System::Drawing::Point(85, 54);
			this->textBox_Coordinates_lambda_deg->Name = L"textBox_Coordinates_lambda_deg";
			this->textBox_Coordinates_lambda_deg->Size = System::Drawing::Size(46, 20);
			this->textBox_Coordinates_lambda_deg->TabIndex = 2;
			this->textBox_Coordinates_lambda_deg->Text = L"37";
			// 
			// textBox_Coordinates_fi_deg
			// 
			this->textBox_Coordinates_fi_deg->Location = System::Drawing::Point(85, 28);
			this->textBox_Coordinates_fi_deg->Name = L"textBox_Coordinates_fi_deg";
			this->textBox_Coordinates_fi_deg->Size = System::Drawing::Size(46, 20);
			this->textBox_Coordinates_fi_deg->TabIndex = 0;
			this->textBox_Coordinates_fi_deg->Text = L"55";
			// 
			// textBox_Height
			// 
			this->textBox_Height->Location = System::Drawing::Point(833, 103);
			this->textBox_Height->Name = L"textBox_Height";
			this->textBox_Height->Size = System::Drawing::Size(63, 20);
			this->textBox_Height->TabIndex = 4;
			this->textBox_Height->Text = L"1";
			// 
			// label_Height
			// 
			this->label_Height->AutoSize = true;
			this->label_Height->Location = System::Drawing::Point(685, 106);
			this->label_Height->Name = L"label_Height";
			this->label_Height->Size = System::Drawing::Size(105, 13);
			this->label_Height->TabIndex = 1;
			this->label_Height->Text = L"Высота гномона, м";
			// 
			// comboBox_TimeZone
			// 
			this->comboBox_TimeZone->FormattingEnabled = true;
			this->comboBox_TimeZone->Items->AddRange(gcnew cli::array< System::Object^  >(25) {
				L"-12", L"-11", L"-10", L"-9", L"-8", L"-7",
					L"-6", L"-5", L"-4", L"-3", L"-2", L"-1", L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"11", L"12"
			});
			this->comboBox_TimeZone->Location = System::Drawing::Point(833, 129);
			this->comboBox_TimeZone->Name = L"comboBox_TimeZone";
			this->comboBox_TimeZone->Size = System::Drawing::Size(63, 21);
			this->comboBox_TimeZone->TabIndex = 6;
			// 
			// label_TimeZone
			// 
			this->label_TimeZone->AutoSize = true;
			this->label_TimeZone->Location = System::Drawing::Point(685, 132);
			this->label_TimeZone->Name = L"label_TimeZone";
			this->label_TimeZone->Size = System::Drawing::Size(78, 13);
			this->label_TimeZone->TabIndex = 7;
			this->label_TimeZone->Text = L"Часовой пояс";
			// 
			// label_Info
			// 
			this->label_Info->Location = System::Drawing::Point(688, 315);
			this->label_Info->Name = L"label_Info";
			this->label_Info->Size = System::Drawing::Size(214, 96);
			this->label_Info->TabIndex = 8;
			this->label_Info->Text = L"За основное время принимается Зимнее.\r\n\r\nЧтобы выбрать постоянное Летнее время, ч"
				L"асовой пояс нужно оставить для Зимнеего времени и отметить пункт \"Летнее время\"."
				L"";
			// 
			// button_ClearYear
			// 
			this->button_ClearYear->Location = System::Drawing::Point(441, 343);
			this->button_ClearYear->Name = L"button_ClearYear";
			this->button_ClearYear->Size = System::Drawing::Size(109, 23);
			this->button_ClearYear->TabIndex = 8;
			this->button_ClearYear->Text = L"Очистить график";
			this->button_ClearYear->UseVisualStyleBackColor = true;
			this->button_ClearYear->Click += gcnew System::EventHandler(this, &MyForm::button_ClearYear_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(914, 427);
			this->Controls->Add(this->label_Info);
			this->Controls->Add(this->label_TimeZone);
			this->Controls->Add(this->groupBox_Coordinates);
			this->Controls->Add(this->comboBox_TimeZone);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->textBox_Height);
			this->Controls->Add(this->label_Height);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Гномон и его тень";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->groupBox_Coordinates->ResumeLayout(false);
			this->groupBox_Coordinates->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_Modelling_Day_Click(System::Object^  sender, System::EventArgs^  e) 
	{

		label_InProgress->Visible = true;
		MyForm::Refresh();

		Coordinates coord =
		{
			Convert::ToDouble(textBox_Coordinates_fi_deg->Text),
			Convert::ToDouble(textBox_Coordinates_fi_minutes->Text),
			Convert::ToDouble(textBox_Coordinates_lambda_deg->Text),
			Convert::ToDouble(textBox_Coordinates_fi_minutes->Text)
		};

		TYPE height = Convert::ToDouble(textBox_Height->Text);

		DateTime raw_date;
		raw_date = Convert::ToDateTime(maskedTextBox_Date->Text);

		MyTime::Date date = { 0, 0, 0, 0, 0, 0 };
		date.day = raw_date.Day;
		date.month = raw_date.Month;
		date.year = raw_date.Year;

		UINT timeZone = Convert::ToInt32(comboBox_TimeZone->SelectedItem->ToString());

		CMatrix Result(GenerateShadow(date, coord, timeZone, height));

		chart1->Series->FindByName(L"Series1")->Points->Clear();	// стираем предыдущий результат
		chart1->Series->FindByName(L"Series1")->Points->Add(dataPoint_Gnomon);	// отобразили гномон

		for (int i = 0; i < Result.getRowCount(); i++)
		{
			if (abs(Result[i][0]) < 13){
				chart1->Series->FindByName(L"Series1")->Points->AddXY(Result[i][0], Result[i][1]);
			}
		}

		label_InProgress->Visible = false;
	}


	private: System::Void button_LightTime_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		label_InProgress_LightTime->Visible = true;
		MyForm::Refresh();

		Coordinates coord =
		{
			Convert::ToDouble(textBox_Coordinates_fi_deg->Text),
			Convert::ToDouble(textBox_Coordinates_fi_minutes->Text),
			Convert::ToDouble(textBox_Coordinates_lambda_deg->Text),
			Convert::ToDouble(textBox_Coordinates_fi_minutes->Text)
		};

		UINT timeZone = Convert::ToInt32(comboBox_TimeZone->SelectedItem->ToString());

		bool
			SummerTime	= checkedListBox_LightTime->GetItemChecked(0),
			WorkTime	= checkedListBox_LightTime->GetItemChecked(1),
			TimeSwitch	= checkedListBox_LightTime->GetItemChecked(2);

		if (SummerTime && !TimeSwitch) timeZone++;

		CVector Result(GetLightTime(coord, timeZone, WorkTime, TimeSwitch));

		// добавление результата в определённые графики, в зависимости от выбранного моделирования
		if (WorkTime) {
			if (TimeSwitch) {
				AddPoints(chart2->Series->FindByName(L"Series_Switch"), Result);
			}
			else {
				if (SummerTime) {
					AddPoints(chart2->Series->FindByName(L"Series_Summer"), Result);
				}
				else
					AddPoints(chart2->Series->FindByName(L"Series_Winter"), Result);
			}
		}
		else
			AddPoints(chart2->Series->FindByName(L"Series_InAll"), Result);


		label_InProgress_LightTime->Visible = false;
	}


	private: System::Void button_ClearYear_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		chart2->Series->FindByName(L"Series_Switch")->Points->Clear();
		chart2->Series->FindByName(L"Series_Summer")->Points->Clear();
		chart2->Series->FindByName(L"Series_Winter")->Points->Clear();
		chart2->Series->FindByName(L"Series_InAll")->Points->Clear();

		System::Windows::Forms::DataVisualization::Charting::DataPoint^  Empty_dataPoint = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0, 0));
		Empty_dataPoint->IsEmpty = true;

		chart2->Series->FindByName(L"Series_InAll")->Points->Add(Empty_dataPoint);	// отобразили гномон
	}


	private: System::Void checkedListBox_LightTime_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e) 
	{
		if (e->Index == 2)
		{
			if (checkedListBox_LightTime->GetItemCheckState(0) != CheckState::Unchecked)
				checkedListBox_LightTime->SetItemCheckState(0, CheckState::Unchecked);
		}

		if (e->Index == 0)
		{
			if (checkedListBox_LightTime->GetItemCheckState(2) != CheckState::Unchecked)
				checkedListBox_LightTime->SetItemCheckState(2, CheckState::Unchecked);
		}
	}

};
}