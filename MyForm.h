#pragma once
#include <stack>
#include <iostream>

int clicked_caclulate = 0;

System::String^ delt_nulls(System::String ^input) {
	System::String^ str = input;
	int i = 0;
	System::String^ tmp = "";
	if (str == "")return "";
	if (str[i] == '-') {
		tmp = str->Remove(i, 1);
		str = tmp;
		while (str[i] == '0') {
			tmp = str->Remove(i, 1);
			str = tmp;
			if (str == "") {
				str = "0";
				break;
			}
			if (str[i] == ',') {
				str = "0" + str;
				break;
			}
		}
		str = "-" + str;
	}
	else{
		while (str[i] == '0') {
			tmp = str->Remove(i, 1);
			str = tmp;
			if (str == "") {
				str = "0";
				break;
			}
			if (str[i] == ',') {
				str = "0" + str;
				break;
			}
		}
	}
	if (str->Contains(",") == true) {
		i = str->Length - 1;
		while (str[i] == '0') {
			tmp = str->Remove(i, 1);
			str = tmp;
			i--;
			if (str[i] == ',') {
				str = str + "0";
				break;
			}
		}
	}
	return str;
}

bool Is_last_number(System::String^ s) {
	if (s->Length > 0) {
		return s[s->Length - 1] == '1' || s[s->Length - 1] == '2' || s[s->Length - 1] == '3' || s[s->Length - 1] == '4' || s[s->Length - 1] == '5' || s[s->Length - 1] == '6' || s[s->Length - 1] == '7' || s[s->Length - 1] == '8' || s[s->Length - 1] == '9' || s[s->Length - 1] == '0' || s[s->Length - 2] == '(' || s[s->Length - 2] == ')';
	}
	else {
		return true;
	}
}

