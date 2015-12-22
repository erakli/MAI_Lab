#pragma once

#include "Types.h"
#include "Time.h"
#include "Coord_Transformation.h"
#include "Earth.h"
#include "Functions.h"
#include "Matrix_Operations.h"

namespace GelioGeo_transform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tBox_Date;
	private: System::Windows::Forms::GroupBox^  gBox_Gelio_Geo;
	private: System::Windows::Forms::Label^  label_Date;
	private: System::Windows::Forms::Label^  label_Gelio_Geo;
	private: System::Windows::Forms::GroupBox^  gBox_Gelio_Geo_Coord;
	private: System::Windows::Forms::Label^  label_Coord;
	private: System::Windows::Forms::TextBox^  tBox_Coord_x;
	private: System::Windows::Forms::GroupBox^  gBox_Date;
	private: System::Windows::Forms::ComboBox^  cBox_Date_Type;
	private: System::Windows::Forms::Label^  label_Date_Type;
	private: System::Windows::Forms::Label^  label_Coord_z;
	private: System::Windows::Forms::TextBox^  tBox_Coord_z;
	private: System::Windows::Forms::Label^  label_Coord_y;
	private: System::Windows::Forms::TextBox^  tBox_Coord_y;
	private: System::Windows::Forms::Label^  label_Coord_x;

	private: System::Windows::Forms::Button^  button_Convert;
	private: System::Windows::Forms::DataGridView^  dataGrid_Result;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::GroupBox^  gBox_Result;
	private: System::Windows::Forms::Label^  label_Result;
	private: System::Windows::Forms::TabControl^  tabControl;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::GroupBox^  gBox_vector;
	private: System::Windows::Forms::TextBox^  tBox_vector_x;




	private: System::Windows::Forms::GroupBox^  gBox_frac;
	private: System::Windows::Forms::Button^  button_frac;
	private: System::Windows::Forms::TextBox^  tBox_frac;
	private: System::Windows::Forms::GroupBox^  gBox_deg2rad;
	private: System::Windows::Forms::Label^  label_deg2rad;
	private: System::Windows::Forms::TextBox^  tBox_deg2rad;
	private: System::Windows::Forms::Button^  button_deg2rad;
	private: System::Windows::Forms::Button^  button_vector;
	private: System::Windows::Forms::TextBox^  tBox_vector_z;

	private: System::Windows::Forms::TextBox^  tBox_vector_y;
	private: System::Windows::Forms::Label^  label_vector_z;

	private: System::Windows::Forms::Label^  label_vector_y;



	private: System::Windows::Forms::Label^  label_vector_x;



	private: System::Windows::Forms::Label^  label_vector;
	private: System::Windows::Forms::ComboBox^  cBox_vector;
	private: System::Windows::Forms::GroupBox^  gBox_Time;
	private: System::Windows::Forms::ComboBox^  cBox_Time;
	private: System::Windows::Forms::Label^  label_Time;
	private: System::Windows::Forms::MaskedTextBox^  maskedTBox_Time;
	private: System::Windows::Forms::Button^  button_Time;
	private: System::Windows::Forms::Label^  label_Time2;
	private: System::Windows::Forms::MaskedTextBox^  maskedTBox_Date;
	private: System::Windows::Forms::Label^  label_result_functions;
	private: System::Windows::Forms::DataGridView^  dataGrid_Result2;

	private: System::Windows::Forms::GroupBox^  gBox_Earth;
	private: System::Windows::Forms::Button^  button_Earth;
	private: System::Windows::Forms::Label^  label_Earth;
	private: System::Windows::Forms::TextBox^  tBox_Earth;
	private: System::Windows::Forms::TextBox^  tBox_Time;





	private: System::Windows::Forms::Label^  label_vector_Date;
	private: System::Windows::Forms::TextBox^  tBox_vector_Date;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DataGridViewTextBoxColumn01;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DataGridViewTextBoxColumn4;
private: System::Windows::Forms::TabPage^  tabPage3;
private: System::Windows::Forms::DataGridView^  dataGrid_vector;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn7;
private: System::Windows::Forms::Label^  label_Matrix_vector;
private: System::Windows::Forms::DataGridView^  dataGrid_Matrix;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn10;
private: System::Windows::Forms::GroupBox^  gBox_Matrix;
private: System::Windows::Forms::RadioButton^  radioButton3;
private: System::Windows::Forms::RadioButton^  radioButton2;
private: System::Windows::Forms::RadioButton^  radioButton1;
private: System::Windows::Forms::Label^  label_Matrix_result;
private: System::Windows::Forms::Label^  label_Matrix;
private: System::Windows::Forms::DataGridView^  dataGrid_Matrix_result;

