#if EXT_TYPE == 0
"checkdate", T(Boolean), S(0), "month", T(Int32), NULL, S(0), "day", T(Int32), NULL, S(0), "year", T(Int32), NULL, S(0), NULL, S(0), 
"date_create", T(Object), S(0), "time", T(String), "null_string", S(0), "timezone", T(Object), "null_object", S(0), NULL, S(0), 
"date_date_set", T(Void), S(0), "object", T(Object), NULL, S(0), "year", T(Int32), NULL, S(0), "month", T(Int32), NULL, S(0), "day", T(Int32), NULL, S(0), NULL, S(0), 
"date_default_timezone_get", T(String), S(0), NULL, S(0), 
"date_default_timezone_set", T(Boolean), S(0), "name", T(String), NULL, S(0), NULL, S(0), 
"date_format", T(String), S(0), "object", T(Object), NULL, S(0), "format", T(String), NULL, S(0), NULL, S(0), 
"date_isodate_set", T(Void), S(0), "object", T(Object), NULL, S(0), "year", T(Int32), NULL, S(0), "week", T(Int32), NULL, S(0), "day", T(Int32), "1", S(0), NULL, S(0), 
"date_modify", T(Void), S(0), "object", T(Object), NULL, S(0), "modify", T(String), NULL, S(0), NULL, S(0), 
"date_offset_get", T(Int32), S(0), "object", T(Object), NULL, S(0), NULL, S(0), 
"date_parse", T(Variant), S(0), "date", T(String), NULL, S(0), NULL, S(0), 
"date_sun_info", T(Array), S(0), "ts", T(Int64), NULL, S(0), "latitude", T(Double), NULL, S(0), "longitude", T(Double), NULL, S(0), NULL, S(0), 
"date_sunrise", T(Variant), S(0), "timestamp", T(Int64), NULL, S(0), "format", T(Int32), "0", S(0), "latitude", T(Double), "0.0", S(0), "longitude", T(Double), "0.0", S(0), "zenith", T(Double), "0.0", S(0), "gmt_offset", T(Double), "99999.0", S(0), NULL, S(0), 
"date_sunset", T(Variant), S(0), "timestamp", T(Int64), NULL, S(0), "format", T(Int32), "0", S(0), "latitude", T(Double), "0.0", S(0), "longitude", T(Double), "0.0", S(0), "zenith", T(Double), "0.0", S(0), "gmt_offset", T(Double), "99999.0", S(0), NULL, S(0), 
"date_time_set", T(Void), S(0), "object", T(Object), NULL, S(0), "hour", T(Int32), NULL, S(0), "minute", T(Int32), NULL, S(0), "second", T(Int32), "0", S(0), NULL, S(0), 
"date_timezone_get", T(Variant), S(0), "object", T(Object), NULL, S(0), NULL, S(0), 
"date_timezone_set", T(Void), S(0), "object", T(Object), NULL, S(0), "timezone", T(Object), NULL, S(0), NULL, S(0), 
"date", T(String), S(0), "format", T(String), NULL, S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"getdate", T(Array), S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"gettimeofday", T(Variant), S(0), "return_float", T(Boolean), "false", S(0), NULL, S(0), 
"gmdate", T(String), S(0), "format", T(String), NULL, S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"gmmktime", T(Variant), S(0), "hour", T(Int32), "-1", S(0), "minute", T(Int32), "-1", S(0), "second", T(Int32), "-1", S(0), "month", T(Int32), "-1", S(0), "day", T(Int32), "-1", S(0), "year", T(Int32), "-1", S(0), NULL, S(0), 
"gmstrftime", T(String), S(0), "format", T(String), NULL, S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"idate", T(Int64), S(0), "format", T(String), NULL, S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"localtime", T(Array), S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), "is_associative", T(Boolean), "false", S(0), NULL, S(0), 
"microtime", T(Variant), S(0), "get_as_float", T(Boolean), "false", S(0), NULL, S(0), 
"mktime", T(Variant), S(0), "hour", T(Int32), "-1", S(0), "minute", T(Int32), "-1", S(0), "second", T(Int32), "-1", S(0), "month", T(Int32), "-1", S(0), "day", T(Int32), "-1", S(0), "year", T(Int32), "-1", S(0), NULL, S(0), 
"strftime", T(String), S(0), "format", T(String), NULL, S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"strptime", T(Variant), S(0), "date", T(String), NULL, S(0), "format", T(String), NULL, S(0), NULL, S(0), 
"strtotime", T(Variant), S(0), "input", T(String), NULL, S(0), "timestamp", T(Int64), "TimeStamp::Current()", S(0), NULL, S(0), 
"time", T(Int32), S(0), NULL, S(0), 
"timezone_abbreviations_list", T(Array), S(0), NULL, S(0), 
"timezone_identifiers_list", T(Array), S(0), NULL, S(0), 
"timezone_name_from_abbr", T(Variant), S(0), "abbr", T(String), NULL, S(0), "gmtoffset", T(Int32), "-1", S(0), "isdst", T(Boolean), "true", S(0), NULL, S(0), 
"timezone_name_get", T(String), S(0), "object", T(Object), NULL, S(0), NULL, S(0), 
"timezone_offset_get", T(Int32), S(0), "object", T(Object), NULL, S(0), "dt", T(Object), NULL, S(0), NULL, S(0), 
"timezone_open", T(Object), S(0), "timezone", T(String), NULL, S(0), NULL, S(0), 
"timezone_transitions_get", T(Array), S(0), "object", T(Object), NULL, S(0), NULL, S(0), 
#elif EXT_TYPE == 1
#elif EXT_TYPE == 2
"datetime", "", NULL, "__construct", T(Void), S(0), "time", T(String), "\"now\"", S(0), "timezone", T(Object), "null_object", S(0), NULL, S(0), S(0), S(0), S(0),"format", T(String), S(0), "format", T(String), NULL, S(0), NULL, S(0), S(0), S(0), S(0),"getoffset", T(Int64), S(0), NULL, S(0), S(0), S(0), S(0),"gettimezone", T(Variant), S(0), NULL, S(0), S(0), S(0), S(0),"modify", T(Object), S(0), "modify", T(String), NULL, S(0), NULL, S(0), S(0), S(0), S(0),"setdate", T(Object), S(0), "year", T(Int64), NULL, S(0), "month", T(Int64), NULL, S(0), "day", T(Int64), NULL, S(0), NULL, S(0), S(0), S(0), S(0),"setisodate", T(Object), S(0), "year", T(Int64), NULL, S(0), "week", T(Int64), NULL, S(0), "day", T(Int64), "1", S(0), NULL, S(0), S(0), S(0), S(0),"settime", T(Object), S(0), "hour", T(Int64), NULL, S(0), "minute", T(Int64), NULL, S(0), "second", T(Int64), "0", S(0), NULL, S(0), S(0), S(0), S(0),"settimezone", T(Object), S(0), "timezone", T(Object), NULL, S(0), NULL, S(0), S(0), S(0), S(0),"__destruct", T(Variant), S(0), NULL, S(0), S(0), S(0), S(0),NULL,"ATOM", T(String),"COOKIE", T(String),"ISO8601", T(String),"RFC822", T(String),"RFC850", T(String),"RFC1036", T(String),"RFC1123", T(String),"RFC2822", T(String),"RFC3339", T(String),"RSS", T(String),"W3C", T(String),NULL,
"datetimezone", "", NULL, "__construct", T(Void), S(0), "timezone", T(String), NULL, S(0), NULL, S(0), S(0), S(0), S(0),"getname", T(String), S(0), NULL, S(0), S(0), S(0), S(0),"getoffset", T(Int64), S(0), "datetime", T(Object), NULL, S(0), NULL, S(0), S(0), S(0), S(0),"gettransitions", T(Array), S(0), NULL, S(0), S(0), S(0), S(0),"listabbreviations", T(Array), S(0), NULL, S(0), S(0), S(0), S(1),"listidentifiers", T(Array), S(0), NULL, S(0), S(0), S(0), S(1),"__destruct", T(Variant), S(0), NULL, S(0), S(0), S(0), S(0),NULL,"AFRICA", T(Int64),"AMERICA", T(Int64),"ANTARCTICA", T(Int64),"ARCTIC", T(Int64),"ASIA", T(Int64),"ATLANTIC", T(Int64),"AUSTRALIA", T(Int64),"EUROPE", T(Int64),"INDIAN", T(Int64),"PACIFIC", T(Int64),"UTC", T(Int64),"ALL", T(Int64),"ALL_WITH_BC", T(Int64),"PER_COUNTRY", T(Int64),NULL,
#elif EXT_TYPE == 3

#endif
