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
#include "settings.h"

boost::shared_ptr<sDatabaseMovie> sSettings::m_current_movie;
boost::shared_ptr<sDatabaseShow> sSettings::m_current_show;
boost::shared_ptr<sMovieScrapeOptions> sSettings::m_default_movie_options;
boost::shared_ptr<sShowScrapeOptions> sSettings::default_show_options;
boost::shared_ptr<cSettings> sSettings::settings;
boost::shared_ptr<sScrapeModifier> sSettings::scrape_modifier;

cSettings::cSettings()
{
}
