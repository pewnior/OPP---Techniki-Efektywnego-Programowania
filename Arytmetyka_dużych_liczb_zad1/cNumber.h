#define CNUMBER_H

#include<string>

using namespace std;

const int I_NUMBER_SYSTEM = 10;
const int I_DEFAULT_SIZE = 10;
const int I_DEFAULT_TABLE_INCEASE = 5;
const string S_DIVISION_BY_ZERO_ERROR = "ERROR: division by zero";

class cNumber {
public:
	cNumber();
	cNumber(const cNumber& cOtherNumber);
	~cNumber();

	void operator=(const cNumber& cOtherNumber);
	void operator=(int iValue);
	cNumber operator+(const cNumber& cOtherNumber) const;
	cNumber operator-(const cNumber& cOtherNumber) const;
	cNumber operator*(const cNumber& cOtherNumber) const;
	cNumber operator/(const cNumber& cOtherNumber) const;
	bool operator<(const cNumber& cOtherNumber) const;
	bool operator>(const cNumber& cOtherNumber) const;
	bool operator==(const cNumber& cOtherNumber) const;
	bool operator!=(const cNumber& cOtherNumber) const;
	bool operator<=(const cNumber& cOtherNumber) const;
	bool operator>=(const cNumber& cOtherNumber) const;

	string sGetNumber() const;

	int iGetSymbolFlag() const;

private:
	int* pi_table;
	int i_table_size;
	int i_digits_count;
	int i_sign;

	cNumber operator*(const int iDigit) const;

	void vPutDigitFront(int iDigit);
	void vPutDigitBack(int iDigit);
	void vIncreaseTableSize(int iTableIncrease);
	void vDeleteFrontZeros();
	void vResetNumber();
	void vSetTableSize(int iNewSize);
	void vMakeCarries();
	void vSetDigitsCount();
	int iSingleDivision(const cNumber& cDivident, const cNumber& cDivisor) const;
	bool bIsZero() const;
	void vBorrowDigit(int iStartIndex) const;
	cNumber cGetAbs() const;
};
