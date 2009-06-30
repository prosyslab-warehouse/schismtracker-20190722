/*
 * Schism Tracker - a cross-platform Impulse Tracker clone
 * copyright (c) 2003-2005 Storlek <storlek@rigelseven.com>
 * copyright (c) 2005-2008 Mrs. Brisby <mrs.brisby@nimh.org>
 * copyright (c) 2009 Storlek & Mrs. Brisby
 * URL: http://schismtracker.org/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "headers.h"
#include "fmt.h"

/* --------------------------------------------------------------------- */

/* TODO: test this */

int fmt_ult_read_info(dmoz_file_t *file, const uint8_t *data, size_t length)
{
        if (!(length > 48 && memcmp(data, "MAS_UTrack_V00", 14) == 0))
                return false;

        file->description = "UltraTracker Module";
        file->type = TYPE_MODULE_S3M;
        /*file->extension = str_dup("ult");*/
        file->title = calloc(33, sizeof(char));
        memcpy(file->title, data + 15, 32);
        file->title[32] = 0;
        return true;
}