private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn11;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn12;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn13;
private: System::Windows::Forms::Button^  button_Mult;
private: System::Windows::Forms::Button^  button_RotMatr;
private: System::Windows::Forms::Label^  label_Matrix_angle;
private: System::Windows::Forms::TextBox^  tBox_Matrix_angle;
private: System::Windows::Forms::Label^  label_Matrix_RotMatr;




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
			this->tBox_Date = (gcnew System::Windows::Forms::TextBox());
			this->gBox_Gelio_Geo = (gcnew System::Windows::Forms::GroupBox());
			this->gBox_Result = (gcnew System::Windows::Forms::GroupBox());
			this->label_Result = (gcnew System::Windows::Forms::Label());
			this->dataGrid_Result = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button_Convert = (gcnew System::Windows::Forms::Button());
			this->gBox_Date = (gcnew System::Windows::Forms::GroupBox());
			this->maskedTBox_Date = (gcnew System::Windows::Forms::MaskedTextBox());
			this->cBox_Date_Type = (gcnew System::Windows::Forms::ComboBox());
			this->label_Date_Type = (gcnew System::Windows::Forms::Label());
			this->label_Date = (gcnew System::Windows::Forms::Label());
			this->gBox_Gelio_Geo_Coord = (gcnew System::Windows::Forms::GroupBox());
			this->label_Coord_z = (gcnew System::Windows::Forms::Label());
			this->tBox_Coord_z = (gcnew System::Windows::Forms::TextBox());
			this->label_Coord_y = (gcnew System::Windows::Forms::Label());
			this->tBox_Coord_y = (gcnew System::Windows::Forms::TextBox());
			this->label_Coord_x = (gcnew System::Windows::Forms::Label());
			this->label_Coord = (gcnew System::Windows::Forms::Label());
			this->tBox_Coord_x = (gcnew System::Windows::Forms::TextBox());
			this->label_Gelio_Geo = (gcnew System::Windows::Forms::Label());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->label_result_functions = (gcnew System::Windows::Forms::Label());
			this->dataGrid_Result2 = (gcnew System::Windows::Forms::DataGridView());
			this->DataGridViewTextBoxColumn01 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->gBox_Earth = (gcnew System::Windows::Forms::GroupBox());
			this->button_Earth = (gcnew System::Windows::Forms::Button());
			this->label_Earth = (gcnew System::Windows::Forms::Label());
			this->tBox_Earth = (gcnew System::Windows::Forms::TextBox());
			this->gBox_Time = (gcnew System::Windows::Forms::GroupBox());
			this->tBox_Time = (gcnew System::Windows::Forms::TextBox());
			this->button_Time = (gcnew System::Windows::Forms::Button());
			this->label_Time2 = (gcnew System::Windows::Forms::Label());
			this->cBox_Time = (gcnew System::Windows::Forms::ComboBox());
			this->label_Time = (gcnew System::Windows::Forms::Label());
			this->maskedTBox_Time = (gcnew System::Windows::Forms::MaskedTextBox());
			this->gBox_vector = (gcnew System::Windows::Forms::GroupBox());
			this->label_vector_Date = (gcnew System::Windows::Forms::Label());
			this->tBox_vector_Date = (gcnew System::Windows::Forms::TextBox());
			this->cBox_vector = (gcnew System::Windows::Forms::ComboBox());
			this->label_vector_z = (gcnew System::Windows::Forms::Label());
			this->label_vector_y = (gcnew System::Windows::Forms::Label());
			this->label_vector_x = (gcnew System::Windows::Forms::Label());
			this->label_vector = (gcnew System::Windows::Forms::Label());
			this->button_vector = (gcnew System::Windows::Forms::Button());
			this->tBox_vector_z = (gcnew System::Windows::Forms::TextBox());
			this->tBox_vector_y = (gcnew System::Windows::Forms::TextBox());
			this->tBox_vector_x = (gcnew System::Windows::Forms::TextBox());
			this->gBox_frac = (gcnew System::Windows::Forms::GroupBox());
			this->button_frac = (gcnew System::Windows::Forms::Button());
			this->tBox_frac = (gcnew System::Windows::Forms::TextBox());
			this->gBox_deg2rad = (gcnew System::Windows::Forms::GroupBox());
			this->label_deg2rad = (gcnew System::Windows::Forms::Label());
			this->tBox_deg2rad = (gcnew System::Windows::Forms::TextBox());
			this->button_deg2rad = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label_Matrix_result = (gcnew System::Windows::Forms::Label());
			this->label_Matrix = (gcnew System::Windows::Forms::Label());
			this->dataGrid_Matrix_result = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button_Mult = (gcnew System::Windows::Forms::Button());
			this->gBox_Matrix = (gcnew System::Windows::Forms::GroupBox());
			this->button_RotMatr = (gcnew System::Windows::Forms::Button());
			this->label_Matrix_angle = (gcnew System::Windows::Forms::Label());
			this->tBox_Matrix_angle = (gcnew System::Windows::Forms::TextBox());
			this->label_Matrix_RotMatr = (gcnew System::Windows::Forms::Label());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->dataGrid_Matrix = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label_Matrix_vector = (gcnew System::Windows::Forms::Label());
			this->dataGrid_vector = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->gBox_Gelio_Geo->SuspendLayout();
			this->gBox_Result->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Result))->BeginInit();
			this->gBox_Date->SuspendLayout();
			this->gBox_Gelio_Geo_Coord->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Result2))->BeginInit();
			this->gBox_Earth->SuspendLayout();
			this->gBox_Time->SuspendLayout();
			this->gBox_vector->SuspendLayout();
			this->gBox_frac->SuspendLayout();
			this->gBox_deg2rad->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Matrix_result))->BeginInit();
			this->gBox_Matrix->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Matrix))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_vector))->BeginInit();
			this->SuspendLayout();
			// 
			// tBox_Date
			// 
			this->tBox_Date->Location = System::Drawing::Point(94, 83);
			this->tBox_Date->Name = L"tBox_Date";
			this->tBox_Date->Size = System::Drawing::Size(100, 20);
			this->tBox_Date->TabIndex = 0;
			this->tBox_Date->Text = L"2450000";
			// 
			// gBox_Gelio_Geo
			// 
			this->gBox_Gelio_Geo->Controls->Add(this->gBox_Result);
			this->gBox_Gelio_Geo->Controls->Add(this->button_Convert);
			this->gBox_Gelio_Geo->Controls->Add(this->gBox_Date);
			this->gBox_Gelio_Geo->Controls->Add(this->gBox_Gelio_Geo_Coord);
			this->gBox_Gelio_Geo->Controls->Add(this->label_Gelio_Geo);
			this->gBox_Gelio_Geo->Location = System::Drawing::Point(6, 6);
			this->gBox_Gelio_Geo->Name = L"gBox_Gelio_Geo";
			this->gBox_Gelio_Geo->Size = System::Drawing::Size(511, 326);
			this->gBox_Gelio_Geo->TabIndex = 1;
			this->gBox_Gelio_Geo->TabStop = false;
			this->gBox_Gelio_Geo->Text = L"Перевод координат";
			// 
			// gBox_Result
			// 
			this->gBox_Result->Controls->Add(this->label_Result);
			this->gBox_Result->Controls->Add(this->dataGrid_Result);
			this->gBox_Result->Location = System::Drawing::Point(158, 201);
			this->gBox_Result->Name = L"gBox_Result";
			this->gBox_Result->Size = System::Drawing::Size(303, 119);
			this->gBox_Result->TabIndex = 8;
			this->gBox_Result->TabStop = false;
			this->gBox_Result->Text = L"Результат преобразования";
			// 
			// label_Result
			// 
			this->label_Result->AutoSize = true;
			this->label_Result->Location = System::Drawing::Point(6, 21);
			this->label_Result->Name = L"label_Result";
			this->label_Result->Size = System::Drawing::Size(188, 13);
			this->label_Result->TabIndex = 8;
			this->label_Result->Text = L"Геоцентрические координаты, в км";
			// 
			// dataGrid_Result
			// 
			this->dataGrid_Result->AllowUserToAddRows = false;
			this->dataGrid_Result->AllowUserToDeleteRows = false;
			this->dataGrid_Result->AllowUserToResizeColumns = false;
			this->dataGrid_Result->AllowUserToResizeRows = false;
			this->dataGrid_Result->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGrid_Result->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1,
					this->Column2, this->Column3
			});
			this->dataGrid_Result->Location = System::Drawing::Point(9, 50);
			this->dataGrid_Result->Name = L"dataGrid_Result";
			this->dataGrid_Result->ReadOnly = true;
			this->dataGrid_Result->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGrid_Result->RowTemplate->DefaultCellStyle->NullValue = L"0";
			this->dataGrid_Result->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGrid_Result->Size = System::Drawing::Size(288, 63);
			this->dataGrid_Result->TabIndex = 7;
			// 
			// Column1
			// 
			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column1->HeaderText = L"X";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			// 
			// Column2
			// 
			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column2->HeaderText = L"Y";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column3->HeaderText = L"Z";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// button_Convert
			// 
			this->button_Convert->Location = System::Drawing::Point(33, 251);
			this->button_Convert->Name = L"button_Convert";
			this->button_Convert->Size = System::Drawing::Size(103, 34);
			this->button_Convert->TabIndex = 6;
			this->button_Convert->Text = L"Конвертировать";
			this->button_Convert->UseVisualStyleBackColor = true;
			this->button_Convert->Click += gcnew System::EventHandler(this, &MainForm::button_Convert_Click);
			// 
			// gBox_Date
			// 
			this->gBox_Date->Controls->Add(this->maskedTBox_Date);
			this->gBox_Date->Controls->Add(this->cBox_Date_Type);
			this->gBox_Date->Controls->Add(this->label_Date_Type);
			this->gBox_Date->Controls->Add(this->label_Date);
			this->gBox_Date->Controls->Add(this->tBox_Date);
			this->gBox_Date->Location = System::Drawing::Point(245, 73);
			this->gBox_Date->Name = L"gBox_Date";
			this->gBox_Date->Size = System::Drawing::Size(216, 122);
			this->gBox_Date->TabIndex = 5;
			this->gBox_Date->TabStop = false;
			this->gBox_Date->Text = L"Дата перевода координат";
			// 
			// maskedTBox_Date
			// 
			this->maskedTBox_Date->Location = System::Drawing::Point(94, 83);
			this->maskedTBox_Date->Mask = L"00/00/0000";
			this->maskedTBox_Date->Name = L"maskedTBox_Date";
			this->maskedTBox_Date->Size = System::Drawing::Size(100, 20);
			this->maskedTBox_Date->TabIndex = 5;
			this->maskedTBox_Date->Text = L"01022010";
			this->maskedTBox_Date->ValidatingType = System::DateTime::typeid;
			this->maskedTBox_Date->Visible = false;
			// 
			// cBox_Date_Type
			// 
			this->cBox_Date_Type->FormattingEnabled = true;
			this->cBox_Date_Type->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Юлианский день", L"Григорианский календарь" });
			this->cBox_Date_Type->Location = System::Drawing::Point(52, 46);
			this->cBox_Date_Type->Name = L"cBox_Date_Type";
			this->cBox_Date_Type->Size = System::Drawing::Size(142, 21);
			this->cBox_Date_Type->TabIndex = 4;
			this->cBox_Date_Type->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cBox_Date_Type_SelectedIndexChanged);
			// 
			// label_Date_Type
			// 
			this->label_Date_Type->AutoSize = true;
			this->label_Date_Type->Location = System::Drawing::Point(29, 27);
			this->label_Date_Type->Name = L"label_Date_Type";
			this->label_Date_Type->Size = System::Drawing::Size(107, 13);
			this->label_Date_Type->TabIndex = 3;
			this->label_Date_Type->Text = L"Тип вводимой даты";
			// 
			// label_Date
			// 
			this->label_Date->AutoSize = true;
			this->label_Date->Location = System::Drawing::Point(29, 86);
			this->label_Date->Name = L"label_Date";
			this->label_Date->Size = System::Drawing::Size(33, 13);
			this->label_Date->TabIndex = 2;
			this->label_Date->Text = L"Дата";
			// 
			// gBox_Gelio_Geo_Coord
			// 
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->label_Coord_z);
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->tBox_Coord_z);
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->label_Coord_y);
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->tBox_Coord_y);
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->label_Coord_x);
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->label_Coord);
			this->gBox_Gelio_Geo_Coord->Controls->Add(this->tBox_Coord_x);
			this->gBox_Gelio_Geo_Coord->Location = System::Drawing::Point(33, 73);
			this->gBox_Gelio_Geo_Coord->Name = L"gBox_Gelio_Geo_Coord";
			this->gBox_Gelio_Geo_Coord->Size = System::Drawing::Size(200, 122);
			this->gBox_Gelio_Geo_Coord->TabIndex = 4;
			this->gBox_Gelio_Geo_Coord->TabStop = false;
			this->gBox_Gelio_Geo_Coord->Text = L"Исходные координаты тела";
			// 
			// label_Coord_z
			// 
			this->label_Coord_z->AutoSize = true;
			this->label_Coord_z->Location = System::Drawing::Point(25, 94);
			this->label_Coord_z->Name = L"label_Coord_z";
			this->label_Coord_z->Size = System::Drawing::Size(14, 13);
			this->label_Coord_z->TabIndex = 9;
			this->label_Coord_z->Text = L"Z";
			// 
			// tBox_Coord_z
			// 
			this->tBox_Coord_z->Location = System::Drawing::Point(87, 91);
			this->tBox_Coord_z->Name = L"tBox_Coord_z";
			this->tBox_Coord_z->Size = System::Drawing::Size(100, 20);
			this->tBox_Coord_z->TabIndex = 8;
			this->tBox_Coord_z->Text = L"100";
			// 
			// label_Coord_y
			// 
			this->label_Coord_y->AutoSize = true;
			this->label_Coord_y->Location = System::Drawing::Point(25, 68);
			this->label_Coord_y->Name = L"label_Coord_y";
			this->label_Coord_y->Size = System::Drawing::Size(14, 13);
			this->label_Coord_y->TabIndex = 7;
			this->label_Coord_y->Text = L"Y";
			// 
			// tBox_Coord_y
			// 
			this->tBox_Coord_y->Location = System::Drawing::Point(87, 65);
			this->tBox_Coord_y->Name = L"tBox_Coord_y";
			this->tBox_Coord_y->Size = System::Drawing::Size(100, 20);
			this->tBox_Coord_y->TabIndex = 6;
			this->tBox_Coord_y->Text = L"100";
			// 
			// label_Coord_x
			// 
			this->label_Coord_x->AutoSize = true;
			this->label_Coord_x->Location = System::Drawing::Point(25, 42);
			this->label_Coord_x->Name = L"label_Coord_x";
			this->label_Coord_x->Size = System::Drawing::Size(14, 13);
			this->label_Coord_x->TabIndex = 5;
			this->label_Coord_x->Text = L"X";
			// 
			// label_Coord
			// 
			this->label_Coord->AutoSize = true;
			this->label_Coord->Location = System::Drawing::Point(6, 16);
			this->label_Coord->Name = L"label_Coord";
			this->label_Coord->Size = System::Drawing::Size(98, 13);
			this->label_Coord->TabIndex = 4;
			this->label_Coord->Text = L"Координаты в км:";
			// 
			// tBox_Coord_x
			// 
			this->tBox_Coord_x->Location = System::Drawing::Point(87, 39);
			this->tBox_Coord_x->Name = L"tBox_Coord_x";
			this->tBox_Coord_x->Size = System::Drawing::Size(100, 20);
			this->tBox_Coord_x->TabIndex = 3;
			this->tBox_Coord_x->Text = L"100";
			// 
			// label_Gelio_Geo
			// 
			this->label_Gelio_Geo->AutoSize = true;
			this->label_Gelio_Geo->Location = System::Drawing::Point(30, 31);
			this->label_Gelio_Geo->Name = L"label_Gelio_Geo";
			this->label_Gelio_Geo->Size = System::Drawing::Size(322, 26);
			this->label_Gelio_Geo->TabIndex = 1;
			this->label_Gelio_Geo->Text = L"Перевод Гелиоцентрических координат в инерциальной СК в \r\nГеоцентрические связанн"
				L"ые.";
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Controls->Add(this->tabPage3);
			this->tabControl->Location = System::Drawing::Point(12, 12);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(531, 362);
			this->tabControl->TabIndex = 9;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->gBox_Gelio_Geo);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(523, 336);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Перевод координат";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->label_result_functions);
			this->tabPage2->Controls->Add(this->dataGrid_Result2);
			this->tabPage2->Controls->Add(this->gBox_Earth);
			this->tabPage2->Controls->Add(this->gBox_Time);
			this->tabPage2->Controls->Add(this->gBox_vector);
			this->tabPage2->Controls->Add(this->gBox_frac);
			this->tabPage2->Controls->Add(this->gBox_deg2rad);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(523, 336);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Разные функции";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// label_result_functions
			// 
			this->label_result_functions->AutoSize = true;
			this->label_result_functions->Location = System::Drawing::Point(417, 210);
			this->label_result_functions->Name = L"label_result_functions";
			this->label_result_functions->Size = System::Drawing::Size(100, 13);
			this->label_result_functions->TabIndex = 9;
			this->label_result_functions->Text = L"Вывод результата";
			// 
			// dataGrid_Result2
			// 
			this->dataGrid_Result2->AllowUserToAddRows = false;
			this->dataGrid_Result2->AllowUserToDeleteRows = false;
			this->dataGrid_Result2->AllowUserToResizeColumns = false;
			this->dataGrid_Result2->AllowUserToResizeRows = false;
			this->dataGrid_Result2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGrid_Result2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->DataGridViewTextBoxColumn01,
					this->dataGridViewTextBoxColumn1, this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3, this->DataGridViewTextBoxColumn4
			});
			this->dataGrid_Result2->Location = System::Drawing::Point(6, 226);
			this->dataGrid_Result2->Name = L"dataGrid_Result2";
			this->dataGrid_Result2->ReadOnly = true;
			this->dataGrid_Result2->RowHeadersWidth = 20;
			this->dataGrid_Result2->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGrid_Result2->RowTemplate->DefaultCellStyle->NullValue = L"0";
			this->dataGrid_Result2->Size = System::Drawing::Size(511, 104);
			this->dataGrid_Result2->TabIndex = 8;
			// 
			// DataGridViewTextBoxColumn01
			// 
			this->DataGridViewTextBoxColumn01->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->DataGridViewTextBoxColumn01->HeaderText = L"Func";
			this->DataGridViewTextBoxColumn01->Name = L"DataGridViewTextBoxColumn01";
			this->DataGridViewTextBoxColumn01->ReadOnly = true;
			this->DataGridViewTextBoxColumn01->Width = 56;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->dataGridViewTextBoxColumn1->HeaderText = L"X";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->Width = 39;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->dataGridViewTextBoxColumn2->HeaderText = L"Y";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			this->dataGridViewTextBoxColumn2->Width = 39;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->dataGridViewTextBoxColumn3->HeaderText = L"Z";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			this->dataGridViewTextBoxColumn3->Width = 39;
			// 
			// DataGridViewTextBoxColumn4
			// 
			this->DataGridViewTextBoxColumn4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->DataGridViewTextBoxColumn4->HeaderText = L"Num";
			this->DataGridViewTextBoxColumn4->Name = L"DataGridViewTextBoxColumn4";
			this->DataGridViewTextBoxColumn4->ReadOnly = true;
			// 
			// gBox_Earth
			// 
			this->gBox_Earth->Controls->Add(this->button_Earth);
			this->gBox_Earth->Controls->Add(this->label_Earth);
			this->gBox_Earth->Controls->Add(this->tBox_Earth);
			this->gBox_Earth->Location = System::Drawing::Point(325, 6);
			this->gBox_Earth->Name = L"gBox_Earth";
			this->gBox_Earth->Size = System::Drawing::Size(192, 75);
			this->gBox_Earth->TabIndex = 6;
			this->gBox_Earth->TabStop = false;
			this->gBox_Earth->Text = L"Earth functions";
			// 
			// button_Earth
			// 
			this->button_Earth->Location = System::Drawing::Point(111, 30);
			this->button_Earth->Name = L"button_Earth";
			this->button_Earth->Size = System::Drawing::Size(75, 23);
			this->button_Earth->TabIndex = 6;
			this->button_Earth->Text = L"Run";
			this->button_Earth->UseVisualStyleBackColor = true;
			this->button_Earth->Click += gcnew System::EventHandler(this, &MainForm::button_Earth_Click);
			// 
			// label_Earth
			// 
			this->label_Earth->AutoSize = true;
			this->label_Earth->Location = System::Drawing::Point(6, 16);
			this->label_Earth->Name = L"label_Earth";
			this->label_Earth->Size = System::Drawing::Size(46, 13);
			this->label_Earth->TabIndex = 5;
			this->label_Earth->Text = L"JD Date";
			// 
			// tBox_Earth
			// 
			this->tBox_Earth->Location = System::Drawing::Point(9, 32);
			this->tBox_Earth->Name = L"tBox_Earth";
			this->tBox_Earth->Size = System::Drawing::Size(87, 20);
			this->tBox_Earth->TabIndex = 0;
			this->tBox_Earth->Text = L"2450000";
			// 
			// gBox_Time
			// 
			this->gBox_Time->Controls->Add(this->tBox_Time);
			this->gBox_Time->Controls->Add(this->button_Time);
			this->gBox_Time->Controls->Add(this->label_Time2);
			this->gBox_Time->Controls->Add(this->cBox_Time);
			this->gBox_Time->Controls->Add(this->label_Time);
			this->gBox_Time->Controls->Add(this->maskedTBox_Time);
			this->gBox_Time->Location = System::Drawing::Point(260, 87);
			this->gBox_Time->Name = L"gBox_Time";
			this->gBox_Time->Size = System::Drawing::Size(257, 89);
			this->gBox_Time->TabIndex = 5;
			this->gBox_Time->TabStop = false;
			this->gBox_Time->Text = L"Time functions";
			// 
			// tBox_Time
			// 
			this->tBox_Time->Location = System::Drawing::Point(65, 56);
			this->tBox_Time->Name = L"tBox_Time";
			this->tBox_Time->Size = System::Drawing::Size(100, 20);
			this->tBox_Time->TabIndex = 14;
			this->tBox_Time->Text = L"2450000";
			this->tBox_Time->Visible = false;
			// 
			// button_Time
			// 
			this->button_Time->Location = System::Drawing::Point(171, 54);
			this->button_Time->Name = L"button_Time";
			this->button_Time->Size = System::Drawing::Size(75, 23);
			this->button_Time->TabIndex = 13;
			this->button_Time->Text = L"Run";
			this->button_Time->UseVisualStyleBackColor = true;
			this->button_Time->Click += gcnew System::EventHandler(this, &MainForm::button_Time_Click);
			// 
			// label_Time2
			// 
			this->label_Time2->AutoSize = true;
			this->label_Time2->Location = System::Drawing::Point(6, 59);
			this->label_Time2->Name = L"label_Time2";
			this->label_Time2->Size = System::Drawing::Size(33, 13);
			this->label_Time2->TabIndex = 12;
			this->label_Time2->Text = L"Дата";
			// 
			// cBox_Time
			// 
			this->cBox_Time->FormattingEnabled = true;
			this->cBox_Time->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Date2JD", L"JD2Date", L"LeapYear", L"DayNumber" });
			this->cBox_Time->Location = System::Drawing::Point(125, 23);
			this->cBox_Time->Name = L"cBox_Time";
			this->cBox_Time->Size = System::Drawing::Size(121, 21);
			this->cBox_Time->TabIndex = 11;
			this->cBox_Time->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cBox_Time_SelectedIndexChanged);
			// 
			// label_Time
			// 
			this->label_Time->AutoSize = true;
			this->label_Time->Location = System::Drawing::Point(6, 26);
			this->label_Time->Name = L"label_Time";
			this->label_Time->Size = System::Drawing::Size(104, 13);
			this->label_Time->TabIndex = 10;
			this->label_Time->Text = L"Выбрать операцию";
			// 
			// maskedTBox_Time
			// 
			this->maskedTBox_Time->Location = System::Drawing::Point(65, 56);
			this->maskedTBox_Time->Mask = L"00/00/0000";
			this->maskedTBox_Time->Name = L"maskedTBox_Time";
			this->maskedTBox_Time->Size = System::Drawing::Size(100, 20);
			this->maskedTBox_Time->TabIndex = 0;
			this->maskedTBox_Time->Text = L"01022010";
			this->maskedTBox_Time->ValidatingType = System::DateTime::typeid;
			// 
			// gBox_vector
			// 
			this->gBox_vector->Controls->Add(this->label_vector_Date);
			this->gBox_vector->Controls->Add(this->tBox_vector_Date);
			this->gBox_vector->Controls->Add(this->cBox_vector);
			this->gBox_vector->Controls->Add(this->label_vector_z);
			this->gBox_vector->Controls->Add(this->label_vector_y);
			this->gBox_vector->Controls->Add(this->label_vector_x);
			this->gBox_vector->Controls->Add(this->label_vector);
			this->gBox_vector->Controls->Add(this->button_vector);
			this->gBox_vector->Controls->Add(this->tBox_vector_z);
			this->gBox_vector->Controls->Add(this->tBox_vector_y);
			this->gBox_vector->Controls->Add(this->tBox_vector_x);
			this->gBox_vector->Location = System::Drawing::Point(6, 87);
			this->gBox_vector->Name = L"gBox_vector";
			this->gBox_vector->Size = System::Drawing::Size(248, 133);
			this->gBox_vector->TabIndex = 4;
			this->gBox_vector->TabStop = false;
			this->gBox_vector->Text = L"Vector functions";
			// 
			// label_vector_Date
			// 
			this->label_vector_Date->AutoSize = true;
			this->label_vector_Date->Location = System::Drawing::Point(7, 88);
			this->label_vector_Date->Name = L"label_vector_Date";
			this->label_vector_Date->Size = System::Drawing::Size(33, 13);
			this->label_vector_Date->TabIndex = 11;
			this->label_vector_Date->Text = L"Дата";
			// 
			// tBox_vector_Date
			// 
			this->tBox_vector_Date->Location = System::Drawing::Point(10, 104);
			this->tBox_vector_Date->Name = L"tBox_vector_Date";
			this->tBox_vector_Date->Size = System::Drawing::Size(100, 20);
			this->tBox_vector_Date->TabIndex = 10;
			this->tBox_vector_Date->Text = L"2450000";
			// 
			// cBox_vector
			// 
			this->cBox_vector->FormattingEnabled = true;
			this->cBox_vector->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"module", L"Spher2Fix", L"Fix2Spher", L"GeoPos",
					L"Cel2Fix"
			});
			this->cBox_vector->Location = System::Drawing::Point(10, 42);
			this->cBox_vector->Name = L"cBox_vector";
			this->cBox_vector->Size = System::Drawing::Size(118, 21);
			this->cBox_vector->TabIndex = 9;
			this->cBox_vector->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cBox_vector_SelectedIndexChanged);
			// 
			// label_vector_z
			// 
			this->label_vector_z->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label_vector_z->Location = System::Drawing::Point(101, 78);
			this->label_vector_z->Name = L"label_vector_z";
			this->label_vector_z->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->label_vector_z->Size = System::Drawing::Size(47, 16);
			this->label_vector_z->TabIndex = 8;
			this->label_vector_z->Text = L"Z";
			this->label_vector_z->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label_vector_y
			// 
			this->label_vector_y->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label_vector_y->AutoSize = true;
			this->label_vector_y->Location = System::Drawing::Point(134, 55);
			this->label_vector_y->Name = L"label_vector_y";
			this->label_vector_y->Size = System::Drawing::Size(14, 13);
			this->label_vector_y->TabIndex = 6;
			this->label_vector_y->Text = L"Y";
			this->label_vector_y->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			// 
			// label_vector_x
			// 
			this->label_vector_x->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label_vector_x->AutoSize = true;
			this->label_vector_x->Location = System::Drawing::Point(134, 29);
			this->label_vector_x->Name = L"label_vector_x";
			this->label_vector_x->Size = System::Drawing::Size(14, 13);
			this->label_vector_x->TabIndex = 5;
			this->label_vector_x->Text = L"X";
			this->label_vector_x->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			// 
			// label_vector
			// 
			this->label_vector->AutoSize = true;
			this->label_vector->Location = System::Drawing::Point(6, 26);
			this->label_vector->Name = L"label_vector";
			this->label_vector->Size = System::Drawing::Size(104, 13);
			this->label_vector->TabIndex = 4;
			this->label_vector->Text = L"Выбрать операцию";
			// 
			// button_vector
			// 
			this->button_vector->Location = System::Drawing::Point(167, 104);
			this->button_vector->Name = L"button_vector";
			this->button_vector->Size = System::Drawing::Size(75, 23);
			this->button_vector->TabIndex = 3;
			this->button_vector->Text = L"Run";
			this->button_vector->UseVisualStyleBackColor = true;
			this->button_vector->Click += gcnew System::EventHandler(this, &MainForm::button_vector_Click);
			// 
			// tBox_vector_z
			// 
			this->tBox_vector_z->Location = System::Drawing::Point(154, 78);
			this->tBox_vector_z->Name = L"tBox_vector_z";
			this->tBox_vector_z->Size = System::Drawing::Size(88, 20);
			this->tBox_vector_z->TabIndex = 2;
			this->tBox_vector_z->Text = L"100";
			// 
			// tBox_vector_y
			// 
			this->tBox_vector_y->Location = System::Drawing::Point(154, 52);
			this->tBox_vector_y->Name = L"tBox_vector_y";
			this->tBox_vector_y->Size = System::Drawing::Size(88, 20);
			this->tBox_vector_y->TabIndex = 1;
			this->tBox_vector_y->Text = L"100";
			// 
			// tBox_vector_x
			// 
			this->tBox_vector_x->Location = System::Drawing::Point(154, 26);
			this->tBox_vector_x->Name = L"tBox_vector_x";
			this->tBox_vector_x->Size = System::Drawing::Size(88, 20);
			this->tBox_vector_x->TabIndex = 0;
			this->tBox_vector_x->Text = L"100";
			// 
			// gBox_frac
			// 
			this->gBox_frac->Controls->Add(this->button_frac);
			this->gBox_frac->Controls->Add(this->tBox_frac);
			this->gBox_frac->Location = System::Drawing::Point(207, 6);
			this->gBox_frac->Name = L"gBox_frac";
			this->gBox_frac->Size = System::Drawing::Size(112, 75);
			this->gBox_frac->TabIndex = 3;
			this->gBox_frac->TabStop = false;
			this->gBox_frac->Text = L"frac function";
			// 
			// button_frac
			// 
			this->button_frac->Location = System::Drawing::Point(31, 42);
			this->button_frac->Name = L"button_frac";
			this->button_frac->Size = System::Drawing::Size(75, 23);
			this->button_frac->TabIndex = 1;
			this->button_frac->Text = L"frac";
			this->button_frac->UseVisualStyleBackColor = true;
			this->button_frac->Click += gcnew System::EventHandler(this, &MainForm::button_frac_Click);
			// 
			// tBox_frac
			// 
			this->tBox_frac->Location = System::Drawing::Point(6, 18);
			this->tBox_frac->Name = L"tBox_frac";
			this->tBox_frac->Size = System::Drawing::Size(100, 20);
			this->tBox_frac->TabIndex = 0;
			this->tBox_frac->Text = L"13.45";
			// 
			// gBox_deg2rad
			// 
			this->gBox_deg2rad->Controls->Add(this->label_deg2rad);
			this->gBox_deg2rad->Controls->Add(this->tBox_deg2rad);
			this->gBox_deg2rad->Controls->Add(this->button_deg2rad);
			this->gBox_deg2rad->Location = System::Drawing::Point(6, 6);
			this->gBox_deg2rad->Name = L"gBox_deg2rad";
			this->gBox_deg2rad->Size = System::Drawing::Size(195, 75);
			this->gBox_deg2rad->TabIndex = 2;
			this->gBox_deg2rad->TabStop = false;
			this->gBox_deg2rad->Text = L"Перевод из градусов в радианы";
			// 
			// label_deg2rad
			// 
			this->label_deg2rad->AutoSize = true;
			this->label_deg2rad->Location = System::Drawing::Point(7, 25);
			this->label_deg2rad->Name = L"label_deg2rad";
			this->label_deg2rad->Size = System::Drawing::Size(94, 13);
			this->label_deg2rad->TabIndex = 2;
			this->label_deg2rad->Text = L"Введите градусы";
			// 
			// tBox_deg2rad
			// 
			this->tBox_deg2rad->Location = System::Drawing::Point(9, 42);
			this->tBox_deg2rad->Name = L"tBox_deg2rad";
			this->tBox_deg2rad->Size = System::Drawing::Size(100, 20);
			this->tBox_deg2rad->TabIndex = 1;
			this->tBox_deg2rad->Text = L"45";
			// 
			// button_deg2rad
			// 
			this->button_deg2rad->Location = System::Drawing::Point(115, 42);
			this->button_deg2rad->Name = L"button_deg2rad";
			this->button_deg2rad->Size = System::Drawing::Size(75, 23);
			this->button_deg2rad->TabIndex = 0;
			this->button_deg2rad->Text = L"deg2rad";
			this->button_deg2rad->UseVisualStyleBackColor = true;
			this->button_deg2rad->Click += gcnew System::EventHandler(this, &MainForm::button_deg2rad_Click);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->label_Matrix_result);
			this->tabPage3->Controls->Add(this->label_Matrix);
			this->tabPage3->Controls->Add(this->dataGrid_Matrix_result);
			this->tabPage3->Controls->Add(this->button_Mult);
			this->tabPage3->Controls->Add(this->gBox_Matrix);
			this->tabPage3->Controls->Add(this->dataGrid_Matrix);
			this->tabPage3->Controls->Add(this->label_Matrix_vector);
			this->tabPage3->Controls->Add(this->dataGrid_vector);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(523, 336);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Matrix Operations";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// label_Matrix_result
			// 
			this->label_Matrix_result->AutoSize = true;
			this->label_Matrix_result->Location = System::Drawing::Point(3, 257);
			this->label_Matrix_result->Name = L"label_Matrix_result";
			this->label_Matrix_result->Size = System::Drawing::Size(59, 13);
			this->label_Matrix_result->TabIndex = 19;
			this->label_Matrix_result->Text = L"Результат";
			// 
			// label_Matrix
			// 
			this->label_Matrix->AutoSize = true;
			this->label_Matrix->Location = System::Drawing::Point(3, 15);
			this->label_Matrix->Name = L"label_Matrix";
			this->label_Matrix->Size = System::Drawing::Size(51, 13);
			this->label_Matrix->TabIndex = 18;
			this->label_Matrix->Text = L"Матрица";
			// 
			// dataGrid_Matrix_result
			// 
			this->dataGrid_Matrix_result->AllowUserToAddRows = false;
			this->dataGrid_Matrix_result->AllowUserToDeleteRows = false;
			this->dataGrid_Matrix_result->AllowUserToResizeColumns = false;
			this->dataGrid_Matrix_result->AllowUserToResizeRows = false;
			this->dataGrid_Matrix_result->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dataGrid_Matrix_result->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGrid_Matrix_result->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->dataGridViewTextBoxColumn11,
					this->dataGridViewTextBoxColumn12, this->dataGridViewTextBoxColumn13
			});
			this->dataGrid_Matrix_result->Location = System::Drawing::Point(3, 273);
			this->dataGrid_Matrix_result->Name = L"dataGrid_Matrix_result";
			this->dataGrid_Matrix_result->RowHeadersWidth = 20;
			this->dataGrid_Matrix_result->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGrid_Matrix_result->RowTemplate->DefaultCellStyle->NullValue = L"0";
			this->dataGrid_Matrix_result->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGrid_Matrix_result->Size = System::Drawing::Size(288, 60);
			this->dataGrid_Matrix_result->TabIndex = 17;
			// 
			// dataGridViewTextBoxColumn11
			// 
			this->dataGridViewTextBoxColumn11->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn11->HeaderText = L"X";
			this->dataGridViewTextBoxColumn11->Name = L"dataGridViewTextBoxColumn11";
			// 
			// dataGridViewTextBoxColumn12
			// 
			this->dataGridViewTextBoxColumn12->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn12->HeaderText = L"Y";
			this->dataGridViewTextBoxColumn12->Name = L"dataGridViewTextBoxColumn12";
			// 
			// dataGridViewTextBoxColumn13
			// 
			this->dataGridViewTextBoxColumn13->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn13->HeaderText = L"Z";
			this->dataGridViewTextBoxColumn13->Name = L"dataGridViewTextBoxColumn13";
			// 
			// button_Mult
			// 
			this->button_Mult->Location = System::Drawing::Point(216, 224);
			this->button_Mult->Name = L"button_Mult";
			this->button_Mult->Size = System::Drawing::Size(75, 23);
			this->button_Mult->TabIndex = 16;
			this->button_Mult->Text = L"Mult";
			this->button_Mult->UseVisualStyleBackColor = true;
			this->button_Mult->Click += gcnew System::EventHandler(this, &MainForm::button_Mult_Click);
			// 
			// gBox_Matrix
			// 
			this->gBox_Matrix->Controls->Add(this->button_RotMatr);
			this->gBox_Matrix->Controls->Add(this->label_Matrix_angle);
			this->gBox_Matrix->Controls->Add(this->tBox_Matrix_angle);
			this->gBox_Matrix->Controls->Add(this->label_Matrix_RotMatr);
			this->gBox_Matrix->Controls->Add(this->radioButton3);
			this->gBox_Matrix->Controls->Add(this->radioButton2);
			this->gBox_Matrix->Controls->Add(this->radioButton1);
			this->gBox_Matrix->Location = System::Drawing::Point(309, 31);
			this->gBox_Matrix->Name = L"gBox_Matrix";
			this->gBox_Matrix->Size = System::Drawing::Size(200, 120);
			this->gBox_Matrix->TabIndex = 11;
			this->gBox_Matrix->TabStop = false;
			this->gBox_Matrix->Text = L"Создание матрицы поворота";
			// 
			// button_RotMatr
			// 
			this->button_RotMatr->Location = System::Drawing::Point(119, 83);
			this->button_RotMatr->Name = L"button_RotMatr";
			this->button_RotMatr->Size = System::Drawing::Size(75, 23);
			this->button_RotMatr->TabIndex = 15;
			this->button_RotMatr->Text = L"RotMatr";
			this->button_RotMatr->UseVisualStyleBackColor = true;
			this->button_RotMatr->Click += gcnew System::EventHandler(this, &MainForm::button_RotMatr_Click);
			// 
			// label_Matrix_angle
			// 
			this->label_Matrix_angle->AutoSize = true;
			this->label_Matrix_angle->Location = System::Drawing::Point(111, 27);
			this->label_Matrix_angle->Name = L"label_Matrix_angle";
			this->label_Matrix_angle->Size = System::Drawing::Size(32, 13);
			this->label_Matrix_angle->TabIndex = 14;
			this->label_Matrix_angle->Text = L"Угол";
			// 
			// tBox_Matrix_angle
			// 
			this->tBox_Matrix_angle->Location = System::Drawing::Point(114, 52);
			this->tBox_Matrix_angle->Name = L"tBox_Matrix_angle";
			this->tBox_Matrix_angle->Size = System::Drawing::Size(80, 20);
			this->tBox_Matrix_angle->TabIndex = 13;
			this->tBox_Matrix_angle->Text = L"45";
			// 
			// label_Matrix_RotMatr
			// 
			this->label_Matrix_RotMatr->AutoSize = true;
			this->label_Matrix_RotMatr->Location = System::Drawing::Point(6, 27);
			this->label_Matrix_RotMatr->Name = L"label_Matrix_RotMatr";
			this->label_Matrix_RotMatr->Size = System::Drawing::Size(81, 13);
			this->label_Matrix_RotMatr->TabIndex = 12;
			this->label_Matrix_RotMatr->Text = L"Ось вращения";
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(24, 89);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(40, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->Text = L"OZ";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(24, 66);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(40, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"OY";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(24, 43);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(40, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"OX";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// dataGrid_Matrix
			// 
			this->dataGrid_Matrix->AllowUserToAddRows = false;
			this->dataGrid_Matrix->AllowUserToDeleteRows = false;
			this->dataGrid_Matrix->AllowUserToResizeColumns = false;
			this->dataGrid_Matrix->AllowUserToResizeRows = false;
			this->dataGrid_Matrix->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dataGrid_Matrix->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGrid_Matrix->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->dataGridViewTextBoxColumn8,
					this->dataGridViewTextBoxColumn9, this->dataGridViewTextBoxColumn10
			});
			this->dataGrid_Matrix->Location = System::Drawing::Point(3, 31);
			this->dataGrid_Matrix->Name = L"dataGrid_Matrix";
			this->dataGrid_Matrix->RowHeadersWidth = 20;
			this->dataGrid_Matrix->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGrid_Matrix->RowTemplate->DefaultCellStyle->NullValue = L"0";
			this->dataGrid_Matrix->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->dataGrid_Matrix->Size = System::Drawing::Size(288, 91);
			this->dataGrid_Matrix->TabIndex = 10;
			// 
			// dataGridViewTextBoxColumn8
			// 
			this->dataGridViewTextBoxColumn8->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn8->HeaderText = L"1";
			this->dataGridViewTextBoxColumn8->Name = L"dataGridViewTextBoxColumn8";
			// 
			// dataGridViewTextBoxColumn9
			// 
			this->dataGridViewTextBoxColumn9->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn9->HeaderText = L"2";
			this->dataGridViewTextBoxColumn9->Name = L"dataGridViewTextBoxColumn9";
			// 
			// dataGridViewTextBoxColumn10
			// 
			this->dataGridViewTextBoxColumn10->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn10->HeaderText = L"3";
			this->dataGridViewTextBoxColumn10->Name = L"dataGridViewTextBoxColumn10";
			// 
			// label_Matrix_vector
			// 
			this->label_Matrix_vector->AutoSize = true;
			this->label_Matrix_vector->Location = System::Drawing::Point(3, 148);
			this->label_Matrix_vector->Name = L"label_Matrix_vector";
			this->label_Matrix_vector->Size = System::Drawing::Size(43, 13);
			this->label_Matrix_vector->TabIndex = 9;
			this->label_Matrix_vector->Text = L"Вектор";
			// 
			// dataGrid_vector
			// 
			this->dataGrid_vector->AllowUserToAddRows = false;
			this->dataGrid_vector->AllowUserToDeleteRows = false;
			this->dataGrid_vector->AllowUserToResizeColumns = false;
			this->dataGrid_vector->AllowUserToResizeRows = false;
			this->dataGrid_vector->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dataGrid_vector->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGrid_vector->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->dataGridViewTextBoxColumn5,
					this->dataGridViewTextBoxColumn6, this->dataGridViewTextBoxColumn7
			});
			this->dataGrid_vector->Location = System::Drawing::Point(3, 164);
			this->dataGrid_vector->Name = L"dataGrid_vector";
			this->dataGrid_vector->RowHeadersWidth = 20;
			this->dataGrid_vector->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGrid_vector->RowTemplate->DefaultCellStyle->NullValue = L"0";
			this->dataGrid_vector->ScrollBars = System::Windows::Forms::ScrollBars::None;
			this->dataGrid_vector->Size = System::Drawing::Size(288, 44);
			this->dataGrid_vector->TabIndex = 8;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn5->HeaderText = L"X";
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			// 
			// dataGridViewTextBoxColumn6
			// 
			this->dataGridViewTextBoxColumn6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn6->HeaderText = L"Y";
			this->dataGridViewTextBoxColumn6->Name = L"dataGridViewTextBoxColumn6";
			// 
			// dataGridViewTextBoxColumn7
			// 
			this->dataGridViewTextBoxColumn7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->dataGridViewTextBoxColumn7->HeaderText = L"Z";
			this->dataGridViewTextBoxColumn7->Name = L"dataGridViewTextBoxColumn7";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(552, 381);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Преобразование координат";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->gBox_Gelio_Geo->ResumeLayout(false);
			this->gBox_Gelio_Geo->PerformLayout();
			this->gBox_Result->ResumeLayout(false);
			this->gBox_Result->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Result))->EndInit();
			this->gBox_Date->ResumeLayout(false);
			this->gBox_Date->PerformLayout();
			this->gBox_Gelio_Geo_Coord->ResumeLayout(false);
			this->gBox_Gelio_Geo_Coord->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Result2))->EndInit();
			this->gBox_Earth->ResumeLayout(false);
			this->gBox_Earth->PerformLayout();
			this->gBox_Time->ResumeLayout(false);
			this->gBox_Time->PerformLayout();
			this->gBox_vector->ResumeLayout(false);
			this->gBox_vector->PerformLayout();
			this->gBox_frac->ResumeLayout(false);
			this->gBox_frac->PerformLayout();
			this->gBox_deg2rad->ResumeLayout(false);
			this->gBox_deg2rad->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Matrix_result))->EndInit();
			this->gBox_Matrix->ResumeLayout(false);
			this->gBox_Matrix->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Matrix))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_vector))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		// начальный выбранный элемент выпадающего меню
		cBox_Date_Type->SelectedIndex = 0;
		cBox_vector->SelectedIndex = 0;
		cBox_Time->SelectedIndex = 0;

		dataGrid_vector->Rows->Add();
		dataGrid_Matrix->Rows->Add(3);
	}
	private: System::Void button_Convert_Click(System::Object^  sender, System::EventArgs^  e) {
		
		coord Original = new double[VECSIZE];
		Original[0] = Convert::ToDouble(tBox_Coord_x->Text) * 1000.0;
		Original[1] = Convert::ToDouble(tBox_Coord_y->Text) * 1000.0;
		Original[2] = Convert::ToDouble(tBox_Coord_z->Text) * 1000.0;

		double Time;
		DateTime tempDate;
		String ^ Text;
		
		switch (cBox_Date_Type->SelectedIndex)
		{
		case 0:
			Time = Convert::ToDouble(tBox_Date->Text);	
			break;

		case 1:
			Text = maskedTBox_Date->Text;
			tempDate = Convert::ToDateTime(Text);

			TDate resDate;
			resDate.Year = tempDate.Year;
			resDate.Month = tempDate.Month;
			resDate.Day = tempDate.Day;

			Time = Date2JD(resDate);
			break;

		default:
			break;
		}

		coord Converted = Gelio2GeoFix(Time, Original);
		int i = dataGrid_Result->Rows->Add();

		for (ushort j = 0; j < VECSIZE; j++)
			dataGrid_Result->Rows[i]->Cells[j]->Value = Converted[j] / 1000.0;

		Clear(Original);
		Clear(Converted);

	}

