#ifndef ESP32MDNS_H
#define ESP32MDNS_H
#endif

#include "Arduino.h"
#include "IPv6Address.h"
#include "mdns.h"

/*
 Arduino IPv6 address class
 
 This class represents an IPv6 address (16 octets) used by the IPv6 stack
 
 created 29 June 2012
 by Alejandro Lampropulos (alejandro.lampropulos@telecom-bretagne.eu)
 Telecom Bretagne Rennes, France
 
 Copyright (c) 2012, Telecom Bretagne Rennes, France.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 3. Neither the name of the Institute nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 SUCH DAMAGE.
 
 */

#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H

// extern "C" {        	
	// #include "uip.h>
// }

class IPv6Address{
  private:
    uip_ipaddr_t address;
    friend class IPv6Stack;
  public:
    IPv6Address(uint8_t addr0, uint8_t addr1, uint8_t addr2, uint8_t addr3, uint8_t addr4, uint8_t addr5, uint8_t addr6, uint8_t addr7, uint8_t addr8, uint8_t addr9, uint8_t addr10, uint8_t addr11, uint8_t addr12, uint8_t addr13, uint8_t addr14, uint8_t addr15);
    IPv6Address(uint16_t addr0, uint16_t addr1, uint16_t addr2, uint16_t addr3, uint16_t addr4, uint16_t addr5, uint16_t addr6, uint16_t addr7);
    IPv6Address();//Creates a link local multicast ipv6 address
    void print();
    uint16_t getAddressValue(uint8_t pos);//pos goes between 0 and 7
    void setAddressValue(uint16_t value, uint8_t pos);//pos goes between 0 and 7
    IPv6Address& operator=(IPv6Address const &addr);
};

#endif


/*
ESP8266 Multicast DNS (port of CC3000 Multicast DNS library)
Version 1.1
Copyright (c) 2013 Tony DiCola (tony@tonydicola.com)
ESP8266 port (c) 2015 Ivan Grokhotkov (ivan@esp8266.com)
MDNS-SD Suport 2015 Hristo Gochkov (hristo@espressif.com)
Extended MDNS-SD support 2016 Lars Englund (lars.englund@gmail.com)
Rewritten for ESP32 by Hristo Gochkov (hristo@espressif.com)

This is a simple implementation of multicast DNS query support for an Arduino
running on ESP32 chip. 

Usage:
- Include the ESP32 Multicast DNS library in the sketch.
- Call the begin method in the sketch's setup and provide a domain name (without
  the '.local' suffix, i.e. just provide 'foo' to resolve 'foo.local'), and the
  Adafruit CC3000 class instance.  Optionally provide a time to live (in seconds)
  for the DNS record--the default is 1 hour.
- Call the update method in each iteration of the sketch's loop function.

License (MIT license):
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/
#ifndef ESP32MDNS_H
#define ESP32MDNS_H

#include "Arduino.h"
#include "IPv6Address.h"
#include "mdns.h"

//this should be defined at build time
#ifndef ARDUINO_VARIANT
#define ARDUINO_VARIANT "esp32"
#endif

class MDNSResponder {
public:
  MDNSResponder();
  ~MDNSResponder();
  bool begin(const char* hostName);
  void end();

  void setInstanceName(String name);
  void setInstanceName(const char * name){
    setInstanceName(String(name));
  }
  void setInstanceName(char * name){
    setInstanceName(String(name));
  }

  bool addService(char *service, char *proto, uint16_t port);
  bool addService(const char *service, const char *proto, uint16_t port){
    return addService((char *)service, (char *)proto, port);
  }
  bool addService(String service, String proto, uint16_t port){
    return addService(service.c_str(), proto.c_str(), port);
  }
  
  bool addServiceTxt(char *name, char *proto, char * key, char * value);
  void addServiceTxt(const char *name, const char *proto, const char *key,const char * value){
    addServiceTxt((char *)name, (char *)proto, (char *)key, (char *)value);
  }
  void addServiceTxt(String name, String proto, String key, String value){
    addServiceTxt(name.c_str(), proto.c_str(), key.c_str(), value.c_str());
  }

  void enableArduino(uint16_t port=3232, bool auth=false);
  void disableArduino();

  void enableWorkstation(wifi_interface_t interface=ESP_IF_WIFI_STA);
  void disableWorkstation();

  IPAddress queryHost(char *host, uint32_t timeout=2000);
  IPAddress queryHost(const char *host, uint32_t timeout=2000){
    return queryHost((char *)host, timeout);
  }
  IPAddress queryHost(String host, uint32_t timeout=2000){
    return queryHost(host.c_str(), timeout);
  }
  
  int queryService(char *service, char *proto);
  int queryService(const char *service, const char *proto){
    return queryService((char *)service, (char *)proto);
  }
  int queryService(String service, String proto){
    return queryService(service.c_str(), proto.c_str());
  }

  String hostname(int idx);
  IPAddress IP(int idx);
  IPv6Address IPv6(int idx);
  uint16_t port(int idx);
  int numTxt(int idx);
  bool hasTxt(int idx, const char * key);
  String txt(int idx, const char * key);
  String txt(int idx, int txtIdx);
  
private:
  String _hostname;
  mdns_result_t * results;
  mdns_result_t * _getResult(int idx);
};

extern MDNSResponder MDNS;

#endif //ESP32MDNS_H