void Add_symbol(System::String^ symbol, System::Windows::Forms::TextBox^ outputBox, System::Windows::Forms::TextBox^ inputBox) {
	System::String^ sentence = outputBox->Text;
	System::String^ number = inputBox->Text;
	if ((number == "exp(" || number == "sqrt(") && (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" || symbol == "=" || symbol == "^")) {
		if (number == "exp(") {
			number = System::Convert::ToString(exp(1));
			number = delt_nulls(number);
			sentence += " " + number + " " + symbol;
			number = "";
		}
		else {
			number = System::Convert::ToString(sqrt(1));
			number = delt_nulls(number);
			sentence += " " + number + " " + symbol;
			number = "";
		}
	}
	else if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" || symbol == "=" || symbol == "^" || symbol == "s" || symbol == "e") {
		if (number->Length == 0) {
			if (symbol == "-") {
				number += symbol;
			}
			else {
				if (symbol == "=") {
					sentence = sentence->Remove(sentence->Length - 2);
				}
				else {
					if (symbol == "s" || symbol == "e") {
						if(symbol == "s")
							number += "sqrt(";
						else
							number += "exp(";
					}else{
						if (sentence->Length > 0) {
							sentence = sentence->Remove(sentence->Length - 2);
							sentence += " " + symbol;
						}
					}
				}
			}
		}
		else {
			if (symbol == "=") {
				if (number[0] == 's') {
					number = number->Remove(0, 5);
					if (number[0] == '-')System::Windows::Forms::MessageBox::Show("Нельзя найти корень из отрицательного числа!", "Ошибка");
					else {
						number = delt_nulls(number);
						double res = sqrt(System::Convert::ToDouble(number));
						number = System::Convert::ToString(res);
					}
				}
				if (number[0] == 'e') {
					number = number->Remove(0, 4);
					number = delt_nulls(number);
					double res = exp(System::Convert::ToDouble(number));
					number = System::Convert::ToString(res);
				}
				if (number->Contains(",") == true) {
					number += "0";
					number = delt_nulls(number);
				}
				if (System::Convert::ToDouble(number) < 0) {
					number = delt_nulls(number);
					sentence += " ( " + number + " ) ";
					number = "";
				}
				else {
					number = delt_nulls(number);
					sentence += " " + number + " ";
					number = "";
				}
			}
			else {
				if (number != "-" && number != "sqrt(" && number != "exp(") {
					if (number[0] == 's') {
						if (symbol != "s" && symbol != "e") {
							number = number->Remove(0, 5);
							if (number[0] == '-') {
								System::Windows::Forms::MessageBox::Show("Нельзя найти корень из отрицательного числа!", "Ошибка");
							}
							else {
								double res = sqrt(System::Convert::ToDouble(number));
								number = System::Convert::ToString(res);
							}
						}
					}
					if (number[0] == 'e') {
						if (symbol != "e" && symbol != "s") {
							number = number->Remove(0, 4);
							double res = exp(System::Convert::ToDouble(number));
							number = System::Convert::ToString(res);
						}
					}
					if (symbol == "s" || symbol == "e") {
						if (number[0] == '-' && symbol == "s")System::Windows::Forms::MessageBox::Show("Нельзя найти корень из отрицательного числа!", "Ошибка");
						else {
							if (number[0] != 's' && number[0] != 'e') {
								if (symbol == "s"){
									double res = sqrt(System::Convert::ToDouble(number));
									number = System::Convert::ToString(res);
								}
								else {
									double res = exp(System::Convert::ToDouble(number));
									number = System::Convert::ToString(res);
								}
							}
						}
					}
					else {
						if (number->Contains(",") == true) {
							number += "0";
							number = delt_nulls(number);
						}
						if (System::Convert::ToDouble(number) < 0) {
							number = delt_nulls(number);
							sentence += " ( " + number + " ) " + symbol;
							number = "";
						}
						else {
							number = delt_nulls(number);
							sentence += " " + number + " " + symbol;
							number = "";
						}
					}
				}
				else {
					if (number[0] == 's' && symbol == "-" || number[0] == 'e' && symbol == "-") {
						number += "-";
					}
					else {
						if (symbol != "s")number = number->Remove(number->Length - 1);
					}
				}
			}
		}
	}
	else {
		if (symbol == ",") {
				if (number == "" || number == "-" || number == "sqrt(" || number == "exp(") {
					number += "0,";
				}
				else {
					if (number->Contains(",") == false) {
						number += symbol;
					}
				}
		}
		else {
			number += symbol;
		}
	}
	if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" || symbol == "=" || symbol == "^" || symbol == "s" || symbol == "e") {
		
	}
	outputBox->Text = sentence;
	inputBox->Text = number;
}

int Num_of_symbols(System::String^ s, char symbol) {
	int res = 0;
	for (int i = 0; i < s->Length; i++) {
		if (s[i] == symbol)res ++;
	}
	return res;
}

int Priority(char symbol) {
	switch (symbol)
	{
	case '-': return 1; break;
	case '+': return 1; break;
	case '*': return 2; break;
	case '/': return 2; break;
	case '^': return 3; break;
		break;
	}
}

