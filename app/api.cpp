#include <stdio.h>
#include <string>

#include "api.h"
#include "cpp-utils.h"
#include "Exif.h"

using namespace std;

void API::setFrame(QWebFrame *frame) {
  this->frame = frame;
}

int API::log() {
  fprintf(stderr, "log!\n");
  return 33;
}

void API::addJSObject() {
  frame->addToJavaScriptWindowObject(QString("api"), this);
}

// readThumbnail:  
// Example
// <img id="thumbnail" style="width:160px; height:120px">
// <script>
// window.api.readThumbnail("../patp10/00IMG_9946.JPG").assignToHTMLImageElement(document.getElementById('thumbnail'));
// </script>

QPixmap API::readThumbnail(QString path) {
  try {
    string path_utf8 = path.toUtf8().constData();
    FILE *in = fopen_utf8(path_utf8, "rw");
    EXIF_ASSERT(in, ExifErr() << "Can't read " << path_utf8);
    ExifView exif(path_utf8);
    size_t offset = exif.get_thumbnail_location();
    int32 length;
    exif.query_by_tag(EXIF_ThumbnailLength, length);
    EXIF_ASSERT(length > 0, ExifErr() << "Illegal thumbnail length");
    vector<unsigned char> buf(length);
    EXIF_ASSERT(fseek(in, offset, SEEK_SET) == 0, ExifErr() << "Error reading thumbnail");
    EXIF_ASSERT(1 == (int32)fread(&buf[0], length, 1, in), ExifErr() << "Error reading thumbnail");
    fclose(in);
    QPixmap ret;
    ret.loadFromData(&buf[0], length);
    return ret;
  } catch (ExifErr &e) {
    fprintf(stderr, "ExifErr: %s\n", e.what());
    return QPixmap();
  }
}

double API::exifTime(QString path) {
  try {
    string path_utf8 = path.toUtf8().constData();
    ExifView exif(path_utf8);
    ExifDateTime capture_time = exif.get_capture_time();
    struct tm tm;
    memset(&tm, 0, sizeof(tm));
    tm.tm_year = capture_time.m_year - 1900;
    tm.tm_mon = capture_time.m_month - 1;
    tm.tm_mday = capture_time.m_day;
    tm.tm_hour = capture_time.m_hour;
    tm.tm_min = capture_time.m_minute;
    tm.tm_sec = capture_time.m_second;
    double seconds = (double) timegm(&tm);

    int32 hundredths = 0;
    try {
      exif.query_by_tag(EXIF_SubSecTimeDigitized, hundredths);
    } catch (ExifErr &e) {}
    
    return seconds + hundredths / 100.0;
  } catch (ExifErr &e) {
    fprintf(stderr, "ExifErr: %s\n", e.what());
    // Would be nicer to return null here, but don't know how to do that
    return -1.0;
  }
}
