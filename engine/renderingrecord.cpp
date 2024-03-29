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

#include "renderingrecord.h"

RenderingRecord::RenderingRecord(WebContent* owner, long long int forceId)
{
  static long long int idCounter = time(NULL);

  _uniqueId = ( forceId >= 0 ) ? forceId : idCounter++;
  _owner = owner;
  _timestamp = -1;
}

void RenderingRecord::clearRecords()
{
  for ( size_t i = 0; i < _nestedRecords.size(); i++ )
    delete _nestedRecords[i];
  _nestedRecords.clear();
}

RenderingRecord::~RenderingRecord()
{
  clearRecords();
}