private: System::Void cBox_Date_Type_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	switch (cBox_Date_Type->SelectedIndex)
	{
	case 0:
		tBox_Date->Visible = true;
		maskedTBox_Date->Visible = false;
		break;

	case 1:
		maskedTBox_Date->Visible = true;
		tBox_Date->Visible = false;
		break;

	default:
		break;
	}
}

private: System::Void button_deg2rad_Click(System::Object^  sender, System::EventArgs^  e) {
	int i = dataGrid_Result2->Rows->Add();

	dataGrid_Result2->Rows[i]->Cells[0]->Value = "deg2rad";
	dataGrid_Result2->Rows[i]->Cells[4]->Value = deg2rad(Convert::ToDouble(tBox_deg2rad->Text));
}

private: System::Void button_frac_Click(System::Object^  sender, System::EventArgs^  e) {
	int i = dataGrid_Result2->Rows->Add();

	dataGrid_Result2->Rows[i]->Cells[0]->Value = "frac";
	dataGrid_Result2->Rows[i]->Cells[4]->Value = frac(Convert::ToDouble(tBox_frac->Text));
}

private: System::Void cBox_vector_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	switch (cBox_vector->SelectedIndex)
	{
	case 1:
		label_vector_x->Text = "R";
		label_vector_y->Text = "fi";
		label_vector_z->Text = "lambda";
		label_vector_Date->Visible = false;
		tBox_vector_Date->Visible = false;
		break;

	case 3:
		label_vector_x->Text = "X";
		label_vector_y->Text = "Y";
		label_vector_z->Text = "Z";
		label_vector_Date->Visible = true;
		tBox_vector_Date->Visible = true;
		break;

	case 4:
		label_vector_x->Text = "X";
		label_vector_y->Text = "Y";
		label_vector_z->Text = "Z";
		label_vector_Date->Visible = true;
		tBox_vector_Date->Visible = true;
		break;

	default:
		label_vector_x->Text = "X";
		label_vector_y->Text = "Y";
		label_vector_z->Text = "Z";
		label_vector_Date->Visible = false;
		tBox_vector_Date->Visible = false;
		break;
	}
}

