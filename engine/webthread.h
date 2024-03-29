/* Copyright (c) 2018 Jiri Ocenasek, http://nettomation.com
 *
 * This file is part of Nettomation.
 *
 * Nettomation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * For tutorials, donations and proprietary licensing options
 * please visit http://nettomation.com
 */

#ifndef WEBTHREAD_H_
#define WEBTHREAD_H_

#include "genericthread.h"
#include "watchdogthread.h"
#include "sharedqueue.h"

#define BUFFSIZE 500000   // take enough to accommodate the header plus POST content
#define FBSIZE    65536   // intermediate buffer size for downloading files

class Dispatcher;

class WebThread : public GenericThread {
 protected:
  char        _buffer[BUFFSIZE+1]; // this limits the max size of a request, including the POST body
  char        _fbuf[FBSIZE];

  int         _handle; // this is the TCP-IP socket
  FILE*       _output; // this is the duplicated socket, wrapped as regular file descriptor for convenience
  FILE*       _file;   // this is for reading the external files

 private:
  SharedQueue<int>* _sharedQueue;
  WatchdogThread*   _watchdog;
  Dispatcher*       _dispatcher;
  virtual void run();
  virtual void parseStream();
 public:
  WebThread(SharedQueue<int>* sharedQueue, WatchdogThread* watchdog, Dispatcher* dispatcher);
  virtual void cleanup();
};

#endif // WEBTHREAD_H_
