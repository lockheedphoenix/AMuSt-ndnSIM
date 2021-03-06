/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2015 Christian Kreuzberger and Daniel Posch, Alpen-Adria-University 
 * Klagenfurt
 *
 * This file is part of amus-ndnSIM, based on ndnSIM. See AUTHORS for complete list of 
 * authors and contributors.
 *
 * amus-ndnSIM and ndnSIM are free software: you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free Software 
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * amus-ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * amus-ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef OON_PROCESSOR_H
#define OON_PROCESSOR_H

#define D_ACTUAL_OVERHEAD 100

#include "ns3/ndnSIM/model/ndn-common.hpp"

#include "ndn-app.hpp"
#include "ns3/ndnSIM/model/ndn-common.hpp"

#include "ns3/nstime.h"
#include "ns3/ptr.h"
#include <map>

namespace ns3 {
namespace ndn {

/**
This general OON processor is under construction 05012017
 */

//OON
typedef std::map<std::string, int> NAME_MAP;
typedef std::map<int, std::string> RENAME_MAP;

class Processor : public App {
public:

  static TypeId
  GetTypeId(void);

  Processor();

  // inherited from NdnApp
  virtual void
  OnInterest(shared_ptr<const Interest> interest);

protected:
  // inherited from Application base class.
  virtual void
  StartApplication(); // Called at time specified by Start

  virtual void
  StopApplication(); // Called at time specified by Stop

  void
  ReturnManifestData(shared_ptr<const Interest> interest, std::string& fname); // return file-manifest data

  void
  ReturnPayloadData(shared_ptr<const Interest> interest, std::string& fname, uint32_t seqNo);

  void 
  Rename_Interest(std::string& fname);

  long
  GetFileSize(std::string filename);

  uint16_t
  GetFaceMTU(uint32_t faceId);

  size_t
  EstimateOverhead(std::string& fname);



  uint16_t m_MTU;

private:
  //OON
  static NAME_MAP  name_map;
  static RENAME_MAP  rename_map;
  static NAME_MAP init_name_map();
  static RENAME_MAP init_rename_map();

  std::string m_prefix;
  std::string m_processorInterface;
  std::string m_contentDir;
  std::string m_postfixManifest;

  std::map<std::string,long> m_fileSizes;
  std::map<std::string,size_t> m_packetSizes;


  uint32_t m_maxPayloadSize;
  Time m_freshness;

  uint32_t m_signature;
  Name m_keyLocator;
};


} // namespace ndn
} // namespace ns3
#endif // OON_PROCESSOR_H