private: System::Void button_vector_Click(System::Object^  sender, System::EventArgs^  e) {
	int i = dataGrid_Result2->Rows->Add();

	coord Original = new double[VECSIZE];
	Original[0] = Convert::ToDouble(tBox_vector_x->Text);
	Original[1] = Convert::ToDouble(tBox_vector_y->Text);
	Original[2] = Convert::ToDouble(tBox_vector_z->Text);

	coord Converted;
	switch (cBox_vector->SelectedIndex)
	{
	case 0:

		dataGrid_Result2->Rows[i]->Cells[0]->Value = "module";

		dataGrid_Result2->Rows[i]->Cells[4]->Value = module(Original, VECSIZE);

		break;

	case 1:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "Spher2Fix";

		Original[1] = deg2rad(Original[1]);
		Original[2] = deg2rad(Original[2]);
		Converted = Spher2Fix(Original);
		for (ushort j = 0; j < VECSIZE; j++)
			dataGrid_Result2->Rows[i]->Cells[j + 1]->Value = Converted[j];
		break;

	case 2:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "Fix2Spher";

		Converted = Fix2Spher(Original);
		Converted[1] *= 180 / PI;
		Converted[2] *= 180 / PI;
		for (ushort j = 0; j < VECSIZE; j++)
			dataGrid_Result2->Rows[i]->Cells[j + 1]->Value = Converted[j];
		break;

	case 3:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "GeoPos";

		Converted = GeoPos(Convert::ToDouble(tBox_vector_Date->Text), Original);
		for (ushort j = 0; j < VECSIZE; j++)
			dataGrid_Result2->Rows[i]->Cells[j + 1]->Value = Converted[j];
		break;

	case 4:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "Cel2Fix";

		Converted = Cel2Fix(Convert::ToDouble(tBox_vector_Date->Text), Original);
		for (ushort j = 0; j < VECSIZE; j++)
			dataGrid_Result2->Rows[i]->Cells[j + 1]->Value = Converted[j];
		break;

	default:
		break;
	}

}

