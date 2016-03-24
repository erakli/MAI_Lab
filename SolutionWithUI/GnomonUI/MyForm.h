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

			dataPoint_Gnomon = (gcnew System::Windows::Forms::DataVisualization::Charting::DataPoint(0, 0));
			dataPoint_Gnomon->MarkerColor = System::Drawing::Color::Red;
			dataPoint_Gnomon->MarkerSize = 7;
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
	private: System::Windows::Forms::Label^  label_InProcces;


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
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label_InProcces = (gcnew System::Windows::Forms::Label());
			this->label_Date = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox_Date = (gcnew System::Windows::Forms::MaskedTextBox());
			this->button_Modelling_Day = (gcnew System::Windows::Forms::Button());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
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
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
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
			this->tabControl1->Size = System::Drawing::Size(526, 403);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label_InProcces);
			this->tabPage1->Controls->Add(this->label_Date);
			this->tabPage1->Controls->Add(this->maskedTextBox_Date);
			this->tabPage1->Controls->Add(this->button_Modelling_Day);
			this->tabPage1->Controls->Add(this->chart1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(518, 377);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Движение тени";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label_InProcces
			// 
			this->label_InProcces->AutoSize = true;
			this->label_InProcces->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label_InProcces->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_InProcces->Location = System::Drawing::Point(188, 133);
			this->label_InProcces->Name = L"label_InProcces";
			this->label_InProcces->Size = System::Drawing::Size(174, 26);
			this->label_InProcces->TabIndex = 5;
			this->label_InProcces->Text = L"Моделирование...";
			this->label_InProcces->Visible = false;
			// 
			// label_Date
			// 
			this->label_Date->AutoSize = true;
			this->label_Date->Location = System::Drawing::Point(28, 339);
			this->label_Date->Name = L"label_Date";
			this->label_Date->Size = System::Drawing::Size(116, 13);
			this->label_Date->TabIndex = 4;
			this->label_Date->Text = L"Дата моделирования";
			// 
			// maskedTextBox_Date
			// 
			this->maskedTextBox_Date->Location = System::Drawing::Point(162, 336);
			this->maskedTextBox_Date->Mask = L"00/00/0000";
			this->maskedTextBox_Date->Name = L"maskedTextBox_Date";
			this->maskedTextBox_Date->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox_Date->TabIndex = 5;
			this->maskedTextBox_Date->Text = L"22062016";
			this->maskedTextBox_Date->ValidatingType = System::DateTime::typeid;
			// 
			// button_Modelling_Day
			// 
			this->button_Modelling_Day->Location = System::Drawing::Point(398, 334);
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
			chartArea1->AxisX->MajorGrid->LineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			chartArea1->AxisX->Maximum = 20;
			chartArea1->AxisX->Minimum = -20;
			chartArea1->AxisX->Title = L"Z, м";
			chartArea1->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
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
			this->chart1->Size = System::Drawing::Size(506, 319);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(518, 377);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
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
			this->groupBox_Coordinates->Location = System::Drawing::Point(544, 12);
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
			this->textBox_Height->Location = System::Drawing::Point(701, 105);
			this->textBox_Height->Name = L"textBox_Height";
			this->textBox_Height->Size = System::Drawing::Size(60, 20);
			this->textBox_Height->TabIndex = 4;
			this->textBox_Height->Text = L"1";
			// 
			// label_Height
			// 
			this->label_Height->AutoSize = true;
			this->label_Height->Location = System::Drawing::Point(550, 108);
			this->label_Height->Name = L"label_Height";
			this->label_Height->Size = System::Drawing::Size(105, 13);
			this->label_Height->TabIndex = 1;
			this->label_Height->Text = L"Высота гномона, м";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(779, 427);
			this->Controls->Add(this->groupBox_Coordinates);
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
			this->groupBox_Coordinates->ResumeLayout(false);
			this->groupBox_Coordinates->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_Modelling_Day_Click(System::Object^  sender, System::EventArgs^  e) {

		label_InProcces->Visible = true;
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

		CMatrix Result(GenerateShadow(date, coord, height));

		chart1->Series->FindByName(L"Series1")->Points->Clear();	// стираем предыдущий результат
		chart1->Series->FindByName(L"Series1")->Points->Add(dataPoint_Gnomon);	// отобразили гномон

		for (int i = 0; i < Result.getRowCount(); i++)
		{
			if (abs(Result[i][0]) < 13){
				chart1->Series->FindByName(L"Series1")->Points->AddXY(Result[i][0], Result[i][1]);
			}
		}

		label_InProcces->Visible = false;
	}
};
}
