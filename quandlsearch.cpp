#include "quandlsearch.h"

QuandlSearch::QuandlSearch(QLineEdit* _searchKeywords, QTreeWidget* _listWidget) : QDialog()
{
    searchKeywords = _searchKeywords;
    listWidget = _listWidget;
}

//Sert a extraire les données renvoyer par l'appel à libcurl
QString getResp;
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        getResp.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}


void QuandlSearch::searchResponse()
{
    listWidget->clear();

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        std::string url = std::string("https://www.quandl.com/api/v3/datasets.json?api_key=kuExaMxAa629HY7dRvgH&"
                                      "database_code=WIKI&per_page=5&page=1&query=")
                                        + std::string(searchKeywords->text().toUtf8().constData());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    //On remplit la liste des résultats affichés
    QJsonDocument doc = QJsonDocument::fromJson(getResp.toUtf8());
    QJsonArray jsonArray = doc.object()["datasets"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QList<QString> list;
        list << obj["name"].toString() << obj["dataset_code"].toString() << obj["oldest_available_date"].toString() << obj["newest_available_date"].toString();
        listWidget->addTopLevelItem(new QTreeWidgetItem(list));
    }
    getResp = "";

}

QString QuandlSearch::downloadDataset(const QString start_date, const QString end_date, const QString dir)
{
    if(dir != ""){
        if(listWidget->currentItem() != NULL){
            QString dataset_code = (*(listWidget->currentItem())).text(1);
            CURL *curl;
            curl = curl_easy_init();
            if(curl) {
                std::string url = std::string("https://www.quandl.com/api/v3/datasets/WIKI/")
                                              + std::string(dataset_code.toUtf8().constData())
                                              + std::string(".csv?api_key=kuExaMxAa629HY7dRvgH&start_date=")
                                              + std::string(start_date.toUtf8().constData())
                                              + std::string("&end_date=")
                                              + std::string(end_date.toUtf8().constData());

                FILE *fp;
                CURLcode res;
                std::string filename = dir.toStdString() + "/"
                                                         + dataset_code.toStdString()
                                                         + start_date.toStdString()
                                                         + "_"
                                                         + end_date.toStdString()
                                                         + ".csv";
                curl = curl_easy_init();
                if (curl)
                {
                    fp = fopen(filename.c_str(),"wb");
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                    res = curl_easy_perform(curl);
                    curl_easy_cleanup(curl);
                    fclose(fp);
                    std::string message = "The download is finished. The data is available in" + filename;
                    QMessageBox::information(this, "Data", message.c_str());
                    return QString::fromStdString(filename);
                }
            }
        }
    }
    return "";
}


QuandlSearch::~QuandlSearch()
{
    delete listWidget;
}
