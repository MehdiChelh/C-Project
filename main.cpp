#include <QApplication>
#include <QPushButton>
#include "window.h"
#include <curl/curl.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);





    Window win;
    win.show();

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    return app.exec();
}
