#include "user.h"

/*
 * Constructor/Destructor
 */

user::user() {}

/*
 * Setters
 */

void user::setNickname(std::string nickname) {
	this->nickname = nickname;
}

void user::setUsername(std::string username) {
	this->username = username;
}

void user::setRealname(std::string realname) {
	this->realname = realname;
}

void user::setPassword(std::string password) {
	this->password = password;
}

/*
 * Getters
 */

std::string user::getNickname() {
	return this->nickname;
}

std::string user::getUsername() {
	return this->username;
}

std::string user::getRealname() {
	return this->realname;
}

std::string user::getPassword() {
	return this->password;
}