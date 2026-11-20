#include "cNumber.h"
#include<algorithm>
#include <stdexcept>

using namespace std;

cNumber::cNumber() {
	i_table_size = I_DEFAULT_SIZE;
	i_digits_count = 0;
	pi_table = new int[i_table_size];
	i_sign = 0;
	
}

cNumber::cNumber(const cNumber& cOtherNumber) {
	i_table_size = cOtherNumber.i_table_size;
	i_digits_count = cOtherNumber.i_digits_count;
	pi_table = new int[i_table_size];
	i_sign = cOtherNumber.i_sign;

	for (int i = 0;i < i_digits_count;++i) {
		pi_table[i] = cOtherNumber.pi_table[i];
	}
}

cNumber::~cNumber() {
	delete[] pi_table;
}

void cNumber::operator=(int iValue) {
	vResetNumber();

	unsigned int uiValue = (unsigned int)iValue;

	if (iValue < 0) {
		i_sign = -1;
		uiValue = 0u - (unsigned int)iValue;
	}
	else {
		i_sign = 1;
	}

	

	if (uiValue == 0) {
		vPutDigitBack(0);
	}

	while (uiValue != 0) {
		int iNextDigit;
		iNextDigit = uiValue % I_NUMBER_SYSTEM;
		vPutDigitFront(iNextDigit);
		uiValue = (uiValue - iNextDigit) / I_NUMBER_SYSTEM;
	}

	
}

void cNumber::operator=(const cNumber& cOtherNumber) {
	i_table_size = cOtherNumber.i_table_size;
	i_digits_count = cOtherNumber.i_digits_count;
	i_sign = cOtherNumber.i_sign;
	
	int* piCopyTable = new int[i_table_size];
	for (int i = 0;i < i_digits_count;++i) {
		piCopyTable[i] = cOtherNumber.pi_table[i];
	}

	delete[] pi_table;

	pi_table = piCopyTable;

	
}

cNumber cNumber::operator+(const cNumber& cOtherNumber) const {
	cNumber cResult;
	int iCarry = 0;
	int iSingleSum = 0;
	if (i_sign == cOtherNumber.i_sign) {
		int i = 0;
		while (i < i_digits_count || i < cOtherNumber.i_digits_count || iCarry > 0) {
			iSingleSum = iCarry;

			if (i < i_digits_count) {
				iSingleSum += pi_table[i];
			}

			if (i < cOtherNumber.i_digits_count) {
				iSingleSum += cOtherNumber.pi_table[i];
			}

			if (iSingleSum >= I_NUMBER_SYSTEM) {
				iCarry = iSingleSum / I_NUMBER_SYSTEM;
				iSingleSum -= I_NUMBER_SYSTEM * iCarry;
			}
			else {
				iCarry = 0;
			}

			cResult.vPutDigitFront(iSingleSum);
			++i;

		}
		cResult.i_sign = i_sign;
	}
	else {
		cNumber cAbsCopyThis, cAbsCopyOtherNumber;
		cAbsCopyThis = cGetAbs();
		cAbsCopyOtherNumber = cOtherNumber.cGetAbs();

		if (cAbsCopyThis > cAbsCopyOtherNumber) {
			cResult = cAbsCopyThis - cAbsCopyOtherNumber;
		}
		else {
			cResult = cAbsCopyOtherNumber - cAbsCopyThis;
		}

		if (cAbsCopyThis > cAbsCopyOtherNumber) {
			cResult.i_sign = i_sign;
		}
		else {
			cResult.i_sign = cOtherNumber.i_sign;
		}
	}

	if (cResult.bIsZero()) {
		cResult.i_sign = 1;
	}

	return cResult;
}

