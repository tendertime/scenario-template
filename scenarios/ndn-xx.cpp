/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

// ndn-grid.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/ndnSIM-module.h"

#include <sstream>
#include <iostream>
#include <map>

namespace ns3 {

/**
 * This scenario simulates a grid topology (using PointToPointGrid module)
 *
 * (consumer) -- ( ) ----- ( )
 *     |          |         |
 *    ( ) ------ ( ) ----- ( )
 *     |          |         |
 *    ( ) ------ ( ) -- (producer)
 *
 * All links are 1Mbps with propagation 10ms delay.
 *
 * FIB is populated using NdnGlobalRoutingHelper.
 *
 * Consumer requests data from producer with frequency 100 interests per second
 * (interests contain constantly increasing sequence number).
 *
 * For every received interest, producer replies with a data packet, containing
 * 1024 bytes of virtual payload.
 *
 * To run scenario and see what is happening, use the following command:
 *
 *     NS_LOG=ndn.Consumer:ndn.Producer ./waf --run=ndn-grid
 */

int
main(int argc, char* argv[])
{
  // Setting default parameters for PointToPoint links and channels
  Config::SetDefault("ns3::PointToPointNetDevice::DataRate", StringValue("1Mbps"));
  Config::SetDefault("ns3::PointToPointChannel::Delay", StringValue("10ms"));
  Config::SetDefault("ns3::DropTailQueue::MaxPackets", StringValue("10"));

  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse(argc, argv);
  
  // Creating 3x3 topology
  PointToPointHelper p2p;
  PointToPointGridHelper grid(3, 3, p2p);
  grid.BoundingBox(100, 100, 200, 200);

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  //ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize","4096");
  ndnHelper.setCsSize(10240);
  ndnHelper.setPolicy("nfd::cs::priority_fifo");
  ndnHelper.InstallAll();

  // Set BestRoute strategy
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");

  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();


  // Install NDN applications
  std::string pre = "/%FE%0";//至今无法理解
  //ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerZipfMandelbrot");
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  // add my prefix;
  std::map<Ptr<Node>,std::string> prefixmap;
  prefixmap.insert(pair<Ptr<Node>,std::string>(grid.GetNode(2, 2),pre));
  std::stringstream s;
  for (NodeList::Iterator node = NodeList::Begin(); node != NodeList::End(); node++)
  {
    s<<(*node)->GetId();
    std::string prefix=pre+s.str();
    s.str("");
    prefixmap.insert(pair<Ptr<Node>,std::string>(*node,prefix));
    producerHelper.SetPrefix(prefix);
    producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
    producerHelper.Install(*node);
    ndnGlobalRoutingHelper.AddOrigin(prefix, *node);
    //cout<<prefix<<endl;
  }

  //NodeContainer consumerNodes;
  //consumerNodes.Add(grid.GetNode(0, 0));

  for (NodeList::Iterator node = NodeList::Begin(); node != NodeList::End(); node++)   
  {
    for (NodeList::Iterator nodex = NodeList::Begin(); nodex != NodeList::End(); nodex++)
    {
      //consumerHelper.SetPrefix(prefixmap[*node]);
      //cout<<prefixmap[*node]<<endl;
      consumerHelper.SetAttribute("NumberOfContents", StringValue("100"));
      consumerHelper.SetAttribute("Frequency", StringValue("100"));
      consumerHelper.Install(*nodex);
    }
  }
  // Add /prefix origins to ndn::GlobalRouter
  //ndnGlobalRoutingHelper.AddOrigins(prefix, producer);

  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();

  Simulator::Stop(Seconds(20.0));

  //ndn::CsTracer::InstallAll("cs-trace.txt", Seconds(1));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}

} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
