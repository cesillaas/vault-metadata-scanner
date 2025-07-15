#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <chrono>
#include <thread>

#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define RESET   "\033[0m"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void log(std::string tag, std::string message, std::string color = "") {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string time = std::ctime(&now);
    time.pop_back(); 
    std::cout << color << "[" << tag << " - " << time << "] " << message << RESET << std::endl;
}

void scan_vaults(int start_id, int end_id) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        log("ERROR", "Curl init failed", RED);
        return;
    }

    for (int id = start_id; id <= end_id; ++id) {
        std::ostringstream url_stream;
        url_stream << "https://start.1password.com/api/v1/vaults/" << id << "/items";
        std::string url = url_stream.str();

        readBuffer.clear();  // Yeni istek için temizle
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "User-Agent: VaultScanner/1.0");
        headers = curl_slist_append(headers, "Accept: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (res != CURLE_OK) {
            log("ERROR", "Curl failed: " + std::string(curl_easy_strerror(res)), RED);
        } else if (http_code == 200) {
            log("FOUND", "Vault ID " + std::to_string(id) + " returned 200 ✅", GREEN);
            std::cout << "→ Response (first 300 chars):\n"
                      << readBuffer.substr(0, 300) << "\n\n";
        } else if (http_code == 403) {
            log("BLOCKED", "Vault ID " + std::to_string(id) + " → Forbidden", YELLOW);
        } else if (http_code == 404) {
            log("MISS", "Vault ID " + std::to_string(id) + " not found", RESET);
        } else if (http_code == 429) {
            log("RATE", "Rate limited at ID " + std::to_string(id) + " — sleeping", RED);
            std::this_thread::sleep_for(std::chrono::seconds(10));
        } else {
            log("?", "Unexpected code " + std::to_string(http_code) + " at " + std::to_string(id), YELLOW);
        }

        curl_slist_free_all(headers);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

int main() {
    int start = 1000;
    int end = 1020;

    log("INIT", "Vault metadata scanner starting...");
    scan_vaults(start, end);
    log("DONE", "Scanning complete.");

    return 0;
}
