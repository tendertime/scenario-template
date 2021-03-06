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

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>

namespace ns3 {

int
main(int argc, char* argv[])
{
  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse(argc, argv);
  
  AnnotatedTopologyReader topologyReader("", 25);
  //topologyReader.SetFileName("./results/cernet/cernet.txt");//37
  //topologyReader.SetFileName("./results/garr/garr.txt");//47
  //topologyReader.SetFileName("./results/geant/geant.txt");//37
  topologyReader.SetFileName("./results/janet/janet.txt");//28
  //topologyReader.SetFileName("./results/surfnet/surfnet.txt");//50
  //topologyReader.SetFileName("./results/dfn/dfn.txt");//51
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize","0");
  //ndnHelper.setCsSize(10240);
  //ndnHelper.setPolicy("nfd::cs::priority_fifo");
 // ndnHelper.SetOldContentStore("ns3::ndn::cs::Probability::Lru", "MaxSize","0","CacheProbability","0.5");
  ndnHelper.InstallAll();

  // Set BestRoute strategy
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");
  
  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();
  
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerZipfMandelbrot");
  consumerHelper.SetAttribute("NumberOfContents", StringValue("100"));
  consumerHelper.SetAttribute("Frequency", StringValue("10"));
  //consumerHelper.SetPrefix("");
  NodeContainer consumerNodes;


  for (NodeList::Iterator node = NodeList::Begin(); node != NodeList::End(); node++)   
  {
    consumerNodes.Add(*node);
  }
  //consumerHelper.SetPrefix("/");
  //consumerHelper.Install(consumerNodes);


  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  for (NodeList::Iterator node = NodeList::Begin(); node != NodeList::End(); node++)
  {
    char buffer[10];
    uint32_t x=(*node)->GetId();
    sprintf(buffer,"%02d",x);
    std::string prefix=buffer;
    //std::cout<<prefix<<endl;
    ndnGlobalRoutingHelper.AddOrigin(prefix, *node);
    producerHelper.SetPrefix(prefix);
    producerHelper.Install(*node);
    consumerHelper.SetPrefix(prefix);
    consumerHelper.Install(consumerNodes);
  }
  
  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();

  Simulator::Stop(Seconds(10.0));

  //ndn::CsTracer::InstallAll("cs-trace-xx.txt", Seconds(1));
  //ndn::L3RateTracer::InstallAll("rate-trace.txt", Seconds(0.5));
  //L2RateTracer::InstallAll("drop-trace-xx.txt", Seconds(0.5));

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
