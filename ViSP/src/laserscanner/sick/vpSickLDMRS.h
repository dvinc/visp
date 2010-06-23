/****************************************************************************
 *
 * $Id$
 *
 * Copyright (C) 1998-2010 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * Sick LD-MRS laser driver.
 *
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/
#ifndef vpSickLDMRS_h
#define vpSickLDMRS_h

#ifdef UNIX

#include <arpa/inet.h>
#include <iostream>
#include <vector>

#include "visp/vpConfig.h"
#include "visp/vpScanPoint.h"
#include "visp/vpLaserScan.h"
#include "visp/vpLaserScanner.h"
#include "visp/vpSickLDMRSHeader.h"

/*!

  \file vpSickLDMRS.h

  \brief Driver for the Sick LD-MRS laser scanner.
*/

/*!

  \class vpSickLDMRS

  \ingroup LaserDriver

  \brief Driver for the Sick LD-MRS laser scanner.

  \warning For the moment, this driver works only on UNIX platform.

  The code below shows how the four laser scan provided by the Sick
  LD-MRS could be acquired.

  \code
  #include "visp/vpSickLDMRS.h"

int main()
{
  std::string ip = "131.254.12.119";

  vpSickLDMRS laser;
  laser.setIpAddress(ip);
  laser.setup();
    
  vpLaserScan laserscan[4];
  while (1)
    laser.measure(laserscan);
}
  \endcode
*/
class VISP_EXPORT vpSickLDMRS : public vpLaserScanner
{
 public:
  vpSickLDMRS();
  /*! Copy constructor. */
 vpSickLDMRS(const vpSickLDMRS &sick) : vpLaserScanner(sick) {
    socket_fd = sick.socket_fd;
    body = new unsigned char [104000];
  };
  virtual ~vpSickLDMRS();
  bool setup(std::string ip, int port);
  bool setup();
  bool measure(vpLaserScan laserscan[4]);

 protected:
#ifdef WIN32
  SOCKET socket_fd;
#else
  int socket_fd;  
#endif
 private:
  unsigned char *body;
 };

#endif

#endif