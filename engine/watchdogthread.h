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

#ifndef WATCHDOGTHREAD_H_
#define WATCHDOGTHREAD_H_

#include "genericthread.h"
#include <stdio.h>
#include <map>
#include <set>

class WatchdogThread : public GenericThread {
 private:
  unsigned long long         _counter;
  int                        _time;
  pthread_mutex_t            _accessMutex;  
  std::set< GenericThread* > _previousThreads;
  std::set< GenericThread* > _currentThreads;
  std::map< GenericThread*, unsigned long long >   _ageOfThread;
  std::map< unsigned long long, GenericThread* >   _threadOfAge;
  virtual void run();
 public:
  WatchdogThread(int time);
  void tic( GenericThread* thread );
  void tac( GenericThread* thread );
  void respawnSlowestThread();
  void atomicCloseFileIfOpen(FILE*& file);
  ~WatchdogThread();
};

#endif // WATCHDOGTHREAD_H_
