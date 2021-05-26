#ifndef RTCPEERHANDLER_HPP
#define RTCPEERHANDLER_HPP

#include "libdatachannel/rtc.hpp"
#include <iostream>
#include <memory>
#include "nlohmann/json.hpp"
#include <array>
#include <set>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int SOCKET;
#endif

#define closesocket(param) close(param) //Same name for both win & linux socket libs
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

using json = nlohmann::json;
class rtcPeerHandler{
public:
	rtcPeerHandler();
	void initiateConnection(std::string peerIP, int peerPort);
	uint16_t openUdpSocket();
	struct client
	{
		std::shared_ptr<rtc::PeerConnection> pc;
		std::shared_ptr<rtc::DataChannel> dc;
		std::string addr;
		uint16_t port;
	};

private:
	std::map<SOCKET, client> clients;
	std::set<uint16_t> usedPorts;

	

};


#endif // RTCPEERHANDLER_HPP