cNumber cNumber::operator-(const cNumber& cOtherNumber) const  {
	cNumber cResult;
	int iSingleDifference;
	cNumber cMinuend;
	cNumber cSubtrahend;

	if (i_sign == 1 && cOtherNumber.i_sign == 1) { //obie dodatnie
		
		if (*this >= cOtherNumber) { //większa odjąć mniejsza - dodatni
			cMinuend = *this;
			cSubtrahend = cOtherNumber;
			cResult.i_sign = 1;
		}
		else {//mniejsza odjąć większa - ujemny
			cMinuend = cOtherNumber;
			cSubtrahend = *this;
			cResult.i_sign = -1;
		}

		int i = 0;
		while (i < cMinuend.i_digits_count || i < cSubtrahend.i_digits_count) {
			if (i >= cSubtrahend.i_digits_count) {
				iSingleDifference = cMinuend.pi_table[i];
			}
			else {
				if (cMinuend.pi_table[i] < cSubtrahend.pi_table[i]) {
					cMinuend.vBorrowDigit(i);
				}

				iSingleDifference = cMinuend.pi_table[i] - cSubtrahend.pi_table[i];

			}

			cResult.vPutDigitFront(iSingleDifference);
			++i;
		}

	}
	else if (i_sign == 1 && cOtherNumber.i_sign == -1) { //dodatnie - ujemna
		cMinuend = *this;
		cSubtrahend = cOtherNumber;

		cSubtrahend.i_sign = 1;
		cResult = cMinuend + cSubtrahend;
		cResult.i_sign = 1;
	}
	else if (i_sign == -1 && cOtherNumber.i_sign == 1) { //ujemna - dodatnia
		cMinuend = *this;
		cSubtrahend = cOtherNumber;

		cMinuend.i_sign = 1;
		cResult = cMinuend + cSubtrahend;
		cResult.i_sign = -1;
	}
	else {//ujemna - ujemna
		cMinuend = *this;
		cSubtrahend = cOtherNumber;

		cSubtrahend.i_sign = 1;
		cResult = cMinuend + cSubtrahend;
	}


	if (cResult.bIsZero()) {
		cResult.i_sign = 1;
	}

	cResult.vDeleteFrontZeros();
	return cResult;
}

void cNumber::vBorrowDigit(int iStartIndex) const {
	int j = iStartIndex + 1;
	while (pi_table[j] == 0) {
		++j;
	}

	--pi_table[j];
	--j;
	while (j != iStartIndex) {
		pi_table[j] = I_NUMBER_SYSTEM - 1;
		--j;
	}
	pi_table[iStartIndex] += I_NUMBER_SYSTEM;
}

cNumber cNumber::operator*(const cNumber& cOtherNumber) const {
	cNumber cResult;
	int iSingleResult;
	cResult.vSetTableSize(i_digits_count + cOtherNumber.i_digits_count + 1);
	cResult.vResetNumber();

	if (bIsZero() || cOtherNumber.bIsZero()) {
		cResult.pi_table[0] = 0;
		cResult.i_digits_count = 1;
	}
	else {
		for (int i = 0;i < i_digits_count;++i) {
			for (int j = 0;j < cOtherNumber.i_digits_count;++j) {
				iSingleResult = pi_table[i] * cOtherNumber.pi_table[j];

				if (iSingleResult >= I_NUMBER_SYSTEM) {
					cResult.pi_table[i + j + 1] += iSingleResult / I_NUMBER_SYSTEM;
					iSingleResult = iSingleResult % I_NUMBER_SYSTEM;
				}

				cResult.pi_table[i + j] += iSingleResult;
			}
		}

		cResult.i_digits_count = cResult.i_table_size;
		cResult.vMakeCarries();
		cResult.vSetDigitsCount();
	}

	cResult.vDeleteFrontZeros();

	if (i_sign == cOtherNumber.i_sign || cResult.bIsZero()) {
		cResult.i_sign = 1;
	}
	else {
		cResult.i_sign = -1;
	}

	return cResult;
}

cNumber cNumber::operator*(int iDigit) const  {
	cNumber cResult;
	if (iDigit == 0 || bIsZero() ) {
		cResult = 0;
	}
	else {
		for (int i = 0; i < iDigit;++i) {
			cResult = cResult + *this;
		}
	}

	return cResult;
}

