#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H

// Standard headers
#include <vector>
#include <thread>
#include <string>

// Project headers
#include "user.h"
#include "interface.h"
#include "server.h"

enum serverReply {
	// Welcome replies
	RPL_WELCOME = 001,
	RPL_YOURHOST = 002,
	RPL_CREATED = 003,
	RPL_MYINFO = 004,
	RPL_BOUNCE = 005,
	RPL_USERHOST = 302,
	RPL_ISON = 303,
	
	// Away replies
	RPL_AWAY = 301,
	RPL_UNAWAY = 305,
	RPL_NOWAWAY = 306,

	// WHOIS replies
	RPL_WHOISUSER = 311,
	RPL_WHOISSERVER = 312,
	RPL_WHOISOPERATOR = 313,
	RPL_WHOISIDLE = 317,
	RPL_ENDOFWHOIS = 318,
	RPL_WHOISCHANNELS = 319,

	// WHOWAS replies
	RPL_WHOWASUSER = 314,
	RPL_ENDOFWHOWAS = 369,

	// LIST replies
	RPL_LISTSTART = 321,
	RPL_LIST = 322,
	RPL_LISTEND = 323,

	// TOPIC replies
	RPL_UNIQOPIS = 325,
	RPL_CHANNELMODEIS = 324,
	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,

	// INVITE replies
	RPL_INVITING = 341,
	RPL_SUMMONING = 342,
	RPL_INVITELIST = 346,
	RPL_ENDOFINVITELIST = 347,
	RPL_EXCEPTLIST = 348,
	RPL_ENDOFEXCEPTLIST = 349,

	// VERSION replies
	RPL_VERSION = 351,

	// WHO replies
	RPL_WHOREPLY = 352,
	RPL_ENDOFWHO = 315,

	// NAMES replies
	RPL_NAMEREPLY = 353,
	RPL_ENDOFNAMES = 366,

	// LINKS replies
	RPL_LINKS = 364,
	RPL_ENDOFLINKS = 365,

	// BAN replies
	RPL_BANLIST = 367,
	RPL_ENDOFBANLIST = 368,

	// INFO replies
	RPL_INFO = 371,
	RPL_ENDOFINFO = 374,

	// MOTD replies
	RPL_MOTDSTART = 375,
	RPL_MOTD = 372,
	RPL_ENDOFMOTD = 376,

	// OPER replies
	RPL_YOUREOPER = 381,

	// REHASH replies
	RPL_REHASHING = 382,

	// SERVICE replies
	RPL_YOURESERVICE = 383,

	// TIME replies
	RPL_TIME = 391,

	// USERS replies
	RPL_USERSSTART = 392,
	RPL_USERS = 393,
	RPL_ENDOFUSERS = 394,
	RPL_NOUSERS = 395,

	// TRACE replies
	RPL_TRACELINK = 200,
	RPL_TRACECONNECTING = 201,
	RPL_TRACEHANDSHAKE = 202,
	RPL_TRACEUNKNOWN = 203,
	RPL_TRACEOPERATOR = 204,
	RPL_TRACEUSER = 205,
	RPL_TRACESERVER = 206,
	RPL_TRACESERVICE = 207,
	RPL_TRACENEWTYPE = 208,
	RPL_TRACENEWCLASS = 209,
	RPL_TRACERECONNECT = 210,
	RPL_TRACELOG = 261,
	RPL_TRACEEND = 262,

	// STATS replies
	RPL_STATSLINKINFO = 211,
	RPL_STATSCOMMANDS = 212,
	RPL_ENDOFSTATS = 219,
	RPL_STATSUPTIME = 242,
	RPL_STATSOLINE = 243,

	// unsure what these are lol
	RPL_UMODEIS = 221,
	RPL_SERVLIST = 234,
	RPL_SERVLISTEND = 235,

	// LUSER replies
	RPL_LUSERCLIENT = 251,
	RPL_LUSEROP = 252,
	RPL_LUSERUNKNOWN = 253,
	RPL_LUSERCHANNELS = 254,
	RPL_LUSERME = 255,

	// ADMIN replies
	RPL_ADMINME = 256,
	RPL_ADMINLOC1 = 257,
	RPL_ADMINLOC2 = 258,
	RPL_ADMINLOC3 = 259,

	// TRY AGAIN
	RPL_TRYAGAIN = 263 // called when server drops a command without processing it
};

class responseHandler {
public:

	// Constructor
	responseHandler(user* currentUser, interface* mainInterface, server* serv);
	void handleResponse(std::string res);

private:

	// Misc data
	std::vector<std::string> *MOTDVec;

	// Misc functions
	std::string getBody(int startIndex, std::vector<std::string> msgVec);

	// Message data
	const char MESSAGE_PREFIX = ':';

	// Handling
	void directMessage(std::string msg);
	
	// Numeric handlers
	void handleStandard(std::vector<std::string> msgVec);
	void handleLusers(std::vector<std::string> msgVec);
	void handleMOTD(std::vector<std::string> msgVec);

	// Non-numeric handlers

	// End of handlers
	void printRawMessage(std::string res); // For testing purposes only (and when a message cant be handled)

	// Pointers to session stuff
	user* currentUser;
	interface* mainInterface;
	server* serv;
	
};

#endif