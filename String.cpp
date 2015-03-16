/*************************************************************************
	> File Name: String.cpp
	> Author: zxx
	> Mail: zxx178239@163.com 
	> Created Time: Wed 11 Mar 2015 09:30:46 PM CST
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
class String
{
public:
	String();
	String(const char *);
	String(const String &);
	~String();
	String &operator=(const String &);
	String &operator=(const char *);

	String &operator+=(const String &);
	String &operator+=(const char *);

	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;
	
	std::size_t size() const;
	const char *c_str() const;

	friend String operator+(const String &, const String &);
	friend String operator+(const String &, const char *);
	friend String operator+(const char *, const String &);

	friend bool operator==(const String &, const String &) ;
	friend bool operator!=(const String &, const String &) ;
	
	friend bool operator<(const String &, const String &) ;
	friend bool operator>(const String &, const String &) ;
	friend bool operator<=(const String &, const String &) ;
	friend bool operator>=(const String &, const String &) ;

	friend std::ostream &operator<<(std::ostream &os, const String &s) ;
	friend std::istream &operator>>(std::istream &is, String &s);
private:
	char *m_str;
	void destroy();
};

String::String() : m_str(NULL)
{
}
String::String(const char *str)
{
	int len = strlen(str);
	m_str = new char[len + 2];
	strcpy(m_str, str);
	m_str[len] = '\0';
	m_str[len + 1] = '1';
}
String::String(const String &str)
{
	m_str = str.m_str;
	int len = strlen(m_str);
	m_str[len + 1] += 1;
}
String::~String()
{
		destroy();
}

void String::destroy()
{
	if(m_str != NULL)
	{
		int len = strlen(m_str);
		if(m_str[len + 1] == '1')
		{
			delete [] m_str;
			m_str = NULL;
		}else
		{
			m_str[len + 1] -= 1;
		}
	}
}

String &String::operator=(const String &str)
{
	if(this != &str)
	{
		destroy();
		m_str = str.m_str;
		int len = strlen(m_str);
		m_str[len + 1] += 1;
	}
	return *this;
}
String &String::operator=(const char *str)
{
	destroy();
	int len;
	len = strlen(str);
	m_str = new char[len + 2];
	strcpy(m_str, str);
	m_str[len + 1] = '1';
	return *this;
}
String &String::operator+=(const String &str)
{
	String tmp;
	tmp = *this;
	destroy();
	int len = strlen(tmp.m_str) + strlen(str.m_str);
	m_str = new char[len + 2];
	strcpy(m_str, tmp.m_str);
	strcat(m_str, str.m_str);
	m_str[len + 1] = '1';
	return *this;
}

String &String::operator+=(const char *str)
{
	String tmp;
	tmp = *this;
	destroy();
	int len = strlen(tmp.m_str) + strlen(str);
	m_str = new char[len + 2];
	strcpy(m_str, tmp.m_str);
	strcat(m_str, str);
	m_str[len + 1] = '1';
	return *this;
}

char &String::operator[](std::size_t index)
{
	int len;
	if(index < 0 || index > this->size())
	{
		static char nullchar = '\0';
		return nullchar;
	}
	len = strlen(m_str);
	if(m_str[len + 1] > 1)
	{
		char *tmp = new char[len + 2];
		strcpy(tmp, m_str);
		-- m_str[len + 1];
		m_str = tmp;
		m_str[len + 1] = 1;
	}
	return m_str[index];
}

const char &String::operator[](std::size_t index) const
{
	return m_str[index] ;
}

std::size_t String::size() const
{
	return strlen(m_str);
}

const char *String::c_str() const
{
	return m_str;
}

String operator+(const String &str1, const String &str2)
{
	String tmp;
	int len = strlen(str1.m_str) + strlen(str2.m_str);
	tmp.m_str = new char[len + 2];
	strcpy(tmp.m_str, str1.m_str);
	strcat(tmp.m_str, str2.m_str);
	tmp.m_str[len + 1] = '1';
	return tmp;
}

String operator+(const String &str1, const char *str2)
{
	String tmp;
	int len = strlen(str1.m_str) + strlen(str2);
	tmp.m_str = new char[len + 2];
	strcpy(tmp.m_str, str1.m_str);
	strcat(tmp.m_str, str2);
	tmp.m_str[len + 1] = '1';
	return tmp;
}

String operator+(const char *str1, const String &str2)
{
	String tmp;
	int len = strlen(str1) + strlen(str2.m_str);
	tmp.m_str = new char[len + 2];
	strcpy(tmp.m_str, str1);
	strcat(tmp.m_str, str2.m_str);
	tmp.m_str[len + 1] = '1';
	return tmp;
}

bool operator==(const String & str1, const String &str2) 
{
	return (strcmp(str1.m_str, str2.m_str) == 0);
}

bool operator!=(const String &str1, const String &str2) 
{
	return (strcmp(str1.m_str, str2.m_str) != 0);
}

bool operator<(const String &str1, const String &str2) 
{
	return (strcmp(str1.m_str, str2.m_str) < 0);
}

bool operator>(const String &str1, const String &str2) 
{
	return (strcmp(str1.m_str, str2.m_str) > 0);
}

bool operator<=(const String &str1, const String &str2) 
{
	return (strcmp(str1.m_str, str2.m_str) <= 0);
}

bool operator>=(const String &str1, const String &str2) 
{
	return (strcmp(str1.m_str, str2.m_str) >= 0);
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
	return os << str.m_str;
}

std::istream &operator>>(std::istream &is, String &str)
{
	char *tmp = new char[1024];
	is >> tmp;
	str.m_str = new char[strlen(tmp) + 1];
	strcpy(str.m_str, tmp);
	delete [] tmp;
	return is;
}

int main(int argc, char *argv[])
{
	String str1("hello");
	const char *ch1 = "abcde";
	const char *ch2 = "eagde";
	std::cout << "str1: "<< str1 << std::endl;
	String str2(str1);
	std::cout << "str2: " << str2 << std::endl;
	std::cout << "ch1: " << ch1 << std::endl;
	std::cout << "ch2: " << ch2 << std::endl;
	String str3 = str2;
	String str4;
	// str + str
	str4 = str1 + str2;
	// <<
	std::cout << str1 << " + " << str2 << " = " << str4 << std::endl;
	// str + char *
	str4 = str1 + ch1;
	std::cout << str1 << " + " << ch1 << " = " << str4 << std::endl;
	//char * + str
	str4 = ch1 + str1;
	std::cout << ch1 << " + " << str1 << " = " << str4 << std::endl;
	// == false is 0
	std::cout << str1 << " == " << str4 << " " << (str4 == str1) << std::endl;
	// == true is 1
	std::cout << str1 << " == " << str2 << " " << (str1 == str2) << std::endl;
	// >
	std::cout << str1 << " > " << str4 << " " << (str1 > str4) << std::endl;
	// <
	std::cout << str1 << " < " << str4 << " " << (str1 < str4) << std::endl;
	// >=
	std::cout << str1 << " >= " << str4 << " " << (str1 >= str4) << std::endl;
	std::cout << str1 << " >= " << str2 << " " << (str1 >= str2) << std::endl;
	// <=
	std::cout << str1 << " <= " << ch1 << " " << (str1 <= ch1) << std::endl;
	std::cout << str1 << " <= " << str2 << " " << (str1 <= str2) << std::endl;
	//c_str
	std::cout << str1 << " c_str: " << str1.c_str() << std::endl;
	//size
	std::cout << str1 << " size: " << str1.size() << std::endl;

	//>>
	String str6;
	std::cout << "input a string: " << std::endl;
	std::cin >> str6;
	std::cout << str6 << std::endl;

	//copy on write test
	printf("str1 address: %x\n", str1.c_str());
	printf("str2 address: %x\n", str2.c_str());
	printf("str3 address: %x\n", str3.c_str());
	//change str1
//	str1 = "myname";
	std::cout << "str1 is: " << str1 << std::endl;
	std::cout << "str2 is: " << str2 << std::endl;

	printf("str1 address: %x\n", str1.c_str());
	printf("str2 address: %x\n", str2.c_str());
	printf("str3 address: %x\n", str3.c_str());
	printf("str1[2]: %c\n", str1[2]);
	str1[1] = 'a';
	std::cout << "str1 is: " << str1 << std::endl;
	std::cout << "str2 is: " << str2 << std::endl;

}


