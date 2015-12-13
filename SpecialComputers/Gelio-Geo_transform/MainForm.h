#pragma once

#include "Types.h"
#include "Coord_Transformation.h"
#include "Functions.h"

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
			this->gBox_Gelio_Geo->SuspendLayout();
			this->gBox_Result->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGrid_Result))->BeginInit();
			this->gBox_Date->SuspendLayout();
			this->gBox_Gelio_Geo_Coord->SuspendLayout();
			this->SuspendLayout();
			// 
			// tBox_Date
			// 
			this->tBox_Date->Location = System::Drawing::Point(114, 83);
			this->tBox_Date->Name = L"tBox_Date";
			this->tBox_Date->Size = System::Drawing::Size(80, 20);
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
			this->gBox_Gelio_Geo->Location = System::Drawing::Point(12, 12);
			this->gBox_Gelio_Geo->Name = L"gBox_Gelio_Geo";
			this->gBox_Gelio_Geo->Size = System::Drawing::Size(451, 337);
			this->gBox_Gelio_Geo->TabIndex = 1;
			this->gBox_Gelio_Geo->TabStop = false;
			this->gBox_Gelio_Geo->Text = L"Перевод координат";
			// 
			// gBox_Result
			// 
			this->gBox_Result->Controls->Add(this->label_Result);
			this->gBox_Result->Controls->Add(this->dataGrid_Result);
			this->gBox_Result->Location = System::Drawing::Point(142, 201);
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
			this->gBox_Date->Controls->Add(this->cBox_Date_Type);
			this->gBox_Date->Controls->Add(this->label_Date_Type);
			this->gBox_Date->Controls->Add(this->label_Date);
			this->gBox_Date->Controls->Add(this->tBox_Date);
			this->gBox_Date->Location = System::Drawing::Point(245, 73);
			this->gBox_Date->Name = L"gBox_Date";
			this->gBox_Date->Size = System::Drawing::Size(200, 122);
			this->gBox_Date->TabIndex = 5;
			this->gBox_Date->TabStop = false;
			this->gBox_Date->Text = L"Дата перевода координат";
			// 
			// cBox_Date_Type
			// 
			this->cBox_Date_Type->FormattingEnabled = true;
			this->cBox_Date_Type->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Юлианский день", L"Григорианский календарь" });
			this->cBox_Date_Type->Location = System::Drawing::Point(52, 46);
			this->cBox_Date_Type->Name = L"cBox_Date_Type";
			this->cBox_Date_Type->Size = System::Drawing::Size(142, 21);
			this->cBox_Date_Type->TabIndex = 4;
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
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 361);
			this->Controls->Add(this->gBox_Gelio_Geo);
			this->Name = L"MainForm";
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
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		// начальный выбранный элемент выпадающего меню
		cBox_Date_Type->SelectedIndex = 0;
	}
	private: System::Void button_Convert_Click(System::Object^  sender, System::EventArgs^  e) {
		
		coord Original = new double[VECSIZE];
		Original[0] = Convert::ToDouble(tBox_Coord_x->Text) * 1000.0;
		Original[1] = Convert::ToDouble(tBox_Coord_y->Text) * 1000.0;
		Original[2] = Convert::ToDouble(tBox_Coord_z->Text) * 1000.0;

		double Time;
		switch (cBox_Date_Type->SelectedIndex)
		{
		case 0:
			Time = Convert::ToDouble(tBox_Date->Text);
			break;

		case 1:
			//char Text;
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
};

}