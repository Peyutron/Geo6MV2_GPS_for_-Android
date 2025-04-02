String neo6mv2data() {
	//static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  int satellites = -1;
  float hdop = 0.0;
  float location_lat = 0.0;
  float location_lng = 0.0;
  int age = 0;
  String date = "";
  String time = "";
  char dateBuffer[10]; // 00/00/0000
  char timeBuffer[8]; // 00:00:00
  float altitude = 0;
  float course = 0;
  float speed = 0;

  if (gps.satellites.isValid()) satellites = gps.satellites.value();
  else satellites = -1;
  if (gps.hdop.isValid()) hdop = gps.hdop.hdop();
  else hdop = -1;
  if (gps.location.isValid()) location_lat = gps.location.lat();
  else location_lat = 0.0;    
  if (gps.location.isValid()) location_lng = gps.location.lng();
  else location_lng = -1;
  if (gps.location.isValid()) age = gps.location.age();
  else age = -1;
  if (gps.altitude.isValid()) altitude = gps.altitude.meters();
  else altitude = -1;
  if (gps.course.isValid()) course = gps.course.deg();
  else course = -1;      
  if (gps.speed.isValid()) speed = gps.speed.kmph();
  else speed = -1;

   if (gps.date.isUpdated())
    {
    sprintf(dateBuffer, "%d/%d/%d", gps.date.day(), gps.date.month(), gps.date.year());
    date = String(dateBuffer);
    }

  if (gps.time.isUpdated())
    {
    sprintf(timeBuffer, "%d:%d:%d", gps.time.hour(), gps.time.minute(), gps.time.second());
    time = String(timeBuffer);
    }
  
/**
	printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
	printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
	printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
	printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
	printInt(gps.location.age(), gps.location.isValid(), 5);
	printDateTime(gps.date, gps.time);
	printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
	printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
	printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
	printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);
**/
  return "<gps" 
            + String(satellites)
            + " " 
            + String(hdop)
            + " " 
            + String(location_lat,6)
            + " "
            + String(location_lng,6)
            + " "
            + String(age)
            + " "
            + date
            + " "
            + time
            + " "
            + String(altitude, 2)
            + " "
            + String(course, 2)
            + " "
            + String(speed, 2)
            + ">";
}