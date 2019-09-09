////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility.hpp
// Robert M. Baker | Created : 11JAN12 | Last Modified : 03SEP19 by Robert M. Baker
// Version : 2.2.1
// This is a header file for 'QMXStdLib'; it defines the interface for a general utility class.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
//
// This file is part of 'QMXStdLib'.
//
// 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @file
  * @author  Robert M. Baker
  * @date    Created : 11JAN12
  * @date    Last Modified : 03SEP19 by Robert M. Baker
  * @version 2.2.1
  *
  * @brief This header file defines the interface for a general utility class.
  *
  * @section UtilityH0000 Description
  *
  * This header file defines the interface for a general utility class.
  *
  * @section UtilityH0001 License
  *
  * Copyright (C) 2011-2019 QuantuMatriX Software, a QuantuMatriX Technologies Cooperative Partnership
  *
  * This file is part of 'QMXStdLib'.
  *
  * 'QMXStdLib' is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free
  * Software Foundation, either version 3 of the License, or (at your option) any later version.
  *
  * 'QMXStdLib' is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License along with 'QMXStdLib'.  If not, see <http://www.gnu.org/licenses/>.
  */

#ifndef __QMX_QMXSTDLIB_UTILITY_HPP_
#define __QMX_QMXSTDLIB_UTILITY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header Files
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <random>
#include <boost/locale.hpp>

#include "Base.hpp"
#include "Timer.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Static Macros
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define UTILITY_LANGUAGES 187
#define UTILITY_COUNTRIES 249

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Start of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QMXStdLib
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The 'Utility' Class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @class Utility Utility.hpp "include/Utility.hpp"
  *
  * @brief This class defines general utility algorithms.
  *
  * It is defined as a utility class; thus, it cannot be instantiated and contains only static members.
  *
  * Platform Independent     : Yes<br>
  * Architecture Independent : Yes<br>
  * Thread-Safe              : Yes
  */

class Utility
{
public:

	// Public Data Types

		/**
		  * @brief This structure holds version number data.
		  */

		struct VersionData
		{
		public:

			// Public Fields

				/**
				  * @brief This is the major version.
				  */

				uint64_t major;

				/**
				  * @brief This is the minor version.
				  */

				uint64_t minor;

				/**
				  * @brief This is the patch version.
				  */

				uint64_t patch;
		};

		/**
		  * @brief This structure stores data about a locale.
		  */

		struct LocaleData
		{
		public:

			// Public Fields

				/**
				  * @brief This is the full name of the locale (e.g. "en_US.UTF-8@currency=USD").
				  */

				std::string name;

				/**
				  * @brief This is the ISO 639-1 language code of the locale (e.g. "en").
				  */

				std::string language;

				/**
				  * @brief This is the ISO 3166-1 alpha-2 country code of the locale (e.g. "US").
				  */

				std::string country;

				/**
				  * @brief This is the character encoding of the locale (e.g. "UTF-8").
				  */

				std::string encoding;

				/**
				  * @brief This is the variant of the locale (e.g. "currency=USD").
				  */

				std::string variant;
		};

		/**
		  * @brief This union allows access of a dwords lower and upper words.
		  */

		template< typename DWType, typename WType > union DWord
		{
		public:

			// Public Fields

				/**
				  * @brief This is the dword data.
				  */

				DWType dword;

				/**
				  * @brief This is the array to access the upper and lower words.
				  */

				WType word[ 2 ];
		};

	// Public Fields

		/**
		  * @brief This is the array of languages paired with their ISO 639-1 code.
		  */

