#ifndef USER_H
#define USER_H

// Standard headers
#include <string>

// Project headers

class user {
public:

	user();

private:

	// User data
	std::string nickname;
	std::string username;
	std::string realname;
	std::string password;

	void setNickname(std::string nickname);
	void setUsername(std::string username);
	void setRealname(std::string realname);
	void setPassword(std::string password);

	std::string getNickname();
	std::string getUsername();
	std::string getRealname();
	std::string getPassword();
};

#endif