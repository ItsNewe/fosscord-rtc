#ifndef MONGOSTUB_HPP
#define MONGOSTUB_HPP

#include <boost/utility.hpp>
#include <cstdint>
#include <iostream>
#include <vector>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/change_stream.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/document/element.hpp>
#include "rtcPeerHandler.hpp"


class mongoStub{
	public:
		mongoStub(std::shared_ptr<rtcPeerHandler> commsHandler);

		struct mongoMessage{
			std::string eventName;
			std::vector<std::string> data;
		};

		std::vector<mongoMessage> getNewMessages(mongocxx::change_stream* colCs);

		mongocxx::collection getCol() const { return col; }

		
		
	private:
		mongocxx::instance instance;
		mongocxx::client client{mongocxx::uri{}};
		mongocxx::database db;
		mongocxx::collection col;
		mongocxx::change_stream* colCs = nullptr;
		std::shared_ptr<rtcPeerHandler> commsHandler = nullptr;

		void handleUdpRequest(std::string address, std::string mode);
		void handleVoiceRequest();
};

#endif