		inline static const StringPair languages[] = {
			std::make_pair( u8"Abkhaz",              u8"ab" ),
			std::make_pair( u8"Afar",                u8"aa" ),
			std::make_pair( u8"Afrikaans",           u8"af" ),
			std::make_pair( u8"Akan",                u8"ak" ),
			std::make_pair( u8"Albanian",            u8"sq" ),
			std::make_pair( u8"Alemannic ",          u8"gsw" ),
			std::make_pair( u8"Amharic",             u8"am" ),
			std::make_pair( u8"Arabic",              u8"ar" ),
			std::make_pair( u8"Aragonese",           u8"an" ),
			std::make_pair( u8"Armenian",            u8"hy" ),
			std::make_pair( u8"Assamese",            u8"as" ),
			std::make_pair( u8"Avaric",              u8"av" ),
			std::make_pair( u8"Avestan",             u8"ae" ),
			std::make_pair( u8"Aymara",              u8"ay" ),
			std::make_pair( u8"Azerbaijani",         u8"az" ),
			std::make_pair( u8"Bambara",             u8"bm" ),
			std::make_pair( u8"Banjar",              u8"bj" ),
			std::make_pair( u8"Bashkir",             u8"ba" ),
			std::make_pair( u8"Basque",              u8"eu" ),
			std::make_pair( u8"Belarusian",          u8"be" ),
			std::make_pair( u8"Bengali",             u8"bn" ),
			std::make_pair( u8"Bihari",              u8"bh" ),
			std::make_pair( u8"Bislama",             u8"bi" ),
			std::make_pair( u8"Bosnian",             u8"bs" ),
			std::make_pair( u8"Breton",              u8"br" ),
			std::make_pair( u8"Bulgarian",           u8"bg" ),
			std::make_pair( u8"Burmese",             u8"my" ),
			std::make_pair( u8"Catalan",             u8"ca" ),
			std::make_pair( u8"Chamorro",            u8"ch" ),
			std::make_pair( u8"Chechen",             u8"ce" ),
			std::make_pair( u8"Chichewa",            u8"ny" ),
			std::make_pair( u8"Chinese",             u8"zh" ),
			std::make_pair( u8"Chuvash",             u8"cv" ),
			std::make_pair( u8"Cornish",             u8"kw" ),
			std::make_pair( u8"Corsican",            u8"co" ),
			std::make_pair( u8"Cree",                u8"cr" ),
			std::make_pair( u8"Croatian",            u8"hr" ),
			std::make_pair( u8"Czech",               u8"cs" ),
			std::make_pair( u8"Danish",              u8"da" ),
			std::make_pair( u8"Dayak",               u8"da" ),
			std::make_pair( u8"Divehi",              u8"dv" ),
			std::make_pair( u8"Dutch",               u8"nl" ),
			std::make_pair( u8"Dzongkha",            u8"dz" ),
			std::make_pair( u8"English",             u8"en" ),
			std::make_pair( u8"Esperanto",           u8"eo" ),
			std::make_pair( u8"Estonian",            u8"et" ),
			std::make_pair( u8"Ewe",                 u8"ee" ),
			std::make_pair( u8"Faroese",             u8"fo" ),
			std::make_pair( u8"Fijian",              u8"fj" ),
			std::make_pair( u8"Finnish",             u8"fi" ),
			std::make_pair( u8"French",              u8"fr" ),
			std::make_pair( u8"Fula",                u8"ff" ),
			std::make_pair( u8"Galician",            u8"gl" ),
			std::make_pair( u8"Ganda",               u8"lg" ),
			std::make_pair( u8"Georgian",            u8"ka" ),
			std::make_pair( u8"German",              u8"de" ),
			std::make_pair( u8"Greek",               u8"el" ),
			std::make_pair( u8"Guaraní",             u8"gn" ),
			std::make_pair( u8"Gujarati",            u8"gu" ),
			std::make_pair( u8"Haitian",             u8"ht" ),
			std::make_pair( u8"Hausa",               u8"ha" ),
			std::make_pair( u8"Hebrew",              u8"he" ),
			std::make_pair( u8"Herero",              u8"hz" ),
			std::make_pair( u8"Hindi",               u8"hi" ),
			std::make_pair( u8"Hiri Motu",           u8"ho" ),
			std::make_pair( u8"Hungarian",           u8"hu" ),
			std::make_pair( u8"Icelandic",           u8"is" ),
			std::make_pair( u8"Ido",                 u8"io" ),
			std::make_pair( u8"Igbo",                u8"ig" ),
			std::make_pair( u8"Indonesian",          u8"id" ),
			std::make_pair( u8"Interlingua",         u8"ia" ),
			std::make_pair( u8"Interlingue",         u8"ie" ),
			std::make_pair( u8"Inuktitut",           u8"iu" ),
			std::make_pair( u8"Inupiaq",             u8"ik" ),
			std::make_pair( u8"Irish",               u8"ga" ),
			std::make_pair( u8"Italian",             u8"it" ),
			std::make_pair( u8"Japanese",            u8"ja" ),
			std::make_pair( u8"Javanese",            u8"jv" ),
			std::make_pair( u8"Kalaallisut",         u8"kl" ),
			std::make_pair( u8"Kannada",             u8"kn" ),
			std::make_pair( u8"Kanuri",              u8"kr" ),
			std::make_pair( u8"Kashmiri",            u8"ks" ),
			std::make_pair( u8"Kazakh",              u8"kk" ),
			std::make_pair( u8"Khmer",               u8"km" ),
			std::make_pair( u8"Kikuyu",              u8"ki" ),
			std::make_pair( u8"Kinyarwanda",         u8"rw" ),
			std::make_pair( u8"Kirundi",             u8"rn" ),
			std::make_pair( u8"Komi",                u8"kv" ),
			std::make_pair( u8"Kongo",               u8"kg" ),
			std::make_pair( u8"Korean",              u8"ko" ),
			std::make_pair( u8"Kurdish",             u8"ku" ),
			std::make_pair( u8"Kwanyama",            u8"kj" ),
			std::make_pair( u8"Kyrgyz",              u8"ky" ),
			std::make_pair( u8"Lao",                 u8"lo" ),
			std::make_pair( u8"Latin",               u8"la" ),
			std::make_pair( u8"Latvian",             u8"lv" ),
			std::make_pair( u8"Limburgish",          u8"li" ),
			std::make_pair( u8"Lingala",             u8"ln" ),
			std::make_pair( u8"Lithuanian",          u8"lt" ),
			std::make_pair( u8"Luba-Katanga",        u8"lu" ),
			std::make_pair( u8"Luxembourgish",       u8"lb" ),
			std::make_pair( u8"Macedonian",          u8"mk" ),
			std::make_pair( u8"Malagasy",            u8"mg" ),
			std::make_pair( u8"Malay",               u8"ms" ),
			std::make_pair( u8"Malayalam",           u8"ml" ),
			std::make_pair( u8"Maltese",             u8"mt" ),
			std::make_pair( u8"Manx",                u8"gv" ),
			std::make_pair( u8"Marathi",             u8"mr" ),
			std::make_pair( u8"Marshallese",         u8"mh" ),
			std::make_pair( u8"Mongolian",           u8"mn" ),
			std::make_pair( u8"Māori",               u8"mi" ),
			std::make_pair( u8"Nauru",               u8"na" ),
			std::make_pair( u8"Navajo",              u8"nv" ),
			std::make_pair( u8"Ndonga",              u8"ng" ),
			std::make_pair( u8"Nepali",              u8"ne" ),
			std::make_pair( u8"North Ndebele",       u8"nd" ),
			std::make_pair( u8"Northern Sami",       u8"se" ),
			std::make_pair( u8"Norwegian",           u8"no" ),
			std::make_pair( u8"Norwegian Bokmål",    u8"nb" ),
			std::make_pair( u8"Norwegian Nynorsk",   u8"nn" ),
			std::make_pair( u8"Nuosu",               u8"ii" ),
			std::make_pair( u8"Occitan",             u8"oc" ),
			std::make_pair( u8"Ojibwe",              u8"oj" ),
			std::make_pair( u8"Old Church Slavonic", u8"cu" ),
			std::make_pair( u8"Oriya",               u8"or" ),
			std::make_pair( u8"Oromo",               u8"om" ),
			std::make_pair( u8"Ossetian",            u8"os" ),
			std::make_pair( u8"Panjabi",             u8"pa" ),
			std::make_pair( u8"Pashto",              u8"ps" ),
			std::make_pair( u8"Persian",             u8"fa" ),
			std::make_pair( u8"Polish",              u8"pl" ),
			std::make_pair( u8"Portuguese",          u8"pt" ),
			std::make_pair( u8"Pāli",                u8"pi" ),
			std::make_pair( u8"Quechua",             u8"qu" ),
			std::make_pair( u8"Romanian",            u8"ro" ),
			std::make_pair( u8"Romansh",             u8"rm" ),
			std::make_pair( u8"Russian",             u8"ru" ),
			std::make_pair( u8"Samoan",              u8"sm" ),
			std::make_pair( u8"Sango",               u8"sg" ),
			std::make_pair( u8"Sanskrit",            u8"sa" ),
			std::make_pair( u8"Sardinian",           u8"sc" ),
			std::make_pair( u8"Scottish Gaelic",     u8"gd" ),
			std::make_pair( u8"Serbian",             u8"sr" ),
			std::make_pair( u8"Shona",               u8"sn" ),
			std::make_pair( u8"Sindhi",              u8"sd" ),
			std::make_pair( u8"Sinhala",             u8"si" ),
			std::make_pair( u8"Slovak",              u8"sk" ),
			std::make_pair( u8"Slovene",             u8"sl" ),
			std::make_pair( u8"Somali",              u8"so" ),
			std::make_pair( u8"South Ndebele",       u8"nr" ),
			std::make_pair( u8"Southern Sotho",      u8"st" ),
			std::make_pair( u8"Spanish",             u8"es" ),
			std::make_pair( u8"Sundanese",           u8"su" ),
			std::make_pair( u8"Swahili",             u8"sw" ),
			std::make_pair( u8"Swati",               u8"ss" ),
			std::make_pair( u8"Swedish",             u8"sv" ),
			std::make_pair( u8"Tagalog",             u8"tl" ),
			std::make_pair( u8"Tahitian",            u8"ty" ),
			std::make_pair( u8"Tajik",               u8"tg" ),
			std::make_pair( u8"Tamil",               u8"ta" ),
			std::make_pair( u8"Tatar",               u8"tt" ),
			std::make_pair( u8"Telugu",              u8"te" ),
			std::make_pair( u8"Thai",                u8"th" ),
			std::make_pair( u8"Tibetan",             u8"bo" ),
			std::make_pair( u8"Tigrinya",            u8"ti" ),
			std::make_pair( u8"Tonga",               u8"to" ),
			std::make_pair( u8"Tsonga",              u8"ts" ),
			std::make_pair( u8"Tswana",              u8"tn" ),
			std::make_pair( u8"Turkish",             u8"tr" ),
			std::make_pair( u8"Turkmen",             u8"tk" ),
			std::make_pair( u8"Twi",                 u8"tw" ),
			std::make_pair( u8"Uighur",              u8"ug" ),
			std::make_pair( u8"Ukrainian",           u8"uk" ),
			std::make_pair( u8"Urdu",                u8"ur" ),
			std::make_pair( u8"Uzbek",               u8"uz" ),
			std::make_pair( u8"Venda",               u8"ve" ),
			std::make_pair( u8"Vietnamese",          u8"vi" ),
			std::make_pair( u8"Volapük",             u8"vo" ),
			std::make_pair( u8"Walloon",             u8"wa" ),
			std::make_pair( u8"Welsh",               u8"cy" ),
			std::make_pair( u8"Western Frisian",     u8"fy" ),
			std::make_pair( u8"Wolof",               u8"wo" ),
			std::make_pair( u8"Xhosa",               u8"xh" ),
			std::make_pair( u8"Yiddish",             u8"yi" ),
			std::make_pair( u8"Yoruba",              u8"yo" ),
			std::make_pair( u8"Zhuang",              u8"za" ),
			std::make_pair( u8"Zulu",                u8"zu" )
		};