private: System::Void button_Earth_Click(System::Object^  sender, System::EventArgs^  e) {
	int i = dataGrid_Result2->Rows->Add();
	dataGrid_Result2->Rows[i]->Cells[0]->Value = "EarthPos";

	coord Converted = EarthPos(Convert::ToDouble(tBox_Earth->Text));
	for (ushort j = 0; j < VECSIZE; j++)
		dataGrid_Result2->Rows[i]->Cells[j + 1]->Value = Converted[j];

	i = dataGrid_Result2->Rows->Add();
	dataGrid_Result2->Rows[i]->Cells[0]->Value = "EarthRotAngle";

	dataGrid_Result2->Rows[i]->Cells[4]->Value = EarthRotAngle(Convert::ToDouble(tBox_Earth->Text)) * 180 / PI;
}

private: System::Void cBox_Time_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	switch (cBox_Time->SelectedIndex)
	{
	case 0:
		tBox_Time->Visible = false;
		maskedTBox_Time->Visible = true;
		break;

	case 2:
		tBox_Time->Visible = false;
		maskedTBox_Time->Visible = true;
		break;

	case 3:
		tBox_Time->Visible = false;
		maskedTBox_Time->Visible = true;
		break;

	default:
		maskedTBox_Time->Visible = false;
		tBox_Time->Visible = true;
		break;
	}
}

