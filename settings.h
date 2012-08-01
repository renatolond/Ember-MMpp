/** ----------------------------------------------------------------------------
 * Embed Media Manager++ -- Renato "Lond" Cerqueira based on Embed Media Manager
 * Created by Lond in July/2012
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
#ifndef SETTINGS_H
#define SETTINGS_H

#include "boost/shared_ptr.hpp"

struct sDatabaseMovie;
struct sDatabaseShow;
struct sMovieScrapeOptions;
struct sScrapeModifier;
struct sShowScrapeOptions;

class cSettings
{
  cSettings();
};

struct sSettings
{
  static bool m_can_scan_disk_image;
  // void database;
  static boost::shared_ptr<sDatabaseMovie> m_current_movie;
  static boost::shared_ptr<sDatabaseShow> m_current_show;
  static boost::shared_ptr<sMovieScrapeOptions> m_default_movie_options;
  static boost::shared_ptr<sShowScrapeOptions> default_show_options;
  // void language
  // void logger
  static boost::shared_ptr<cSettings> settings;
  static boost::shared_ptr<sScrapeModifier> scrape_modifier;
  // is_windows?
  // sourcesList list<string>
  // QString tmpPath;
  // void tmpMovie
  // moviesSources
  // tvsources
  // majorversion = 0.1
public:
  static void set_can_scan_disk_image(bool b)
  {
    m_can_scan_disk_image = b;
  }
  static bool get_can_scan_disk_image(void)
  {
    return m_can_scan_disk_image;
  }

  static void set_current_movie(boost::shared_ptr<sDatabaseMovie> ptr)
  {
    m_current_movie = ptr;
  }
  static boost::shared_ptr<sDatabaseMovie> get_current_movie(void)
  {
    return m_current_movie;
  }

  static void set_current_show(boost::shared_ptr<sDatabaseShow> ptr)
  {
    m_current_show = ptr;
  }
  static boost::shared_ptr<sDatabaseShow> get_current_show(void)
  {
    return m_current_show;
  }

  static void set_default_movie_options(boost::shared_ptr<sMovieScrapeOptions> ptr)
  {
    m_default_movie_options = ptr;
  }
  static boost::shared_ptr<sMovieScrapeOptions> get_default_movie_options(void)
  {
    return m_default_movie_options;
  }
};

#endif // SETTINGS_H