		/**
		  * @brief This is the array of countries paired with their ISO 3166-1 alpha-2 code.
		  */

		inline static const StringPair countries[] = {
			std::make_pair( u8"Afghanistan",                                  u8"AF" ),
			std::make_pair( u8"Åland Islands",                                u8"AX" ),
			std::make_pair( u8"Albania",                                      u8"AL" ),
			std::make_pair( u8"Algeria",                                      u8"DZ" ),
			std::make_pair( u8"American Samoa",                               u8"AS" ),
			std::make_pair( u8"Andorra",                                      u8"AD" ),
			std::make_pair( u8"Angola",                                       u8"AO" ),
			std::make_pair( u8"Anguilla",                                     u8"AI" ),
			std::make_pair( u8"Antarctica",                                   u8"AQ" ),
			std::make_pair( u8"Antigua and Barbuda",                          u8"AG" ),
			std::make_pair( u8"Argentina",                                    u8"AR" ),
			std::make_pair( u8"Armenia",                                      u8"AM" ),
			std::make_pair( u8"Aruba",                                        u8"AW" ),
			std::make_pair( u8"Australia",                                    u8"AU" ),
			std::make_pair( u8"Austria",                                      u8"AT" ),
			std::make_pair( u8"Azerbaijan",                                   u8"AZ" ),
			std::make_pair( u8"The Bahamas",                                  u8"BS" ),
			std::make_pair( u8"Bahrain",                                      u8"BH" ),
			std::make_pair( u8"Bangladesh",                                   u8"BD" ),
			std::make_pair( u8"Barbados",                                     u8"BB" ),
			std::make_pair( u8"Belarus",                                      u8"BY" ),
			std::make_pair( u8"Belgium",                                      u8"BE" ),
			std::make_pair( u8"Belize",                                       u8"BZ" ),
			std::make_pair( u8"Benin",                                        u8"BJ" ),
			std::make_pair( u8"Bermuda",                                      u8"BM" ),
			std::make_pair( u8"Bhutan",                                       u8"BT" ),
			std::make_pair( u8"Bolivia",                                      u8"BO" ),
			std::make_pair( u8"Caribbean Netherlands",                        u8"BQ" ),
			std::make_pair( u8"Bosnia and Herzegovina",                       u8"BA" ),
			std::make_pair( u8"Botswana",                                     u8"BW" ),
			std::make_pair( u8"Bouvet Island",                                u8"BV" ),
			std::make_pair( u8"Brazil",                                       u8"BR" ),
			std::make_pair( u8"British Indian Ocean Territory",               u8"IO" ),
			std::make_pair( u8"Brunei",                                       u8"BN" ),
			std::make_pair( u8"Bulgaria",                                     u8"BG" ),
			std::make_pair( u8"Burkina Faso",                                 u8"BF" ),
			std::make_pair( u8"Burundi",                                      u8"BI" ),
			std::make_pair( u8"Cambodia",                                     u8"KH" ),
			std::make_pair( u8"Cameroon",                                     u8"CM" ),
			std::make_pair( u8"Canada",                                       u8"CA" ),
			std::make_pair( u8"Cape Verde",                                   u8"CV" ),
			std::make_pair( u8"Cayman Islands",                               u8"KY" ),
			std::make_pair( u8"Central African Republic",                     u8"CF" ),
			std::make_pair( u8"Chad",                                         u8"TD" ),
			std::make_pair( u8"Chile",                                        u8"CL" ),
			std::make_pair( u8"China",                                        u8"CN" ),
			std::make_pair( u8"Christmas Island",                             u8"CX" ),
			std::make_pair( u8"Cocos (Keeling) Islands",                      u8"CC" ),
			std::make_pair( u8"Colombia",                                     u8"CO" ),
			std::make_pair( u8"Comoros",                                      u8"KM" ),
			std::make_pair( u8"Congo",                                        u8"CG" ),
			std::make_pair( u8"Democratic Republic of the Congo",             u8"CD" ),
			std::make_pair( u8"Cook Islands",                                 u8"CK" ),
			std::make_pair( u8"Costa Rica",                                   u8"CR" ),
			std::make_pair( u8"Côte d'Ivoire",                                u8"CI" ),
			std::make_pair( u8"Croatia",                                      u8"HR" ),
			std::make_pair( u8"Cuba",                                         u8"CU" ),
			std::make_pair( u8"Curaçao",                                      u8"CW" ),
			std::make_pair( u8"Cyprus",                                       u8"CY" ),
			std::make_pair( u8"Czech Republic",                               u8"CZ" ),
			std::make_pair( u8"Denmark",                                      u8"DK" ),
			std::make_pair( u8"Djibouti",                                     u8"DJ" ),
			std::make_pair( u8"Dominica",                                     u8"DM" ),
			std::make_pair( u8"Dominican Republic",                           u8"DO" ),
			std::make_pair( u8"Ecuador",                                      u8"EC" ),
			std::make_pair( u8"Egypt",                                        u8"EG" ),
			std::make_pair( u8"El Salvador",                                  u8"SV" ),
			std::make_pair( u8"Equatorial Guinea",                            u8"GQ" ),
			std::make_pair( u8"Eritrea",                                      u8"ER" ),
			std::make_pair( u8"Estonia",                                      u8"EE" ),
			std::make_pair( u8"Ethiopia",                                     u8"ET" ),
			std::make_pair( u8"Falkland Islands",                             u8"FK" ),
			std::make_pair( u8"Faroe Islands",                                u8"FO" ),
			std::make_pair( u8"Fiji",                                         u8"FJ" ),
			std::make_pair( u8"Finland",                                      u8"FI" ),
			std::make_pair( u8"France",                                       u8"FR" ),
			std::make_pair( u8"French Guiana",                                u8"GF" ),
			std::make_pair( u8"French Polynesia",                             u8"PF" ),
			std::make_pair( u8"French Southern and Antarctic Lands",          u8"TF" ),
			std::make_pair( u8"Gabon",                                        u8"GA" ),
			std::make_pair( u8"The Gambia",                                   u8"GM" ),
			std::make_pair( u8"Georgia",                                      u8"GE" ),
			std::make_pair( u8"Germany",                                      u8"DE" ),
			std::make_pair( u8"Ghana",                                        u8"GH" ),
			std::make_pair( u8"Gibraltar",                                    u8"GI" ),
			std::make_pair( u8"Greece",                                       u8"GR" ),
			std::make_pair( u8"Greenland",                                    u8"GL" ),
			std::make_pair( u8"Grenada",                                      u8"GD" ),
			std::make_pair( u8"Guadeloupe",                                   u8"GP" ),
			std::make_pair( u8"Guam",                                         u8"GU" ),
			std::make_pair( u8"Guatemala",                                    u8"GT" ),
			std::make_pair( u8"Guernsey",                                     u8"GG" ),
			std::make_pair( u8"Guinea",                                       u8"GN" ),
			std::make_pair( u8"Guinea-Bissau",                                u8"GW" ),
			std::make_pair( u8"Guyana",                                       u8"GY" ),
			std::make_pair( u8"Haiti",                                        u8"HT" ),
			std::make_pair( u8"Heard Island and McDonald Islands",            u8"HM" ),
			std::make_pair( u8"Vatican City",                                 u8"VA" ),
			std::make_pair( u8"Honduras",                                     u8"HN" ),
			std::make_pair( u8"Hong Kong",                                    u8"HK" ),
			std::make_pair( u8"Hungary",                                      u8"HU" ),
			std::make_pair( u8"Iceland",                                      u8"IS" ),
			std::make_pair( u8"India",                                        u8"IN" ),
			std::make_pair( u8"Indonesia",                                    u8"ID" ),
			std::make_pair( u8"Iran",                                         u8"IR" ),
			std::make_pair( u8"Iraq",                                         u8"IQ" ),
			std::make_pair( u8"Republic of Ireland",                          u8"IE" ),
			std::make_pair( u8"Isle of Man",                                  u8"IM" ),
			std::make_pair( u8"Israel",                                       u8"IL" ),
			std::make_pair( u8"Italy",                                        u8"IT" ),
			std::make_pair( u8"Jamaica",                                      u8"JM" ),
			std::make_pair( u8"Japan",                                        u8"JP" ),
			std::make_pair( u8"Jersey",                                       u8"JE" ),
			std::make_pair( u8"Jordan",                                       u8"JO" ),
			std::make_pair( u8"Kazakhstan",                                   u8"KZ" ),
			std::make_pair( u8"Kenya",                                        u8"KE" ),
			std::make_pair( u8"Kiribati",                                     u8"KI" ),
			std::make_pair( u8"North Korea",                                  u8"KP" ),
			std::make_pair( u8"South Korea",                                  u8"KR" ),
			std::make_pair( u8"Kuwait",                                       u8"KW" ),
			std::make_pair( u8"Kyrgyzstan",                                   u8"KG" ),
			std::make_pair( u8"Laos",                                         u8"LA" ),
			std::make_pair( u8"Latvia",                                       u8"LV" ),
			std::make_pair( u8"Lebanon",                                      u8"LB" ),
			std::make_pair( u8"Lesotho",                                      u8"LS" ),
			std::make_pair( u8"Liberia",                                      u8"LR" ),
			std::make_pair( u8"Libya",                                        u8"LY" ),
			std::make_pair( u8"Liechtenstein",                                u8"LI" ),
			std::make_pair( u8"Lithuania",                                    u8"LT" ),
			std::make_pair( u8"Luxembourg",                                   u8"LU" ),
			std::make_pair( u8"Macau",                                        u8"MO" ),
			std::make_pair( u8"Republic of Macedonia",                        u8"MK" ),
			std::make_pair( u8"Madagascar",                                   u8"MG" ),
			std::make_pair( u8"Malawi",                                       u8"MW" ),
			std::make_pair( u8"Malaysia",                                     u8"MY" ),
			std::make_pair( u8"Maldives",                                     u8"MV" ),
			std::make_pair( u8"Mali",                                         u8"ML" ),
			std::make_pair( u8"Malta",                                        u8"MT" ),
			std::make_pair( u8"Marshall Islands",                             u8"MH" ),
			std::make_pair( u8"Martinique",                                   u8"MQ" ),
			std::make_pair( u8"Mauritania",                                   u8"MR" ),
			std::make_pair( u8"Mauritius",                                    u8"MU" ),
			std::make_pair( u8"Mayotte",                                      u8"YT" ),
			std::make_pair( u8"Mexico",                                       u8"MX" ),
			std::make_pair( u8"Federated States of Micronesia",               u8"FM" ),
			std::make_pair( u8"Moldova",                                      u8"MD" ),
			std::make_pair( u8"Monaco",                                       u8"MC" ),
			std::make_pair( u8"Mongolia",                                     u8"MN" ),
			std::make_pair( u8"Montenegro",                                   u8"ME" ),
			std::make_pair( u8"Montserrat",                                   u8"MS" ),
			std::make_pair( u8"Morocco",                                      u8"MA" ),
			std::make_pair( u8"Mozambique",                                   u8"MZ" ),
			std::make_pair( u8"Myanmar",                                      u8"MM" ),
			std::make_pair( u8"Namibia",                                      u8"NA" ),
			std::make_pair( u8"Nauru",                                        u8"NR" ),
			std::make_pair( u8"Nepal",                                        u8"NP" ),
			std::make_pair( u8"Netherlands",                                  u8"NL" ),
			std::make_pair( u8"New Caledonia",                                u8"NC" ),
			std::make_pair( u8"New Zealand",                                  u8"NZ" ),
			std::make_pair( u8"Nicaragua",                                    u8"NI" ),
			std::make_pair( u8"Niger",                                        u8"NE" ),
			std::make_pair( u8"Nigeria",                                      u8"NG" ),
			std::make_pair( u8"Niue",                                         u8"NU" ),
			std::make_pair( u8"Norfolk Island",                               u8"NF" ),
			std::make_pair( u8"Northern Mariana Islands",                     u8"MP" ),
			std::make_pair( u8"Norway",                                       u8"NO" ),
			std::make_pair( u8"Oman",                                         u8"OM" ),
			std::make_pair( u8"Pakistan",                                     u8"PK" ),
			std::make_pair( u8"Palau",                                        u8"PW" ),
			std::make_pair( u8"Palestinian Territories",                      u8"PS" ),
			std::make_pair( u8"Panama",                                       u8"PA" ),
			std::make_pair( u8"Papua New Guinea",                             u8"PG" ),
			std::make_pair( u8"Paraguay",                                     u8"PY" ),
			std::make_pair( u8"Peru",                                         u8"PE" ),
			std::make_pair( u8"Philippines",                                  u8"PH" ),
			std::make_pair( u8"Pitcairn Islands",                             u8"PN" ),
			std::make_pair( u8"Poland",                                       u8"PL" ),
			std::make_pair( u8"Portugal",                                     u8"PT" ),
			std::make_pair( u8"Puerto Rico",                                  u8"PR" ),
			std::make_pair( u8"Qatar",                                        u8"QA" ),
			std::make_pair( u8"Réunion",                                      u8"RE" ),
			std::make_pair( u8"Romania",                                      u8"RO" ),
			std::make_pair( u8"Russia",                                       u8"RU" ),
			std::make_pair( u8"Rwanda",                                       u8"RW" ),
			std::make_pair( u8"Saint Barthélemy",                             u8"BL" ),
			std::make_pair( u8"Saint Helena, Ascension and Tristan da Cunha", u8"SH" ),
			std::make_pair( u8"Saint Kitts and Nevis",                        u8"KN" ),
			std::make_pair( u8"Saint Lucia",                                  u8"LC" ),
			std::make_pair( u8"Collectivity of Saint Martin",                 u8"MF" ),
			std::make_pair( u8"Saint Pierre and Miquelon",                    u8"PM" ),
			std::make_pair( u8"Saint Vincent and the Grenadines",             u8"VC" ),
			std::make_pair( u8"Samoa",                                        u8"WS" ),
			std::make_pair( u8"San Marino",                                   u8"SM" ),
			std::make_pair( u8"São Tomé and Príncipe",                        u8"ST" ),
			std::make_pair( u8"Saudi Arabia",                                 u8"SA" ),
			std::make_pair( u8"Senegal",                                      u8"SN" ),
			std::make_pair( u8"Serbia",                                       u8"RS" ),
			std::make_pair( u8"Seychelles",                                   u8"SC" ),
			std::make_pair( u8"Sierra Leone",                                 u8"SL" ),
			std::make_pair( u8"Singapore",                                    u8"SG" ),
			std::make_pair( u8"Sint Maarten",                                 u8"SX" ),
			std::make_pair( u8"Slovakia",                                     u8"SK" ),
			std::make_pair( u8"Slovenia",                                     u8"SI" ),
			std::make_pair( u8"Solomon Islands",                              u8"SB" ),
			std::make_pair( u8"Somalia",                                      u8"SO" ),
			std::make_pair( u8"South Africa",                                 u8"ZA" ),
			std::make_pair( u8"South Georgia and the South Sandwich Islands", u8"GS" ),
			std::make_pair( u8"South Sudan",                                  u8"SS" ),
			std::make_pair( u8"Spain",                                        u8"ES" ),
			std::make_pair( u8"Sri Lanka",                                    u8"LK" ),
			std::make_pair( u8"Sudan",                                        u8"SD" ),
			std::make_pair( u8"Suriname",                                     u8"SR" ),
			std::make_pair( u8"Svalbard and Jan Mayen",                       u8"SJ" ),
			std::make_pair( u8"Swaziland",                                    u8"SZ" ),
			std::make_pair( u8"Sweden",                                       u8"SE" ),
			std::make_pair( u8"Switzerland",                                  u8"CH" ),
			std::make_pair( u8"Syria",                                        u8"SY" ),
			std::make_pair( u8"Taiwan",                                       u8"TW" ),
			std::make_pair( u8"Tajikistan",                                   u8"TJ" ),
			std::make_pair( u8"Tanzania",                                     u8"TZ" ),
			std::make_pair( u8"Thailand",                                     u8"TH" ),
			std::make_pair( u8"East Timor",                                   u8"TL" ),
			std::make_pair( u8"Togo",                                         u8"TG" ),
			std::make_pair( u8"Tokelau",                                      u8"TK" ),
			std::make_pair( u8"Tonga",                                        u8"TO" ),
			std::make_pair( u8"Trinidad and Tobago",                          u8"TT" ),
			std::make_pair( u8"Tunisia",                                      u8"TN" ),
			std::make_pair( u8"Turkey",                                       u8"TR" ),
			std::make_pair( u8"Turkmenistan",                                 u8"TM" ),
			std::make_pair( u8"Turks and Caicos Islands",                     u8"TC" ),
			std::make_pair( u8"Tuvalu",                                       u8"TV" ),
			std::make_pair( u8"Uganda",                                       u8"UG" ),
			std::make_pair( u8"Ukraine",                                      u8"UA" ),
			std::make_pair( u8"United Arab Emirates",                         u8"AE" ),
			std::make_pair( u8"United Kingdom",                               u8"GB" ),
			std::make_pair( u8"United States",                                u8"US" ),
			std::make_pair( u8"United States Minor Outlying Islands",         u8"UM" ),
			std::make_pair( u8"Uruguay",                                      u8"UY" ),
			std::make_pair( u8"Uzbekistan",                                   u8"UZ" ),
			std::make_pair( u8"Vanuatu",                                      u8"VU" ),
			std::make_pair( u8"Venezuela",                                    u8"VE" ),
			std::make_pair( u8"Vietnam",                                      u8"VN" ),
			std::make_pair( u8"British Virgin Islands",                       u8"VG" ),
			std::make_pair( u8"United States Virgin Islands",                 u8"VI" ),
			std::make_pair( u8"Wallis and Futuna",                            u8"WF" ),
			std::make_pair( u8"Western Sahara",                               u8"EH" ),
			std::make_pair( u8"Yemen",                                        u8"YE" ),
			std::make_pair( u8"Zambia",                                       u8"ZM" ),
			std::make_pair( u8"Zimbabwe",                                     u8"ZW" )
		};