cNumber cNumber::operator/(const cNumber& cOtherNumber) const  {
	cNumber cResult;
	cNumber cAbsCopyThis, cAbsCopyOtherNumber;
	cAbsCopyThis = cGetAbs();
	cAbsCopyOtherNumber = cOtherNumber.cGetAbs();

	cResult.vSetTableSize(i_table_size);
	int iRightRange, iSingleResult;
	cNumber cTempNumber, cTempResult;
	cTempNumber.i_sign = 1;
	cTempResult.i_sign = 1;

	if (cOtherNumber.bIsZero()) {
		//dzielenie przez zero
		throw runtime_error(S_DIVISION_BY_ZERO_ERROR);
	}

	if (cAbsCopyOtherNumber > cAbsCopyThis) {
		cResult.vPutDigitFront(0);
	}
	else if(cAbsCopyThis == cAbsCopyOtherNumber){
		cResult.vPutDigitFront(1);
	}
	else {
		iRightRange = i_digits_count - 1;

		while (iRightRange != -1) {
			cTempNumber.vPutDigitBack(cAbsCopyThis.pi_table[iRightRange]);
			cTempNumber.vDeleteFrontZeros();

			if (cTempNumber >= cAbsCopyOtherNumber) {
				iSingleResult = iSingleDivision(cTempNumber, cAbsCopyOtherNumber);

				cResult.vPutDigitBack(iSingleResult);

				cTempResult = cAbsCopyOtherNumber * iSingleResult;
				cTempNumber = cTempNumber - cTempResult;
			}
			else {
				cResult.vPutDigitBack(0);
			}

			--iRightRange;
		}

	}


	cResult.vDeleteFrontZeros();

	if (i_sign == cOtherNumber.i_sign || cResult.bIsZero()) {
		cResult.i_sign = 1;
	}
	else {
		cResult.i_sign = -1;
	}

	return cResult;
}

bool cNumber::operator==(const cNumber& cOtherNumber) const {
	bool bResult;
	if (i_sign == cOtherNumber.i_sign && i_digits_count == cOtherNumber.i_digits_count) {
		int i = i_digits_count - 1;
		while (i >= 0 && pi_table[i] == cOtherNumber.pi_table[i]) {
			--i;
		}

		if (i == -1) {
			bResult = true;
		}
		else {
			bResult = false;
		}

	}
	else {
		bResult = false;
	}

	return bResult;
}

bool cNumber::operator!=(const cNumber& cOtherNumber) const {
	return !(*this == cOtherNumber);
}

bool cNumber::operator<=(const cNumber& cOtherNumber) const {
	return (*this < cOtherNumber) || (*this == cOtherNumber);
}

bool cNumber::operator>=(const cNumber& cOtherNumber) const {
	return (*this > cOtherNumber) || (*this == cOtherNumber);
}

bool cNumber::operator<(const cNumber& cOtherNumber) const {
	bool bResult;
	if (i_sign == -1 && cOtherNumber.i_sign == 1) { //a<0 i b>0
		bResult = true;
	}
	else if (i_sign == 1 && cOtherNumber.i_sign == -1) { //a>0 i b<0
		bResult = false;
	}
	// te same znaki
	else if (i_digits_count == cOtherNumber.i_digits_count) {
		int i = i_digits_count - 1;
		while (i >= 0 && pi_table[i] == cOtherNumber.pi_table[i]) {
			--i;
		}

		if (i < 0) {// te same liczby
			bResult = false;
		}
		else if (pi_table[i] < cOtherNumber.pi_table[i]) {//pierwsza inna mniejsza
			if (i_sign == 1) {
				bResult = true;
			}
			else {
				bResult = false;
			}
		}
		else {
			if (i_sign == 1) {
				bResult = false;
			}
			else {
				bResult = true;
			}
		}
	}
	else if(i_digits_count < cOtherNumber.i_digits_count) { //mniej znaków
		if (i_sign == 1) {
			bResult = true;
		}
		else {
			bResult = false;
		}
	}
	else {
		if (i_sign == 1) {
			bResult = false;
		}
		else {
			bResult = true;
		}
	}

	return bResult;
}

