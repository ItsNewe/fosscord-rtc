#include "rtcPeerHandler.hpp"

rtcPeerHandler::rtcPeerHandler() {
    rtc::InitLogger(rtc::LogLevel::Verbose, NULL);
}

uint16_t rtcPeerHandler::openUdpSocket(){
	// Socket connection between client and server
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	uint16_t port=61000;

	while(this->usedPorts.count(port)!=0){
		port+=1;
	}

	if (sock == INVALID_SOCKET){
		return -1;
	}

    sockaddr_in addr;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	listen(sock, 5);

	this->usedPorts.insert(port);
	return port; //Return the port

}
void rtcPeerHandler::initiateConnection(std::string peerIP, int peerPort) {

    rtc::Configuration conf;
    conf.enableIceTcp = false;
    conf.disableAutoNegotiation = false;

    auto pc = std::make_shared<rtc::PeerConnection>(conf);

    rtc::Description::Audio media("audio",
                                  rtc::Description::Direction::SendRecv);
    media.addOpusCodec(96);
    media.setBitrate(64);

    auto track = pc->addTrack(media);

    // auto session = std::make_shared<rtc::MediaHandler>();

    // track->setMediaHandler(session);

    rtc::Reliability rtcRel;
    rtcRel.unordered = true;
    rtcRel.type = rtc::Reliability::Type::Timed;
    rtcRel.rexmit = 500;

    rtc::DataChannelInit rtcConf;
    rtcConf.reliability = rtcRel;
    rtcConf.negotiated = false;

    pc->onStateChange([](rtc::PeerConnection::State state) {
        std::cout << "State: " << state << std::endl;
        if (state == rtc::PeerConnection::State::Disconnected ||
            state == rtc::PeerConnection::State::Failed ||
            state == rtc::PeerConnection::State::Closed) {
            // remove disconnected client
        }
    });

    pc->onGatheringStateChange([](rtc::PeerConnection::GatheringState state) {
        std::cout << "Gathering State: " << state << std::endl;
    });

    /*auto audio = rtc::Description::Audio(cname);
    audio.addOpusCodec(96);
    audio.addSSRC(ssrc, cname, msid, cname);
    auto track = pc->addTrack(audio);
    // create RTP configuration
    auto rtpConfig = make_shared<RtpPacketizationConfig>(
        ssrc, cname, payloadType, OpusRtpPacketizer::defaultClockRate);
    // create packetizer
    auto packetizer = make_shared<OpusRtpPacketizer>(rtpConfig);
    // create opus handler
    auto opusHandler = make_shared<OpusPacketizationHandler>(packetizer);

    // add RTCP SR handler
    auto srReporter = make_shared<RtcpSrReporter>(rtpConfig);
    opusHandler->addToChain(srReporter);

    // set handler
    track->setMediaHandler(opusHandler);
    track->onOpen([] { std::cout << "Track opened" << std::endl; });

    pc->setLocalDescription();
    track-// Socket connection between client and server
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(peerIP.c_str());
    addr.sin_port = htons(peerPort);
    addr.sin_family = AF_INET;, this, peerIP](rtc::binary message) {
            // This is an RTP packet
            for (auto c : clients) {
                if (peerIP != c.second.addr) {
                    sendto(c.first,
                           reinterpret_cast<const char *>(message.data()),
                           int(message.size()),
						   0,
                           reinterpret_cast<const struct sockaddr *>(c.second.addr),
                           sizeof(c.second.addr));
                }
            }
        },
        nullptr);*/

    pc->createDataChannel("Fosscord voice connection", rtcConf);
}