	// Public Methods

		/**
		  * @brief This method gets the current version data for this library.
		  *
		  * @return
		  * 	A 'VersionData' instance containing the version data for this library.
		  */

		static VersionData getVersionNumber()
		{
			// Return version data for this library to calling routine.

				return { QMXSTDLIB_VER_MAJOR, QMXSTDLIB_VER_MINOR, QMXSTDLIB_VER_PATCH };
		}

		/**
		  * @brief This method gets the current version string for this library.
		  *
		  * @return
		  * 	A string representing the current version data for this library.
		  */

		static std::string getVersionString()
		{
			// Create local variables.

				std::ostringstream result;

			// Construct a string representation of the current version data for this library.

				result << QMXSTDLIB_VER_MAJOR << '.' << QMXSTDLIB_VER_MINOR << '.' << QMXSTDLIB_VER_PATCH;

			// Return result to calling routine.

				return result.str();
		}

		/**
		  * @brief This method gets the ISO 639-1 code for the specified language.
		  *
		  * @param language
		  * 	This is the language from which to get the ISO 639-1 code.
		  *
		  * @return
		  * 	The ISO 639-1 code for the specified language, if it exists, or an empty string otherwise.
		  */

		static std::string getLanguageCode( const std::string& language )
		{
			// Create local variables.

				std::string result;
				bool isDone = false;
				const StringPair* languagesIterator = &languages[ 0 ];
				const StringPair* languagesEnd = &languages[ ( UTILITY_LANGUAGES - 1 ) ] + 1;

			// Get ISO 639-1 Code for specified language, if it exists.

				while( !isDone && ( languagesIterator != languagesEnd ) )
				{
					if( languagesIterator->first == language )
					{
						result = languagesIterator->second;
						isDone = true;
					}

					languagesIterator++;
				}

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method gets the ISO 3166-1 alpha-2 code for the specified country.
		  *
		  * @param country
		  * 	This is the country from which to get the ISO 3166-1 alpha-2 code.
		  *
		  * @return
		  * 	The ISO 3166-1 alpha-2 code for the specified country, if it exists, or an empty string otherwise.
		  */

		static std::string getCountryCode( const std::string& country )
		{
			// Create local variables.

				std::string result;
				bool isDone = false;
				const StringPair* countriesIterator = &countries[ 0 ];
				const StringPair* countriesEnd = &countries[ ( UTILITY_COUNTRIES - 1 ) ] + 1;

			// Get ISO 3166-1 alpha-2 Code for specified country, if it exists.

				while( !isDone && ( countriesIterator != countriesEnd ) )
				{
					if( countriesIterator->first == country )
					{
						result = countriesIterator->second;
						isDone = true;
					}

					countriesIterator++;
				}

			// Return result to calling routine.

				return result;
		}

		/**
		  * @brief This method generates a locale based on the specified ID.
		  *
		  * @param id
		  * 	This is the ID to use when generating the locale.
		  *
		  * @return
		  * 	A locale object generated using the specified ID.
		  */

		static std::locale generateLocale( const std::string& id )
		{
			// Create local variables.

				boost::locale::generator localeGenerator;

			// Return generated locale to calling routine.

				return localeGenerator( id );
		}

		/**
		  * @brief This method gets data about the specified locale, if it is valid.
		  *
		  * @param target
		  * 	This is a 'LocaleData' structure reference which will receive the data for the specified locale; if the specified locale is invalid, this will not
		  * 	be modified.
		  *
		  * @param source
		  * 	This is the locale from which to retrieve data.
		  */

		static void getLocaleData( LocaleData& target, const std::locale& source )
		{
			// Get locale data for specified locale, if it is valid.

				if( std::has_facet< boost::locale::info >( source ) )
					target = {
						std::use_facet< boost::locale::info >( source ).name(),
						std::use_facet< boost::locale::info >( source ).language(),
						std::use_facet< boost::locale::info >( source ).country(),
						std::use_facet< boost::locale::info >( source ).encoding(),
						std::use_facet< boost::locale::info >( source ).variant()
					};
		}

		/**
		  * @brief This method generates a time stamp, in 24-hour format, using the current time (e.g. "13:37:00h" ).
		  *
		  * @return
		  * 	A string representing the time stamp.
		  */

		static std::string timeStamp()
		{
			// Create local variables.

				std::ostringstream result;
				time_t currentTime = time( nullptr );
				tm* systemTime = localtime( &currentTime );

			// Construct a string representation of the time stamp using the current time.

				result << std::setfill( '0' ) << std::setw( 2 ) << systemTime->tm_hour << ':' <<
					std::setw( 2 ) << systemTime->tm_min << ':' <<
					std::setw( 2 ) << systemTime->tm_sec << 'h';

			// Return result to calling routine.

				return result.str();
		}

		/**
		  * @brief This method halts execution of the application for the specified amount of time.
		  *
		  * This method will block any further execution during the period it is in effect.  This should only be used when constant logic processing is unneeded.
		  *
		  * @param interval
		  * 	This is the time interval that the application will be halted.
		  *
		  * @param units
		  * 	These are the units to use with the specified time interval.
		  */

		static void pause( real_t interval, Timer::TimeUnits units = Timer::MILLISECONDS )
		{
			// Create local variables.

				Timer::InstancePtr delayTimer = Timer::create();

			// Pause for the specified time interval.

				delayTimer->toggle();

				while( delayTimer->getTime( units ) < interval );
					// Empty Loop
		}

		/**
		  * @brief This method sets the seed for the random number generator.
		  *
		  * @param seed
		  * 	This is the seed to use; if it is set to 'UNSET', the current time will be used instead.
		  */

		static void setRandomSeed( uint32_t seed = UNSET )
		{
			// Seed random number generator with specified value, or use current time if specified value is 'UNSET'.

				generator.seed( ( !seed ? time( nullptr ) : seed ) );
		}

		/**
		  * @brief This method defines the structure for a random integral number generator.
		  *
		  * @param min
		  * 	This is the minimum value of the random number.
		  *
		  * @param max
		  * 	This is the maximum value of the random number.
		  *
		  * @return
		  * 	The random number generated.
		  */

		template< typename IType > static IType randInt( IType min, IType max )
		{
			// Create local variables.

				std::uniform_int_distribution< IType > distro( min, max );

			// Return a random number within the specified range to calling routine.

				return distro( generator );
		}

		/**
		  * @brief This method defines the structure for a random floating point number generator.
		  *
		  * @param min
		  * 	This is the minimum value of the random number.
		  *
		  * @param max
		  * 	This is the maximum value of the random number.
		  *
		  * @return
		  * 	The random number generated.
		  */

		template< typename FType > static FType randFloat( FType min, FType max )
		{
			// Create local variables.

				std::uniform_real_distribution< FType > distro( min, max );

			// Return a random number within the specified range to calling routine.

				return distro( generator );
		}

private:

	// Private Fields

		/**
		  * @brief This is the generator to use for the random number generation methods.
		  */

		inline static std::mt19937 generator;

	// Private Constructors

		/**
		  * @brief This is the default constructor, which is made private to prevent instantiation.
		  */

		Utility()
		{
			// Do nothing.
		}
};

} // 'QMXStdLib' Namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of the 'QMXStdLib' Namespace
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // __QMX_QMXSTDLIB_UTILITY_HPP_

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of 'Utility.hpp'
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