int Get_result(System::Windows::Forms::TextBox^ inputBox, System::Windows::Forms::TextBox^ outputBox) {
	System::String^ sentence = inputBox->Text;
	System::String^ result = "";
	std::stack <double> numbers;
	std::stack <char> signs;
	array<System::String^>^ splited_sentence = sentence->Split();
	if (outputBox->Text == "" || outputBox->Text == splited_sentence[0]) {
			for (int i = 0; i < Num_of_symbols(sentence, ' ') + 1; i++) {
				if (splited_sentence[i] != "") {
					int len_of_symbol = splited_sentence[i]->Length;
					if (std::isdigit(splited_sentence[i][0]) || len_of_symbol > 1) {
						double tmp = System::Convert::ToDouble(splited_sentence[i]);
						numbers.push(tmp);
					}
					else {
						if (signs.empty() == false) {
							if (Priority(signs.top()) >= Priority(System::Convert::ToChar(splited_sentence[i])) && System::Convert::ToChar(splited_sentence[i]) != '(' && System::Convert::ToChar(splited_sentence[i]) != ')') {
								bool exit = false;
								while (exit == false) {
									double tmp = numbers.top();
									numbers.pop();
									if (signs.top() == '/' && tmp == 0) {
										System::Windows::Forms::MessageBox::Show("Деление на 0");
										return -1;
									}
									switch (signs.top())
									{
									case '-':tmp = numbers.top() - tmp; break;
									case '+':tmp = numbers.top() + tmp; break;
									case '*':tmp = numbers.top() * tmp; break;
									case '^':tmp = pow(numbers.top(),tmp); break;
									case '/':tmp = numbers.top() / tmp;
										break;
									}
									numbers.pop();
									numbers.push(tmp);
									signs.pop();
									exit = signs.empty();
									if (exit == false) {
										exit = !(Priority(signs.top()) >= Priority(System::Convert::ToChar(splited_sentence[i])));
									}
								}
								if (System::Convert::ToChar(splited_sentence[i]) != '=') {
									signs.push(System::Convert::ToChar(splited_sentence[i]));
								}
							}
							else {
								if (System::Convert::ToChar(splited_sentence[i]) != '(' && System::Convert::ToChar(splited_sentence[i]) != ')') {
									signs.push(System::Convert::ToChar(splited_sentence[i]));
								}
							}
						}
						else {
							if (System::Convert::ToChar(splited_sentence[i]) != '(' && System::Convert::ToChar(splited_sentence[i]) != ')') {
								signs.push(System::Convert::ToChar(splited_sentence[i]));
							}
						}
					}
				}
			}
			if (signs.empty()) {
				result = System::Convert::ToString(numbers.top());
			}
			else {
				while (signs.empty() == false) {
					double tmp = numbers.top();
					numbers.pop();
					if (signs.top() == '/' && tmp == 0) {
						System::Windows::Forms::MessageBox::Show("Деление на 0");
						return -1;
					}
					switch (signs.top())
					{
					case '-':tmp = numbers.top() - tmp; break;
					case '+':tmp = numbers.top() + tmp; break;
					case '*':tmp = numbers.top() * tmp; break;
					case '^':tmp = pow(numbers.top(), tmp); break;
					case '/':tmp = numbers.top() / tmp;
						break;
					}
					numbers.pop();
					numbers.push(tmp);
					signs.pop();
					result = System::Convert::ToString(numbers.top());
				}
				outputBox->Text = "";
				outputBox->Text = result;
			}
		}
		else {
			inputBox->Text = outputBox->Text;
		}
	return 0;
}

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button_plus;
	private: System::Windows::Forms::Button^ button_minus;
	private: System::Windows::Forms::Button^ button_multiply;
	private: System::Windows::Forms::Button^ button_division;
	private: System::Windows::Forms::Button^ button_calculate;





	private: System::Windows::Forms::Button^ button_separator;

	private: System::Windows::Forms::Button^ button0;

	private: System::Windows::Forms::TextBox^ sentenceBox;
	private: System::Windows::Forms::TextBox^ resultBox;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ delete_symbol;


	private: System::Windows::Forms::Button^ button00;
	private: System::Windows::Forms::Button^ button_power;
	private: System::Windows::Forms::Button^ button_reverse;


	private: System::Windows::Forms::Button^ button_sqrt;
	private: System::Windows::Forms::Button^ button_exp;










	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button_plus = (gcnew System::Windows::Forms::Button());
			this->button_minus = (gcnew System::Windows::Forms::Button());
			this->button_multiply = (gcnew System::Windows::Forms::Button());
			this->button_division = (gcnew System::Windows::Forms::Button());
			this->button_calculate = (gcnew System::Windows::Forms::Button());
			this->button_separator = (gcnew System::Windows::Forms::Button());
			this->button0 = (gcnew System::Windows::Forms::Button());
			this->sentenceBox = (gcnew System::Windows::Forms::TextBox());
			this->resultBox = (gcnew System::Windows::Forms::TextBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->delete_symbol = (gcnew System::Windows::Forms::Button());
			this->button00 = (gcnew System::Windows::Forms::Button());
			this->button_power = (gcnew System::Windows::Forms::Button());
			this->button_reverse = (gcnew System::Windows::Forms::Button());
			this->button_sqrt = (gcnew System::Windows::Forms::Button());
			this->button_exp = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(22, 105);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(55, 58);
			this->button1->TabIndex = 0;
			this->button1->Text = L"1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(83, 105);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(55, 58);
			this->button2->TabIndex = 1;
			this->button2->Text = L"2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(144, 105);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(55, 58);
			this->button3->TabIndex = 2;
			this->button3->Text = L"3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(22, 169);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(55, 58);
			this->button4->TabIndex = 3;
			this->button4->Text = L"4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(83, 169);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(55, 58);
			this->button5->TabIndex = 4;
			this->button5->Text = L"5";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(144, 169);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(55, 58);
			this->button6->TabIndex = 5;
			this->button6->Text = L"6";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(22, 233);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(55, 58);
			this->button7->TabIndex = 6;
			this->button7->Text = L"7";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(83, 233);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(55, 58);
			this->button8->TabIndex = 7;
			this->button8->Text = L"8";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(144, 233);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(55, 58);
			this->button9->TabIndex = 8;
			this->button9->Text = L"9";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button_plus
			// 
			this->button_plus->Location = System::Drawing::Point(205, 105);
			this->button_plus->Name = L"button_plus";
			this->button_plus->Size = System::Drawing::Size(55, 58);
			this->button_plus->TabIndex = 9;
			this->button_plus->Text = L"+";
			this->button_plus->UseVisualStyleBackColor = true;
			this->button_plus->Click += gcnew System::EventHandler(this, &MyForm::button_plus_Click);
			// 
			// button_minus
			// 
			this->button_minus->Location = System::Drawing::Point(205, 169);
			this->button_minus->Name = L"button_minus";
			this->button_minus->Size = System::Drawing::Size(55, 58);
			this->button_minus->TabIndex = 10;
			this->button_minus->Text = L"-";
			this->button_minus->UseVisualStyleBackColor = true;
			this->button_minus->Click += gcnew System::EventHandler(this, &MyForm::button_minus_Click);
			// 
			// button_multiply
			// 
			this->button_multiply->Location = System::Drawing::Point(205, 233);
			this->button_multiply->Name = L"button_multiply";
			this->button_multiply->Size = System::Drawing::Size(55, 58);
			this->button_multiply->TabIndex = 11;
			this->button_multiply->Text = L"x";
			this->button_multiply->UseVisualStyleBackColor = true;
			this->button_multiply->Click += gcnew System::EventHandler(this, &MyForm::button_multiply_Click);
			// 
			// button_division
			// 
			this->button_division->Location = System::Drawing::Point(205, 297);
			this->button_division->Name = L"button_division";
			this->button_division->Size = System::Drawing::Size(55, 58);
			this->button_division->TabIndex = 12;
			this->button_division->Text = L"/";
			this->button_division->UseVisualStyleBackColor = true;
			this->button_division->Click += gcnew System::EventHandler(this, &MyForm::button_division_Click);
			// 
			// button_calculate
			// 
			this->button_calculate->Location = System::Drawing::Point(329, 233);
			this->button_calculate->Name = L"button_calculate";
			this->button_calculate->Size = System::Drawing::Size(55, 122);
			this->button_calculate->TabIndex = 13;
			this->button_calculate->Text = L"=";
			this->button_calculate->UseVisualStyleBackColor = true;
			this->button_calculate->Click += gcnew System::EventHandler(this, &MyForm::button_calculate_Click);
			// 
			// button_separator
			// 
			this->button_separator->Location = System::Drawing::Point(22, 297);
			this->button_separator->Name = L"button_separator";
			this->button_separator->Size = System::Drawing::Size(55, 58);
			this->button_separator->TabIndex = 14;
			this->button_separator->Text = L",";
			this->button_separator->UseVisualStyleBackColor = true;
			this->button_separator->Click += gcnew System::EventHandler(this, &MyForm::button_separator_Click);
			// 
			// button0
			// 
			this->button0->Location = System::Drawing::Point(83, 297);
			this->button0->Name = L"button0";
			this->button0->Size = System::Drawing::Size(55, 58);
			this->button0->TabIndex = 15;
			this->button0->Text = L"0";
			this->button0->UseVisualStyleBackColor = true;
			this->button0->Click += gcnew System::EventHandler(this, &MyForm::button0_Click);
			// 
			// sentenceBox
			// 
			this->sentenceBox->Enabled = false;
			this->sentenceBox->Location = System::Drawing::Point(22, 32);
			this->sentenceBox->Name = L"sentenceBox";
			this->sentenceBox->Size = System::Drawing::Size(362, 22);
			this->sentenceBox->TabIndex = 16;
			// 
			// resultBox
			// 
			this->resultBox->Enabled = false;
			this->resultBox->Location = System::Drawing::Point(22, 60);
			this->resultBox->Name = L"resultBox";
			this->resultBox->Size = System::Drawing::Size(362, 22);
			this->resultBox->TabIndex = 17;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(329, 105);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(55, 58);
			this->button10->TabIndex = 18;
			this->button10->Text = L"C";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// delete_symbol
			// 
			this->delete_symbol->Location = System::Drawing::Point(329, 169);
			this->delete_symbol->Name = L"delete_symbol";
			this->delete_symbol->Size = System::Drawing::Size(55, 58);
			this->delete_symbol->TabIndex = 19;
			this->delete_symbol->Text = L"<-";
			this->delete_symbol->UseVisualStyleBackColor = true;
			this->delete_symbol->Click += gcnew System::EventHandler(this, &MyForm::delete_symbol_Click);
			// 
			// button00
			// 
			this->button00->Location = System::Drawing::Point(144, 297);
			this->button00->Name = L"button00";
			this->button00->Size = System::Drawing::Size(55, 58);
			this->button00->TabIndex = 20;
			this->button00->Text = L"00";
			this->button00->UseVisualStyleBackColor = true;
			this->button00->Click += gcnew System::EventHandler(this, &MyForm::button00_Click);
			// 
			// button_power
			// 
			this->button_power->Location = System::Drawing::Point(266, 105);
			this->button_power->Name = L"button_power";
			this->button_power->Size = System::Drawing::Size(55, 58);
			this->button_power->TabIndex = 21;
			this->button_power->Text = L"x^y";
			this->button_power->UseVisualStyleBackColor = true;
			this->button_power->Click += gcnew System::EventHandler(this, &MyForm::button_power_Click);
			// 
			// button_reverse
			// 
			this->button_reverse->Location = System::Drawing::Point(266, 233);
			this->button_reverse->Name = L"button_reverse";
			this->button_reverse->Size = System::Drawing::Size(55, 58);
			this->button_reverse->TabIndex = 22;
			this->button_reverse->Text = L"1/x";
			this->button_reverse->UseVisualStyleBackColor = true;
			this->button_reverse->Click += gcnew System::EventHandler(this, &MyForm::button_reverse_Click);
			// 
			// button_sqrt
			// 
			this->button_sqrt->Location = System::Drawing::Point(266, 169);
			this->button_sqrt->Name = L"button_sqrt";
			this->button_sqrt->Size = System::Drawing::Size(55, 58);
			this->button_sqrt->TabIndex = 23;
			this->button_sqrt->Text = L"sqrt";
			this->button_sqrt->UseVisualStyleBackColor = true;
			this->button_sqrt->Click += gcnew System::EventHandler(this, &MyForm::button_sqrt_Click);
			// 
			// button_exp
			// 
			this->button_exp->Location = System::Drawing::Point(266, 297);
			this->button_exp->Name = L"button_exp";
			this->button_exp->Size = System::Drawing::Size(55, 58);
			this->button_exp->TabIndex = 24;
			this->button_exp->Text = L"exp";
			this->button_exp->UseVisualStyleBackColor = true;
			this->button_exp->Click += gcnew System::EventHandler(this, &MyForm::button_exp_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(396, 370);
			this->Controls->Add(this->button_exp);
			this->Controls->Add(this->button_sqrt);
			this->Controls->Add(this->button_reverse);
			this->Controls->Add(this->button_power);
			this->Controls->Add(this->button00);
			this->Controls->Add(this->delete_symbol);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->resultBox);
			this->Controls->Add(this->sentenceBox);
			this->Controls->Add(this->button0);
			this->Controls->Add(this->button_separator);
			this->Controls->Add(this->button_calculate);
			this->Controls->Add(this->button_division);
			this->Controls->Add(this->button_multiply);
			this->Controls->Add(this->button_minus);
			this->Controls->Add(this->button_plus);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"Калькулятор";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("1", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("1", sentenceBox, resultBox);
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("2", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("2", sentenceBox, resultBox);
	}
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("3", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("3", sentenceBox, resultBox);
	}
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("4", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("4", sentenceBox, resultBox);
	}
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("5", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("5", sentenceBox, resultBox);
	}
}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("6", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("6", sentenceBox, resultBox);
	}
}
private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("7", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("7", sentenceBox, resultBox);
	}
}
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("8", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("8", sentenceBox, resultBox);
	}
}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("9", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("9", sentenceBox, resultBox);
	}
}
private: System::Void button0_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("0", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("0", sentenceBox, resultBox);
	}
}
private: System::Void button_plus_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("+", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("+", sentenceBox, resultBox);
	}
}
private: System::Void button_minus_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("-", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("-", sentenceBox, resultBox);
	}
}
private: System::Void button_multiply_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("*", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("*", sentenceBox, resultBox);
	}
}
private: System::Void button_division_Click(System::Object^ sender, System::EventArgs^ e) {
	if (clicked_caclulate == 0) {
		Add_symbol("/", sentenceBox, resultBox);
	}
	else {
		clicked_caclulate = 0;
		sentenceBox->Text = "";
		Add_symbol("/", sentenceBox, resultBox);
	}
}
private: System::Void button_calculate_Click(System::Object^ sender, System::EventArgs^ e) {
	if (sentenceBox->Text == "" && resultBox->Text == "") {
		sentenceBox->Text = "";
		resultBox->Text = "";
	}
	else {
		if (sentenceBox->Text == "" && resultBox->TextLength > 0 && resultBox->Text[0] != 's' && resultBox->Text[0] != 'e') {
			if (resultBox->Text == "-")resultBox->Text = "";
			resultBox->Text = delt_nulls(resultBox->Text);
			sentenceBox->Text = resultBox->Text;
			if (sentenceBox->Text == "0,") {
				sentenceBox->Text = "0,0";
				resultBox->Text = "0,0";
			}
		}
		else {
			if (sentenceBox->Text != resultBox->Text) {
				if (clicked_caclulate == 0) {
					Add_symbol("=", sentenceBox, resultBox);
					int error = Get_result(sentenceBox, resultBox);
					if (error == -1) {
						sentenceBox->Text = "";
						resultBox->Text = "";
					}
					clicked_caclulate++;
				}
				else {
					System::String^ sentence = sentenceBox->Text;
					array<System::String^>^ splited_sentence = sentence->Split();
					sentenceBox->Text = resultBox->Text + " " + splited_sentence[Num_of_symbols(sentence, ' ') - 2] + " " + splited_sentence[Num_of_symbols(sentence, ' ') - 1] + " ";
					int error = Get_result(sentenceBox, resultBox);
					if (error == -1) {
						sentenceBox->Text = "";
						resultBox->Text = "";
					}
				}
			}
			else {
				if (sentenceBox->Text == "0,") {
					sentenceBox->Text = "0,0";
					resultBox->Text = "0,0";
				}
			}
		}
	}
}
private: System::Void button_separator_Click(System::Object^ sender, System::EventArgs^ e) {
	Add_symbol(",", sentenceBox, resultBox);
}
private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
	sentenceBox->Text = "";
	resultBox->Text = "";
	clicked_caclulate = 0;
}
private: System::Void delete_symbol_Click(System::Object^ sender, System::EventArgs^ e) {
	if (resultBox->Text != "") {
		if (sentenceBox->Text == resultBox->Text) {
			sentenceBox->Text = "";
			resultBox->Text = "";
		}else{
		System::String^ tmp = resultBox->Text;
		if (tmp[tmp->Length - 1] == ' ') {
			resultBox->Text = tmp->Remove(tmp->Length - 3);
		}
		else {
			resultBox->Text = tmp->Remove(tmp->Length - 1);
		}
		}
	}
	else {
		if (sentenceBox->Text == resultBox->Text) {
			sentenceBox->Text = "";
			resultBox->Text = "";
		}
		if (sentenceBox->Text != "") {
			System::String^ sentence = sentenceBox->Text;
			array<System::String^>^ splited_sentence = sentence->Split();
			sentenceBox->Text = "";
			for (int i = 0; i < Num_of_symbols(sentence, ' ') - 2; i++) {
				sentenceBox->Text += splited_sentence[i] + " ";
			}
			sentenceBox->Text += splited_sentence[Num_of_symbols(sentence, ' ') - 2];
			resultBox->Text = splited_sentence[Num_of_symbols(sentence, ' ') - 1];
		}
	}
}
private: System::Void button00_Click(System::Object^ sender, System::EventArgs^ e) {
	Add_symbol("00", sentenceBox, resultBox);
}
private: System::Void button_power_Click(System::Object^ sender, System::EventArgs^ e) {
	Add_symbol("^", sentenceBox, resultBox);
}
private: System::Void button_sqrt_Click(System::Object^ sender, System::EventArgs^ e) {
	Add_symbol("s", sentenceBox, resultBox);
}
private: System::Void button_reverse_Click(System::Object^ sender, System::EventArgs^ e) {
	if (resultBox->Text == "") {
		if (sentenceBox->Text == "")sentenceBox->Text += "1 /";
		else sentenceBox->Text += " 1 /";
	}
	else {
		double res = 1 / System::Convert::ToDouble(resultBox->Text);
		resultBox->Text = System::Convert::ToString(res);
	}
}
private: System::Void button_exp_Click(System::Object^ sender, System::EventArgs^ e) {
	Add_symbol("e", sentenceBox, resultBox);
}
private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode.ToString() == "D1") {
		Add_symbol("1", sentenceBox, resultBox);
	}
	else if (e->Shift && e->KeyCode.ToString() == "D8") {
		button_multiply_Click(sender, e);
	}
	else if (e->Shift && e->KeyCode.ToString() == "Oemplus") {
		button_plus_Click(sender, e);
	}
	else if (e->Shift && e->KeyCode.ToString() == "D6") {
		button_power_Click(sender, e);
	}
	else if(e->KeyCode.ToString() == "D2"){
		Add_symbol("2", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D3") {
		Add_symbol("3", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D4") {
		Add_symbol("4", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D5") {
		Add_symbol("5", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D6") {
		Add_symbol("6", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D7") {
		Add_symbol("7", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D8") {
		Add_symbol("8", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D9") {
		Add_symbol("9", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "D0") {
		Add_symbol("0", sentenceBox, resultBox);
	}
	else if (e->KeyCode.ToString() == "Back") {
		delete_symbol_Click(sender, e);
	}
	else if (e->KeyCode.ToString() == "OemMinus") {
		button_minus_Click(sender, e);
	}
	else if (e->KeyCode.ToString() == "OemQuestion") {
		button_division_Click(sender, e);
	}
	else if (e->KeyCode.ToString() == "S") {
		button_sqrt_Click(sender, e);
	}
	else if (e->KeyCode.ToString() == "E") {
		button_exp_Click(sender, e);
	}
	else if (e->KeyCode.ToString() == "Oemplus") {
		button_calculate_Click(sender, e);	
	}
	return System::Void();
}
};
}
	