private: System::Void button_Time_Click(System::Object^  sender, System::EventArgs^  e) {
	int i = dataGrid_Result2->Rows->Add();

	String ^ Text;
	DateTime tempDate;
	TDate resDate;
	int Year;

	switch (cBox_Time->SelectedIndex)
	{
	case 0:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "Date2JD";

		Text = maskedTBox_Time->Text;
		tempDate = Convert::ToDateTime(Text);

		Year = tempDate.Year;
		resDate.Year = Year;
		resDate.Month = tempDate.Month;
		resDate.Day = tempDate.Day;

		dataGrid_Result2->Rows[i]->Cells[4]->Value = Date2JD(resDate);
		break;

	case 1:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "JD2Date";

		resDate = JD2Date(Convert::ToDouble(tBox_Time->Text));

		dataGrid_Result2->Rows[i]->Cells[1]->Value = resDate.Day;
		dataGrid_Result2->Rows[i]->Cells[2]->Value = resDate.Month;
		dataGrid_Result2->Rows[i]->Cells[3]->Value = resDate.Year;
		break;

	case 2:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "LeapYear";

		Text = maskedTBox_Time->Text;
		tempDate = Convert::ToDateTime(Text);

		dataGrid_Result2->Rows[i]->Cells[4]->Value = LeapYear((ushort)tempDate.Year);
		break;

	case 3:
		dataGrid_Result2->Rows[i]->Cells[0]->Value = "DayNumber";

		Text = maskedTBox_Time->Text;
		tempDate = Convert::ToDateTime(Text);

		TDate Date;
		Date.Year = (ushort)tempDate.Year;
		Date.Month = (ushort)tempDate.Month;
		Date.Day = tempDate.Day;

		dataGrid_Result2->Rows[i]->Cells[4]->Value = DayNumber(Date);
		break;

	default:
		break;
	}
}

