/*  internal_config - Internal config settings
Copyright (C) 2025 Dream Helium
    This file is part of dhmcdir.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include "internal_config.h"

#include "../config.h"

DhStrArray* translation_dir = NULL;

void dhmcdir_set_single_translation_dir(const char* dir)
{
    dh_str_array_free(translation_dir);
    dh_str_array_add_str(&translation_dir, dir);
}

void dhmcdir_set_multi_translation_dir(DhStrArray* arr)
{
    dh_str_array_free(translation_dir);
    for (int i = 0 ; i < arr->num ; i++)
        dh_str_array_add_str(&translation_dir, arr->val[i]);
}

const DhStrArray* dhmcdir_get_translation_dir()
{
    return translation_dir;
}

void dhmcdir_exit()
{
    dh_str_array_free(translation_dir);
}

void dhmcdir_update_content(const cJSON* json)
{
    char* transdir = dh_get_config_item("itemTranslate");
    /* Analyse */
    DhStrArray* arr = NULL;
    char** dirarray_o = g_strsplit(transdir, ":", -1);
    char** dirarray = dirarray_o;
    for (; *dirarray && **dirarray ; dirarray++)
        dh_str_array_add_str(&arr, *dirarray);
    g_strfreev(dirarray_o);
    /* Add */
    dhmcdir_set_multi_translation_dir(arr);

    dh_str_array_free(arr);
    g_free(transdir);
}
