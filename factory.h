/** ----------------------------------------------------------------------------
 * Embed Media Manager++ -- Renato "Lond" Cerqueira based on Embed Media Manager
 * Created by Lond in August/2012
 * -----------------------------------------------------------------------------
 * This file is part of Embed Media Manager++.
 *
 * Embed Media Manager++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * Embed Media Manager++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Ember Media Manager++.  If not, see <http://www.gnu.org/licenses/>.
 * -----------------------------------------------------------------------------
 */
#ifndef FACTORY_H
#define FACTORY_H

class cFileDownloader;

struct sqlite3;

namespace nDao
{
/**
 * @brief Clear the new flag from some databases: movies, tvshows, tvseason, tveps
 */
void clear_new(void);

class cMovie;
class cTvEpisodes;
class cTvSeason;
class cTvShows;

class cFactory
{
  static sqlite3 *m_connection;
  static sqlite3 *m_jobs_connection;
  static void create_databases(void);
  static void create_jobs_database(void);
protected:
public:
  static sqlite3* get_connection();
  static void begin_connection_scope(void);
  static void end_connection_scope(void);

  static cMovie* create_movie_dao(void);
  static cTvEpisodes* create_tvepisodes_dao(void);
  static cTvSeason* create_tvseason_dao(void);
  static cTvShows* create_tvshows_dao(void);
  cFactory();
};

}

#endif // FACTORY_H