private: System::Void button_RotMatr_Click(System::Object^  sender, System::EventArgs^  e) {
	double angle = Convert::ToDouble(tBox_Matrix_angle->Text) * 180 / PI;
	ushort axis;
	
	if (radioButton1->Checked) axis = 1;
	else 
		if (radioButton2->Checked) axis = 2;
		else if (radioButton3->Checked) axis = 3;

	matrix R = RotMatr(axis, angle);

	for (ushort i = 0; i < VECSIZE; i++)
		for (ushort j = 0; j < VECSIZE; j++)
			dataGrid_Matrix->Rows[i]->Cells[j]->Value = *(*(R + i) + j);

	Clear(R);
}
private: System::Void button_Mult_Click(System::Object^  sender, System::EventArgs^  e) {
	matrix R = new coord[VECSIZE];
	for (ushort i = 0; i < VECSIZE; i++)
		*(R + i) = new double[VECSIZE];

	for (ushort i = 0; i < VECSIZE; i++)
		for (ushort j = 0; j < VECSIZE; j++)
			*(*(R + i) + j) = Convert::ToDouble(dataGrid_Matrix->Rows[i]->Cells[j]->Value);

	coord vec = new double[VECSIZE];
	for (ushort j = 0; j < VECSIZE; j++)
		*(vec + j) = Convert::ToDouble(dataGrid_vector->Rows[0]->Cells[j]->Value);

	int i = dataGrid_Matrix_result->Rows->Add();
	coord result = Mult(R, vec);
	for (ushort j = 0; j < VECSIZE; j++)
		dataGrid_Matrix_result->Rows[i]->Cells[j]->Value = *(result + j);

	Clear(R); Clear(vec); Clear(result);
}
};
}