bool cNumber::operator>(const cNumber& cOtherNumber) const {
	return cOtherNumber < *this;
}

void cNumber::vPutDigitFront(int iDigit) {
	if (i_digits_count == i_table_size) {
		vIncreaseTableSize(I_DEFAULT_TABLE_INCEASE);
	}
	pi_table[i_digits_count] = iDigit;
	++i_digits_count;
}

void cNumber::vPutDigitBack(int iDigit) {
	if (i_digits_count == i_table_size) {
		vIncreaseTableSize(I_DEFAULT_TABLE_INCEASE);
	}
	for (int i = i_digits_count - 1; i >= 0;--i) {
		pi_table[i + 1] = pi_table[i];
	}

	pi_table[0] = iDigit;
	++i_digits_count;
}

void cNumber::vMakeCarries() {
	for (int i = 0;i < i_digits_count;++i) {
		if (pi_table[i] >= I_NUMBER_SYSTEM) {
			pi_table[i + 1] += pi_table[i] / I_NUMBER_SYSTEM;
			pi_table[i] = pi_table[i] % I_NUMBER_SYSTEM;
		}
	}
}

void cNumber::vSetDigitsCount() {
	int i = i_table_size - 1;
	while (pi_table[i] == 0) {
		--i;
	}
	i_digits_count = i + 1;
}

void cNumber::vIncreaseTableSize(int iTableInreace) {
	int iNewSize = i_table_size + iTableInreace;
	int* piNewTable = new int[iNewSize];

	for (int i = 0;i < i_table_size;++i) {
		piNewTable[i] = pi_table[i];
	}
	for (int i = i_digits_count; i < iNewSize;++i) {
		piNewTable[i] = 0;
	}

	i_table_size = iNewSize;
	delete[] pi_table;
	pi_table = piNewTable;
}

void cNumber::vDeleteFrontZeros() {
	int i = i_digits_count;
	while (i>0 && pi_table[i - 1] == 0) {
		--i;
		--i_digits_count;
	}
	if (i == 0) {
		++i_digits_count;
	}
}

void cNumber::vResetNumber() {
	i_digits_count = 0;

	for (int i = 0;i < i_table_size;++i) {
		pi_table[i] = 0;
	}

	i_sign = 0;
}

void cNumber::vSetTableSize(int iNewSize) {
	int* piNewTable = new int[iNewSize];

	for (int i = 0;i < min(i_table_size, iNewSize);++i) {
		piNewTable[i] = pi_table[i];
	}

	delete[] pi_table;
	i_table_size = iNewSize;
	pi_table = piNewTable;
}

int cNumber::iSingleDivision(const cNumber& cDivident, const cNumber& cDivisor) const {
	int iResult = 0;
	cNumber cTempCopyDivisor;
	cTempCopyDivisor = 0;

	while (cDivident >= cTempCopyDivisor) {
		++iResult;
		cTempCopyDivisor = cTempCopyDivisor + cDivisor;
	}

	return iResult-1;
}

string cNumber::sGetNumber() const {
	string sResult = "";
	if (i_sign == -1) {
		sResult += "-";
	}
	if (i_digits_count == 0) {
		sResult += "0";
	}
	for (int i = i_digits_count - 1;i >= 0;--i) {
		sResult += to_string(pi_table[i]);
	}
	return sResult;
}

int cNumber::iGetSymbolFlag() const {
	return i_sign;
}

bool cNumber::bIsZero() const {
	bool bResult;
	if ((i_digits_count == 1 && pi_table[0] == 0) || i_digits_count == 0) {
		bResult = true;
	}
	else{
		bResult = false;
	}
	return bResult;
}

cNumber cNumber::cGetAbs() const {
	cNumber cAbsCopy(*this);
	cAbsCopy.i_sign = 1;
	return cAbsCopy;
}
